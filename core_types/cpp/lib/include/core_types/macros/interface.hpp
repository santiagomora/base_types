#ifndef CORE_TYPES_MACROS_INTERFACE
#define CORE_TYPES_MACROS_INTERFACE
#include "core_types/macros/definition.hpp"
#include "core_types/macros/declaration.hpp"


#define IFACE_CPP_CLASSDEF_DECLARATION(CLASS_DEF)\
struct T_NAME(T_NAMETUPLE(CLASS_DEF))\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(CLASS_DEF));\
\
    BOOST_PP_SEQ_FOR_EACH(IFACE_CL_MEMBER_DECLARATION, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF))()\
    {}\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (\
        BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_ARGUMENT, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))\
    ) : \
    BOOST_PP_SEQ_FOR_EACH_I(CM_INITIALIZE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (const T_NAME(T_NAMETUPLE(CLASS_DEF))& other)\
    : \
    BOOST_PP_SEQ_FOR_EACH_I(CM_INITIALIZE, other, C_ALL_MEMBERS(CLASS_DEF))\
    {}\
\
    auto as_tuple() const\
    {\
        return std::make_tuple(BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
    }\
\
    T_QUALNAME(T_NAMETUPLE(CLASS_DEF)) wrapped() const\
    {\
        return {BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_VALUE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))};\
    }\
\
    static std::optional<py::object>& cls()\
    {\
        static std::optional<py::object> cls;\
        return cls;\
    }\
}


#define IFACE_CPP_ENUMDEF_DECLARATION(ENUM_DEF)\
struct T_NAME(T_IFACE_TYPE(ENUM_DEF)) : public core_types::interface::wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(ENUM_DEF));\
    using core_types::interface::wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>::wrapper;\
    T_NAME(T_IFACE_TYPE(ENUM_DEF))(const T_NAME(T_IFACE_TYPE(ENUM_DEF))& other) : wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>(other) {}\
    static std::optional<py::object>& cls()\
    {\
        static std::optional<py::object> cls;\
        return cls;\
    }\
}


#define IFACE_CPP_ALIASDEF_DECLARATION(ALIAS_DEF)\
struct T_NAME(T_IFACE_TYPE(ALIAS_DEF)) : public T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(ALIAS_DEF));\
    using T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))::T_NAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)));\
    \
    T_NAME(T_IFACE_TYPE(ALIAS_DEF))(const T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))& other) : T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))(other) {}\
    \
    T_NAME(T_IFACE_TYPE(ALIAS_DEF))(const T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))& other) : T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))(other) {}\
    static std::optional<py::object>& cls()\
    {\
        static std::optional<py::object> cls;\
        return cls;\
    }\
}



#endif
