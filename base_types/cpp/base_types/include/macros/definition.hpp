#ifndef BASE_TYPES_DEFINITION_MACROS
#define BASE_TYPES_DEFINITION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <pybind11/pybind11.h>
#include "./base.hpp"


namespace py = pybind11;


# define HAS_PY_REPRESENTATION(name, ...)\
private:\
    static py::object cls;\
public:\
    static void set_py_cls (py::object c) {\
        if (name::cls != Py_None){\
            std::string tp_name = py::getattr(c, "__name__").cast<std::string>();\
            std::cout << "WARNING: py_cls already set for class \"" << tp_name << "\". Skipping..." << std::endl;\
            return;\
        }\
        name::cls = c;\
    }\
    py::object to_py () const {\
        return name::cls(__VA_ARGS__);\
    }


#define CL_INHERIT_BASES(r, data, elem)\
    (public T_QUALNAME(T_NAMETUPLE(elem)))


#define CL_MEMBER_NAME(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define CL_MEMBER_DECLARATION(r, data, elem)\
    T_QUALNAME(CM_TYPE(elem)) CM_NAME(elem) data


#define CM_INITIALIZE(r, data, elem)\
    CM_NAME(elem)(CM_NAME(elem))


#define CL_INITIALIZE_BASE(r, data, elem)\
    T_NAME(T_NAMETUPLE(elem))(BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem))) ,


#define CPP_DATACLASS(CLASS_DEF)\
class T_NAME(T_NAMETUPLE(CLASS_DEF))\
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (: BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CL_INHERIT_BASES, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)))))\
    )\
{\
HAS_PY_REPRESENTATION(T_QUALNAME(T_NAMETUPLE(CLASS_DEF)),  BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
\
public:\
    BOOST_PP_SEQ_FOR_EACH(CL_MEMBER_DECLARATION, ;, T_DIRECT_MEMBERS(CLASS_DEF))\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(CL_MEMBER_DECLARATION, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
    ) : \
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (BOOST_PP_SEQ_FOR_EACH(CL_INITIALIZE_BASE, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)))\
    ))\
      BOOST_PP_SEQ_ENUM(\
          BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, BOOST_PP_EMPTY(), T_DIRECT_MEMBERS(CLASS_DEF)))\
    {}\
}


#define CPP_ENUM(ENUM_DEF)\
enum T_NAME(T_NAMETUPLE(ENUM_DEF)) {\
BOOST_PP_SEQ_ENUM(T_DIRECT_MEMBERS(ENUM_DEF))\
}


// #define ALIAS(CLASS_DEF)
// class CLASS(CLASS_DEF) : public QUALNAME(ALIAS_BASE(CLASS_DEF)) {
// HAS_PY_REPRESENTATION(CLASS(CLASS_DEF), BOOST_PP_SEQ_ENUM(
// BOOST_PP_SEQ_FOR_EACH(MEMBER_NAME, BOOST_PP_EMPTY(), MEMBERS(ALIAS_BASE(CLASS_DEF)))))
// using QUALNAME(ALIAS_BASE(CLASS_DEF))::CLASS(ALIAS_BASE(CLASS_DEF));
// CLASS(CLASS_DEF)(const QUALNAME(ALIAS_BASE(CLASS_DEF))& other) : CLASS(ALIAS_BASE(CLASS_DEF))(other) {}
// }


#define T_PY_PRIMITIVE(TYPE_DEF)\
    BOOST_PP_TUPLE_ELEM(2, TYPE_DEF)


#define T_BASE_PRIMITIVE(TYPE_DEF)\
    BOOST_PP_TUPLE_ELEM(3, TYPE_DEF)


#define BTP_BOOLEAN TYPE_DEFINITION(\
    BTP_BOOLEAN,\
    (btp, bool_py),\
    py::bool_,\
    btp::boolean\
)


#define BTP_INT1 TYPE_DEFINITION(\
    BTP_INT1,\
    (btp, int1_py),\
    py::int_,\
    btp::int8\
)


#define BTP_INT2 TYPE_DEFINITION(\
    BTP_INT2,\
    (btp, int2_py),\
    py::int_,\
    btp::int8\
)


#define BTP_INT4 TYPE_DEFINITION(\
    BTP_INT4,\
    (btp, int4_py),\
    py::int_,\
    btp::int8\
)

#define BTP_INT8 TYPE_DEFINITION(\
    BTP_INT8,\
    (btp, int8_py),\
    py::int_,\
    btp::int8\
)


#define BTP_FLOAT4 TYPE_DEFINITION(\
    BTP_FLOAT4,\
    (btp, float4_py),\
    py::float_,\
    btp::float8\
)


#define BTP_FLOAT8 TYPE_DEFINITION(\
    BTP_FLOAT8,\
    (btp, float8_py),\
    py::float_,\
    btp::float8\
)


#define BTP_TEXT TYPE_DEFINITION(\
    BTP_TEXT,\
    (btp, text_py),\
    py::str,\
    btp::text\
)


#define BTP_TIMESTAMPTZ TYPE_DEFINITION(\
    BTP_TIMESTAMPTZ,\
    (btp, timestamptz_py),\
    py::str,\
    btp::text\
)


#define BTP_TIMETZ TYPE_DEFINITION(\
    BTP_TIMETZ,\
    (btp, timetz_py),\
    py::str,\
    btp::text\
)


#define BTP_DATE TYPE_DEFINITION(\
    BTP_DATE,\
    (btp, date_py),\
    py::str,\
    btp::text\
)


#define BTP_BOOLEAN_CONSTRUCTORS (BTP_BOOLEAN)
#define BTP_INT1_CONSTRUCTORS (BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)
#define BTP_INT2_CONSTRUCTORS (BTP_INT2)(BTP_INT1)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)
#define BTP_INT4_CONSTRUCTORS (BTP_INT4)(BTP_INT1)(BTP_INT2)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)
#define BTP_INT8_CONSTRUCTORS (BTP_INT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_FLOAT4)(BTP_FLOAT8)
#define BTP_FLOAT8_CONSTRUCTORS (BTP_FLOAT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)
#define BTP_FLOAT4_CONSTRUCTORS (BTP_FLOAT4)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT8)
#define BTP_TEXT_CONSTRUCTORS (BTP_TEXT)
#define BTP_TIMESTAMPTZ_CONSTRUCTORS (BTP_TIMESTAMPTZ)
#define BTP_TIMETZ_CONSTRUCTORS (BTP_TIMETZ)
#define BTP_DATE_CONSTRUCTORS (BTP_DATE)


#endif
