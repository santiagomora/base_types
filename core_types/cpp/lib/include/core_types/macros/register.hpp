#ifndef BASE_TYPES_REGISTRATION_MACROS
#define BASE_TYPES_REGISTRATION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include "./base.hpp"


#define C_PY_MEMBER_REF(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) const T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem)))& CM_NAME(elem)


#define C_PY_MEMBER_NAME(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define C_PY_FIELD_DEF_AS_MAP_PAIR(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) {BOOST_PP_STRINGIZE(CM_NAME(elem)), T_REGISTERED_TYPE(CM_TYPE(elem))}


#define C_PY_MEMBER_NAME_STR(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, elem))


#define C_PY_MEMBER_TP(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) T_REGISTERED_TYPE(CM_TYPE(elem))


#define C_PY_BASE_TP(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) T_REGISTERED_TYPE(elem)


#define C_PY_CONSTRUCTOR(r, data, elem)\
.def(py::init([](\
    BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_REF, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem))\
){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(elem))>(\
        new T_QUALNAME(T_NAMETUPLE(elem))(\
            BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem)))\
    );\
}))


#define PY_CLASSDEF_DECLARE_SUBCLASS_REG(CLASS_DEF)\
core_types::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry= core_types::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))>()


#define PY_CLASSDEF_REGISTER(CLASS_DEF, m)\
py::class_<T_QUALNAME(T_NAMETUPLE(CLASS_DEF))>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(CLASS_DEF))))\
BOOST_PP_SEQ_FOR_EACH(C_PY_CONSTRUCTOR, BOOST_PP_EMPTY(), T_CONSTRUCTORS(CLASS_DEF))\
.def_property_readonly_static("_cpp_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::to_string)\
.def_property_readonly_static("_cpp_field_types", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_TP, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def_property_readonly_static("_cpp_bases", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_BASE_TP, BOOST_PP_EMPTY(), T_BASE(CLASS_DEF)));\
})\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(CLASS_DEF)).T_NAME(T_NAMETUPLE(CLASS_DEF)));\
})\


#define PY_REGISTER_CLASS_ALIASDEF(ALIAS_DEF, m)\
py::class_<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(ALIAS_DEF))))\
BOOST_PP_SEQ_FOR_EACH(C_PY_CONSTRUCTOR, BOOST_PP_EMPTY(), T_CONSTRUCTORS(ALIAS_DEF))\
.def_property_readonly_static("_cpp_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(ALIAS_DEF)));\
})\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_string)\
.def_property_readonly_static("_cpp_field_types", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_TP, BOOST_PP_EMPTY(), C_ALL_MEMBERS(ALIAS_DEF)));\
})\
.def_property_readonly_static("_cpp_fields", [](const py::object&) -> py::tuple {\
    return std::make_shared<std::map<std::string, py::object>>(BOOST_PP_SEQ_FOR_EACH_I(C_PY_FIELD_DEF_AS_MAP_PAIR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(ALIAS_DEF)));\
})\
.def_property_readonly_static("_cpp_bases", [](const py::object&) -> py::tuple {\
    return py::make_tuple(py::type::of<T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))>());\
})\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(ALIAS_DEF)).T_NAME(T_NAMETUPLE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))>();\
})


#define E_PY_VALUE(r, data, elem)\
.value(BOOST_PP_STRINGIZE(elem), data::elem)


#define TD_PY_BASE_TYPE_CONSTRUCTOR_(r, data, elem)\
.def(py::init([](const T_QUALNAME(T_NAMETUPLE(elem))& other){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(data))>(\
        new T_QUALNAME(T_NAMETUPLE(data))(other.to_string()));\
}))


#define TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)\
.def(py::init([](const T_PY_PRIMITIVE(TYPE_DEF)& other){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>(\
        new T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(other.attr("__str__")().cast<core_types::text_>()));\
}))


#define TD_PY_COPY_CONSTRUCTOR(TYPE_DEF)\
.def(py::init([](const T_QUALNAME(T_NAMETUPLE(TYPE_DEF))& other){\
    return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(other);\
}))


#define TD_PY_TYPE_CONSTRUCTORS(TYPE_DEF, CONSTRUCTORS)\
TD_PY_COPY_CONSTRUCTOR(BOOST_PP_SEQ_HEAD(CONSTRUCTORS))\
BOOST_PP_SEQ_FOR_EACH(TD_PY_BASE_TYPE_CONSTRUCTOR_, TYPE_DEF, BOOST_PP_SEQ_TAIL(CONSTRUCTORS))\
TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)


#define TD_DECLARE_COMPARE(r, data, elem)\
.def("compare", [](const T_QUALNAME(T_NAMETUPLE(data))& t, const T_QUALNAME(T_NAMETUPLE(elem))& v) {\
    return t.compare<T_BASE_PRIMITIVE(elem)>(v);\
})


#define PY_TYPEDEF_DECLARE_SUBCLASS_REG(TYPE_DEF)\
core_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))> T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry = core_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>()


