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
    for(const T& elem : w)
    {
        oss << (ctr++ > 0 ? ", " : "") << tp_to_string(elem);
    }
    oss << "}";
    return oss.str();
}
template<typename T>//, typename = std::enable_if_t<is_vector<T>::value>>
std::string tp_to_string (const std::deque<T>& w)
{
    std::ostringstream oss;
    oss << "{";
    int ctr = 0;
    for(const T& elem : w)
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
    if constexpr (std::tuple_size<std::tuple<Rest...>>{} > 0)
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


// template<typename T> T tp_from_string (const std::string& value) { return T(value); }
// template <> int1 tp_from_string<int1> (const std::string& w) { return static_cast<int1>(std::stoi(w)); }
// template <> int2 tp_from_string<int2> (const std::string& w) { return static_cast<int2>(std::stoi(w)); }
// template <> int4 tp_from_string<int4> (const std::string& w) { return static_cast<int4>(std::stoi(w)); }
// template <> float4 tp_from_string<float4> (const std::string& w) { return static_cast<float4>(std::stod(text)); }
// template <> float8 tp_from_string<float8> (const std::string& w) { return static_cast<float8>(std::stod(text)); }
// template <> text tp_from_string<text> (const std::string& w) { return w; }
// template <> boolean tp_from_string<boolean> (const std::string& w) { return w == "true" ? boolean(1) : boolean(0); }
// template <> timestamptz tp_from_string<timestamptz> (const std::string& w)
// {
//     ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
//     return timestamptz(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
// }
// template <> date tp_from_string<date> (const std::string& w) { return (ct::date) dt::from_string(value); }


}


#endif
