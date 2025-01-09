from typing import\
    Any
import base_types.cpp.wrapper as bw
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler


__all__ = ['enum']


class enum(type(bw.base)):
    def __new__(
        cls, clsname: str, clsbases: tuple[type], clsdict: dict[str, Any]
    ) -> type:
        if len(clsbases) > 1:
            raise TypeError(f'enum {cls} doesnt allow multiple bases')
        rettype: type = super().__new__(
            cls, clsname, clsbases, clsdict
        )
        return rettype

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.enum_schema(self, list(self.__members__.values()))
