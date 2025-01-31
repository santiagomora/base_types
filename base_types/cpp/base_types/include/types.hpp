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

typedef int8_t int1;
typedef int16_t int2;
typedef int32_t int4;
typedef int64_t int8;
typedef float float4;
typedef double float8;
typedef std::string text;
typedef ldt::local_date_time timestamptz;
typedef pt::ptime timetz;
typedef dt::date date;
typedef bool boolean;


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


class bool_py : public wrapper<boolean> {
HAS_PY_REPRESENTATION(bool_py, value());
private:
    bool check_value (const std::string& value) const {
        if(value != "true" || value != "false"){
            throw std::out_of_range("Invalid boolean value");
        }
        return value != "true" ? false : true;
    }
public:
    using wrapper<boolean>::wrapper;
    bool_py(const std::string text) : wrapper<boolean>(check_value(text)) {}
    bool_py(const bool_py& other) : wrapper<boolean>(other) {}
    std::string to_string() const {
        return this->value() ? "true" : "false";
    }
    bool_py& operator=(const bool_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int1_py : public wrapper<int1> {
HAS_PY_REPRESENTATION(int1_py, value());
public:
    using wrapper<int1>::wrapper;
    // int1_py(long int v) : wrapper<int1>(_check_value<int1, long int>(v)) {}
    int1_py(const std::string text) : wrapper<int1>(_check_value<int1, long int>(std::stoi(text))) {}
    int1_py(const int1_py& other) : wrapper<int1>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int1_py& operator=(const int1_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int2_py : public wrapper<int2> {
HAS_PY_REPRESENTATION(int2_py, value());
public:
    using wrapper<int2>::wrapper;
    // int2_py(long int v) : wrapper<int2>(_check_value<int2, long int>(v)) {}
    int2_py(const std::string text) : wrapper<int2>(_check_value<int2, long int>(std::stoi(text))) {}
    int2_py(const int2_py& other) : wrapper<int2>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int2_py& operator=(const int2_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int4_py : public wrapper<int4> {
HAS_PY_REPRESENTATION(int4_py, value());
public:
    using wrapper<int4>::wrapper;
    // int4_py(long int v) : wrapper<int4>(_check_value<int4, long int>(v)) {}
    int4_py(const std::string text) : wrapper<int4>(_check_value<int4, long int>(std::stoi(text))) {}
    int4_py(const int4_py& other) : wrapper<int4>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int4_py& operator=(const int4_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class int8_py : public wrapper<int8> {
HAS_PY_REPRESENTATION(int8_py, value());
public:
    using wrapper<int8>::wrapper;
    // int8_py(long int v) : wrapper<int8>(_check_value<int8, long int>(v)) {}
    int8_py(const std::string text) : wrapper<int8>(_check_value<int8, long int>(std::stoi(text))) {}
    int8_py(const int8_py& other) : wrapper<int8>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    int8_py& operator=(const int8_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};



class float4_py : public wrapper<float4> {
HAS_PY_REPRESENTATION(float4_py, value());
public:
    using wrapper<float4>::wrapper;
    // float4_py(double v) : wrapper<float4>(_check_value<float4, double>(v)) {}
    float4_py(const std::string text) : wrapper<float4>(_check_value<float4, double>(std::stod(text))) {}
    float4_py(const float4_py& other) : wrapper<float4>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    float4_py& operator=(const float4_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class float8_py : public wrapper<float8> {
HAS_PY_REPRESENTATION(float8_py, value());
public:
    using wrapper<float8>::wrapper;
    // float8_py(double v) : wrapper<float8>(_check_value<float8, double>(v)) {}
    float8_py(const std::string text) : wrapper<float8>(_check_value<float8, double>(std::stod(text))) {}
    float8_py(const float8_py& other) : wrapper<float8>(other) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
    float8_py& operator=(const float8_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class text_py : public wrapper<std::string> {
HAS_PY_REPRESENTATION(text_py, value());
public:
    using wrapper<std::string>::wrapper;
    text_py(const text_py& other) : wrapper<std::string>(other) {}
    std::string to_string() const {
        return QUOTE_FUNCTION(this->value());
    }
    text_py& operator=(const text_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class timestamptz_py : public wrapper<timestamptz> {
HAS_PY_REPRESENTATION(timestamptz_py, value());
private:
    timestamptz parse_from_string (std::string value) const {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return timestamptz(pt::from_iso_extended_string(value.replace(10, 1, "T")), zone);
    }
public:
    using wrapper<timestamptz>::wrapper;
    timestamptz_py(const timestamptz_py& other) : wrapper<timestamptz>(other) {}
    timestamptz_py(std::string value) : wrapper<timestamptz>(parse_from_string(value)) {}
    std::string to_string() const {
        std::ostringstream oss;
        ldt::local_time_facet *facet = new ldt::local_time_facet("%Y-%m-%dT%H:%M:%S.%f%Q");
        oss.imbue(std::locale(std::locale::classic(), facet));
        oss << value();
        delete facet;
        return oss.str(); //to_iso_extended_string(value().utc_time());// + value().zone()->to_posix_string();
    }
    timestamptz_py& operator=(const timestamptz_py& other) {
        _value = other.wrapped_ptr();
        return *this;
    }
};


class date_py : public wrapper<date> {
HAS_PY_REPRESENTATION(date_py, value());
private:
    date parse_from_string (const std::string value) const {
        return (date) dt::from_string(value);
    }
public:
    using wrapper<date>::wrapper;
    date_py(const date_py& other) : wrapper<date>(other) {}
    date_py(std::string value) : wrapper<date>(parse_from_string(value)) {}
    std::string to_string() const {
        return to_iso_extended_string(value());
    }
    date_py& operator=(const date_py& other) {
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
