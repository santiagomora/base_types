#ifndef BASE_TYPES_DEFINITION_MACROS
#define BASE_TYPES_DEFINITION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/algorithm/string/find.hpp>
#include <sstream>
#include "./base.hpp"


#ifndef QUOTE_FUNCTION
    #define QUOTE_FUNCTION(FIELD_STR) FIELD_STR
#endif


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
    static py::object py_cls () {\
        return name::cls;\
    }\
    py::object to_py () const {\
        return name::cls(__VA_ARGS__);\
    }


#define CL_INHERIT_BASES(r, data, elem)\
    (public T_QUALNAME(T_NAMETUPLE(elem)))


#define CL_MEMBER_NAME(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define CL_ACCESS_MEMBER(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) data.CM_NAME(elem)


#define CL_MEMBER_TYPE(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) CM_QUALIFIED_TYPE(elem)


#define CL_MEMBER_DECLARATION(r, data, elem)\
    CM_QUALIFIED_TYPE(elem) CM_NAME(elem) data


#define CL_INITIALIZE_BASE(r, data, elem)\
    T_NAME(T_NAMETUPLE(elem))(BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem))) ,


#define CL_INITIALIZE_EMPTY_BASE(r, data, i, elem)\
    BOOST_PP_COMMA_IF(i) T_NAME(T_NAMETUPLE(elem))()


#define CL_INITIALIZE_BASE_COPY(r, data, elem)\
    T_NAME(T_NAMETUPLE(elem))(data) ,


#define CM_INITIALIZE(r, data, elem)\
    CM_NAME(elem)(BOOST_PP_IF(BOOST_PP_IS_EMPTY(data), CM_NAME(elem), data.CM_NAME(elem)))


#define CM_COPY(r, data, elem)\
    CM_NAME(elem) = data.CM_NAME(elem);


#define CM_STREAM_TO_STRING(r, data, i, elem)\
    BOOST_PP_IF(i, << ", " <<, BOOST_PP_EMPTY())\
    BOOST_PP_IF(CM_IS_OPTIONAL(elem), ((CM_NAME(elem).has_value()) ? CM_NAME(elem).value().to_string() : "NULL"), CM_NAME(elem).to_string())


#define CPP_DATACLASS_DECLARATION(CLASS_DEF)\
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
\
    T_NAME(T_NAMETUPLE(CLASS_DEF))()\
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (: BOOST_PP_SEQ_FOR_EACH_I(CL_INITIALIZE_EMPTY_BASE, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)))\
    ))\
    {}\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(CL_MEMBER_DECLARATION, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
    ) : \
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (BOOST_PP_SEQ_FOR_EACH(CL_INITIALIZE_BASE, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)))\
    ))\
\
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, BOOST_PP_EMPTY(), T_DIRECT_MEMBERS(CLASS_DEF)))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (const T_NAME(T_NAMETUPLE(CLASS_DEF))& other)\
    : \
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (BOOST_PP_SEQ_FOR_EACH(CL_INITIALIZE_BASE_COPY, other, T_BASES(CLASS_DEF)))\
    ))\
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, other, T_DIRECT_MEMBERS(CLASS_DEF)))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF))& operator=(const T_NAME(T_NAMETUPLE(CLASS_DEF))& other) {\
        BOOST_PP_SEQ_FOR_EACH(CM_COPY, other, C_ALL_MEMBERS(CLASS_DEF))\
        return *this;\
    }\
    std::string to_string () const {\
        std::ostringstream oss;\
        oss << "(" << BOOST_PP_SEQ_FOR_EACH_I(CM_STREAM_TO_STRING, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)) << ")";\
        return oss.str();\
    }\
}


#define ED_TO_STRING_CASE(r, data, elem)\
    case data::elem:\
        return BOOST_PP_STRINGIZE(elem);


#define ED_FROM_STRING_CASE(r, data, i, elem)\
    BOOST_PP_IF(\
        i,\
        else if (BOOST_PP_STRINGIZE(elem) == BOOST_PP_TUPLE_ELEM(1, data))\
            return BOOST_PP_TUPLE_ELEM(0, data)::elem;,\
        if (BOOST_PP_STRINGIZE(elem) == BOOST_PP_TUPLE_ELEM(1, data))\
            return BOOST_PP_TUPLE_ELEM(0, data)::elem;\
    )


