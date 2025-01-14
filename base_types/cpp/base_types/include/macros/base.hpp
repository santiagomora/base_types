#ifndef BASE_TYPES_DEFINITION_BASE
#define BASE_TYPES_DEFINITION_BASE


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>


#define DATACLASS_MEMBER(TP_NAMESPACE, TP_NAME, NAME)(\
    (TP_NAMESPACE, TP_NAME),\
    NAME\
)

#define DATACLASS_DEFINITION(NAME, CLS, MEMBERS, BASES)(\
    NAME,\
    CLS,\
    MEMBERS,\
    BASES\
)

#define ENUM_MEMBER(NAME) NAME


#define ENUM_DEFINITION(NAME, CLS, MEMBERS)(\
    NAME,\
    CLS,\
    MEMBERS\
)


// #define ALIAS_DEFINITION(NAME, CLS, BASE)(
//     NAME,
//     CLS,
//     BASE
// )


#define TYPE_DEFINITION(NAME, CLS, PY_BASES, BASES)(\
    NAME,\
    CLS,\
    PY_BASES,\
    BASES\
)


// #define ALIAS_BASE(CLASS_DEF)
//     BOOST_PP_TUPLE_ELEM(1, CLASS_DEF)


#define T_MACRO_NAME(TYPE_DEF)\
    BOOST_PP_TUPLE_ELEM(0, TYPE_DEF)


#define T_NAMESPACE(NAMETUPLE)\
    BOOST_PP_TUPLE_ELEM(0, NAMETUPLE)


#define T_NAME(NAMETUPLE)\
    BOOST_PP_TUPLE_ELEM(1, NAMETUPLE)


#define T_NAMETUPLE(TYPE_DEF)\
    BOOST_PP_TUPLE_ELEM(1, TYPE_DEF)


#define T_QUALNAME(TYPE_DEF)\
    T_NAMESPACE(TYPE_DEF)::T_NAME(TYPE_DEF)


#define T_DIRECT_MEMBERS(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(2, CLASS_DEF)


#define T_BASES(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(3, CLASS_DEF)


#define CM_NAME(CLASS_MEMBER)\
    BOOST_PP_TUPLE_ELEM(1, CLASS_MEMBER)


#define CM_TYPE(CLASS_MEMBER)\
    BOOST_PP_TUPLE_ELEM(0, CLASS_MEMBER)


#define C_ALL_MEMBERS(CLASS_DEF)\
    BOOST_PP_SEQ_CAT((T_MACRO_NAME(CLASS_DEF))(_MEMBERS))


#endif
