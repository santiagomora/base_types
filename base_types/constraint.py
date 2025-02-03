from __future__ import\
    annotations
from abc import\
    ABC,\
    abstractclassmethod,\
    abstractmethod
from typing import\
    Any,\
    Type,\
    TypeVar,\
    Union,\
    Optional,\
    Generic,\
    Callable,\
    Sized
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler,\
    ValidationInfo
from pydantic import\
    BaseModel
from functools import\
    reduce
from typing_extensions import\
    Self
from enum import \
    Enum,\
    auto


__all__ = ['literal', 'this', 'field', 'Operand', 'LogicOperand', 'length', 'OperandDefinitionContext']


class OperandDefinitionContext:
    @abstractclassmethod
    def parse_field(cls, field_instance: field) -> str:
        pass

    @abstractclassmethod
    def parse_this(cls, this_instance: this) -> str:
        pass

    @classmethod
    def parse_literal(cls, literal_instance: literal) -> str:
        return f'{literal_instance._lit if literal_instance._lit is not None else literal_instance._args[0]}'


# TODO this whole module will eventually be cythonized
T = TypeVar('T')


class Operand(Generic[T]):
    @abstractmethod
    def merge(self, operation_cls: type[T], other: Operand[T]) -> Operand[T]:
        pass

    @abstractmethod
    def __str__(self) -> str:
        pass

    @abstractmethod
    def __repr__(self) -> str:
        pass

    @abstractmethod
    def value(self, info: dict[str, Any]) -> T:
        pass

    @abstractmethod
    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        pass


class LogicOperand(Operand[bool]):
    def __init__(self) -> None:
        self.source = None
        self.field_name = ''
        self.name = None
        self.parent = None

    def merge(
        self, operation_cls: type, other: LogicOperand[bool]
    ) -> LogicOperand[bool]:
        return operation_cls(self, other)

    def __and__(self, other: LogicOperand) -> LogicOperand:
        return self.merge(_and, other)

    def __or__(self, other: LogicOperand) -> LogicOperand:
        return self.merge(_or, other)

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        self.source = source
        self.field_name = handler.field_name
        return core_schema.with_info_after_validator_function(
            function=self.validate_value,
            schema=handler(source),
            field_name=self.field_name)

    def _validate(
        self, value: Any, info_data: Optional[ValidationInfo] = None
    ) -> Any:
        data = {self.field_name: value} if info_data is None else info_data
        if self.field_name not in data:
            info_data[self.field_name] = value
        if not self.value(data):
            raise ValueError(f'constraint validation failed for value "{value}"')
        return value

    def validate_value(
        self, value: Any, info: ValidationInfo
    ) -> Any:
        # if self.field_name not in info.data:
        #     return getattr(self._source, '__default__')()
        return self._validate(value, info.data)


class ArithmeticOperand(Operand[Any]):
    def merge(self, operation_cls: type, other: Operand[Any]) -> Operand[Any]:
        other.apply_parentheses_as_righthand_operand(operation_cls)
        self.apply_parentheses_as_lefthand_operand(operation_cls)
        return self.merge_in_operation(operation_cls, other)

    def apply_parentheses_as_righthand_operand(self, operation_cls: type) -> None:
        pass

    def apply_parentheses_as_lefthand_operand(self, operation_cls: type) -> None:
        pass

    def merge_in_operation(self, operation_cls: type, other: Operand[T]) -> Operand[T]:
        if operation_cls == self.__class__:
            self.append(other)
            return self
        else:
            return operation_cls(self, other)

    def __add__(self, other: ArithmeticOperand) -> ArithmeticOperand:
        return self.merge(_add, other)

    def __sub__(self, other: ArithmeticOperand) -> ArithmeticOperand:
        return self.merge(_sub, other)

    def __mul__(self, other: ArithmeticOperand) -> ArithmeticOperand:
        return self.merge(_mul, other)

    def __truediv__(self, other: ArithmeticOperand) -> ArithmeticOperand:
        return self.merge(_div, other)

    def __mod__(self, other: ArithmeticOperand) -> ArithmeticOperand:
        return self.merge(_mod, other)

    def __ge__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_ge, other)

    def __gt__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_gt, other)

    def __le__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_le, other)

    def __lt__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_lt, other)

    def __eq__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_eq, other)

    def __ne__(self, other: ArithmeticOperand) -> LogicOperand:
        return self.merge(_ne, other)


