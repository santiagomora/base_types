#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <cstdint>
#include <string>

#include "base_types/include/types.hpp"
#include "base_types/include/macros/overload.hpp"
#include "base_types/include/macros/base.hpp"
#include "base_types/include/macros/definition.hpp"
#include "base_types/include/macros/register.hpp"

namespace py = pybind11;
using namespace btp;

// DEBUG MACROS
// clear && g++ -P -E -I/usr/include/boost -I./base_types/cpp -I./ -I../../../pg_definition/venv/lib/python3.12/site-packages/pybind11/include wrapper.cpp


PYBIND11_MODULE(wrapper, m) {
    py::class_<int>(m, "base").def(py::init());
    PY_TYPEDEF_REGISTER(BTP_BOOLEAN, m, bl);
    PY_TYPEDEF_REGISTER(BTP_INT1, m, i1);
    PY_TYPEDEF_REGISTER(BTP_INT2, m, i2);
    PY_TYPEDEF_REGISTER(BTP_INT4, m, i4);
    PY_TYPEDEF_REGISTER(BTP_INT8, m, i8);
    PY_TYPEDEF_REGISTER(BTP_FLOAT4, m, f4);
    PY_TYPEDEF_REGISTER(BTP_FLOAT8, m, f8);
    // PY_TYPEDEF_REGISTER(BTP_TIMETZ, m, tz);
    PY_TYPEDEF_REGISTER(BTP_TIMESTAMPTZ, m, dtz);
    PY_TYPEDEF_REGISTER(BTP_DATE, m, dt);
    PY_TYPEDEF_REGISTER(BTP_TEXT, m, tx);

    bl.def("__eq__", [](const bool_py& self, const bool_py& other){
            return self.value() == other.value();
        })
        .def("__eq__", [](const bool_py& self, const py::bool_& other){
            return self.value() == other.cast<bool>();
        })
        .def("__ne__", [](const bool_py& self, const bool_py& other){
            return self.value() != other.value();
        })
        .def("__ne__", [](const bool_py& self, const py::bool_& other){
            return self.value() != other.cast<bool>();
        })
        .def("__and__", [](const bool_py& self, const bool_py& other){
            return self.value() && other.value();
        })
        .def("__and__", [](const bool_py& self, const py::bool_& other){
            return self.value() && other.cast<bool>();
        })
        .def("__or__", [](const bool_py& self, const bool_py& other){
            return self.value() || other.value();
        })
        .def("__or__", [](const bool_py& self, const py::bool_& other){
            return self.value() || other.cast<bool>();
        })
        .def("__str__", [](const bool_py& self){
            return std::to_string(self.value());
        });

    // int1_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, int1_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, int2_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, int4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, int8_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, float4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i1, int1_py, float8_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, int1_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, int1_py, long int);
    
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int1_py, int1_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int1_py, int2_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int1_py, int4_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int1_py, int8_py);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", +, py::int_, int1_py, long int);
    
    MAKE_LOGIC_OPERABLE(i1, int1_py, int1_py);
    MAKE_LOGIC_OPERABLE(i1, int1_py, int2_py);
    MAKE_LOGIC_OPERABLE(i1, int1_py, int4_py);
    MAKE_LOGIC_OPERABLE(i1, int1_py, int8_py);
    MAKE_LOGIC_OPERABLE(i1, int1_py, float4_py);
    MAKE_LOGIC_OPERABLE(i1, int1_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(i1, py::int_, int1_py, long int);
    MAKE_PY_LOGIC_OPERABLE(i1, py::float_, int1_py, double);

    // int2_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, int2_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, int1_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, int2_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, int4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, int8_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, float4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i2, int2_py, float8_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, int2_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, int2_py, long int);
    
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int2_py, int1_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int2_py, int2_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int2_py, int4_py);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, int2_py, int8_py);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", %, py::int_, int2_py, long int);
    
    MAKE_LOGIC_OPERABLE(i2, int2_py, int1_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, int2_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, int2_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, int4_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, int8_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, float4_py);
    MAKE_LOGIC_OPERABLE(i2, int2_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(i2, py::int_, int2_py, long int);
    MAKE_PY_LOGIC_OPERABLE(i2, py::float_, int2_py, double);
    
    // int4_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, int1_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, int2_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, int4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, int8_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, float4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i4, int4_py, float8_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::int_, int4_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::float_, int4_py, long int);
    
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, int4_py, int1_py);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, int4_py, int2_py);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, int4_py, int4_py);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, int4_py, int8_py);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i4, "__mod__", %, py::int_, int4_py, long int);
    
    MAKE_LOGIC_OPERABLE(i4, int4_py, int1_py);
    MAKE_LOGIC_OPERABLE(i4, int4_py, int2_py);
    MAKE_LOGIC_OPERABLE(i4, int4_py, int4_py);
    MAKE_LOGIC_OPERABLE(i4, int4_py, int8_py);
    MAKE_LOGIC_OPERABLE(i4, int4_py, float4_py);
    MAKE_LOGIC_OPERABLE(i4, int4_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(i4, py::int_, int4_py, long int);
    MAKE_PY_LOGIC_OPERABLE(i4, py::float_, int4_py, double);
    
    // int8_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, int1_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, int2_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, int4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, int8_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, float4_py, long int);
    MAKE_ARITHMETIC_COMPATIBLE(i8, int8_py, float8_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::int_, int8_py, long int);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::float_, int8_py, long int);
    
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, int8_py, int1_py);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, int8_py, int2_py);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, int8_py, int4_py);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, int8_py, int8_py);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i8, "__mod__", %, py::int_, int8_py, long int);
    
    MAKE_LOGIC_OPERABLE(i8, int8_py, int1_py);
    MAKE_LOGIC_OPERABLE(i8, int8_py, int2_py);
    MAKE_LOGIC_OPERABLE(i8, int8_py, int4_py);
    MAKE_LOGIC_OPERABLE(i8, int8_py, int8_py);
    MAKE_LOGIC_OPERABLE(i8, int8_py, float4_py);
    MAKE_LOGIC_OPERABLE(i8, int8_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(i8, py::int_, int8_py, long int);
    MAKE_PY_LOGIC_OPERABLE(i8, py::float_, int8_py, double);
    
    // float4_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, int1_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, int2_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, int4_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, int8_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, float4_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f4, float4_py, float8_py, double);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::int_, float4_py, double);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::float_, float4_py, double);
    
    MAKE_LOGIC_OPERABLE(f4, float4_py, int1_py);
    MAKE_LOGIC_OPERABLE(f4, float4_py, int2_py);
    MAKE_LOGIC_OPERABLE(f4, float4_py, int4_py);
    MAKE_LOGIC_OPERABLE(f4, float4_py, int8_py);
    MAKE_LOGIC_OPERABLE(f4, float4_py, float4_py);
    MAKE_LOGIC_OPERABLE(f4, float4_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(f4, py::int_, float4_py, long int);
    MAKE_PY_LOGIC_OPERABLE(f4, py::float_, float4_py, double);
    
    // float8_py OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, int1_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, int2_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, int4_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, int8_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, float4_py, double);
    MAKE_ARITHMETIC_COMPATIBLE(f8, float8_py, float8_py, double);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::int_, float8_py, double);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::float_, float8_py, double);
    
    MAKE_LOGIC_OPERABLE(f8, float8_py, int1_py);
    MAKE_LOGIC_OPERABLE(f8, float8_py, int2_py);
    MAKE_LOGIC_OPERABLE(f8, float8_py, int4_py);
    MAKE_LOGIC_OPERABLE(f8, float8_py, int8_py);
    MAKE_LOGIC_OPERABLE(f8, float8_py, float4_py);
    MAKE_LOGIC_OPERABLE(f8, float8_py, float8_py);
    MAKE_PY_LOGIC_OPERABLE(f8, py::int_, float8_py, long int);
    MAKE_PY_LOGIC_OPERABLE(f8, py::float_, float8_py, double);

    MAKE_PY_STRING_COMPARABLE(tx, py::str, text_py, std::string);
    // MAKE_PY_STRING_COMPARABLE(tz, py::str, timetz_py, std::string);
    MAKE_PY_STRING_COMPARABLE(dtz, py::str, timestamptz_py, std::string);
    MAKE_PY_STRING_COMPARABLE(dt, py::str, date_py, std::string);
}

