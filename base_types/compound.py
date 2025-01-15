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
    check,\
    Operand,\
    OperandDefinitionContext
import copy
from abc import\
    abstractmethod
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
import copy


def configure_default(
    name: str, info: FieldInfo, tp: type, definition_context: OperandDefinitionContext
) -> None:
    if isinstance(info.default, Operand):
        info.default.propagate_definition(tp, name, definition_context)
        # cant have default_factory and default set at the same time
        default_factory = copy.deepcopy(info.default.value)
        info.default_factory = lambda value: tp(default_factory(value))
        info.default = pydantic_core._pydantic_core.PydanticUndefined
    elif info.default != pydantic_core._pydantic_core.PydanticUndefined:
        info.default = tp(info.default) if info.default is not None and not isinstance(info.default, tp) else None


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
                data = self.__class__.tuple_to_dict(args)
            data = self.__class__.model.__pydantic_validator__.validate_python(data, self_instance=self)
            clsbases[0].__init__(self, *tuple([getattr(data, name) for name in self.__class__.model_fields]))

        def __repr__(self) -> str:
            return f'{self.__class__.__name__}({", ".join([f"{name}={repr(getattr(self, name))}" for name in self.__class__.model_fields])})'

        # def __setattr__(self, name: str, value: Any) -> None:
            # raise NotImplementedError

        rettype: type = super().__new__(
            cls, clsname, clsbases, namespace | {
                '__init__': __init__,
                '__repr__': __repr__,
                # '__setattr__': __setattr__
            })
        clsbases[0].set_py_cls(rettype)
        rettype._configure_defaults()
        return rettype

    def tuple_to_dict(self, tup: tuple[Any, ...]) -> dict[str, Any]:
        return {name: tup[ix] for name, ix in zip(self.model_fields.keys(), range(0, len(tup)))}

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
                configure_default(name, info, tp, self.definition_context())
            elif hasattr(tp, '__default__'):
                info.default = getattr(tp, '__default__')()
                configure_default(name, info, tp, self.definition_context())
            for meta in info.metadata:
                if isinstance(meta, check):
                    meta.predicate.propagate_definition(tp, name, self.definition_context())
        self.model.model_rebuild(force=True)

    @abstractmethod
    def definition_context(self) -> OperandDefinitionContext:
        pass

    def __attempt_to_create_instance__(self, value: Any, info: core_schema.ValidationInfo):
        if isinstance(value, self):
            return value
        if isinstance(value, tuple):
            value = self.tuple_to_dict(value)
        return self(**value)

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.with_info_plain_validator_function(
            function=self.__attempt_to_create_instance__)


class inherits:
    def __init__(
        self, *bases: Any
    ) -> None:
        for base in bases:
            assert isinstance(base, compound)
        self.bases = bases

    def _check_consistent_base_class_fields(self, target: type):
        model_fields: dict[str, FieldInfo] = target.model_fields
        errors: list[str] = []
        for base in self.bases:
            for name, info in base.model_fields.items():
                if name not in model_fields:
                    errors.append(f'Field {name} from base {base.__name__} must be present in {target.__name__} definition')
                    continue
                if model_fields[name].annotation != info.annotation:
                    errors.append(f'Field {name} must be of same type as {base.__name__}.{name} in {target.__name__} definition')
        if len(errors) > 0:
            raise TypeError(f'Base class errors:\n{"\n".join(errors)}')

    def _inherit_metadata_from_bases(self, target: type) -> None:
        model_fields: dict[str, FieldInfo] = target.model_fields
        errors: list[str] = []
        for base in self.bases:
            for name, info in base.model_fields.items():
                tf_info = model_fields[name]
                tf_info.metadata += info.metadata
                tp = info.annotation
                if info.is_required() and tf_info.is_required():
                    continue
                elif info.is_required() and not tf_info.is_required():
                    # parent defines default, child doesnt, pass
                    pass
                elif not info.is_required() and not tf_info.is_required():
                    # each one is required
                    pass
                else:
                    # parent defines default, child doesnt, inherit parents
                    if isinstance(info.default, Operand):
                        # cant have default_factory and default set at the same time
                        default_factory = copy.deepcopy(info.default.value)
                        tf_info.default_factory = lambda value: tp(default_factory(value))
                        tf_info.default = pydantic_core._pydantic_core.PydanticUndefined
                    else:
                        model_fields[name].default = info.default
        if len(errors) > 0:
            raise TypeError(f'Base class errors:\n{"\n".join(errors)}')
        target.model.model_rebuild(force=True)

    def __call__(self, target: type):
        assert isinstance(target, compound)
        self._check_consistent_base_class_fields(target)
        self._inherit_metadata_from_bases(target)
        return target

