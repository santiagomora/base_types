#ifndef BASE_TYPES_REGISTRATION_MACROS
#define BASE_TYPES_REGISTRATION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include "./base.hpp"


#define C_PY_MEMBER_REF(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) const T_QUALNAME(BOOST_PP_TUPLE_ELEM(0, elem))& BOOST_PP_TUPLE_ELEM(1, elem)


#define C_PY_MEMBER_NAME(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(1, elem)


#define C_PY_MEMBER_NAME_STR(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(1, elem))


#define C_PY_MEMBER_TP(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) py::type::of<T_QUALNAME(BOOST_PP_TUPLE_ELEM(0, elem))>()


#define C_PY_BASE_TP(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) py::type::of<T_QUALNAME(T_NAMETUPLE(elem))>()


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
    btp::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry= btp::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))>()


#define PY_CLASSDEF_REGISTER(CLASS_DEF, m)\
py::class_<T_QUALNAME(T_NAMETUPLE(CLASS_DEF))>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(CLASS_DEF))))\
BOOST_PP_SEQ_FOR_EACH(C_PY_CONSTRUCTOR, BOOST_PP_EMPTY(), BOOST_PP_CAT(T_MACRO_NAME(CLASS_DEF), _CONSTRUCTORS))\
.def_property_readonly_static("_cpp_field_names", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_NAME_STR, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::to_string)\
.def_property_readonly_static("_cpp_field_types", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_MEMBER_TP, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
})\
.def_property_readonly_static("_cpp_bases", [](const py::object&) -> py::tuple {\
    return py::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(C_PY_BASE_TP, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)));\
})\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.get_py_cls(subclass_name);\
})


#define E_PY_VALUE(r, data, elem)\
    .value(BOOST_PP_STRINGIZE(elem), data::elem)


#define TD_PY_BASE_TYPE_CONSTRUCTOR_(r, data, elem)\
    .def(py::init([](const T_QUALNAME(T_NAMETUPLE(elem))& other){\
        return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(data))>(\
            new T_QUALNAME(T_NAMETUPLE(data))(static_cast<T_BASE_PRIMITIVE(data)>(other.value())));\
    }))


#define TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)\
    .def(py::init([](const T_PY_PRIMITIVE(TYPE_DEF)& other){\
        return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>(\
            new T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(other.cast<T_BASE_PRIMITIVE(TYPE_DEF)>()));\
    }))


#define TD_PY_COPY_CONSTRUCTOR(TYPE_DEF)\
    .def(py::init([](const T_QUALNAME(T_NAMETUPLE(TYPE_DEF))& other){\
        return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>(\
            new T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(other));\
    }))


#define TD_PY_TYPE_CONSTRUCTORS(TYPE_DEF, CONSTRUCTORS)\
    TD_PY_COPY_CONSTRUCTOR(BOOST_PP_SEQ_HEAD(CONSTRUCTORS))\
    BOOST_PP_SEQ_FOR_EACH(TD_PY_BASE_TYPE_CONSTRUCTOR_, TYPE_DEF, BOOST_PP_SEQ_TAIL(CONSTRUCTORS))\
    TD_PY_PY_TYPE_CONSTRUCTOR(TYPE_DEF)


#define PY_TYPEDEF_DECLARE_SUBCLASS_REG(TYPE_DEF)\
    btp::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))> T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry = btp::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>()


#define PY_TYPEDEF_REGISTER(TYPE_DEF, m, VAR_NAME)\
py::class_<T_QUALNAME(T_NAMETUPLE(TYPE_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>> VAR_NAME(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(TYPE_DEF))));\
VAR_NAME.def(py::pickle(\
    [](const T_QUALNAME(T_NAMETUPLE(TYPE_DEF))& a) { return py::make_tuple(a.value()); },\
    [](py::tuple t) { return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))(t[0].cast<T_BASE_PRIMITIVE(TYPE_DEF)>()); }\
))\
TD_PY_TYPE_CONSTRUCTORS(TYPE_DEF, BOOST_PP_CAT(T_MACRO_NAME(TYPE_DEF), _CONSTRUCTORS))\
.def("__str__", &T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::to_string)\
.def("to_py", &T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::to_py)\
.def_static("set_py_cls", [](std::string& subclass_name, py::object& cls){\
    return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry.set_py_cls(subclass_name, cls);\
})\
.def_static("get_py_cls", [](std::string& subclass_name){\
    return T_QUALNAME(T_NAMETUPLE(TYPE_DEF))::subclass_registry.get_py_cls(subclass_name);\
})


#define ED_PY_COPY_CONSTRUCTOR(r, data, elem)\
    .def(py::init([](const T_QUALNAME(T_NAMETUPLE(elem))& other){\
        return std::unique_ptr<T_QUALNAME(T_NAMETUPLE(elem))>(\
            new T_QUALNAME(T_NAMETUPLE(elem))(other));\
    }))


#define PY_ENUMDEF_DECLARE_SUBCLASS_REG(ENUM_DEF)\
    btp::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))> T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::subclass_registry= btp::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>()


#define PY_ENUMDEF_REGISTER(ENUM_DEF, m)\
py::enum_<ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>(m, BOOST_PP_STRINGIZE(ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF)))\
BOOST_PP_SEQ_FOR_EACH(E_PY_VALUE, ENUM_QUALIFIED_UNDERLYING_CLASS(ENUM_DEF), T_DIRECT_MEMBERS(ENUM_DEF));\
py::class_<T_QUALNAME(T_NAMETUPLE(ENUM_DEF)), std::unique_ptr<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>>(m, BOOST_PP_STRINGIZE(T_NAME(T_NAMETUPLE(ENUM_DEF))))\
BOOST_PP_SEQ_FOR_EACH(ED_PY_COPY_CONSTRUCTOR, BOOST_PP_EMPTY(), BOOST_PP_CAT(T_MACRO_NAME(ENUM_DEF), _CONSTRUCTORS))\
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
})


// #define PY_ALIAS_DEFINITION(CLASS_DEF, m)
// py::class_<QUALNAME(CLASS_DEF)>(m, BOOST_PP_STRINGIZE(CLASS(CLASS_DEF)))
// .def(py::init([](
//     const QUALNAME(ALIAS_BASE(CLASS_DEF))& base
// ){
//     return std::unique_ptr<QUALNAME(CLASS_DEF)>(
//         new QUALNAME(CLASS_DEF)(base)
//     );
// }))
// .def(py::init([](
//     const QUALNAME(CLASS_DEF)& base
// ){
//     return std::unique_ptr<QUALNAME(CLASS_DEF)>(
//         new QUALNAME(CLASS_DEF)(base)
//     );
// }))
// .def_static("set_py_cls", &QUALNAME(CLASS_DEF)::set_py_cls)


#endif
