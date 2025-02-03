from typing import\
    Any
from pydantic.fields import\
    FieldInfo
import base_types.cpp.module.wrapper as bw
import functools
from pydantic import\
    create_model,\
    BaseModel
from ..constraint import \
    LogicOperand,\
    Operand,\
    literal,\
    OperandDefinitionContext
from abc import\
    abstractmethod
from pydantic_core import\
    core_schema
from pydantic import\
    GetCoreSchemaHandler
from .builtin import\
    Undefined


__all__ = ['compound']


def _tuple_to_dict(
    tup: tuple[Any, ...], field_names: tuple[str, ...]
) -> dict[str, Any]:
    return {name: tup[ix] for name, ix in zip(field_names, range(0, len(tup)))}


class _CompoundPydanticAdapt:
    def __init__(self, tp) -> None:
        self._tp = tp

    @property
    @functools.cache
    def model(self) -> BaseModel:
        members = {}
        for base in self._tp._cpp_bases:
            for name, info in base.get_py_cls(base.__name__).model_fields.items():
                members[name] = (info.annotation, info.default, )
        for ix in range(0, len(self._tp._cpp_field_names)):
            field_name: str = self._tp._cpp_field_names[ix]
            field_type: str = self._tp._cpp_field_types[ix]
            members[field_name] = (field_type.get_py_cls(field_type.__name__), Undefined, )
        model: BaseModel = create_model(
            f'{self._tp.__name__}_Model', **members
        )
        for base in self._tp._cpp_bases:
            for name, info in base.get_py_cls(base.__name__).model_fields.items():
                model.model_fields[name].metadata += info.metadata
                if hasattr(info, 'default_factory'):
                    model.model_fields[name].default_factory = info.default_factory
        model.model_rebuild(force=True)
        return model

    def attempt_to_create_instance(
        self, value: Any, info: core_schema.ValidationInfo
    ):
        if isinstance(value, self._tp):
            return value
        if isinstance(value, tuple):
            value = _tuple_to_dict(value)
        return self._tp(**value)


class compound(type(bw.base)):
    class set_default:
        def __init__(
            self, *, value: Operand, field: str
        ) -> None:
            if not isinstance(value, literal):
                self._default = literal(value)
            else:
                self._default = value
            self._field = field

        def __call__(self, target: type):
            assert isinstance(target, compound)
            assert self._field in target.model_fields
            info: FieldInfo = target.model_fields[self._field]
            self._default.propagate_definition(
                info.annotation, self._field, target.definition_context()
            )
            # cant have default_factory and default set at the same time
            info.default_factory = lambda value: info.annotation(self._default.value(value))
            info.default = Undefined
            target._pydantic_adapt.model.model_rebuild(force=True)
            return target

    class set_constraint:
        def __init__(
            self, *, constraint: LogicOperand, field: str
        ) -> None:
            self._constraint = constraint
            self._field = field

        def __call__(self, target: type):
            assert isinstance(target, compound)
            assert self._field in target.model_fields
            info: FieldInfo = target.model_fields[self._field]
            self._constraint.propagate_definition(
                info.annotation, self._field, target.definition_context()
            )
            info.metadata.append(self._constraint)
            target._pydantic_adapt.model.model_rebuild(force=True)
            return target

    def __new__(
        cls, clsname, clsbases, namespace
    ) -> type:
        if len(clsbases) != 1:
            raise TypeError(f'compound type {cls} only allows one base class')

        if len(namespace) > 2:
            raise TypeError(f'Class {cls} doesnt allow member declarations')

        def __init__(self, *args: Any, **data: dict[str, Any]) -> None:
            if len(args) > 0 and len(data) > 0:
                raise ValueError(f'Can instance {self.__class__.__name__} with position parameters or named parameters, not both.')
            if len(args) > 0:
                data = _tuple_to_dict(args, self.__class__._cpp_field_names)
            data = self.__class__._pydantic_adapt.model.__pydantic_validator__.validate_python(
                data, self_instance=self
            )
            clsbases[0].__init__(
                self, *tuple([getattr(data, name) for name in self.__class__._cpp_field_names])
            )

        def __repr__(self) -> str:
            return f'{self.__class__.__name__}({", ".join([f"{name}={repr(getattr(self, name))}" for name in self.__class__.model_fields])})'

        rettype: type = super().__new__(
            cls, clsname, clsbases, namespace | {
                '__init__': __init__, '__repr__': __repr__
            })
        rettype.set_py_cls(clsname, rettype)
        return rettype

    @property
    @functools.cache
    def _pydantic_adapt(self) -> _CompoundPydanticAdapt:
        return _CompoundPydanticAdapt(self)

    @property
    def model_fields(self) -> dict[str, FieldInfo]:
        return self._pydantic_adapt.model.model_fields

    def __get_pydantic_core_schema__(
        self, source: type, handler: GetCoreSchemaHandler
    ) -> core_schema.CoreSchema:
        return core_schema.with_info_plain_validator_function(
            function=self._pydantic_adapt.attempt_to_create_instance)

    @abstractmethod
    def definition_context(self) -> type[OperandDefinitionContext]:
        pass

