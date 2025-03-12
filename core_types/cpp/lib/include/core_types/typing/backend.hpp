#ifndef CORE_TYPES_TYPING_BACKEND
#define CORE_TYPES_TYPING_BACKEND
#include <magic_enum/magic_enum.hpp>
#include "core_types/typing/definitions.hpp"
#include "core_types/macros/backend.hpp"


namespace py = pybind11;
namespace pt = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt = boost::gregorian;


// TODO add to_interface and to_backend free functions to convert types between their interface/backend types
namespace core_types
{

template <typename T> struct is_optional : std::false_type {};
template <typename T> struct is_optional<std::optional<T>> : std::true_type {};

template <typename T> struct is_vector : std::false_type {};
template <typename T> struct is_vector<std::vector<T>> : std::true_type {};

template <typename T> struct is_deque : std::false_type {};
template <typename T> struct is_deque<std::deque<T>> : std::true_type {};

template <typename T> struct is_tuple : std::false_type {};
template <typename... Args> struct is_tuple<std::tuple<Args...>> : std::true_type {};

template <typename, typename = std::void_t<>> struct has_as_tuple_method : std::false_type {};
template <typename T> struct has_as_tuple_method<T, std::void_t<decltype(std::declval<T>().as_tuple())>> : std::true_type {};

template <typename, typename = std::void_t<>> struct has_wrapped_method : std::false_type {};
template <typename T> struct has_wrapped_method<T, std::void_t<decltype(std::declval<T>().wrapped())>> : std::true_type {};


CPP_TYPEDEF_DECLARATION(CT_BOOLEAN);
CPP_TYPEDEF_DECLARATION(CT_INT1);
CPP_TYPEDEF_DECLARATION(CT_INT2);
CPP_TYPEDEF_DECLARATION(CT_INT4);
CPP_TYPEDEF_DECLARATION(CT_INT8);
CPP_TYPEDEF_DECLARATION(CT_FLOAT4);
CPP_TYPEDEF_DECLARATION(CT_FLOAT8);
CPP_TYPEDEF_DECLARATION(CT_TEXT);
CPP_TYPEDEF_DECLARATION(CT_TIMESTAMPTZ);
CPP_TYPEDEF_DECLARATION(CT_DATE);


std::string to_str (const int1& w);
std::string to_str (const int2& w);
std::string to_str (const int4& w);
std::string to_str (const int8& w);
std::string to_str (const float4& w);
std::string to_str (const float8& w);
std::string to_str (const text& w);
std::string to_str (const boolean& w);
std::string to_str (const timestamptz& w, const std::string format);
std::string to_str (const timestamptz& w);
std::string to_str (const date& w);
template<typename... Args> std::string to_str (const std::tuple<Args...>& w);
template <typename T, typename = std::enable_if_t<std::is_enum<T>::value || has_as_tuple_method<T>::value || has_wrapped_method<T>::value>>
std::string to_str (const T& w)
{
    if constexpr (std::is_enum<T>::value)
    {
        return std::string(magic_enum::enum_name(w));
    }
    else if constexpr (has_wrapped_method<T>::value)
    {
        return to_str(w.wrapped());
    }
    else
    {
        return to_str(w.as_tuple());
    }
}
template<typename T>//, typename = std::enable_if_t<is_vector<T>::value>>
std::string to_str (const std::vector<T>& w)
{
    std::ostringstream oss;
    oss << "{";
    int ctr = 0;
    for(const T& elem : w)
    {
        oss << (ctr++ > 0 ? ", " : "") << to_str(elem);
    }
    oss << "}";
    return oss.str();
}
template<typename T>//, typename = std::enable_if_t<is_vector<T>::value>>
std::string to_str (const std::deque<T>& w)
{
    std::ostringstream oss;
    oss << "{";
    int ctr = 0;
    for(const T& elem : w)
    {
        oss << (ctr++ > 0 ? ", " : "") << to_str(elem);
    }
    oss << "}";
    return oss.str();
}
template<typename T>//, typename = std::enable_if_t<is_optional<T>::value>>
std::string to_str (const std::optional<T>& w)
{
    if (!w.has_value())
    {
        return "NULL";
    }
    return to_str(w.value());
}
template<typename T, typename... Rest>
std::string to_str (const std::tuple<T, Rest...>& w, int level)
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
    oss << to_str(elem);
    if constexpr (std::tuple_size<std::tuple<Rest...>>{} > 0)
    {
        oss << ", " << to_str<Rest...>(tail, level+1);
    }
    else
    {
        oss << ")";
    }
    return oss.str();
}
template<typename... Args>
std::string to_str (const std::tuple<Args...>& w)
{
    return to_str(w, 0);
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
