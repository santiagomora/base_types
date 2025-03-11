#ifndef CORE_TYPES_TYPING_INTERFACE
#define CORE_TYPES_TYPING_INTERFACE
#include "core_types/typing/definitions.hpp"
#include "core_types/typing/backend.hpp"
#include "core_types/macros/interface.hpp"


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


template<typename... Args>
struct py_subclass_registry
{
    py_subclass_registry ()
    {
        clsmap = new std::map<std::string, py::object>();
    }
    ~py_subclass_registry ()
    {
        delete clsmap;
    }
    void set_py_cls (std::string subclass_name, py::object cls) const
    {
        if (clsmap->contains(subclass_name)) {
            std::ostringstream err;
            err << "Context error: subclass_name \"" << subclass_name << "\" already assigned.";
            throw std::invalid_argument(err.str());
        }
        (*clsmap)[subclass_name] = cls;
    }
    py::object get_py_cls (std::string subclass_name) const
    {
        return (*clsmap)[subclass_name];
    }
    py::object to_py (std::string subclass_name, Args... args) const
    {
        return get_py_cls(subclass_name)(args...);
    }
private:
    std::map<std::string, py::object>* clsmap;
};


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
    std::string to_string () const
    {
        return ct::tp_to_string(wrapped());
    }
protected:
    std::unique_ptr<T> _value;
};


struct boolean : public wrapper<ct::boolean>
{
    using wrapper<ct::boolean>::wrapper;
    static py_subclass_registry<boolean> subclass_registry;
    boolean(const std::string text) : wrapper<ct::boolean>(_check_bool_value(text))
    {}
    boolean(const boolean& other) : wrapper<ct::boolean>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return boolean::subclass_registry.to_py(subclass_name, *this);
    }
};


struct int1 : public wrapper<ct::int1>
{
    using wrapper<ct::int1>::wrapper;
    static py_subclass_registry<int1> subclass_registry;
    // int1(long int v) : wrapper<ct::int1>(_check_value<ct::int1, long int>(v)) {}
    int1(const std::string text) : wrapper<ct::int1>(_check_value<ct::int1, long int>(std::stoi(text)))
    {}
    int1(const int1& other) : wrapper<ct::int1>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return int1::subclass_registry.to_py(subclass_name, *this);
    }
};


struct int2 : public wrapper<ct::int2>
{
    using wrapper<ct::int2>::wrapper;
    static py_subclass_registry<int2> subclass_registry;
    // int2(long int v) : wrapper<ct::int2>(_check_value<ct::int2, long int>(v)) {}
    int2(const std::string text) : wrapper<ct::int2>(_check_value<ct::int2, long int>(std::stoi(text)))
    {}
    int2(const int2& other) : wrapper<ct::int2>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return int2::subclass_registry.to_py(subclass_name, *this);
    }
};


struct int4 : public wrapper<ct::int4>
{
    using wrapper<ct::int4>::wrapper;
    static py_subclass_registry<int4> subclass_registry;
    // int4(long int v) : wrapper<ct::int4>(_check_value<ct::int4, long int>(v)) {}
    int4(const std::string text) : wrapper<ct::int4>(_check_value<ct::int4, long int>(std::stoi(text)))
    {}
    int4(const int4& other) : wrapper<ct::int4>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return int4::subclass_registry.to_py(subclass_name, *this);
    }
};


struct int8 : public wrapper<ct::int8>
{
    using wrapper<ct::int8>::wrapper;
    static py_subclass_registry<int8> subclass_registry;
    // int8(long int v) : wrapper<ct::int8>(_check_value<ct::int8, long int>(v)) {}
    int8(const std::string text) : wrapper<ct::int8>(_check_value<ct::int8, long int>(std::stoi(text)))
    {}
    int8(const int8& other) : wrapper<ct::int8>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return int8::subclass_registry.to_py(subclass_name, *this);
    }
};



struct float4 : public wrapper<ct::float4>
{
    using wrapper<ct::float4>::wrapper;
    // float4(double v) : wrapper<ct::float4>(_check_value<ct::float4, double>(v)) {}
    static py_subclass_registry<float4> subclass_registry;
    float4(const std::string text) : wrapper<ct::float4>(_check_value<ct::float4, double>(std::stod(text)))
    {}
    float4(const float4& other) : wrapper<ct::float4>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return float4::subclass_registry.to_py(subclass_name, *this);
    }
};


struct float8 : public wrapper<ct::float8>
{
    using wrapper<ct::float8>::wrapper;
    // float8(double v) : wrapper<ct::float8>(_check_value<ct::float8, double>(v)) {}
    static py_subclass_registry<float8> subclass_registry;
    float8(const std::string text) : wrapper<ct::float8>(_check_value<ct::float8, double>(std::stod(text)))
    {}
    float8(const float8& other) : wrapper<ct::float8>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return float8::subclass_registry.to_py(subclass_name, *this);
    }
};


struct text : public wrapper<ct::text>
{
    using wrapper<ct::text>::wrapper;
    static py_subclass_registry<text> subclass_registry;
    text(const text& other) : wrapper<ct::text>(other)
    {}
    py::object to_py(std::string subclass_name) const
    {
        return text::subclass_registry.to_py(subclass_name, *this);
    }
};


