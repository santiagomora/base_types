#ifndef BASE_TYPES_DEFINITION_BASE
#define BASE_TYPES_DEFINITION_BASE


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>


#define PLAIN_CLASS_DEFINITION(CLS, MEMBERS)\
    (CLS, MEMBERS)


#define COMPOSED_CLASS_DEFINITION(CLS, MEMBERS, BASES)\
    (CLS, MEMBERS, BASES)


#define ENUM_CLASS_DEFINITION(CLS, MEMBERS)\
    (CLS, MEMBERS)


#define ALIAS_CLASS_DEFINITION(CLS, BASE)\
    (CLS, BASE)


#define BASE_TYPE_DEFINITION(CLS, MEMBERS)\
    (CLS, MEMBERS)


#define ALIAS_BASE(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(1, CLASS_DEF)


#define CLASS(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(1, BOOST_PP_TUPLE_ELEM(0, CLASS_DEF))


#define NAMESPACE(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(0, BOOST_PP_TUPLE_ELEM(0, CLASS_DEF))


#define QUALNAME(CLASS_DEF)\
    NAMESPACE(CLASS_DEF)::CLASS(CLASS_DEF)


#define MEMBERS(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(1, CLASS_DEF)


#define BASES(CLASS_DEF)\
    BOOST_PP_TUPLE_ELEM(2, CLASS_DEF)


#define MEMBER_VALUE(r, data, elem)\
    (BOOST_PP_TUPLE_ELEM(1, elem))


#define MEMBER_NAME(r, data, elem)\
    (BOOST_PP_TUPLE_ELEM(1, elem))


#define INITIALIZE_CLASS_MEMBER(r, data, elem)\
    (BOOST_PP_TUPLE_ELEM(1, elem)(BOOST_PP_TUPLE_ELEM(1, elem)))


#define CONST_MEMBER_REF(r, data, elem)\
    (const BOOST_PP_TUPLE_ELEM(0, elem)& BOOST_PP_TUPLE_ELEM(1, elem))


#define CLASS_MEMBER_DECLARATION(r, data, elem)\
    BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_TUPLE_ELEM(1, elem) data


#define EXTRACT_MEMBERS_FROM_BASE_DEFINITION(r, data, elem)\
    MEMBERS(elem)


#define EXTRACT_CLASS_FROM_BASE_DEFINITION(r, data, elem)\
    CLASS(elem)


#define COMPOSED_MEMBERS(CLASS_DEF)\
    MEMBERS_FROM_BASES(BASES(CLASS_DEF)) MEMBERS(CLASS_DEF)


#define INHERIT_BASES(r, data, elem)\
    public QUALNAME(elem)


#define MEMBERS_FROM_BASES(BASES_DEF)\
    BOOST_PP_SEQ_FOR_EACH(EXTRACT_MEMBERS_FROM_BASE_DEFINITION, BOOST_PP_EMPTY(), BASES_DEF)


#define INITIALIZE_BASE(r, data, elem)\
    CLASS(elem)(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(MEMBER_NAME, BOOST_PP_EMPTY(), MEMBERS(elem))))


#define ENUM_VALUE(r, data, elem)\
    .value(BOOST_PP_STRINGIZE(elem), data::elem)


#endif
