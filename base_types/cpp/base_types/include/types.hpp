# ifndef PG_DEFINITION_WRAPPERS
# define PG_DEFINITION_WRAPPERS


#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <limits>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "./macros/definition.hpp"


namespace py = pybind11;
namespace pt = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt = boost::gregorian;


namespace btp {


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

    T value () const {
        return *(_value.get());
    }

    virtual std::string to_string () const = 0;
};


template <typename T, typename V>
T _check_value (V value) {
    if(value < std::numeric_limits<T>::min() || value > std::numeric_limits<T>::max()){
        throw std::out_of_range("Value out of range");
    }
    return static_cast<T>(value);
};


class boolean : public wrapper<boolean_> {
HAS_PY_REPRESENTATION(boolean, value());
private:
    bool check_value (const std::string& value) const {
        if(value != "true" || value != "false"){
            throw std::out_of_range("Invalid boolean value");
        }
        return value != "true" ? false : true;
    }
public:
    using wrapper<boolean_>::wrapper;
    boolean(const std::string text) : wrapper<boolean_>(check_value(text)) {}
    boolean(const boolean& other) : wrapper<boolean_>(other) {}
    std::string to_string() const {
        return this->value() ? "true" : "false";
    }
    boolean& operator=(const boolean& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int1 : public wrapper<int1_> {
HAS_PY_REPRESENTATION(int1, value());
public:
    using wrapper<int1_>::wrapper;
    // int1(long int v) : wrapper<int1_>(_check_value<int1_, long int>(v)) {}
    int1(const std::string text) : wrapper<int1_>(_check_value<int1_, long int>(std::stoi(text))) {}
    int1(const int1& other) : wrapper<int1_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int1& operator=(const int1& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int2 : public wrapper<int2_> {
HAS_PY_REPRESENTATION(int2, value());
public:
    using wrapper<int2_>::wrapper;
    // int2(long int v) : wrapper<int2_>(_check_value<int2_, long int>(v)) {}
    int2(const std::string text) : wrapper<int2_>(_check_value<int2_, long int>(std::stoi(text))) {}
    int2(const int2& other) : wrapper<int2_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int2& operator=(const int2& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int4 : public wrapper<int4_> {
HAS_PY_REPRESENTATION(int4, value());
public:
    using wrapper<int4_>::wrapper;
    // int4(long int v) : wrapper<int4_>(_check_value<int4_, long int>(v)) {}
    int4(const std::string text) : wrapper<int4_>(_check_value<int4_, long int>(std::stoi(text))) {}
    int4(const int4& other) : wrapper<int4_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int4& operator=(const int4& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int8 : public wrapper<int8_> {
HAS_PY_REPRESENTATION(int8, value());
public:
    using wrapper<int8_>::wrapper;
    // int8(long int v) : wrapper<int8_>(_check_value<int8_, long int>(v)) {}
    int8(const std::string text) : wrapper<int8_>(_check_value<int8_, long int>(std::stoi(text))) {}
    int8(const int8& other) : wrapper<int8_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int8& operator=(const int8& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};



class float4 : public wrapper<float4_> {
HAS_PY_REPRESENTATION(float4, value());
public:
    using wrapper<float4_>::wrapper;
    // float4(double v) : wrapper<float4_>(_check_value<float4_, double>(v)) {}
    float4(const std::string text) : wrapper<float4_>(_check_value<float4_, double>(std::stod(text))) {}
    float4(const float4& other) : wrapper<float4_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    float4& operator=(const float4& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class float8 : public wrapper<float8_> {
HAS_PY_REPRESENTATION(float8, value());
public:
    using wrapper<float8_>::wrapper;
    // float8(double v) : wrapper<float8_>(_check_value<float8_, double>(v)) {}
    float8(const std::string text) : wrapper<float8_>(_check_value<float8_, double>(std::stod(text))) {}
    float8(const float8& other) : wrapper<float8_>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    float8& operator=(const float8& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class text : public wrapper<text_> {
HAS_PY_REPRESENTATION(text, value());
public:
    using wrapper<text_>::wrapper;
    text(const text& other) : wrapper<text_>(other) {}
    std::string to_string() const {
        return QUOTE_FUNCTION(this->value());
    }
    text& operator=(const text& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class timestamptz : public wrapper<timestamptz_> {
HAS_PY_REPRESENTATION(timestamptz, value());
private:
    timestamptz_ parse_from_string (std::string value) const {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return timestamptz_(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
    }
public:
    using wrapper<timestamptz_>::wrapper;
    timestamptz(const timestamptz& other) : wrapper<timestamptz_>(other) {}
    timestamptz(std::string value) : wrapper<timestamptz_>(parse_from_string(value)) {}
    std::string to_string() const {
        std::ostringstream oss;
        ldt::local_time_facet *facet = new ldt::local_time_facet("%Y-%m-%dT%H:%M:%S.%f%Q");
        oss.imbue(std::locale(std::locale::classic(), facet));
        oss << value();
        delete facet;
        return oss.str(); //to_iso_extended_string(value().utc_time());// + value().zone()->to_posix_string();
    }
    timestamptz& operator=(const timestamptz& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class date : public wrapper<date_> {
HAS_PY_REPRESENTATION(date, value());
private:
    date_ parse_from_string (const std::string value) const {
        return (date_) dt::from_string(value);
    }
public:
    using wrapper<date_>::wrapper;
    date(const date& other) : wrapper<date_>(other) {}
    date(std::string value) : wrapper<date_>(parse_from_string(value)) {}
    std::string to_string() const {
        return to_iso_extended_string(value());
    }
    date& operator=(const date& other) {
        _value = other.wrapped_ptr();
        return *this;
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
