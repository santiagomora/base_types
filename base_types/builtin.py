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


__all__ = ['builtin']


Undefined = pydantic_core._pydantic_core.PydanticUndefined
DefaultAlias: TypeAlias = Any
# DefaultAlias: TypeAlias = Union[literal, Undefined, None]


class builtin(type(bw.base)):
    def __new__(
        cls, clsname: str, clsbases: tuple[type],
        clsdict: dict[str, Any], *,
        check_predicate: Optional[LogicOperand] = None,
        default: DefaultAlias = Undefined
    ) -> type:

        if len(clsbases) > 1:
            raise TypeError(f'Class {cls} doesnt allow multiple bases')

        # def __repr__(self):
        #     return f'{self.__class__.__name__}({str(self)})'

        def __init__(self, *args: Any):
            value = clsbases[0](*args)
            if hasattr(rettype, '__validate_instance__'):
                value = rettype.__validate_instance__(value)
            clsbases[0].__init__(self, value)

        @classmethod
        def __check_predicate__(cls) -> Optional[LogicOperand]:
            return check_predicate

        @classmethod
        def __default__(cls) -> DefaultAlias:
            return default

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {
                # '__repr__': __repr__,
                '__init__': __init__,
                '__check_predicate__': __check_predicate__, '__default__': __default__
            })
        clsbases[0].set_py_cls(rettype)
        if isinstance(check_predicate, LogicOperand):
            check_predicate.source = rettype
            check_predicate.propagate_definition(clsbases[0], '', rettype.definition_context())
        elif check_predicate is None:
            pass
        else:
            raise TypeError('Invalid check predicate')
        if isinstance(default, literal):
            default.propagate_definition(clsbases[0], '', rettype.definition_context())
        elif default is None or default is Undefined:
            pass
        else:
            raise TypeError('Invalid default value')
        return rettype

    def __validate_instance__(self, instance):
        ck: Optional[LogicOperand] = getattr(self, '__check_predicate__')()
        if ck is not None:
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

    @abstractmethod
    def definition_context(self) -> type[OperandDefinitionContext]:
        pass
