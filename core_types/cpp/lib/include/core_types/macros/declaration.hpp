#ifndef CORE_TYPES_MACROS_DECLARATION
#define CORE_TYPES_MACROS_DECLARATION
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/algorithm/string/find.hpp>
#include <sstream>
#include "core_types/macros/definition.hpp"
#include "core_types/typing/string.hpp"


// NOTE METHODS
#define CL_INHERIT_BASE(r, data, elem)\
(public T_QUALNAME(T_NAMETUPLE(elem)))


#define CL_MEMBER_NAME(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) CM_NAME(elem)


#define CL_ACCESS_MEMBER(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) data.CM_NAME(elem)


#define CL_MEMBER_TYPE(r, data, i, elem)\
BOOST_PP_COMMA_IF(i) T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem)))


#define CL_MEMBER_DECLARATION(r, data, elem)\
T_QUALNAME(T_NAMETUPLE(CM_TYPE(elem))) CM_NAME(elem) data


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


#define CL_PRIMITIVE_ACCESSOR(THIS, TYPEDEF)\
T_BASE_PRIMITIVE(CM_TYPE(TYPEDEF))& CM_NAME(TYPEDEF) ()\
{\
    return THIS->CM_NAME(TYPEDEF).value();\
};


#define CL_DATACLASS_ACCESSOR(THIS, CLASSDEF)\
T_QUALNAME(T_NAMETUPLE(CM_TYPE(CLASSDEF)))& CM_NAME(CLASSDEF) ()\
{\
    return THIS->CM_NAME(CLASSDEF);\
};


#define CL_GENERATE_PROXY_ACCESSOR(r, data, elem)\
BOOST_PP_IF(\
    BOOST_PP_IS_EMPTY(T_BASE_PRIMITIVE(CM_TYPE(elem))),\
    CL_DATACLASS_ACCESSOR(data, elem),\
    CL_PRIMITIVE_ACCESSOR(data, elem)\
)


#define CPP_CLASSDEF_DECLARATION(CLASS_DEF)\
class T_NAME(T_NAMETUPLE(CLASS_DEF))\
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASE(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (: BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CL_INHERIT_BASE, BOOST_PP_EMPTY(), T_BASE(CLASS_DEF)))))\
    )\
{\
public:\
    struct Proxy\
    {\
        T_NAME(T_NAMETUPLE(CLASS_DEF))* parent;\
        Proxy(T_NAME(T_NAMETUPLE(CLASS_DEF))* parent)\
        : parent(parent)\
        {};\
        BOOST_PP_SEQ_FOR_EACH(CL_GENERATE_PROXY_ACCESSOR, parent, C_ALL_MEMBERS(CLASS_DEF))\
    };\
    std::optional<std::shared_ptr<Proxy>> proxy;\
    std::shared_ptr<Proxy> operator->()\
    {\
        if (proxy.has_value())\
        {\
            return proxy.value();\
        }\
        proxy = std::shared_ptr<Proxy>(new Proxy(this));\
        return proxy.value();\
    }\
    static core_types::py_subclass_registry<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> subclass_registry;\
    BOOST_PP_SEQ_FOR_EACH(CL_MEMBER_DECLARATION, ;, T_MEMBERS(CLASS_DEF))\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF))()\
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASE(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (: BOOST_PP_SEQ_FOR_EACH_I(CL_INITIALIZE_EMPTY_BASE, BOOST_PP_EMPTY(), T_BASE(CLASS_DEF)))\
    ))\
    {}\
\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(CL_MEMBER_DECLARATION, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)))\
    ) : \
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASE(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (BOOST_PP_SEQ_FOR_EACH(CL_INITIALIZE_BASE, BOOST_PP_EMPTY(), T_BASE(CLASS_DEF)))\
    ))\
\
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, BOOST_PP_EMPTY(), T_MEMBERS(CLASS_DEF)))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF)) (const T_NAME(T_NAMETUPLE(CLASS_DEF))& other)\
    : \
    BOOST_PP_TUPLE_ENUM(BOOST_PP_IF(\
        BOOST_PP_IS_EMPTY(T_BASE(CLASS_DEF)),\
        (BOOST_PP_EMPTY()),\
        (BOOST_PP_SEQ_FOR_EACH(CL_INITIALIZE_BASE_COPY, other, T_BASE(CLASS_DEF)))\
    ))\
    BOOST_PP_SEQ_ENUM(\
        BOOST_PP_SEQ_TRANSFORM(CM_INITIALIZE, other, T_MEMBERS(CLASS_DEF)))\
    {}\
    T_NAME(T_NAMETUPLE(CLASS_DEF))& operator=(const T_NAME(T_NAMETUPLE(CLASS_DEF))& other) {\
        BOOST_PP_SEQ_FOR_EACH(CM_COPY, other, C_ALL_MEMBERS(CLASS_DEF))\
        return *this;\
    }\
    py::object to_py(std::string subclass_name) const {\
        return T_QUALNAME(T_NAMETUPLE(CLASS_DEF))::subclass_registry.to_py(subclass_name, BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF)));\
    }\
    std::string to_string () const {\
        std::tuple<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))> tuple{BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_NAME, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))};\
        return core_types::tp_to_string<BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(CLASS_DEF))>(tuple);\
    }\
}


#define CPP_ENUMDEF_DECLARATION(ENUM_DEF)\
enum ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF) {\
BOOST_PP_SEQ_ENUM(ENUM_MEMBERS(ENUM_DEF))\
};\
class T_NAME(T_NAMETUPLE(ENUM_DEF)) : public core_types::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>\
{\
public:\
    static core_types::py_subclass_registry<T_QUALNAME(T_NAMETUPLE(ENUM_DEF))> subclass_registry;\
    using core_types::wrapper<ENUM_UNQUALIFIED_UNDERLYING_CLASS(ENUM_DEF)>::wrapper;\
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
class T_NAME(T_NAMETUPLE(ALIAS_DEF)) : public T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF))) {\
public:\
static core_types::py_subclass_registry<BOOST_PP_IF(\
    BOOST_PP_IS_EMPTY(T_BASE_PRIMITIVE(ALIAS_DEF)),\
    BOOST_PP_SEQ_FOR_EACH_I(CL_MEMBER_TYPE, BOOST_PP_EMPTY(), C_ALL_MEMBERS(T_BASE(ALIAS_DEF))),\
    T_QUALNAME(T_NAMETUPLE(T_ALIAS_ORIGIN(ALIAS_DEF)))\
)>& subclass_registry;\
using T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))::T_NAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)));\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))(const T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))& other) : T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))(other) {}\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))(const T_QUALNAME(T_NAMETUPLE(ALIAS_DEF))& other) : T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))(other) {}\
\
T_NAME(T_NAMETUPLE(ALIAS_DEF))& operator=(const T_NAME(T_NAMETUPLE(ALIAS_DEF))& other) {\
    T_QUALNAME(T_NAMETUPLE(T_BASE(ALIAS_DEF)))::operator=(other);\
    return *this;\
}\
}



#endif
