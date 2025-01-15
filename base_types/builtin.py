from typing import\
    Any,\
    Optional,\
    Union
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
import base_types.cpp.wrapper as bw
from .check import\
    check,\
    literal,\
    OperandDefinitionContext
import pydantic_core


__all__ = ['builtin']


class builtin(type(bw.base)):
    def __new__(
        cls, clsname: str, clsbases: tuple[type],
        clsdict: dict[str, Any], *,
        validator: Union[check, pydantic_core._pydantic_core.PydanticUndefined] = pydantic_core._pydantic_core.PydanticUndefined,
        default: Union[literal, pydantic_core._pydantic_core.PydanticUndefined, None] = pydantic_core._pydantic_core.PydanticUndefined
    ) -> type:

        if len(clsbases) > 1:
            raise TypeError(f'Class {cls} doesnt allow multiple bases')

        def __repr__(self):
            return f'{self.__class__.__name__}({str(self)})'

        def __init__(self, *args: Any):
            value = clsbases[0](*args)
            if hasattr(rettype, '__validate_instance__'):
                value = rettype.__validate_instance__(value)
            clsbases[0].__init__(self, value)

        @classmethod
        def __validator__(cls) -> Optional[check]:
            return validator

        @classmethod
        def __default__(cls) -> Optional[literal]:
            return default

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {
                '__repr__': __repr__, '__init__': __init__,
                '__validator__': __validator__, '__default__': __default__
            })
        clsbases[0].set_py_cls(rettype)
        if isinstance(validator, check):
            validator.predicate.propagate_definition(clsbases[0], '', OperandDefinitionContext.BUILTIN_DOMAIN)
        if isinstance(default, literal):
            default.propagate_definition(clsbases[0], '', OperandDefinitionContext.BUILTIN_DOMAIN)
        return rettype

    def __validate_instance__(self, instance):
        ck: Optional[check] = getattr(self, '__validator__')()
        if ck != pydantic_core._pydantic_core.PydanticUndefined:
            instance = ck._validate(instance)
        return instance

    def __attempt_to_create_instance__(self, value, validation_info):
        if value is None:
            default_value: Optional[literal] = getattr(self, '__default__')()
            return value if default_value is None else default_value
        return value if isinstance(value, self) else self(value)

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.with_info_plain_validator_function(
            function=self.__attempt_to_create_instance__)


# class check:
#     def __init__(self, name: str,  predicate: LogicOperand) -> None:
#         self.check_meta: meta.check = meta.check(name=name, predicate=predicate)
# 
#     def __call__(self, target: type):
#         definition = getattr(target, '__btp_definition')()
#         assert definition['check'] is None
#         self.check_meta.predicate.propagate_definition(target, None, OperandDefinitionContext.BUILTIN_DOMAIN)
#         definition['check'] = self.check_meta
#         return target
# 
# 
# def default_value(*args, **kwargs):
# 
#     def _add_to_definition(target: type):
#         # esto va a cambiar, no se deberia poder acceder a la definicion directamente
#         # __btp_definition deberia devolver una copia siempre
#         # no puede usarse con table o composite
#         assert hasattr(target.__bases__[0], '__btp_definition')
#         definition = getattr(target, '__btp_definition')()
#         assert definition['default'] is None
#         value: literal = literal(*args, **kwargs)
#         value.propagate_definition(target, None, OperandDefinitionContext.BUILTIN_DOMAIN)
#         definition['default'] = value
#         return target
# 
#     return _add_to_definition