#define CPP_ENUM_DECLARATION(ENUM_DEF)\
enum ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF) {\
BOOST_PP_SEQ_ENUM(T_DIRECT_MEMBERS(ENUM_DEF))\
};\
class T_NAME(T_NAMETUPLE(ENUM_DEF)) : public btp::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>\
{\
HAS_PY_REPRESENTATION(T_QUALNAME(T_NAMETUPLE(ENUM_DEF)), value())\
public:\
    using btp::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>::wrapper;\
    T_NAME(T_NAMETUPLE(ENUM_DEF))(const T_NAME(T_NAMETUPLE(ENUM_DEF))& other) : wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>(other) {}\
    static std::string static_to_string(const ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF) value) {\
        switch(value){\
            BOOST_PP_SEQ_FOR_EACH(ED_TO_STRING_CASE, ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF), T_DIRECT_MEMBERS(ENUM_DEF))\
        }\
        throw std::invalid_argument(std::string("invalid argument for ") + BOOST_PP_STRINGIZE(ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)) + " enum conversion");\
    }\
    std::string to_string() const {\
        return T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::static_to_string(value());\
    }\
    T_NAME(T_NAMETUPLE(ENUM_DEF))& operator=(const T_NAME(T_NAMETUPLE(ENUM_DEF))& other) {\
        _value = other.wrapped_ptr();\
        return *this;\
    }\
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
    (btp, boolean),\
    py::bool_,\
    btp::boolean_\
)
#define BTP_BOOLEAN_CONSTRUCTORS (BTP_BOOLEAN)


#define BTP_INT1 TYPE_DEFINITION(\
    BTP_INT1,\
    (btp, int1),\
    py::int_,\
    btp::int8_\
)
#define BTP_INT1_CONSTRUCTORS (BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT2 TYPE_DEFINITION(\
    BTP_INT2,\
    (btp, int2),\
    py::int_,\
    btp::int8_\
)
#define BTP_INT2_CONSTRUCTORS (BTP_INT2)(BTP_INT1)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT4 TYPE_DEFINITION(\
    BTP_INT4,\
    (btp, int4),\
    py::int_,\
    btp::int8_\
)
#define BTP_INT4_CONSTRUCTORS (BTP_INT4)(BTP_INT1)(BTP_INT2)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT8 TYPE_DEFINITION(\
    BTP_INT8,\
    (btp, int8),\
    py::int_,\
    btp::int8_\
)
#define BTP_INT8_CONSTRUCTORS (BTP_INT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_FLOAT4 TYPE_DEFINITION(\
    BTP_FLOAT4,\
    (btp, float4),\
    py::float_,\
    btp::float8_\
)
#define BTP_FLOAT4_CONSTRUCTORS (BTP_FLOAT4)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT8)


#define BTP_FLOAT8 TYPE_DEFINITION(\
    BTP_FLOAT8,\
    (btp, float8),\
    py::float_,\
    btp::float8_\
)
#define BTP_FLOAT8_CONSTRUCTORS (BTP_FLOAT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)


#define BTP_TEXT TYPE_DEFINITION(\
    BTP_TEXT,\
    (btp, text),\
    py::str,\
    btp::text_\
)
#define BTP_TEXT_CONSTRUCTORS (BTP_TEXT)


#define BTP_TIMESTAMPTZ TYPE_DEFINITION(\
    BTP_TIMESTAMPTZ,\
    (btp, timestamptz),\
    py::str,\
    btp::text_\
)
#define BTP_TIMESTAMPTZ_CONSTRUCTORS (BTP_TIMESTAMPTZ)


// #define BTP_TIMETZ TYPE_DEFINITION(
//     BTP_TIMETZ,
//     (btp, timetz_py),
//     py::str,
//     btp::text
// )
// #define BTP_TIMETZ_CONSTRUCTORS (BTP_TIMETZ)


#define BTP_DATE TYPE_DEFINITION(\
    BTP_DATE,\
    (btp, date),\
    py::str,\
    btp::text_\
)
#define BTP_DATE_CONSTRUCTORS (BTP_DATE)


#endif
