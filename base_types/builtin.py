from typing import\
    Any,\
    Optional,\
    Union,\
    TypeAlias
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
import base_types.cpp.wrapper as bw
from .predicate import\
    LogicOperand,\
    literal,\
    OperandDefinitionContext
import pydantic_core
from abc import\
    abstractmethod
import functools


__all__ = ['builtin']


Undefined = pydantic_core._pydantic_core.PydanticUndefined
DefaultAlias: TypeAlias = Union[literal, Undefined, None]


class _BuiltinPydanticAdapt:
    def __init__(self, tp: type) -> None:
        self._check_predicate: Optional[LogicOperand] = None
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
    def check_predicate(self):
        return self._check_predicate

    @check_predicate.setter
    def check_predicate(self, check_predicate: LogicOperand):
        if isinstance(check_predicate, LogicOperand):
            check_predicate.source = self._tp
            check_predicate.propagate_definition(self._tp.__bases__[0], '', self._tp.definition_context())
        elif check_predicate is None:
            raise TypeError('Invalid check predicate')
        self._check_predicate = check_predicate

    def validate_instance(self, instance):
        if self._check_predicate is not None:
            instance = self._check_predicate._validate(instance)
        return instance

    def attempt_to_create_instance(
        self, value: Any, validation_info: Any
    ):
        if value is None:
            default_value: Optional[literal] = self._default
            return value if default_value is Undefined or default_value is None else default_value
        return value if isinstance(value, self._tp) else self._tp(value)


class builtin(type(bw.base)):
    class set_default:
        def __init__(
            self, value: literal
        ) -> None:
            self.default = value

        def __call__(self, target: type):
            assert isinstance(target, builtin)
            assert target.pydantic_adapt.default is Undefined
            target.pydantic_adapt.default = self.default
            return target

    class set_check_predicate:
        def __init__(
            self, predicate: LogicOperand
        ) -> None:
            self.check_predicate = predicate

        def __call__(self, target: type):
            assert isinstance(target, builtin)
            print(target.pydantic_adapt.check_predicate)
            assert target.pydantic_adapt.check_predicate is None
            target.pydantic_adapt.check_predicate = self.check_predicate
            return target

    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any]
    ) -> type:

        if len(clsbases) > 1:
            raise TypeError(f'Class {cls} doesnt allow multiple bases')

        # def __repr__(self):
        #     return f'{self.__class__.__name__}({str(self)})'

        def __init__(self, *args: Any):
            value = clsbases[0](*args)
            clsbases[0].__init__(self, rettype.pydantic_adapt.validate_instance(value))

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {
                # '__repr__': __repr__,
                '__init__': __init__
            })
        clsbases[0].set_py_cls(rettype)
        return rettype

    @property
    @functools.cache
    def pydantic_adapt(self) -> _BuiltinPydanticAdapt:
        return _BuiltinPydanticAdapt(self)

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.with_info_plain_validator_function(
            function=self.pydantic_adapt.attempt_to_create_instance)

    @abstractmethod
    def definition_context(self) -> type[OperandDefinitionContext]:
        pass