class ArithmeticOperation(ArithmeticOperand, list[ArithmeticOperand]):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand, opstr: str) -> None:
        super().__init__((operand1, operand2))
        self.opstr = opstr
        self.parentheses = False

    def __str__(self) -> str:
        as_str: str = f' {self.opstr} '.join([
            str(operand) for operand in self
        ])
        return f'({as_str})' if self.parentheses else as_str

    def __repr__(self) -> str:
        return f'{self.__class__.__name__}({", ".join([\
            repr(operand) for operand in self\
        ])})'

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        for operand in self:
            operand.propagate_definition(basecls, fieldname, context)
        return self

    @abstractmethod
    def value(self, info: dict[str, Any]) -> Any:
        pass


class LogicOperandSpec(LogicOperand):
    def __init__(
        self, operand1: ArithmeticOperand, operand2: ArithmeticOperand, opstr: str
    ) -> None:
        LogicOperand.__init__(self)
        self.operand1 = operand1
        self.operand2 = operand2
        self.opstr = opstr

    def __repr__(self):
        return f'{self.__class__.__name__}({repr(self.operand1)}, {repr(self.operand2)})'

    def __str__(self) -> str:
        op1str = str(self.operand1)
        op2str = str(self.operand2)
        if isinstance(self.operand1, ArithmeticOperation):
            op1str = f'({op1str})'
        if isinstance(self.operand2, ArithmeticOperation):
            op2str = f'({op2str})'
        return f'{op1str} {self.opstr} {op2str}'

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        self.operand1.propagate_definition(basecls, fieldname, context)
        self.operand2.propagate_definition(basecls, fieldname, context)
        return self


class LogicOperation(LogicOperand, list[LogicOperandSpec]):
    def __init__(
        self, operand1: LogicOperand, operand2: LogicOperand, opstr: str
    ) -> None:
        list.__init__(self, (operand1, operand2))
        LogicOperand.__init__(self)
        self.opstr = opstr

    def __str__(self) -> str:
        return f' {self.opstr} '.join([
            f'({str(operand)})' for operand in self
        ])

    def __repr__(self):
        return f'{self.__class__.__name__}({", ".join(repr(op) for op in self)})'

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        for op in self:
            op.propagate_definition(basecls, fieldname, context)
        return self


class this(ArithmeticOperand):
    def __init__(self) -> None:
        # el field debe ser un atributo de la clase que registra la anotacion
        self._fieldname: Optional[str] = None
        self._context = OperandDefinitionContext

    def __str__(self) -> str:
        return self._context.parse_this(self)

    def __repr__(self) -> str:
        if self._fieldname is not None:
            return f"this(fieldname={self._fieldname}, context={self._context})"
        else:
            return 'this()'

    def value(self, info: dict[str, Any]) -> Any:
        return info[self._fieldname]

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        self._fieldname = fieldname
        self._context = context
        return self


class field(ArithmeticOperand):
    def __init__(self, fieldname: str) -> None:
        # el field debe ser un atributo de la clase que registra la anotacion
        self._fieldname: str = fieldname
        self._context = OperandDefinitionContext

    def value(self, info: dict[str, Any]) -> Any:
        return info[self._fieldname]

    def __repr__(self):
        return f'field({self._fieldname})'

    def __str__(self) -> str:
        return self._context.parse_field(self)

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        self._context = context
        return self


class literal(ArithmeticOperand):
    def __init__(self, *args: Any, **kwargs: dict[str, Any]) -> None:
        self._args = args
        self._kwargs = kwargs
        self._lit = None
        self._context = OperandDefinitionContext

    def __str__(self):
        return self._context.parse_literal(self)

    def __repr__(self):
        return f'literal({repr(self._lit)})'

    def value(self, info: dict[str, Any]) -> Any:
        return self._args[0] if self._lit is None else self._lit

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        self._context = context
        if not isinstance(self._lit, basecls):
            self._lit = basecls(*self._args, **self._kwargs)
        return self


class length(ArithmeticOperand):
    def __init__(self, target: ArithmeticOperand) -> None:
        self.target = target

    def __str__(self):
        return f'length({str(self.target)})'

    def __repr__(self):
        return f'length({repr(self.target)})'

    def value(self, info: dict[str, Any]) -> Any:
        return len(self.target.value(info))

    def propagate_definition(
        self, basecls: type, fieldname: Optional[str],
        context: type[OperandDefinitionContext]
    ) -> Self:
        self.target.propagate_definition(basecls, fieldname, context)
        return self


