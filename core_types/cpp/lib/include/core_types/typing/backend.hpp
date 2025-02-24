#ifndef CORE_TYPES_TYPING_BACKEND
#define CORE_TYPES_TYPING_BACKEND
#include "core_types/typing/definitions.hpp"
#include "core_types/macros/backend.hpp"


namespace py = pybind11;
namespace pt = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt = boost::gregorian;


namespace core_types
{

template <typename T> struct is_optional : std::false_type {};
template <typename T> struct is_optional<std::optional<T>> : std::true_type {};

template <typename T> struct is_vector : std::false_type {};
template <typename T> struct is_vector<std::vector<T>> : std::true_type {};

CPP_TYPEDEF_DECLARATION(CT_BOOLEAN);
CPP_TYPEDEF_DECLARATION(CT_INT1);
CPP_TYPEDEF_DECLARATION(CT_INT2);
CPP_TYPEDEF_DECLARATION(CT_INT4);
CPP_TYPEDEF_DECLARATION(CT_INT8);
CPP_TYPEDEF_DECLARATION(CT_FLOAT4);
CPP_TYPEDEF_DECLARATION(CT_FLOAT8);
CPP_TYPEDEF_DECLARATION(CT_TEXT);
CPP_TYPEDEF_DECLARATION(CT_TIMESTAMPTZ);
// CPP_TYPEDEF_DECLARATION(CT_TIMETZ);
CPP_TYPEDEF_DECLARATION(CT_DATE);


std::string tp_to_string (const int1& w);
std::string tp_to_string (const int2& w);
std::string tp_to_string (const int4& w);
std::string tp_to_string (const int8& w);
std::string tp_to_string (const float4& w);
std::string tp_to_string (const float8& w);
std::string tp_to_string (const text& w);
std::string tp_to_string (const boolean& w);
std::string tp_to_string (const timestamptz& w, const std::string format);
std::string tp_to_string (const timestamptz& w);
std::string tp_to_string (const date& w);

timestamptz utcnow();
timestamptz now(const ldt::time_zone_ptr&);

template<typename T> T default_constructor ()
{
    if constexpr(is_optional<T>::value)
    {
        return std::nullopt;
    }
    return T{};
}
template<> timestamptz default_constructor<timestamptz>();
}


#endif
