#ifndef CORE_TYPES_MACROS_REGISTER_BASE
#define CORE_TYPES_MACROS_REGISTER_BASE
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include "core_types/macros/definition.hpp"
#include "core_types/macros/interface.hpp"
#include "core_types/typing/interface.hpp"


#define C_PY_MEMBER_REF(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) const T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))& CM_NAME(elem)


#define C_PY_UNUSED_MEMBER_REF(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) const T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))&


#define C_PY_MEMBER_NAME(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define C_PY_MEMBER_NAME_STR(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, elem))


#define C_PY_MEMBER_TP(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) py::make_tuple(\
    py::type::of<core_types::interface::describe_type<T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))>::underlying>(),\
    core_types::interface::describe_type<T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))>::container_name\
)


#define C_PY_BASE_TP(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) py::type::of<T_QUALNAME(T_IFACE_TYPE(elem))>()


#define C_PY_CONSTRUCTOR(r, data, elem)\
.def(py::init([](\
    BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_REF, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem))\
){\
    return std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(elem))>(\
        new T_QUALNAME(T_IFACE_TYPE(elem))(\
            BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem)))\
    );\
}))


#define ED_PY_COPY_CONSTRUCTOR(r, data, elem)\
.def(py::init([](const T_QUALNAME(T_IFACE_TYPE(elem))& other){\
    return std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(elem))>(\
        new T_QUALNAME(T_IFACE_TYPE(elem))(other));\
}))


#define E_PY_VALUE(r, data, elem)\
.value(BOOST_PP_STRINGIZE(elem), data::elem)


#define TD_PY_BASE_TYPE_CONSTRUCTOR_(r, data, elem)\
.def(py::init([](const T_QUALNAME(T_IFACE_TYPE(elem))& other){\
    return std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(data))>(\
        new T_QUALNAME(T_IFACE_TYPE(data))(other.to_string()));\
}))


#define TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)\
.def(py::init([](const T_PY_PRIMITIVE(TYPE_DEF)& other){\
    return std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))>(\
        new T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))(other.attr("__str__")().cast<core_types::text>()));\
}))


#define TD_PY_COPY_CONSTRUCTOR(TYPE_DEF)\
.def(py::init([](const T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))& other){\
    return T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))(other);\
}))


#define TD_PY_TYPE_CONSTRUCTORS(TYPE_DEF, CONSTRUCTORS)\
TD_PY_COPY_CONSTRUCTOR(BOOST_PP_SEQ_HEAD(CONSTRUCTORS))\
BOOST_PP_SEQ_FOR_EACH(TD_PY_BASE_TYPE_CONSTRUCTOR_, TYPE_DEF, BOOST_PP_SEQ_TAIL(CONSTRUCTORS))\
TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)


#define TD_DECLARE_COMPARE(r, data, elem)\
.def("compare", [](const T_QUALNAME(T_IFACE_TYPE(data))& t, const T_QUALNAME(T_IFACE_TYPE(elem))& v) {\
    return t.compare<T_QUALIFIED_UNDERLYING_CLASS(elem)>(v);\
})


#define CT_TYPEDEF_REGISTER_SUBCLASS_REG(TYPE_DEF)\
core_types::interface::py_subclass_registry<T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))> T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))::subclass_registry = core_types::interface::py_subclass_registry<T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))>()


#define CT_ALIASDEF_REGISTER_SUBCLASS_REG(ALIAS_DEF)\
core_types::interface::py_subclass_registry<BOOST_PP_IF(\
    T_IS_CLASSDEF_ALIAS(ALIAS_DEF),\
    BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(T_ALIAS_ORIGIN(ALIAS_DEF))),\
    T_QUALNAME(T_IFACE_TYPE(T_ALIAS_ORIGIN(ALIAS_DEF)))\
)>& T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry = T_QUALNAME(T_IFACE_TYPE(T_ALIAS_ORIGIN(ALIAS_DEF)))::subclass_registry;


#define CT_ENUMDEF_REGISTER_SUBCLASS_REG(ENUM_DEF)\
core_types::interface::py_subclass_registry<T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))> T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::subclass_registry = core_types::interface::py_subclass_registry<T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))>()


