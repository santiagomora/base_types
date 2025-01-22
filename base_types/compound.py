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
from .predicate import \
    LogicOperand,\
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
from .builtin import\
    Undefined
from enum import\
    Enum,\
    auto
from .util.inspection import\
    extract_by_instance_type_from_field_info


def configure_default(
    name: str, info: FieldInfo, tp: type, definition_context: OperandDefinitionContext,
    propagate_definition: bool = True
) -> None:
    if isinstance(info.default, Operand):
        if propagate_definition:
            info.default.propagate_definition(tp, name, definition_context)
        # cant have default_factory and default set at the same time
        default_factory = copy.deepcopy(info.default.value)
        info.default_factory = lambda value: tp(default_factory(value))
        info.default = Undefined
    elif info.default != Undefined:
        if isinstance(info.default, tp) or info.default is None:
            return
        info.default = tp(info.default)


class InheritancePolicy(Enum):
    DISALLOW = auto()
    MERGE_PARENT_FIELDS = auto()
    FORCE_REDECLARATION = auto()


def _tuple_to_dict(
    tup: tuple[Any, ...], model_fields: dict[str, FieldInfo]
) -> dict[str, Any]:
    return {name: tup[ix] for name, ix in zip(model_fields.keys(), range(0, len(tup)))}


def _check_py_fields_compatible_with_cpp_fields(
    _cpp_field_names: tuple[str, ...], _cpp_field_types: tuple[type, ...], model_fields: dict[str, FieldInfo]
) -> None:
    field_names_tuple: tuple[str] = tuple(model_fields.keys())
    if len(_cpp_field_names) != len(field_names_tuple):
        raise TypeError('class must define same fields as those declared in cpp type')
    errors = []
    for ix in range(0, len(_cpp_field_names)):
        if _cpp_field_names[ix] != field_names_tuple[ix]:
            errors.append(f'field {_cpp_field_names[ix]} must be at position {ix} in python type declaration')
        if not issubclass(model_fields[field_names_tuple[ix]].annotation, _cpp_field_types[ix]):
            errors.append(f'field {_cpp_field_names[ix]} must be a subclass of cpp type {_cpp_field_types[ix]}')
    if len(errors) > 0:
        raise TypeError('\n'.join(errors))


def _configure_defaults(
    model_fields: dict[str, FieldInfo], definition_context: type[OperandDefinitionContext]
) -> None:
    for name, info in model_fields.items():
        tp: type = info.annotation
        if not info.is_required():
            configure_default(name, info, tp, definition_context)
        elif hasattr(tp, '__default__'):
            info.default = getattr(tp, '__default__')()
            configure_default(name, info, tp, definition_context)
        for meta in info.metadata:
            if isinstance(meta, LogicOperand):
                meta.propagate_definition(tp, name, definition_context)


def _configure_predicates(
    model_fields: dict[str, FieldInfo], definition_context: type[OperandDefinitionContext]
) -> None:
    for name, info in model_fields.items():
        tp: type = info.annotation
        for pred in extract_by_instance_type_from_field_info(info, LogicOperand):
            pred.propagate_definition(tp, name, definition_context)


class compound(type(bw.base)):
    def __new__(
        cls, clsname, clsbases, namespace, *,
        inheritance_policy: InheritancePolicy = InheritancePolicy.DISALLOW
    ) -> type:
        if len(clsbases) != 1:
            raise TypeError(f'compound type {cls} only allows one base class')

        def __init__(self, *args: Any, **data: dict[str, Any]) -> None:
            if len(args) > 0 and len(data) > 0:
                raise ValueError(f'Can instance {self.__class__.__name__} with position parameters or named parameters, not both.')
            if len(args) > 0:
                data = _tuple_to_dict(args, self.__class__.model_fields)
            data = self.__class__.model.__pydantic_validator__.validate_python(data, self_instance=self)
            clsbases[0].__init__(self, *tuple([getattr(data, name) for name in self.__class__.model_fields]))

        def __repr__(self) -> str:
            return f'{self.__class__.__name__}({", ".join([f"{name}={repr(getattr(self, name))}" for name in self.__class__.model_fields])})'

        rettype: type = super().__new__(
            cls, clsname, clsbases, namespace | {
                '__init__': __init__,
                '__repr__': __repr__,
            })
        _check_py_fields_compatible_with_cpp_fields(rettype._cpp_field_names, rettype._cpp_field_types, rettype.model_fields)
        _configure_defaults(rettype.model_fields, rettype.definition_context())
        _configure_predicates(rettype.model_fields, rettype.definition_context())
        rettype.model.model_rebuild(force=True)
        clsbases[0].set_py_cls(rettype)
        return rettype

    @property
    @functools.cache
    def model(self) -> BaseModel:
        members = self.__annotations__
        return create_model(
            f'{self.__name__}_Model',
            **{memb: (members[memb], getattr(self, memb, Undefined), ) for memb in members}
        )

    @property
    def model_fields(self) -> dict[str, FieldInfo]:
        return self.model.model_fields

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

    @abstractmethod
    def definition_context(self) -> type[OperandDefinitionContext]:
        pass


class inherits:
    def __init__(
        self, *bases: Any
    ) -> None:
        assert all([isinstance(tp, compound) for tp in bases])
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
                    configure_default(name, info, tp, self.definition_context(), False)
        if len(errors) > 0:
            raise TypeError(f'Base class errors:\n{"\n".join(errors)}')
        target.model.model_rebuild(force=True)

    def __call__(self, target: type):
        assert isinstance(target, compound)
        self._check_consistent_base_class_fields(target)
        self._inherit_metadata_from_bases(target)
        return target

