#ifndef BASE_TYPES_DEFINITION_MACROS
#define BASE_TYPES_DEFINITION_MACROS


#include <boost/preprocessor.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/empty.hpp> 
#include <boost/preprocessor/stringize.hpp>
#include "./base.hpp"


#include <pybind11/pybind11.h>
namespace py = pybind11;


# define HAS_PY_REPRESENTATION(name, ...)\
private:\
    static py::object cls;\
public:\
    static void set_py_cls (py::object c) {\
        if (name::cls != Py_None){\
            std::string name = py::getattr(c, "__name__").cast<std::string>();\
            std::cout << "WARNING: py_cls already set for class \"" << name << "\". Skipping..." << std::endl;\
            return;\
        }\
        name::cls = c;\
    }\
    py::object to_py () const {\
        return name::cls(__VA_ARGS__);\
    }


#define PLAIN_DATACLASS(CLASS_DEF)\
class CLASS(CLASS_DEF) {\
HAS_PY_REPRESENTATION(CLASS(CLASS_DEF), BOOST_PP_SEQ_ENUM(\
    BOOST_PP_SEQ_FOR_EACH(MEMBER_NAME, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF)))\
)\
\
public:\
    BOOST_PP_SEQ_FOR_EACH(CLASS_MEMBER_DECLARATION, ;, MEMBERS(CLASS_DEF))\
    CLASS(CLASS_DEF) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(CLASS_MEMBER_DECLARATION, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF)))\
    ) : BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_FOR_EACH(INITIALIZE_CLASS_MEMBER, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF)))\
    {}\
}


#define COMPOSED_DATACLASS(CLASS_DEF)\
class CLASS(CLASS_DEF) : BOOST_PP_SEQ_ENUM(\
    BOOST_PP_SEQ_TRANSFORM(INHERIT_BASES, BOOST_PP_EMPTY(), BASES(CLASS_DEF))) {\
HAS_PY_REPRESENTATION(CLASS(CLASS_DEF), BOOST_PP_SEQ_ENUM(\
    BOOST_PP_SEQ_FOR_EACH(MEMBER_NAME, BOOST_PP_EMPTY(), COMPOSED_MEMBERS(CLASS_DEF))))\
\
public:\
    BOOST_PP_SEQ_FOR_EACH(CLASS_MEMBER_DECLARATION, ;, MEMBERS(CLASS_DEF))\
    CLASS(CLASS_DEF) (\
        BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(CLASS_MEMBER_DECLARATION, BOOST_PP_EMPTY(), COMPOSED_MEMBERS(CLASS_DEF)))\
    ) : BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_TRANSFORM(INITIALIZE_BASE, BOOST_PP_EMPTY(), BASES(CLASS_DEF)))\
        , BOOST_PP_SEQ_ENUM(\
            BOOST_PP_SEQ_FOR_EACH(INITIALIZE_CLASS_MEMBER, BOOST_PP_EMPTY(), MEMBERS(CLASS_DEF)))\
    {}\
}


#define ENUM(CLASS_DEF)\
enum CLASS(CLASS_DEF) {\
BOOST_PP_SEQ_ENUM(MEMBERS(CLASS_DEF))\
}


#define ALIAS(CLASS_DEF)\
class CLASS(CLASS_DEF) : public QUALNAME(ALIAS_BASE(CLASS_DEF)) {\
HAS_PY_REPRESENTATION(CLASS(CLASS_DEF), BOOST_PP_SEQ_ENUM(\
BOOST_PP_SEQ_FOR_EACH(MEMBER_NAME, BOOST_PP_EMPTY(), MEMBERS(ALIAS_BASE(CLASS_DEF)))))\
using QUALNAME(ALIAS_BASE(CLASS_DEF))::CLASS(ALIAS_BASE(CLASS_DEF));\
CLASS(CLASS_DEF)(const QUALNAME(ALIAS_BASE(CLASS_DEF))& other) : CLASS(ALIAS_BASE(CLASS_DEF))(other) {}\
}

#endif
