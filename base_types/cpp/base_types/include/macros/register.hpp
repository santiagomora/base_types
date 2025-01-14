#ifndef BASE_TYPES_REGISTRATION_MACROS
#define BASE_TYPES_REGISTRATION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>


#define PY_PLAIN_CLASS_DEFINITION(CLASS_DEF, m)\
py::class_<QUALNAME(CLASS_DEF)>(m, BOOST_PP_STRINGIZE(CLASS(CLASS_DEF)))\
.def(py::init([](\
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CONST_MEMBER_REF, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF)))\
){\
    return std::unique_ptr<QUALNAME(CLASS_DEF)>(\
        new QUALNAME(CLASS_DEF)(\
            BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(MEMBER_VALUE, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF))))\
    );\
}))\
.def_static("set_py_cls", &QUALNAME(CLASS_DEF)::set_py_cls)


#define PY_COMPOSED_CLASS_DEFINITION(CLASS_DEF, m)\
py::class_<QUALNAME(CLASS_DEF)>(m, BOOST_PP_STRINGIZE(CLASS(CLASS_DEF)))\
.def(py::init([](\
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CONST_MEMBER_REF, BOOST_PP_EMPTY(), COMPOSED_MEMBERS(CLASS_DEF)))\
){\
    return std::unique_ptr<QUALNAME(CLASS_DEF)>(\
        new QUALNAME(CLASS_DEF)(\
            BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(MEMBER_VALUE, BOOST_PP_EMPTY(), COMPOSED_MEMBERS(CLASS_DEF))))\
    );\
}))\
.def_static("set_py_cls", &QUALNAME(CLASS_DEF)::set_py_cls)


#define PY_ENUM_DEFINITION(CLASS_DEF, m)\
py::enum_<QUALNAME(CLASS_DEF)>(m, BOOST_PP_STRINGIZE(CLASS(CLASS_DEF)))\
BOOST_PP_SEQ_FOR_EACH(ENUM_VALUE, QUALNAME(CLASS_DEF), MEMBERS(CLASS_DEF))


#define PY_ALIAS_DEFINITION(CLASS_DEF, m)\
py::class_<QUALNAME(CLASS_DEF)>(m, BOOST_PP_STRINGIZE(CLASS(CLASS_DEF)))\
.def(py::init([](\
    const QUALNAME(ALIAS_BASE(CLASS_DEF))& base\
){\
    return std::unique_ptr<QUALNAME(CLASS_DEF)>(\
        new QUALNAME(CLASS_DEF)(base)\
    );\
}))\
.def(py::init([](\
    const QUALNAME(CLASS_DEF)& base\
){\
    return std::unique_ptr<QUALNAME(CLASS_DEF)>(\
        new QUALNAME(CLASS_DEF)(base)\
    );\
}))\
.def_static("set_py_cls", &QUALNAME(CLASS_DEF)::set_py_cls)


#endif
