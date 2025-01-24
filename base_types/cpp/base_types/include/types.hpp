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


template <typename T>
class int_wrapper : public wrapper<T>
{
private:
    T check_value (long int value) const {
        if(value < std::numeric_limits<T>::min() || value > std::numeric_limits<T>::max()){
            throw std::out_of_range("Value out of range");
        }
        return static_cast<T>(value);
    }
public:
    int_wrapper(const int_wrapper<T>& other) : wrapper<T>(other) {}
    int_wrapper(long int v) : wrapper<T>(check_value(v)) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
};


template <typename T>
class float_wrapper : public wrapper<T>
{
private:
    T check_value (double value) const {
        if(value < std::numeric_limits<T>::min() || value > std::numeric_limits<T>::max()){
            throw std::out_of_range("Value out of range");
        }
        return static_cast<T>(value);
    }
public:
    float_wrapper(const float_wrapper<T>& other) : wrapper<T>(other) {}
    float_wrapper(double v) : wrapper<T>(check_value(v)) {}
    std::string to_string() const {
        return std::to_string(this->value());
    }
};


class bool_py : public wrapper<boolean> {
HAS_PY_REPRESENTATION(bool_py, value());
public:
    using wrapper<boolean>::wrapper;
    std::string to_string() const {
        return std::to_string(this->value());
    }
};


class int1_py : public int_wrapper<int1> {
HAS_PY_REPRESENTATION(int1_py, value());
public:
    using int_wrapper<int1>::int_wrapper;
};


class int2_py : public int_wrapper<int2> {
HAS_PY_REPRESENTATION(int2_py, value());
public:
    using int_wrapper<int2>::int_wrapper;
};


class int4_py : public int_wrapper<int4> {
HAS_PY_REPRESENTATION(int4_py, value());
public:
    using int_wrapper<int4>::int_wrapper;
};


class int8_py : public int_wrapper<int8> {
HAS_PY_REPRESENTATION(int8_py, value());
public:
    using int_wrapper<int8>::int_wrapper;
    int8_py(const int8_py& other) : int_wrapper<int8>(other) {}
};


class float4_py : public float_wrapper<float4> {
HAS_PY_REPRESENTATION(float4_py, value());
public:
    using float_wrapper<float4>::float_wrapper;
    float4_py(const float4_py& other) : float_wrapper<float4>(other) {}
};


class float8_py : public float_wrapper<float8> {
HAS_PY_REPRESENTATION(float8_py, value());
public:
    using float_wrapper<float8>::float_wrapper;
    float8_py(const float8_py& other) : float_wrapper<float8>(other) {}
};


class text_py : public wrapper<std::string> {
HAS_PY_REPRESENTATION(text_py, value());
public:
    using wrapper<std::string>::wrapper;
    text_py(const text_py& other) : wrapper<std::string>(other) {}
    std::string to_string() const {
        return this->value();
    }
};


class timestamptz_py : public wrapper<timestamptz> {
HAS_PY_REPRESENTATION(timestamptz_py, value());
private:
    timestamptz parse_from_string (const std::string value) const {
        ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
        return timestamptz(pt::from_iso_extended_string(value), zone);
    }
public:
    using wrapper<timestamptz>::wrapper;
    timestamptz_py(const timestamptz_py& other) : wrapper<timestamptz>(other) {}
    timestamptz_py(std::string value) : 
    wrapper<timestamptz>(parse_from_string(value)) {}
    std::string to_string() const {
        return to_iso_extended_string(value().utc_time()) + value().zone()->to_posix_string();
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
    date_py(std::string value) : 
    wrapper<date>(parse_from_string(value)) {}
    std::string to_string() const {
        return to_iso_extended_string(value());
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
