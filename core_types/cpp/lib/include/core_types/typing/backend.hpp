#ifndef CORE_TYPES_TYPING_BACKEND
#define CORE_TYPES_TYPING_BACKEND
#include <magic_enum/magic_enum.hpp>
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

template <typename T, typename = void> struct is_tuple : std::false_type {};
template <typename... Args> struct is_tuple<std::tuple<Args...>> : std::true_type {};

template <typename, typename = std::void_t<>> struct has_as_tuple_method : std::false_type {};
template <typename T> struct has_as_tuple_method<T, std::void_t<decltype(std::declval<T>().as_tuple())>> : std::true_type {};


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
template<typename... Args> std::string tp_to_string (const std::tuple<Args...>& w);
template <typename T, typename = std::enable_if_t<std::is_enum<T>::value || has_as_tuple_method<T>::value>>
std::string tp_to_string (const T& w)
{
    if constexpr (std::is_enum<T>::value)
    {
        return std::string(magic_enum::enum_name(w));
    }
    else
    {
        return tp_to_string(w.as_tuple());
    }
}
template<typename T>//, typename = std::enable_if_t<is_vector<T>::value>>
std::string tp_to_string (const std::vector<T>& w)
{
    std::ostringstream oss;
    oss << "{";
    int ctr = 0;
    for(T elem : w)
    {
        oss << (ctr++ > 0 ? ", " : "") << tp_to_string(elem);
    }
    oss << "}";
    return oss.str();
}
template<typename T>//, typename = std::enable_if_t<is_optional<T>::value>>
std::string tp_to_string (const std::optional<T>& w)
{
    if (!w.has_value())
    {
        return "NULL";
    }
    return tp_to_string(w.value());
}
template<typename T, typename... Rest>
std::string tp_to_string (const std::tuple<T, Rest...>& w, int level)
{
    std::ostringstream oss;
    std::tuple<Rest...> tail = std::apply([](auto&, auto&... tail) {
        return std::make_tuple(tail...);
    }, w);
    T elem = std::get<0>(w);
    if (level == 0)
    {
        oss << "(";
    }
    oss << tp_to_string(elem);
    if constexpr(std::tuple_size<std::tuple<Rest...>>{} > 0)
    {
        oss << ", " << tp_to_string<Rest...>(tail, level+1);
    }
    else
    {
        oss << ")";
    }
    return oss.str();
}
template<typename... Args>
std::string tp_to_string (const std::tuple<Args...>& w)
{
    return tp_to_string(w, 0);
}

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
