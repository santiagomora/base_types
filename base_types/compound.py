from typing import\
    Any
from pydantic.fields import\
    FieldInfo
import pydantic_core
import base_types.cpp.wrapper as bw
import functools
from pydantic import\
    create_model,\
    BaseModel
from .check import \
    Operand,\
    OperandDefinitionContext
import copy
from abc import\
    abstractmethod
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler


class compound(type(bw.base)):
    def __new__(
        cls, clsname, clsbases, namespace
    ) -> type:
        if len(clsbases) > 1:
            raise TypeError(f'compound type {cls} doesnt allow multiple bases')

        def __init__(self, *args: Any, **data: dict[str, Any]) -> None:
            if len(args) > 0 and len(data) > 0:
                raise ValueError(f'Can instance {self.__class__.__name__} with position parameters or named parameters, not both.')
            if len(args) > 0:
                data = {name: args[ix] for name, ix in zip(self.__class__.model_fields.keys(), range(0, len(args)))}
            data = self.__class__.model.__pydantic_validator__.validate_python(data, self_instance=self)
            clsbases[0].__init__(self, *tuple([getattr(data, name) for name in self.__class__.model_fields]))

        def __repr__(self) -> str:
            return f'{self.__class__.__name__}({", ".join([f"{name}={repr(getattr(self, name))}" for name in self.__class__.model_fields])})'

        def __setattr__(self, name: str, value: Any) -> None:
            raise NotImplementedError

        rettype: type = super().__new__(
            cls, clsname, clsbases, namespace | {
                '__init__': __init__,
                '__repr__': __repr__,
                '__setattr__': __setattr__
            })
        clsbases[0].set_py_cls(rettype)
        rettype._configure_defaults()
        return rettype

    @property
    @functools.cache
    def model(self) -> BaseModel:
        members = self.__annotations__
        return create_model(
            f'{self.__name__}_Model',
            **{memb: (members[memb], getattr(self, memb, pydantic_core._pydantic_core.PydanticUndefined), ) for memb in members}
        )

    @property
    def model_fields(self) -> dict[str, FieldInfo]:
        return self.model.model_fields

    def _configure_defaults(self) -> None:
        for name, info in self.model_fields.items():
            tp: type = info.annotation
            if not info.is_required():
                if isinstance(info.default, Operand):
                    info.default.propagate_definition(tp, name, self.definition_context())
                    # cant have default_factory and default set at the same time
                    default_factory = copy.deepcopy(info.default.value)
                    info.default_factory = lambda value: tp(default_factory(value))
                    info.default = pydantic_core._pydantic_core.PydanticUndefined
                else:
                    info.default = tp(info.default) if info.default is not None and not isinstance(info.default, tp) else None
        self.model.model_rebuild(force=True)

    @abstractmethod
    def definition_context(self) -> OperandDefinitionContext:
        pass

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return handler(source.model)
