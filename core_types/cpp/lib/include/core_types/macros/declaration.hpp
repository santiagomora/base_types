#ifndef CORE_TYPES_MACROS_DECLARATION
#define CORE_TYPES_MACROS_DECLARATION
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/algorithm/string/find.hpp>
#include <sstream>


// NOTE METHODS
#define CL_INHERIT_BASE(r, data, elem)\
(public T_QUALNAME(T_NAMETUPLE(elem)))


#define CL_MEMBER_NAME(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define CL_ACCESS_MEMBER(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) data.CM_NAME(elem)


#define CL_MEMBER_TYPE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem)))


#define CL_UNDERLYING_MEMBER_TYPE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_QUALIFIED_UNDERLYING_CLASS(CM_TYPE(elem))


#define CL_MEMBER_VALUE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) core_types::interface::tp_unwrap(CM_NAME(elem))


#define CL_MEMBER_DECLARATION(r, data, elem)\
T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem))) CM_NAME(elem) = core_types::default_constructor<T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem)))>();


#define CL_UNDERLYING_MEMBER_DECLARATION(r, data, elem)\
T_QUALIFIED_UNDERLYING_CLASS(CM_TYPE(elem))& CM_NAME(elem);


#define CL_MEMBER_ARGUMENT(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) const T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem)))& CM_NAME(elem)


#define CL_UNDERLYING_MEMBER_ARGUMENT(r, data, elem)\
T_QUALIFIED_UNDERLYING_CLASS(CM_TYPE(elem)) CM_NAME(elem)


#define CL_MEMBER_NAME_T(r, data, elem)\
CM_NAME(elem)


#define CL_INITIALIZE_BASE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_NAME(T_NAMETUPLE(elem))(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(CL_MEMBER_NAME_T, BOOST_PP_EMPTY(), C_ALL_MEMBERS(elem))))


#define CL_INITIALIZE_EMPTY_BASE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_NAME(T_NAMETUPLE(elem))()


#define CL_INITIALIZE_BASE_COPY(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_NAME(T_NAMETUPLE(elem))(data)


#define CM_INITIALIZE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) CM_NAME(elem)(BOOST_PP_IF(BOOST_PP_IS_EMPTY(data), CM_NAME(elem), data.CM_NAME(elem)))


#define CM_INITIALIZE_EMPTY_MEMBER(r, data, elem)\
CM_NAME(elem)()


#define CM_COPY(r, data, elem)\
CM_NAME(elem) = data.CM_NAME(elem);


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


#define IFACE_CL_MEMBER_TYPE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))


#define IFACE_CL_MEMBER_DECLARATION(r, data, elem)\
T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem))) CM_NAME(elem);


#define IFACE_CL_MEMBER_ARGUMENT(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) const T_QUALNAME(T_IFACE_TYPE(CM_TYPE(elem)))& CM_NAME(elem)


#endif
