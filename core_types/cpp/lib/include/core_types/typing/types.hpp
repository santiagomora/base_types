# ifndef CORE_TYPES_TYPING_TYPES
# define CORE_TYPES_TYPING_TYPES
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <limits>
#include <map>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <type_traits>
#include <optional>
#include "core_types/typing/definitions.hpp"


namespace py = pybind11;
namespace pt = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt = boost::gregorian;


namespace core_types
{


typedef int8_t int1_;
typedef int16_t int2_;
typedef int32_t int4_;
typedef int64_t int8_;
typedef float float4_;
typedef double float8_;
typedef std::string text_;
typedef ldt::local_date_time timestamptz_;
// typedef pt::ptime timetz_;
typedef dt::date date_;
typedef bool boolean_;


template<typename... Args>
class py_subclass_registry
{
private:
    std::map<std::string, py::object>* clsmap;

public:
    py_subclass_registry () {
        clsmap = new std::map<std::string, py::object>();
    }
    ~py_subclass_registry () {
        delete clsmap;
    }
    void set_py_cls (std::string subclass_name, py::object cls) const {
        if (clsmap->contains(subclass_name)) {
            std::ostringstream err;
            err << "Context error: subclass_name \"" << subclass_name << "\" already assigned.";
            throw std::invalid_argument(err.str());
        }
        (*clsmap)[subclass_name] = cls;
    }
    py::object get_py_cls (std::string subclass_name) const {
        return (*clsmap)[subclass_name];
    }
    py::object to_py (std::string subclass_name, Args... args) const {
        return get_py_cls(subclass_name)(args...);
    }
};


template <typename T>
struct is_optional : std::false_type
{};
template <typename T>
struct is_optional<std::optional<T>> : std::true_type
{};


template <typename T>
struct is_vector : std::false_type
{};
template <typename T>
struct is_vector<std::vector<T>> : std::true_type
{};



template <typename T>
struct py_determine_container
{
    static constexpr std::string_view value =
        is_vector<T>::value ? "vector" :
        is_optional<T>::value ? "optional": "none";
};


template <typename T>
class wrapper
{
protected:
    std::shared_ptr<T> _value;
public:
    wrapper () {}
    wrapper (T value) {
        _value = std::shared_ptr<T>(new T(value));
    }
    wrapper (const wrapper<T>& other) {
        // increases reference count
        _value = other.wrapped_ptr();
    }
    std::shared_ptr<T> wrapped_ptr () const {
        return _value;
    }
    T& value () const {
        return *(_value.get());
    }
    template<typename V>
    int compare (const wrapper<V>& other) const {
        return compare_<T, V>(*this, other);
    }
    const T& operator*() const {
        return value();
    }
};


template <typename T, typename V>
T _check_value (V value) {
    if(value < std::numeric_limits<T>::min() || value > std::numeric_limits<T>::max()){
        throw std::out_of_range("Value out of range");
    }
    return static_cast<T>(value);
};


class boolean : public wrapper<boolean_>
{
private:
    bool check_value (const std::string& value) const {
        if(value != "true" || value != "false"){
            throw std::out_of_range("Invalid boolean value");
        }
        return value != "true" ? false : true;
    }
public:
    using wrapper<boolean_>::wrapper;
    static py_subclass_registry<boolean> subclass_registry;
    boolean(const std::string text) : wrapper<boolean_>(check_value(text)) {}
    boolean(const boolean& other) : wrapper<boolean_>(other) {}
    boolean& operator=(const boolean& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return this->value() ? "true" : "false";
    }
    py::object to_py(std::string subclass_name) const {
        return boolean::subclass_registry.to_py(subclass_name, *this);
    }
};


class int1 : public wrapper<int1_>
{
public:
    using wrapper<int1_>::wrapper;
    static py_subclass_registry<int1> subclass_registry;
    // int1(long int v) : wrapper<int1_>(_check_value<int1_, long int>(v)) {}
    int1(const std::string text) : wrapper<int1_>(_check_value<int1_, long int>(std::stoi(text))) {}
    int1(const int1& other) : wrapper<int1_>(other) {}
    int1& operator=(const int1& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return int1::subclass_registry.to_py(subclass_name, *this);
    }
};


class int2 : public wrapper<int2_>
{
public:
    using wrapper<int2_>::wrapper;
    static py_subclass_registry<int2> subclass_registry;
    // int2(long int v) : wrapper<int2_>(_check_value<int2_, long int>(v)) {}
    int2(const std::string text) : wrapper<int2_>(_check_value<int2_, long int>(std::stoi(text))) {}
    int2(const int2& other) : wrapper<int2_>(other) {}
    int2& operator=(const int2& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return int2::subclass_registry.to_py(subclass_name, *this);
    }
};


class int4 : public wrapper<int4_>
{
public:
    using wrapper<int4_>::wrapper;
    static py_subclass_registry<int4> subclass_registry;
    // int4(long int v) : wrapper<int4_>(_check_value<int4_, long int>(v)) {}
    int4(const std::string text) : wrapper<int4_>(_check_value<int4_, long int>(std::stoi(text))) {}
    int4(const int4& other) : wrapper<int4_>(other) {}
    int4& operator=(const int4& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return int4::subclass_registry.to_py(subclass_name, *this);
    }
};


class int8 : public wrapper<int8_>
{
public:
    using wrapper<int8_>::wrapper;
    static py_subclass_registry<int8> subclass_registry;
    // int8(long int v) : wrapper<int8_>(_check_value<int8_, long int>(v)) {}
    int8(const std::string text) : wrapper<int8_>(_check_value<int8_, long int>(std::stoi(text))) {}
    int8(const int8& other) : wrapper<int8_>(other) {}
    int8& operator=(const int8& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return int8::subclass_registry.to_py(subclass_name, *this);
    }
};



class float4 : public wrapper<float4_>
{
public:
    using wrapper<float4_>::wrapper;
    // float4(double v) : wrapper<float4_>(_check_value<float4_, double>(v)) {}
    static py_subclass_registry<float4> subclass_registry;
    float4(const std::string text) : wrapper<float4_>(_check_value<float4_, double>(std::stod(text))) {}
    float4(const float4& other) : wrapper<float4_>(other) {}
    float4& operator=(const float4& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return float4::subclass_registry.to_py(subclass_name, *this);
    }
};


class float8 : public wrapper<float8_>
{
public:
    using wrapper<float8_>::wrapper;
    // float8(double v) : wrapper<float8_>(_check_value<float8_, double>(v)) {}
    static py_subclass_registry<float8> subclass_registry;
    float8(const std::string text) : wrapper<float8_>(_check_value<float8_, double>(std::stod(text))) {}
    float8(const float8& other) : wrapper<float8_>(other) {}
    float8& operator=(const float8& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    std::string to_string() const {
        return std::to_string(this->value());
    }
    py::object to_py(std::string subclass_name) const {
        return float8::subclass_registry.to_py(subclass_name, *this);
    }
};


class text : public wrapper<text_>
{
public:
    using wrapper<text_>::wrapper;
    static py_subclass_registry<text> subclass_registry;
    text(const text& other) : wrapper<text_>(other) {}
    std::string to_string() const {
        return this->value();
    }
    text& operator=(const text& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    py::object to_py(std::string subclass_name) const {
        return text::subclass_registry.to_py(subclass_name, *this);
    }
};


class timestamptz : public wrapper<timestamptz_>
{
public:
    using wrapper<timestamptz_>::wrapper;
    static py_subclass_registry<timestamptz> subclass_registry;
    timestamptz(const timestamptz& other) : wrapper<timestamptz_>(other) {}
    timestamptz(std::string value) : wrapper<timestamptz_>(timestamptz::parse_from_string(value)) {}
    timestamptz& operator=(const timestamptz& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    static timestamptz_ parse_from_string (std::string value) {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return timestamptz_(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
    }
    std::string to_string_(const std::string& format) const {
        std::ostringstream oss;
        ldt::local_time_facet *facet = new ldt::local_time_facet(format.c_str());
        oss.imbue(std::locale(std::locale::classic(), facet));
        oss << value();
        delete facet;
        return oss.str(); //to_iso_extended_string(value().utc_time());// + value().zone()->to_posix_string();
    }
    std::string to_string() const {
        return to_string_("%Y-%m-%dT%H:%M:%S.%f%Q");
    }
    py::object to_py(std::string subclass_name) const {
        return timestamptz::subclass_registry.to_py(subclass_name, *this);
    }
    static std::shared_ptr<timestamptz> utcnow();
    static std::shared_ptr<timestamptz> now(const ldt::time_zone_ptr&);
};


class date : public wrapper<date_>
{
public:
    using wrapper<date_>::wrapper;
    static py_subclass_registry<date> subclass_registry;
    date(const date& other) : wrapper<date_>(other) {}
    date(std::string value) : wrapper<date_>(date::parse_from_string(value)) {}
    date& operator=(const date& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
    static date_ parse_from_string (const std::string value) {
        return (date_) dt::from_string(value);
    }
    std::string to_string() const {
        return to_iso_extended_string(value());
    }
    py::object to_py(std::string subclass_name) const {
        return date::subclass_registry.to_py(subclass_name, *this);
    }
};

// class timetz_py : public wrapper<timetz> {
// HAS_PY_REPRESENTATION(timetz_py, value());
// private:
//     timetz parse_from_string (const std::string value) const {
//         return pt::from_iso_string(value);
//     }
// public:
//     using wrapper<timetz>::wrapper;
//     timetz_py(const timetz_py& other) : wrapper<timetz>(other) {}
//     timetz_py(std::string value) : 
//     wrapper<timetz>(parse_from_string(value)) {}
//     std::string to_string() const {
//         return pt::to_iso_string(value());
//     }
// };

}


# endif
