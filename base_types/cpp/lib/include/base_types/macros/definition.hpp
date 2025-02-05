#ifndef BASE_TYPES_DEFINITION_MACROS
#define BASE_TYPES_DEFINITION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/algorithm/string/find.hpp>
#include <sstream>
#include "base_types/macros/base.hpp"


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


#define CPP_CLASSDEF_DECLARATION(CLASS_DEF)\
class T_NAME(T_NAMETUPLE(CLASS_DEF))\
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASES(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (: BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CL_INHERIT_BASES, BOOST_PP_EMPTY(), T_BASES(CLASS_DEF)))))\
    )\
{\
public:\
    static base_types::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> subclass_registry;\
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
    py::object to_py(std::string subclass_name) const {\
        return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.to_py(subclass_name, BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
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


#define CPP_ENUMDEF_DECLARATION(ENUM_DEF)\
enum ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF) {\
BOOST_PP_SEQ_ENUM(ENUM_MEMBERS(ENUM_DEF))\
};\
class T_NAME(T_NAMETUPLE(ENUM_DEF)) : public base_types::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>\
{\
public:\
    static base_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))> subclass_registry;\
    using base_types::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>::wrapper;\
    T_NAME(T_NAMETUPLE(ENUM_DEF))(const T_NAME(T_NAMETUPLE(ENUM_DEF))& other) : wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>(other) {}\
    static std::string static_to_string(const ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF) value) {\
        switch(value){\
            BOOST_PP_SEQ_FOR_EACH(ED_TO_STRING_CASE, ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF), ENUM_MEMBERS(ENUM_DEF))\
        }\
        throw std::invalid_argument(std::string("invalid argument for ") + BOOST_PP_STRINGIZE(ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)) + " enum conversion");\
    }\
    T_NAME(T_NAMETUPLE(ENUM_DEF))& operator=(const T_NAME(T_NAMETUPLE(ENUM_DEF))& other) {\
        _value = other.wrapped_ptr();\
        return *this;\
    }\
    std::string to_string() const {\
        return T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::static_to_string(value());\
    }\
    py::object to_py(std::string subclass_name) const {\
        return T_QUALNAME(T_NAMETUPLE(ENUM_DEF))::subclass_registry.to_py(subclass_name, *this);\
    }\
}


#define CPP_ALIASDEF_DECLARATION(ALIAS_DEF)\
class T_NAME(T_NAMETUPLE(ALIAS_DEF)) : public T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF))) {\
public:\
static base_types::py_subclass_registry<BOOST_PP_IF(\
    BOOST_PP_IS_EMPTY(T_BASE_PRIMITIVE(ALIAS_DEF)),\
    BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(T_ALIAS_BASE(ALIAS_DEF))),\
    T_QUALNAME(T_NAMETUPLE(T_ALIAS_ORIGIN(ALIAS_DEF)))\
)> subclass_registry;\
using T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)))::T_NAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)));\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))(const T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)))& other) : T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)))(other) {}\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))(const T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))& other) : T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)))(other) {}\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))& operator=(const T_NAME(T_NAMETUPLE(ALIAS_DEF))& other) {\
    T_QUALNAME(T_NAMETUPLE(T_ALIAS_BASE(ALIAS_DEF)))::operator=(other);\
    return *this;\
}\
}


#define BTP_BOOLEAN TYPE_DEFINITION(\
    BTP_BOOLEAN,\
    (base_types, boolean),\
    base_types::boolean_,\
    py::bool_\
)
#define BTP_BOOLEAN_CONSTRUCTORS (BTP_BOOLEAN)


#define BTP_INT1 TYPE_DEFINITION(\
    BTP_INT1,\
    (base_types, int1),\
    base_types::int1_,\
    py::int_\
)
#define BTP_INT1_CONSTRUCTORS (BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT2 TYPE_DEFINITION(\
    BTP_INT2,\
    (base_types, int2),\
    base_types::int2_,\
    py::int_\
)
#define BTP_INT2_CONSTRUCTORS (BTP_INT2)(BTP_INT1)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT4 TYPE_DEFINITION(\
    BTP_INT4,\
    (base_types, int4),\
    base_types::int4_,\
    py::int_\
)
#define BTP_INT4_CONSTRUCTORS (BTP_INT4)(BTP_INT1)(BTP_INT2)(BTP_INT8)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_INT8 TYPE_DEFINITION(\
    BTP_INT8,\
    (base_types, int8),\
    base_types::int8_,\
    py::int_\
)
#define BTP_INT8_CONSTRUCTORS (BTP_INT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_FLOAT4)(BTP_FLOAT8)


#define BTP_FLOAT4 TYPE_DEFINITION(\
    BTP_FLOAT4,\
    (base_types, float4),\
    base_types::float4_,\
    py::float_\
)
#define BTP_FLOAT4_CONSTRUCTORS (BTP_FLOAT4)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT8)


#define BTP_FLOAT8 TYPE_DEFINITION(\
    BTP_FLOAT8,\
    (base_types, float8),\
    base_types::float8_,\
    py::float_\
)
#define BTP_FLOAT8_CONSTRUCTORS (BTP_FLOAT8)(BTP_INT1)(BTP_INT2)(BTP_INT4)(BTP_INT8)(BTP_FLOAT4)


#define BTP_TEXT TYPE_DEFINITION(\
    BTP_TEXT,\
    (base_types, text),\
    base_types::text_,\
    py::str\
)
#define BTP_TEXT_CONSTRUCTORS (BTP_TEXT)


#define BTP_TIMESTAMPTZ TYPE_DEFINITION(\
    BTP_TIMESTAMPTZ,\
    (base_types, timestamptz),\
    base_types::timestamptz_,\
    py::str\
)
#define BTP_TIMESTAMPTZ_CONSTRUCTORS (BTP_TIMESTAMPTZ)(BTP_TEXT)


#define BTP_DATE TYPE_DEFINITION(\
    BTP_DATE,\
    (base_types, date),\
    base_types::date_,\
    py::str\
)
#define BTP_DATE_CONSTRUCTORS (BTP_DATE)(BTP_TEXT)


// #define BTP_TIMETZ TYPE_DEFINITION(
//     BTP_TIMETZ,
//     (base_types, timetz_py),
//     py::str,
//     base_types::text
// )
// #define BTP_TIMETZ_CONSTRUCTORS (BTP_TIMETZ)


#endif
