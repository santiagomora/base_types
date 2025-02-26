#ifndef CORE_TYPES_TYPING_DEFINITIONS
#define CORE_TYPES_TYPING_DEFINITIONS
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <limits>
#include <map>
#include <type_traits>
#include <optional>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


namespace core_types::adapt
{
    typedef bool                               boolean;
    typedef float                              float4;
    typedef double                             float8;
    typedef std::int8_t                        int1;
    typedef std::int16_t                       int2;
    typedef std::int32_t                       int4;
    typedef std::int64_t                       int8;
    typedef std::string                        text;
    typedef boost::local_time::local_date_time timestamptz;
    typedef boost::gregorian::date             date;
}


#define CT_BOOLEAN TYPE_DEFINITION(\
    CT_BOOLEAN,\
    (core_types, boolean),\
    (core_types::adapt, boolean),\
    pybind11::bool_,\
    (core_types::interface, boolean)\
)
#define CT_BOOLEAN_CONSTRUCTORS (CT_BOOLEAN)


#define CT_INT1 TYPE_DEFINITION(\
    CT_INT1,\
    (core_types, int1),\
    (core_types::adapt, int1),\
    pybind11::int_,\
    (core_types::interface, int1)\
)
#define CT_INT1_CONSTRUCTORS (CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT2 TYPE_DEFINITION(\
    CT_INT2,\
    (core_types, int2),\
    (core_types::adapt, int2),\
    pybind11::int_,\
    (core_types::interface, int2)\
)
#define CT_INT2_CONSTRUCTORS (CT_INT2)(CT_INT1)(CT_INT4)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT4 TYPE_DEFINITION(\
    CT_INT4,\
    (core_types, int4),\
    (core_types::adapt, int4),\
    pybind11::int_,\
    (core_types::interface, int4)\
)
#define CT_INT4_CONSTRUCTORS (CT_INT4)(CT_INT1)(CT_INT2)(CT_INT8)(CT_FLOAT4)(CT_FLOAT8)


#define CT_INT8 TYPE_DEFINITION(\
    CT_INT8,\
    (core_types, int8),\
    (core_types::adapt, int8),\
    pybind11::int_,\
    (core_types::interface, int8)\
)
#define CT_INT8_CONSTRUCTORS (CT_INT8)(CT_INT1)(CT_INT2)(CT_INT4)(CT_FLOAT4)(CT_FLOAT8)


#define CT_FLOAT4 TYPE_DEFINITION(\
    CT_FLOAT4,\
    (core_types, float4),\
    (core_types::adapt, float4),\
    pybind11::float_,\
    (core_types::interface, float4)\
)
#define CT_FLOAT4_CONSTRUCTORS (CT_FLOAT4)(CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT8)


#define CT_FLOAT8 TYPE_DEFINITION(\
    CT_FLOAT8,\
    (core_types, float8),\
    (core_types::adapt, float8),\
    pybind11::float_,\
    (core_types::interface, float8)\
)
#define CT_FLOAT8_CONSTRUCTORS (CT_FLOAT8)(CT_INT1)(CT_INT2)(CT_INT4)(CT_INT8)(CT_FLOAT4)


#define CT_TEXT TYPE_DEFINITION(\
    CT_TEXT,\
    (core_types, text),\
    (core_types::adapt, text),\
    pybind11::str,\
    (core_types::interface, text)\
)
#define CT_TEXT_CONSTRUCTORS (CT_TEXT)


#define CT_TIMESTAMPTZ TYPE_DEFINITION(\
    CT_TIMESTAMPTZ,\
    (core_types, timestamptz),\
    (core_types::adapt, timestamptz),\
    pybind11::str,\
    (core_types::interface, timestamptz)\
)
#define CT_TIMESTAMPTZ_CONSTRUCTORS (CT_TIMESTAMPTZ)(CT_TEXT)


#define CT_DATE TYPE_DEFINITION(\
    CT_DATE,\
    (core_types, date),\
    (core_types::adapt, date),\
    pybind11::str,\
    (core_types::interface, date)\
)
#define CT_DATE_CONSTRUCTORS (CT_DATE)(CT_TEXT)


// #define IFACE_CT_TIMETZ IFACE_TYPE_DEFINITION(
//     IFACE_CT_TIMETZ,
//     (core_types::interface, timetz_py),
//     py::str,
//     core_types::interface::text
// )
// #define IFACE_CT_TIMETZ_CONSTRUCTORS (IFACE_CT_TIMETZ)


#endif
