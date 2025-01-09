#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <cstdint>
#include <string>

#include "base_types/include/types.hpp"
#include "base_types/include/register.hpp"
#include "base_types/include/macros/overload.hpp"

namespace py = pybind11;
using namespace btp;


PYBIND11_MODULE(wrapper, m) {
    py::class_<int>(m, "base").def(py::init());
    py::class_<int1_py, std::unique_ptr<int1_py>>& i1 = register_int<int1_py>(m, "int1");
    py::class_<int2_py, std::unique_ptr<int2_py>>& i2 = register_int<int2_py>(m, "int2");
    py::class_<int4_py, std::unique_ptr<int4_py>>& i4 = register_int<int4_py>(m, "int4");
    py::class_<int8_py, std::unique_ptr<int8_py>>& i8 = register_int<int8_py>(m, "int8");
    py::class_<float4_py, std::unique_ptr<float4_py>>& f4 = register_float<float4_py>(m, "float4");
    py::class_<float8_py, std::unique_ptr<float8_py>>& f8 = register_float<float8_py>(m, "float8");
    py::class_<bool_py, std::unique_ptr<bool_py>>& bl = register_bool(m, "bool");
    py::class_<timetz_py, std::unique_ptr<timetz_py>>& tz = register_timetz(m, "timetz");
    py::class_<timestamptz_py, std::unique_ptr<timestamptz_py>>& dtz = register_timestamptz(m, "timestamptz");
    py::class_<date_py, std::unique_ptr<date_py>>& dt = register_date(m, "date");
    py::class_<text_py, std::unique_ptr<text_py>>& tx = register_text(m, "text");

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
}