#define CT_CLASSDEF_REGISTER_SUBCLASS_REG(CLASS_DEF)\
core_types::interface::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))::subclass_registry= core_types::interface::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))>()


#define CT_CLASSDEF_REGISTER_BASE(CLASS_DEF, m)\
py::class_<T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))>(m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(CLASS_DEF))))\
.def_property_readonly_static("_cpp_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def_property_readonly_static("_cpp_field_types", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_TP, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def_property_readonly_static("_cpp_direct_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), T_MEMBERS(CLASS_DEF)));\
})\
.def_property_readonly_static("_cpp_bases", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_BASE_TP, BOOST_PP_EMPTY(), T_BASE(CLASS_DEF)));\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(CLASS_DEF)).T_NAME(T_IFACE_TYPE(CLASS_DEF)));\
})\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))::to_string)


#define CT_CLASS_ALIASDEF_REGISTER_BASE(ALIAS_DEF, m)\
py::class_<T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))>(m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(ALIAS_DEF))))\
.def_property_readonly_static("_cpp_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(ALIAS_DEF)));\
})\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::to_string)\
.def_property_readonly_static("_cpp_field_types", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_TP, BOOST_PP_EMPTY(), C_ALL_MEMBERS(ALIAS_DEF)));\
})\
.def_property_readonly_static("_cpp_direct_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), T_MEMBERS(ALIAS_DEF)));\
})\
.def_property_readonly_static("_cpp_bases", [](const py::object&) -> py::tuple {\
    return py::make_tuple(py::type::of<T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))>());\
})\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(ALIAS_DEF)).T_NAME(T_IFACE_TYPE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))>();\
})


#define CT_TYPEDEF_REGISTER_BASE(TYPE_DEF, m)\
py::class_<T_QUALNAME(T_IFACE_TYPE(TYPE_DEF)), std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))>> (m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(TYPE_DEF))))\
.def(py::pickle(\
    [](const T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))& a) { return py::make_tuple(a.value()); },\
    [](py::tuple t) { return T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))(t[0].cast<core_types::text>()); }\
))\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))::to_string)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(TYPE_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(TYPE_DEF)).T_NAME(T_IFACE_TYPE(TYPE_DEF)));\
})


#define CT_TYPE_ALIASDEF_REGISTER_BASE(ALIAS_DEF, m)\
py::class_<T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF)), std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(ALIAS_DEF))))\
.def(py::pickle(\
    [](const T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))& a) { return py::make_tuple(a.value()); },\
    [](py::tuple t) { return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))(t[0].cast<T_QUALIFIED_UNDERLYING_CLASS(ALIAS_DEF)>()); }\
))\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::to_string)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(ALIAS_DEF)).T_NAME(T_IFACE_TYPE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))>();\
})\


#define CT_ENUMDEF_REGISTER_BASE(ENUM_DEF, m)\
py::enum_<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>(m, BOOST_PP_STRINGIZE(T_QUALNAME(T_NAMETUPLE(ENUM_DEF))))\
BOOST_PP_SEQ_FOR_EACH(E_PY_VALUE, T_QUALNAME(T_NAMETUPLE(ENUM_DEF)), T_MEMBERS(ENUM_DEF));\
py::class_<T_QUALNAME(T_IFACE_TYPE(ENUM_DEF)), std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(ENUM_DEF))))\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::to_string)\
.def_property_readonly_static("enum", [](py::object /* self */){\
    return py::type::of<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>();\
})\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(ENUM_DEF)).T_NAME(T_IFACE_TYPE(ENUM_DEF)));\
})\


#define CT_ENUM_ALIASDEF_REGISTER_BASE(ALIAS_DEF, m)\
py::class_<T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF)), std::unique_ptr<T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_IFACE_TYPE(ALIAS_DEF))))\
.def("__str__", &T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::to_string)\
.def_property_readonly_static("enum", [](py::object& /* self */){\
    return py::type::of<T_QUALIFIED_UNDERLYING_CLASS(ALIAS_DEF)>();\
})\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_IFACE_TYPE(ALIAS_DEF)).T_NAME(T_IFACE_TYPE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))>();\
})


#endif
