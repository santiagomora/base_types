from typing import\
    Any,\
    Optional
import base_types.cpp.wrapper as bw
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
from .builtin import\
    DefaultAlias,\
    Undefined
from .predicate import\
    literal,\
    OperandDefinitionContext
import functools


__all__ = ['enum']


class _EnumPydanticAdapt:
    def __init__(self, tp: type) -> None:
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

    def attempt_to_create_instance(
        self, value: Any, validation_info: Any
    ):
        if value is None:
            default_value: Optional[literal] = self._default
            return value if default_value is Undefined or default_value is None else default_value
        return value if isinstance(value, self._tp) else self._tp(value)


class enum(type(bw.base)):
    class set_default:
        def __init__(
            self, value: literal
        ) -> None:
            self._default = value

        def __call__(self, target: type):
            assert isinstance(target, enum)
            assert target.pydantic_adapt.default is Undefined
            target.pydantic_adapt.default = self._default
            return target

    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any]
    ):
        if len(clsbases) > 1:
            raise TypeError(f'enum {cls} doesnt allow multiple bases')
        rettype: type = super().__new__(cls, clsname, clsbases, clsdict)
        clsbases[0].set_py_cls(rettype)
        return rettype

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.chain_schema([
            core_schema.enum_schema(self, list(self.enum.__members__.values())),
            core_schema.with_info_plain_validator_function(function=self.pydantic_adapt.attempt_to_create_instance)
        ])

    @property
    @functools.cache
    def pydantic_adapt(self) -> _EnumPydanticAdapt:
        return _EnumPydanticAdapt(self)

    def definition_context(self) -> type[OperandDefinitionContext]:
        return OperandDefinitionContext
