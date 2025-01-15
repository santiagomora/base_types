from typing import\
    Any,\
    Optional,\
    Union
import base_types.cpp.wrapper as bw
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
from .check import\
    literal
import pydantic_core


__all__ = ['enum']


class enum(type(bw.base)):
    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any],
        default: Union[literal, pydantic_core._pydantic_core.PydanticUndefined, None] = pydantic_core._pydantic_core.PydanticUndefined
    ):
        if len(clsbases) > 1:
            raise TypeError(f'enum {cls} doesnt allow multiple bases')

        @classmethod
        def __default__(cls) -> Optional[literal]:
            return default

        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict | {'__default__': __default__}
        )
        return rettype

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.enum_schema(self, list(self.__members__.values()))