class _add(ArithmeticOperation):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '+')

    def value(self, info: dict[str, Any]) -> Any:
        acc: Any = self[0].value(info)
        for y in self[1:]:
            acc += y.value(info)
        return acc

    def apply_parentheses_as_lefthand_operand(self, opcls: type) -> None:
        self.parentheses = opcls in (_div, _mul, _mod)

    def apply_parentheses_as_righthand_operand(self, opcls: type) -> None:
        self.parentheses = opcls in (_div, _mul, _mod, _sub)


class _sub(ArithmeticOperation):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '-')

    def value(self, info: dict[str, Any]) -> Any:
        return reduce(lambda x, y: x - y.value(info), self[1:], self[0].value(info))

    def apply_parentheses_as_lefthand_operand(self, opcls: type) -> None:
        self.parentheses = opcls in (_div, _mul, _mod)

    def apply_parentheses_as_righthand_operand(self, opcls: type) -> None:
        self.parentheses = opcls in (_div, _mul, _mod, _sub)


class _mul(ArithmeticOperation):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '*')

    def value(self, info: dict[str, Any]) -> Any:
        return reduce(lambda x, y: x * y.value(info), self[1:], self[0].value(info))

    def apply_parentheses_as_righthand_operand(self, opcls: type) -> None:
        self.parentheses = opcls in (_div, _mod)


class _div(ArithmeticOperation):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '/')

    def value(self, info: dict[str, Any]) -> Any:
        return reduce(lambda x, y: x / y.value(info), self[1:], self[0].value(info))

    def merge_in_operation(self, operation_cls: type,
                           other: ArithmeticOperand) -> Reference:
        return operation_cls(self, other)

    def apply_parentheses_as_righthand_operand(self, opcls: type) -> None:
        self.parentheses = True

    def apply_parentheses_as_lefthand_operand(self, opcls: type) -> None:
        self.parentheses = True


class _mod(ArithmeticOperation):
    def __init__(self, operand1: ArithmeticOperand,
                 operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '%')

    def value(self, info: dict[str, Any]) -> Any:
        return reduce(lambda x, y: x % y.value(info), self[1:], self[0].value(info))

    def merge_in_operation(self, operation_cls: type,
                           other: ArithmeticOperand) -> Reference:
        return operation_cls(self, other)

    def add_operand(self, operation_cls: type, other: Reference) -> Reference:
        return operation_cls(self, other)

    def apply_parentheses_as_righthand_operand(self, opcls: type) -> None:
        self.parentheses = True

    def apply_parentheses_as_lefthand_operand(self, opcls: type) -> None:
        self.parentheses = True


class _lt(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '<')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) < self.operand2.value(info)


class _gt(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '>')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) > self.operand2.value(info)


class _ge(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '>=')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) >= self.operand2.value(info)


class _le(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '<=')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) <= self.operand2.value(info)


# f'Check predicate types must be compatible "{source!r}"'
# f'Value "{value!r}" invalid for field "{info.fieldname}"'
class _eq(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '==')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) == self.operand2.value(info)


class _ne(LogicOperandSpec):
    def __init__(self, operand1: ArithmeticOperand, operand2: ArithmeticOperand) -> None:
        super().__init__(operand1, operand2, '!=')

    def value(self, info: dict[str, Any]) -> bool:
        return self.operand1.value(info) != self.operand2.value(info)


class _and(LogicOperation):
    def __init__(self, operand1: LogicOperand, operand2: LogicOperand) -> None:
        super().__init__(operand1, operand2, 'AND')

    def merge(self, operation_cls: type, other: Operand[bool]) -> Operand[bool]:
        if operation_cls == self.__class__:
            self.append(other)
            return self
        else:
            return operation_cls(self, other)

    def value(self, info: dict[str, Any]) -> bool:
        return reduce(lambda x, y: x and y.value(info), self[1:], self[0].value(info))


class _or(LogicOperation):
    def __init__(self, operand1: LogicOperand, operand2: LogicOperand) -> None:
        super().__init__(operand1, operand2, 'OR')

    def merge(self, operation_cls: type, other: Operand[bool]) -> Operand[bool]:
        if operation_cls == self.__class__:
            self.append(other)
            return self
        else:
            return operation_cls(self, other)

    def value(self, info: dict[str, Any]) -> bool:
        return reduce(lambda x, y: x or y.value(info), self[1:], self[0].value(info))

