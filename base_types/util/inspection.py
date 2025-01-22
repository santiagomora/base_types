from typing import\
    Any,\
    Optional,\
    Callable,\
    KeysView,\
    Generator,\
    get_args,\
    get_origin,\
    Union
from pydantic.fields import\
    FieldInfo
import copy
from collections import\
    OrderedDict
from ordered_set import\
    OrderedSet
from pydantic import\
    BaseModel
from deepdiff import \
    DeepDiff
from typing import\
    Iterable


def extract_by_instance_type_from_list(
    elem_list: list[Any],
    instance_type: type
) -> Generator[type, None, None]:
    for elem in elem_list:
        if isinstance(elem, instance_type):
            yield elem


def extract_first_appearance_from_list(
    elem_list: list[Any],
    instance_type: type
) -> Any:
    for elem in elem_list:
        if isinstance(elem, instance_type):
            return elem
    return None


# TODO rename this to extract_by_instance_type_from_field_info_metadata
def extract_by_instance_type_from_field_info(
    info: FieldInfo,
    instance_type: type
) -> Generator[type, None, None]:
    for meta in extract_by_instance_type_from_list(info.metadata, instance_type):
        yield meta


def extract_first_instance_from_field_metadata(
    info: FieldInfo,
    instance_type: type
) -> Any:
    return extract_first_appearance_from_list(info.metadata, instance_type)


def extract_definition_fields(cls: type) -> Generator[tuple[str, FieldInfo], None, None]:
    """
    Exclude inherited fields and yield only those fields defined as table 
    attributes directly. Considerations:
    - Child class can redefine parent attribute, changes wont be detected unless
    type or metadata are modified.
    """
    for field_name, info in cls.model_fields.items():
        yield field_name, info
    # return
    # direct_fields: dict[str, FieldInfo] = set(cls.model_fields.keys())
    # for icls in cls.__bases__:
    #     for inherited_field_name in icls.model_fields:
    #         if inherited_field_name in direct_fields:
    #             # if FieldInfo has not changed it means that the field is inherited
    #             # so we must remove it. Otherwise the field is inherited and overriden
    #             # in cls. It doesnt make sense to declare the field exactly as is in child
    #             # model
    #             if DeepDiff(icls.model_fields[inherited_field_name], cls.model_fields[inherited_field_name]) == {}:
    #                 direct_fields.remove(inherited_field_name)
    # for field_name in direct_fields:
    #     yield (field_name, cls.model_fields[field_name])


def extract_inherited_fields(cls: type) -> Generator[tuple[str, FieldInfo], None, None]:
    """
    Exclude definition fields and yield only those fields inherited from base classes
    """
    for field_name, info in cls.model_fields.items():
        yield field_name, info
    model_fields = set(cls.model_fields.keys())
    direct_fields = set([field for field, _ in extract_definition_fields(cls)])
    for inherited_field in (model_fields - direct_fields):
        yield inherited_field, cls.model_fields[inherited_field]


def extract_by_instance_type_from_model_fields_info(
    cls: type[BaseModel],
    instance_type: type,
    conversion_fn: Optional[Callable[[Any], dict[str, Any]]] = None
) -> Generator[tuple[str, dict[str, Any] | Any], None, None]:
    """
    Extracts by instance type from direct fields metadata
    """
    for field_name, field_info in extract_definition_fields(cls):
        for meta in extract_by_instance_type_from_field_info(field_info, instance_type):
            if conversion_fn is not None:
                yield field_name, conversion_fn(field_name, meta)
            else:
                yield field_name, meta
