#ifndef CORE_TYPES_TYPING_DEFINITIONS
#define CORE_TYPES_TYPING_DEFINITIONS
#include "core_types/macros/definition.hpp"


// NOTE CONTAINERS
#define STD_VECTOR(TYPE_DEF)(\
    STD_VECTOR,\
    (std, vector<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>),\
    BOOST_PP_EMPTY(),\
    BOOST_PP_EMPTY(),\
    BOOST_PP_EMPTY(),\
    TYPE_DEF,\
    CT_STD_VECTOR_IDENTIFIER\
)


#define STD_OPTIONAL(TYPE_DEF)(\
    STD_OPTIONAL,\
    (std, optional<T_QUALNAME(T_NAMETUPLE(TYPE_DEF))>),\
    BOOST_PP_EMPTY(),\
    BOOST_PP_EMPTY(),\
    BOOST_PP_EMPTY(),\
    TYPE_DEF,\
    CT_STD_OPTIONAL_IDENTIFIER\
)


#define CT_BOOLEAN TYPE_DEFINITION(\
    CT_BOOLEAN,\
    (core_types, boolean),\
    core_types::boolean_,\
    py::bool_\
)
#define CT_BOOLEAN_CONSTRUCTORS (CT_BOOLEAN)


#define CT_INT1 TYPE_DEFINITION(\
    CT_INT1,\
    (core_types, int1),\
    core_types::int1_,\
    py::int_\
)
#define CT_INT1_CONSTRUCTORS (CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT2 TYPE_DEFINITION(\
    CT_INT2,\
    (core_types, int2),\
    core_types::int2_,\
    py::int_\
)
#define CT_INT2_CONSTRUCTORS (CT_INT2)(CT_INT1)(CT_INT4)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT4 TYPE_DEFINITION(\
    CT_INT4,\
    (core_types, int4),\
    core_types::int4_,\
    py::int_\
)
#define CT_INT4_CONSTRUCTORS (CT_INT4)(CT_INT1)(CT_INT2)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT8 TYPE_DEFINITION(\
    CT_INT8,\
    (core_types, int8),\
    core_types::int8_,\
    py::int_\
)
#define CT_INT8_CONSTRUCTORS (CT_INT8)(CT_INT1)(CT_INT2)(CT_INT4)(CT_FLOAT4)(CT_FLOAT8)


#define CT_FLOAT4 TYPE_DEFINITION(\
    CT_FLOAT4,\
    (core_types, float4),\
    core_types::float4_,\
    py::float_\
)
#define CT_FLOAT4_CONSTRUCTORS (CT_FLOAT4)(CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT8)


#define CT_FLOAT8 TYPE_DEFINITION(\
    CT_FLOAT8,\
    (core_types, float8),\
    core_types::float8_,\
    py::float_\
)
#define CT_FLOAT8_CONSTRUCTORS (CT_FLOAT8)(CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT4)


#define CT_TEXT TYPE_DEFINITION(\
    CT_TEXT,\
    (core_types, text),\
    core_types::text_,\
    py::str\
)
#define CT_TEXT_CONSTRUCTORS (CT_TEXT)


#define CT_TIMESTAMPTZ TYPE_DEFINITION(\
    CT_TIMESTAMPTZ,\
    (core_types, timestamptz),\
    core_types::timestamptz_,\
    py::str\
)
#define CT_TIMESTAMPTZ_CONSTRUCTORS (CT_TIMESTAMPTZ)(CT_TEXT)


#define CT_DATE TYPE_DEFINITION(\
    CT_DATE,\
    (core_types, date),\
    core_types::date_,\
    py::str\
)
#define CT_DATE_CONSTRUCTORS (CT_DATE)(CT_TEXT)


// #define CT_TIMETZ TYPE_DEFINITION(
//     CT_TIMETZ,
//     (core_types, timetz_py),
//     py::str,
//     core_types::text
// )
// #define CT_TIMETZ_CONSTRUCTORS (CT_TIMETZ)

#endif