struct timestamptz : public wrapper<ct::timestamptz>
{
    using wrapper<ct::timestamptz>::wrapper;
    static py_subclass_registry<timestamptz> subclass_registry;
    timestamptz(const timestamptz& other) : wrapper<ct::timestamptz>(other) {}
    timestamptz(std::string value) : wrapper<ct::timestamptz>(timestamptz::parse_from_string(value))
    {}
    static ct::timestamptz parse_from_string (std::string value)
    {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return ct::timestamptz(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
    }
    py::object to_py(std::string subclass_name) const
    {
        return timestamptz::subclass_registry.to_py(subclass_name, *this);
    }
};


struct date : public wrapper<ct::date>
{
    using wrapper<ct::date>::wrapper;
    static py_subclass_registry<date> subclass_registry;
    date(const date& other) : wrapper<ct::date>(other)
    {}
    date(std::string value) : wrapper<ct::date>(date::parse_from_string(value))
    {}
    static ct::date parse_from_string (const std::string value)
    {
        return (ct::date) dt::from_string(value);
    }
    py::object to_py(std::string subclass_name) const
    {
        return date::subclass_registry.to_py(subclass_name, *this);
    }
};


// NOTE UNWRAP
template<typename V, typename... Rest> std::tuple<typename V::Wrapped, typename Rest::Wrapped...> tp_unwrap (
    const std::tuple<V, Rest...>& w
);
template <typename V> typename V::Wrapped tp_unwrap (
    V& w
) {
    return w.wrapped();
};
template <typename V> std::vector<typename V::Wrapped> tp_unwrap (
    std::vector<V> w
) {
    std::vector<typename V::Wrapped> v_res = {};
    for(auto& d : w)
    {
        v_res.emplace_back(tp_unwrap(d));
    }
    return v_res;
};
template <typename V> std::deque<typename V::Wrapped> tp_unwrap (
    std::deque<V> w
) {
    std::deque<typename V::Wrapped> v_res = {};
    for(auto& d : w)
    {
        v_res.emplace_back(tp_unwrap(d));
    }
    return v_res;
};
template <typename V> std::optional<typename V::Wrapped> tp_unwrap (
    std::optional<V> w
) {
    if (w.has_value())
    {
        return tp_unwrap(w.value());
    }
    return std::nullopt;
};
template<typename V, typename... Rest> std::tuple<typename V::Wrapped, typename Rest::Wrapped...> tp_unwrap (
    const std::tuple<V, Rest...>& w
) {
    auto v_first = std::get<0>(w);
    if constexpr (std::tuple_size<std::tuple<Rest...>>{} > 0)
    {
        auto v_tail = std::apply([](auto&, auto&... tail) {
            return std::make_tuple(tail...);
        }, w);
        return std::apply([&v_first](auto&&... tail) {
            return std::make_tuple(tp_unwrap(v_first), tail...);
        }, tp_unwrap(v_tail));
    }
    else
    {
        return std::make_tuple(tp_unwrap(v_first));
    }
}


// NOTE WRAP
template <typename> struct InnerType;
template <template <typename, typename...> class T, typename V, typename...Args> struct InnerType<T<V, Args...>> {
    using Head = V;
    using Tail = std::tuple<Args...>;
};

template<typename T, typename V> T tp_wrap_tuple (
    const V& w
);
template <typename T, typename V> T tp_wrap (
    const V& w
) {
    if constexpr(ct::is_tuple<T>::value && ct::is_tuple<V>::value)
    {
        return tp_wrap_tuple<T>(w);
    }
    else
    {
        return T(w);
    }
}
template<typename T, typename V> std::vector<T> tp_wrap (
    const std::vector<V>& w
) {
    std::vector<T> v_res = {};
    for(const V& elem : w)
    {
        v_res.emplace_back(tp_wrap<T>(elem));
    }
    return v_res;
}
template<typename T, typename V> std::deque<T> tp_wrap (
    const std::deque<V>& w
) {
    std::deque<T> v_res = {};
    for(const V& elem : w)
    {
        v_res.emplace_back(tp_wrap<T>(elem));
    }
    return v_res;
}
template<typename T, typename V> std::optional<T> tp_wrap (
    const std::optional<V>& w
) {
    if (!w.has_value())
    {
        return std::nullopt;
    }
    return tp_wrap<T>(w.value());
}
template<typename T, typename V> T tp_wrap_tuple (
    const V& w
) {
    using THead = InnerType<T>::Head;
    using TTail = InnerType<T>::Tail;
    auto v_first = std::get<0>(w);
    if constexpr (std::tuple_size<TTail>{} > 0)
    {
        auto v_tail = std::apply([](auto&, auto&... tail) {
            return std::make_tuple(tail...);
        }, w);
        return std::apply([&v_first](auto&&... tail) {
            return std::make_tuple(tp_wrap<THead>(v_first), tail...);
        }, tp_wrap_tuple<TTail>(v_tail));
    }
    else
    {
        return std::make_tuple(tp_wrap<THead>(v_first));
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
