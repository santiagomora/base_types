from typing import\
    Any,\
    Optional,\
    Union,\
    TypeAlias
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
from base_types.cpp.module.wrapper import pybind_base
from ..constraint import\
    LogicOperand,\
    literal,\
    OperandDefinitionContext
import pydantic_core
from abc import\
    abstractmethod
import functools


__all__ = ['builtin', 'Undefined']


Undefined = pydantic_core._pydantic_core.PydanticUndefined
DefaultAlias: TypeAlias = Union[literal, Undefined, None]


class _BuiltinPydanticAdapt:
    def __init__(self, tp: type) -> None:
        self._constraint: Optional[LogicOperand] = None
        self._default: DefaultAlias = Undefined
        self._tp = tp

    @property
    def default(self):
        return self._default

    @default.setter
    def default(self, default: literal):
        if isinstance(default, literal):
            default.propagate_definition(self._tp.__bases__[0], '', self._tp.definition_context())
        elif default is None or default is Undefined:
            raise TypeError('Invalid default value')
        self._default = default

    @property
    def constraint(self):
        return self._constraint

    @constraint.setter
    def constraint(self, constraint: LogicOperand):
        if isinstance(constraint, LogicOperand):
            constraint.source = self._tp
            constraint.propagate_definition(self._tp.__bases__[0], '', self._tp.definition_context())
        elif constraint is None:
            raise TypeError('Invalid check predicate')
        self._constraint = constraint

    def validate_instance(self, instance):
        if self._constraint is not None:
            instance = self._constraint._validate(instance)
        return instance

    def attempt_to_create_instance(
        self, value: Any, validation_info: Any
    ):
        if value is None:
            default_value: Optional[literal] = self._default
            return value if default_value is Undefined or default_value is None else default_value
        return value if isinstance(value, self._tp) else self._tp(value)


class builtin(type(pybind_base)):
    class set_default:
        def __init__(
            self, value: literal
        ) -> None:
            if not isinstance(value, literal):
                value = literal(value)
            self._default = value

        def __call__(self, target: type) -> type:
            assert isinstance(target, builtin)
            assert target._pydantic_adapt.default is Undefined
            target._pydantic_adapt.default = self._default
            return target

    class set_constraint:
        def __init__(
            self, constraint: LogicOperand
        ) -> None:
            self._constraint = constraint

        def __call__(self, target: type) -> type:
            assert isinstance(target, builtin)
            assert target._pydantic_adapt.constraint is None
            target._pydantic_adapt.constraint = self._constraint
            return target

    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any]
    ) -> type:

        if len(clsbases) > 1:
            raise TypeError(f'Class {cls} doesnt allow multiple bases')

        if len(clsdict) > 2:
            raise TypeError(f'Class {cls} doesnt allow member declarations')

        # def __repr__(self):
        #     return f'{self.__class__.__name__}({str(self)})'

        def __init__(self, *args: Any):
            value = clsbases[0](*args)
            clsbases[0].__init__(self, rettype._pydantic_adapt.validate_instance(value))

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {
                # '__repr__': __repr__,
                '__init__': __init__
            })
        rettype.set_py_cls(rettype.qualified_name, rettype)
        return rettype

    @property
    @functools.cache
    def _pydantic_adapt(self) -> _BuiltinPydanticAdapt:
        return _BuiltinPydanticAdapt(self)

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.with_info_plain_validator_function(
            function=self._pydantic_adapt.attempt_to_create_instance)

    @abstractmethod
    def definition_context(self) -> type[OperandDefinitionContext]:
        pass

