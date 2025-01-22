from typing import\
    Any
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


__all__ = ['enum']


class enum(type(bw.base)):
    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any],
        default: DefaultAlias = Undefined
    ):
        if len(clsbases) > 1:
            raise TypeError(f'enum {cls} doesnt allow multiple bases')

        @classmethod
        def __default__(cls) -> DefaultAlias:
            return default

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {'__default__': __default__}
        )
        if isinstance(default, literal):
            default.propagate_definition(clsbases[0], '', rettype.definition_context())
        return rettype

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.enum_schema(self, list(self.__members__.values()))

    def definition_context(self) -> type[OperandDefinitionContext]:
        return OperandDefinitionContext
