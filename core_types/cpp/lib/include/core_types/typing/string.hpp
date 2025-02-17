#ifndef CORE_TYPES_TYPING_STRING
#define CORE_TYPES_TYPING_STRING
#include "core_types/typing/types.hpp"


namespace core_types
{

template<typename T,  typename = std::enable_if_t<!(is_vector<T>::value || is_optional<T>::value)>>
std::string tp_to_string (const T& w)
{
    return w.to_string();
}

template<typename T>
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

template<typename T>
std::string tp_to_string (const std::optional<T>& w)
{
    if (!w.has_value())
    {
        return "NULL";
    }
    return tp_to_string<T>(w.value());
}


template<typename T>
std::string tp_to_string (const std::tuple<T>& w)
{
    return tp_to_string(std::get<0>(w));
}


template<typename T, typename... Rest>
std::string tp_to_string (const std::tuple<T, Rest...>& w)
{
    std::ostringstream oss;
    std::tuple<Rest...> tail = std::apply([](auto&, auto&... tail) {
        return std::make_tuple(tail...);
    }, w);
    oss << tp_to_string(std::get<0>(w)) << ", " << tp_to_string<Rest...>(tail);
    return oss.str();
}

}



#endif