#define PY_TYPEDEF_REGISTER(TYPE_DEF, m, VAR_NAME)\
py::class_<T_QUALNAME(T_NAMETUPLE(TYPE_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>> VAR_NAME(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(TYPE_DEF))));\
VAR_NAME.def(py::pickle(\
    [](const T_QUALNAME(T_NAMETUPLE(TYPE_DEF))& a) { return py::make_tuple(a.value()); },\
    [](py::tuple t) { return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(t[0].cast<core_types::text_>()); }\
))\
TD_PY_TYPE_CONSTRUCTORS(TYPE_DEF, T_CONSTRUCTORS(TYPE_DEF))\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::to_string)\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(TYPE_DEF)).T_NAME(T_NAMETUPLE(TYPE_DEF)));\
})\
.def("compare", [](const T_QUALNAME(T_NAMETUPLE(TYPE_DEF))& t, const T_PY_PRIMITIVE(TYPE_DEF)& other) {\
    T_QUALNAME(T_NAMETUPLE(TYPE_DEF)) v(other.attr("__str__")().cast<core_types::text_>());\
    return t.compare<T_BASE_PRIMITIVE(TYPE_DEF)>(v);\
})\
BOOST_PP_SEQ_FOR_EACH(TD_DECLARE_COMPARE, TYPE_DEF, T_CONSTRUCTORS(TYPE_DEF))


#define PY_REGISTER_TYPE_ALIASDEF(ALIAS_DEF, m, VAR_NAME, CONSTRUCTORS)\
py::class_<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))>> VAR_NAME(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(ALIAS_DEF))));\
VAR_NAME.def(py::pickle(\
    [](const T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))& a) { return py::make_tuple(a.value()); },\
    [](py::tuple t) { return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))(t[0].cast<T_BASE_PRIMITIVE(ALIAS_DEF)>()); }\
))\
TD_PY_TYPE_CONSTRUCTORS(ALIAS_DEF, T_CONSTRUCTORS(ALIAS_DEF))\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_string)\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(ALIAS_DEF)).T_NAME(T_NAMETUPLE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))>();\
})\
.def("compare", [](const T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))& t, const T_PY_PRIMITIVE(ALIAS_DEF)& other) {\
    T_QUALNAME(T_NAMETUPLE(ALIAS_DEF)) v(other.attr("__str__")().cast<core_types::text_>());\
    return t.compare<T_BASE_PRIMITIVE(ALIAS_DEF)>(v);\
})\
BOOST_PP_SEQ_FOR_EACH(TD_DECLARE_COMPARE, ALIAS_DEF, CONSTRUCTORS)


#define ED_PY_COPY_CONSTRUCTOR(r, data, elem)\
.def(py::init([](const T_QUALNAME(T_NAMETUPLE(elem))& other){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(elem))>(\
        new T_QUALNAME(T_NAMETUPLE(elem))(other));\
}))


#define PY_ENUMDEF_DECLARE_SUBCLASS_REG(ENUM_DEF)\
core_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))> T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::subclass_registry = core_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>()


#define PY_ENUMDEF_REGISTER(ENUM_DEF, m)\
py::enum_<ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>(m, BOOST_PP_STRINGIZE(ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)))\
BOOST_PP_SEQ_FOR_EACH(E_PY_VALUE, ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF), ENUM_MEMBERS(ENUM_DEF));\
py::class_<T_QUALNAME(T_NAMETUPLE(ENUM_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(ENUM_DEF))))\
BOOST_PP_SEQ_FOR_EACH(ED_PY_COPY_CONSTRUCTOR, BOOST_PP_EMPTY(), T_CONSTRUCTORS(ENUM_DEF))\
.def(py::init([](const ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)& other){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>(\
        new T_QUALNAME(T_NAMETUPLE(ENUM_DEF))(other));\
}))\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::to_string)\
.def_property_readonly_static("enum", [](py::object /* self */){\
    return py::type::of<ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>();\
})\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(ENUM_DEF)).T_NAME(T_NAMETUPLE(ENUM_DEF)));\
})\


#define PY_ALIASDEF_DECLARE_SUBCLASS_REG(ALIAS_DEF)\
core_types::py_subclass_registry<BOOST_PP_IF(\
    BOOST_PP_IS_EMPTY(T_PY_PRIMITIVE(ALIAS_DEF)),\
    BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(T_ALIAS_ORIGIN(ALIAS_DEF))),\
    T_QUALNAME(T_NAMETUPLE(T_ALIAS_ORIGIN(ALIAS_DEF)))\
)>& T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry = T_QUALNAME(T_NAMETUPLE(T_ALIAS_ORIGIN(ALIAS_DEF)))::subclass_registry;


#define PY_REGISTER_ENUM_ALIASDEF(ALIAS_DEF, m, CONSTRUCTORS)\
py::class_<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(ALIAS_DEF))))\
BOOST_PP_SEQ_FOR_EACH(ED_PY_COPY_CONSTRUCTOR, BOOST_PP_EMPTY(), CONSTRUCTORS)\
.def(py::init([](const ENUM_QUALIFIED_UNDERLYING_CLASS(ALIAS_DEF)& other){\
    return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))>(\
        new T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))(other));\
}))\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_string)\
.def_property_readonly_static("enum", [](py::object& /* self */){\
    return py::type::of<ENUM_QUALIFIED_UNDERLYING_CLASS(ALIAS_DEF)>();\
})\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})\
.def_property_readonly_static("qualified_name", [](py::object&){\
    return BOOST_PP_STRINGIZE(T_NAMESPACE(T_NAMETUPLE(ALIAS_DEF)).T_NAME(T_NAMETUPLE(ALIAS_DEF)));\
})\
.def_property_readonly_static("base_type", [](py::object&){\
    return py::type::of<T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))>();\
})\
BOOST_PP_SEQ_FOR_EACH(TD_DECLARE_COMPARE, ENUM_DEF, CONSTRUCTORS)


#endif
