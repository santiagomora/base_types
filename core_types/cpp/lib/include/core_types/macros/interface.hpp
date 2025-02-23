#ifndef CORE_TYPES_MACROS_INTERFACE
#define CORE_TYPES_MACROS_INTERFACE
#include "core_types/macros/definition.hpp"
#include "core_types/macros/declaration.hpp"


#define IFACE_CPP_CLASSDEF_DECLARATION(CLASS_DEF)\
struct T_NAME(T_NAMETUPLE(CLASS_DEF))\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(CLASS_DEF));\
    static core_types::interface::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> subclass_registry;\
\
    BOOST_PP_SEQ_FOR_EACH(IFACE_CL_MEMBER_DECLARATION, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))\
\
    T_QUALNAME(T_NAMETUPLE(CLASS_DEF)) value()\
    {\
        return {BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_VALUE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))};\
    }\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF))()\
    {}\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(IFACE_CL_MEMBER_ARGUMENT, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
    ) : \
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (const T_NAME(T_NAMETUPLE(CLASS_DEF))& other)\
    : \
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, other, C_ALL_MEMBERS(CLASS_DEF)))\
    {}\
    py::object to_py(std::string subclass_name) const\
    {\
        return T_QUALNAME(T_IFACE_TYPE(CLASS_DEF))::subclass_registry.to_py(subclass_name, BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
    }\
    std::string to_string () const\
    {\
        std::tuple<BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> tuple{BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))};\
        return core_types::interface::tp_to_string<BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))>(tuple);\
    }\
}


#define IFACE_CPP_ENUMDEF_DECLARATION(ENUM_DEF)\
struct T_NAME(T_IFACE_TYPE(ENUM_DEF)) : public core_types::interface::wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(ENUM_DEF));\
    static core_types::interface::py_subclass_registry<T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))> subclass_registry;\
    using core_types::interface::wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>::wrapper;\
\
    T_NAME(T_IFACE_TYPE(ENUM_DEF))(const T_NAME(T_IFACE_TYPE(ENUM_DEF))& other) : wrapper<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))>(other) {}\
\
    static std::string static_to_string(const T_QUALNAME(T_NAMETUPLE(ENUM_DEF)) value)\
    {\
        switch(value){\
            BOOST_PP_SEQ_FOR_EACH(ED_TO_STRING_CASE, T_QUALNAME(T_NAMETUPLE(ENUM_DEF)), T_MEMBERS(ENUM_DEF))\
        }\
        throw std::invalid_argument(std::string("invalid argument for ") + BOOST_PP_STRINGIZE(T_QUALNAME(T_NAMETUPLE(ENUM_DEF)) + " enum conversion"));\
    }\
    std::string to_string() const\
    {\
        return T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::static_to_string(value());\
    }\
    py::object to_py(std::string subclass_name) const\
    {\
        return T_QUALNAME(T_IFACE_TYPE(ENUM_DEF))::subclass_registry.to_py(subclass_name, *this);\
    }\
}


#define IFACE_CPP_ALIASDEF_DECLARATION(ALIAS_DEF)\
struct T_NAME(T_IFACE_TYPE(ALIAS_DEF)) : public T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))\
{\
    using Wrapped = T_QUALNAME(T_NAMETUPLE(ALIAS_DEF));\
    static core_types::interface::py_subclass_registry<BOOST_PP_IF(\
        T_IS_CLASSDEF_ALIAS(ALIAS_DEF),\
        BOOST_PP_SEQ_FOR_EACH_I(IFACE_CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(T_BASE(ALIAS_DEF))),\
        T_QUALNAME(T_IFACE_TYPE(T_ALIAS_ORIGIN(ALIAS_DEF)))\
    )>& subclass_registry;\
    using T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))::T_NAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)));\
    \
    T_NAME(T_IFACE_TYPE(ALIAS_DEF))(const T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))& other) : T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))(other) {}\
    \
    T_NAME(T_IFACE_TYPE(ALIAS_DEF))(const T_QUALNAME(T_IFACE_TYPE(ALIAS_DEF))& other) : T_QUALNAME(T_IFACE_TYPE(T_BASE(ALIAS_DEF)))(other) {}\
}



#endif
