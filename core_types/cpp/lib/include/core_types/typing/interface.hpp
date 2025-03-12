#ifndef CORE_TYPES_TYPING_INTERFACE
#define CORE_TYPES_TYPING_INTERFACE
#include "core_types/typing/definitions.hpp"
#include "core_types/typing/backend.hpp"
#include "core_types/macros/interface.hpp"
#include <stdexcept>


namespace ct = core_types;
namespace py = pybind11;


// TODO remove py_subclass_registry and substitute with a single py::object. I think a map is not needed
namespace core_types::interface
{

template <typename T, typename Enable=void> struct extracts_underlying { using underlying = T; };
template <typename T> struct extracts_underlying<std::vector<T>> { using underlying = T; };
template <typename T> struct extracts_underlying<std::deque<T>> { using underlying = T; };
template <typename T> struct extracts_underlying<std::optional<T>> { using underlying = T; };

template <typename T>
struct describe_type : extracts_underlying<T>
{
    static constexpr std::string_view container_name =
        ct::is_vector<T>::value ? "vector" :
        ct::is_deque<T>::value ? "deque" :
        ct::is_optional<T>::value ? "optional": "none";
};


template <typename, typename = std::void_t<>> struct HasWrapped : std::false_type {};
template <typename T> struct HasWrapped<T, std::void_t<typename T::Wrapped>> : std::true_type {};


template <typename T, typename V>
T _check_value (V value) 
{
    if(value < std::numeric_limits<T>::min() || value > std::numeric_limits<T>::max())
    {
        throw std::out_of_range("Value out of range");
    }
    return static_cast<T>(value);
};
bool _check_bool_value (const std::string& value);


template <typename T>
struct wrapper
{
    using Wrapped = T;
    wrapper ()
    {}
    wrapper (T value)
    {
        _value = std::unique_ptr<T>(new T(value));
    }
    wrapper (const wrapper<T>& other)
    {
        _value = std::unique_ptr<T>(new T(other.wrapped()));
    }
    template<typename V>
    int compare (const wrapper<V>& other) const
    {
        return compare_<T, V>(*this, other);
    }
    T& wrapped () const
    {
        return *(_value.get());
    }
protected:
    std::unique_ptr<T> _value;
};


struct boolean : public wrapper<ct::boolean>
{
    using wrapper<ct::boolean>::wrapper;
    boolean(const std::string text) : wrapper<ct::boolean>(_check_bool_value(text))
    {}
    boolean(const boolean& other) : wrapper<ct::boolean>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct int1 : public wrapper<ct::int1>
{
    using wrapper<ct::int1>::wrapper;
    // int1(long int v) : wrapper<ct::int1>(_check_value<ct::int1, long int>(v)) {}
    int1(const std::string text) : wrapper<ct::int1>(_check_value<ct::int1, long int>(std::stoi(text)))
    {}
    int1(const int1& other) : wrapper<ct::int1>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct int2 : public wrapper<ct::int2>
{
    using wrapper<ct::int2>::wrapper;
    // int2(long int v) : wrapper<ct::int2>(_check_value<ct::int2, long int>(v)) {}
    int2(const std::string text) : wrapper<ct::int2>(_check_value<ct::int2, long int>(std::stoi(text)))
    {}
    int2(const int2& other) : wrapper<ct::int2>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct int4 : public wrapper<ct::int4>
{
    using wrapper<ct::int4>::wrapper;
    // int4(long int v) : wrapper<ct::int4>(_check_value<ct::int4, long int>(v)) {}
    int4(const std::string text) : wrapper<ct::int4>(_check_value<ct::int4, long int>(std::stoi(text)))
    {}
    int4(const int4& other) : wrapper<ct::int4>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct int8 : public wrapper<ct::int8>
{
    using wrapper<ct::int8>::wrapper;
    // int8(long int v) : wrapper<ct::int8>(_check_value<ct::int8, long int>(v)) {}
    int8(const std::string text) : wrapper<ct::int8>(_check_value<ct::int8, long int>(std::stoi(text)))
    {}
    int8(const int8& other) : wrapper<ct::int8>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};



struct float4 : public wrapper<ct::float4>
{
    using wrapper<ct::float4>::wrapper;
    // float4(double v) : wrapper<ct::float4>(_check_value<ct::float4, double>(v)) {}
    float4(const std::string text) : wrapper<ct::float4>(_check_value<ct::float4, double>(std::stod(text)))
    {}
    float4(const float4& other) : wrapper<ct::float4>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct float8 : public wrapper<ct::float8>
{
    using wrapper<ct::float8>::wrapper;
    // float8(double v) : wrapper<ct::float8>(_check_value<ct::float8, double>(v)) {}
    float8(const std::string text) : wrapper<ct::float8>(_check_value<ct::float8, double>(std::stod(text)))
    {}
    float8(const float8& other) : wrapper<ct::float8>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct text : public wrapper<ct::text>
{
    using wrapper<ct::text>::wrapper;
    text(const text& other) : wrapper<ct::text>(other)
    {}
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct timestamptz : public wrapper<ct::timestamptz>
{
    using wrapper<ct::timestamptz>::wrapper;
    timestamptz(const timestamptz& other) : wrapper<ct::timestamptz>(other) {}
    timestamptz(std::string value) : wrapper<ct::timestamptz>(timestamptz::parse_from_string(value))
    {}
    static ct::timestamptz parse_from_string (std::string value)
    {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return ct::timestamptz(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
    }
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


struct date : public wrapper<ct::date>
{
    using wrapper<ct::date>::wrapper;
    date(const date& other) : wrapper<ct::date>(other)
    {}
    date(std::string value) : wrapper<ct::date>(date::parse_from_string(value))
    {}
    static ct::date parse_from_string (const std::string value)
    {
        return (ct::date) dt::from_string(value);
    }
    static std::optional<py::object>& cls()
    {
        static std::optional<py::object> cls;
        return cls;
    }
};


// NOTE UNWRAP
template<typename V, typename... Rest> std::tuple<typename V::Wrapped, typename Rest::Wrapped...> unwrap (
    const std::tuple<V, Rest...>& w
);
template <typename V> typename V::Wrapped unwrap (
    V& w
) {
    return w.wrapped();
};
template <typename V> std::vector<typename V::Wrapped> unwrap (
    std::vector<V> w
) {
    std::vector<typename V::Wrapped> v_res = {};
    for(auto& d : w)
    {
        v_res.emplace_back(unwrap(d));
    }
    return v_res;
};
template <typename V> std::deque<typename V::Wrapped> unwrap (
    std::deque<V> w
) {
    std::deque<typename V::Wrapped> v_res = {};
    for(auto& d : w)
    {
        v_res.emplace_back(unwrap(d));
    }
    return v_res;
};
template <typename V> std::optional<typename V::Wrapped> unwrap (
    std::optional<V> w
) {
    if (w.has_value())
    {
        return unwrap(w.value());
    }
    return std::nullopt;
};
template<typename V, typename... Rest> std::tuple<typename V::Wrapped, typename Rest::Wrapped...> unwrap (
    const std::tuple<V, Rest...>& w
) {
    auto v_first = std::get<0>(w);
    if constexpr (std::tuple_size<std::tuple<Rest...>>{} > 0)
    {
        auto v_tail = std::apply([](auto&, auto&... tail) {
            return std::make_tuple(tail...);
        }, w);
        return std::apply([&v_first](auto&&... tail) {
            return std::make_tuple(unwrap(v_first), tail...);
        }, unwrap(v_tail));
    }
    else
    {
        return std::make_tuple(unwrap(v_first));
    }
}


// NOTE WRAP
template <typename> struct TupleHeadTailType;
template <template <typename, typename...> class T, typename V, typename...Args> struct TupleHeadTailType<T<V, Args...>> {
    using Head = V;
    using Tail = std::tuple<Args...>;
};
template<typename T, typename V> T wrap_tuple (
    const V& w
);
template <typename T, typename V> T wrap (
    const V& w
) {
    if constexpr(ct::is_tuple<T>::value && ct::is_tuple<V>::value)
    {
        return wrap_tuple<T>(w);
    }
    else
    {
        return T(w);
    }
}
template<typename T, typename V> std::vector<T> wrap (
    const std::vector<V>& w
) {
    std::vector<T> v_res = {};
    for(const V& elem : w)
    {
        v_res.emplace_back(wrap<T>(elem));
    }
    return v_res;
}
template<typename T, typename V> std::deque<T> wrap (
    const std::deque<V>& w
) {
    std::deque<T> v_res = {};
    for(const V& elem : w)
    {
        v_res.emplace_back(wrap<T>(elem));
    }
    return v_res;
}
template<typename T, typename V> std::optional<T> wrap (
    const std::optional<V>& w
) {
    if (!w.has_value())
    {
        return std::nullopt;
    }
    return wrap<T>(w.value());
}
template<typename T, typename V> T wrap_tuple (
    const V& w
) {
    using THead = TupleHeadTailType<T>::Head;
    using TTail = TupleHeadTailType<T>::Tail;
    auto v_first = std::get<0>(w);
    if constexpr (std::tuple_size<TTail>{} > 0)
    {
        auto v_tail = std::apply([](auto&, auto&... tail) {
            return std::make_tuple(tail...);
        }, w);
        return std::apply([&v_first](auto&&... tail) {
            return std::make_tuple(wrap<THead>(v_first), tail...);
        }, wrap_tuple<TTail>(v_tail));
    }
    else
    {
        return std::make_tuple(wrap<THead>(v_first));
    }
}


// NOTE TO_PY
struct cpp_py_class_mapping
{
template <typename T> static void set (
    py::object cls
) {
    if (T::cls().has_value())
    {
        std::ostringstream v_msg;
        v_msg << "Type \"" << boost::typeindex::type_id<T>().pretty_name() << "\" cls already set.";
        throw std::invalid_argument(v_msg.str());
    }
    T::cls() = cls;
}
template <typename T> static py::object& get ()
{
    if (!T::cls().has_value())
    {
        std::ostringstream v_msg;
        v_msg << "Type \"" << boost::typeindex::type_id<T>().pretty_name() << "\" cls not assigned.";
        throw std::invalid_argument(v_msg.str());
    }
    return T::cls().value();
}
};
template<typename T, typename... Rest> auto to_py (
    const std::tuple<T, Rest...>& w
);
template <typename T> py::object to_py (
    const T& obj
) {
    py::object cls = py::type::of<T>().attr("get_py_cls")();
    if constexpr (has_as_tuple_method<T>::value)
    {
        return std::apply([&cls](auto&&... args){ return cls(to_py(args)...); }, obj.as_tuple());
    }
    else
    {
        return cls(obj);
    }
}
template<typename T> std::vector<py::object> to_py (
    const std::vector<T>& w
) {
    std::vector<py::object> v_res = {};
    for(const T& elem : w)
    {
        v_res.emplace_back(to_py(elem));
    }
    return v_res;
}
template<typename T> std::deque<py::object> to_py (
    const std::deque<T>& w
) {
    std::deque<T> v_res = {};
    for(const T& elem : w)
    {
        v_res.emplace_back(to_py(elem));
    }
    return v_res;
}
template<typename T> std::optional<py::object> to_py (
    const std::optional<T>& w
) {
    if (!w.has_value())
    {
        return std::nullopt;
    }
    return to_py(w.value());
}
template<typename T, typename... Rest> auto to_py (
    const std::tuple<T, Rest...>& w
) {
    auto v_first = std::get<0>(w);
    if constexpr (std::tuple_size<std::tuple<Rest...>>{} > 0)
    {
        auto v_tail = std::apply([](auto&, auto&... tail) {
            return std::make_tuple(tail...);
        }, w);
        return std::apply([&v_first](auto&&... tail) {
            return std::make_tuple(to_py(v_first), tail...);
        }, to_py(v_tail));
    }
    else
    {
        return std::make_tuple(to_py(v_first));
    }
}


// NOTE COMPARE
template<
typename T, typename V, typename = std::enable_if_t<
    (std::is_arithmetic_v<T> && std::is_arithmetic_v<V>) ||
    (std::is_same_v<T, V>)
>>
bool cmp_greater_(T t, V v) { return t > v; }
bool cmp_greater_(ct::timestamptz t, ct::text v);
bool cmp_greater_(ct::date t, ct::text v);


template<
typename T, typename V, typename = std::enable_if_t<
    (std::is_arithmetic_v<T> && std::is_arithmetic_v<V>) ||
    (std::is_same_v<T, V>)
>>
bool cmp_less_(T t, V v) { return t < v; }
bool cmp_less_(ct::timestamptz t, ct::text v);
bool cmp_less_(ct::date t, ct::text v);


template<typename T, typename V> int compare_ (
    const wrapper<T>& t, const wrapper<V>& v
) {
    if  (cmp_less_(t.wrapped(), v.wrapped())) {
        return -1;
    } else if (cmp_greater_(t.wrapped(), v.wrapped())) {
        return 1;
    }
    return 0;
}

}

#endif
