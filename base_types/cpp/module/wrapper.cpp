#include <pybind11/pybind11.h>


#include "base_types/macros/overload.hpp"
#include "base_types/macros/register.hpp"
#include "base_types/macros/definition.hpp"
#include "base_types/types.hpp"


namespace py = pybind11;


// clear && g++ -P -E -I/usr/include/boost -I./base_types/cpp -I./ -I../../../pg_definition/venv/lib/python3.12/site-packages/pybind11/include wrapper.cpp


PYBIND11_MODULE(wrapper, m) {

    py::class_<py::object>(m, "base");

    PY_TYPEDEF_REGISTER(BTP_BOOLEAN, m, bl);
    PY_TYPEDEF_REGISTER(BTP_INT1, m, i1);
    PY_TYPEDEF_REGISTER(BTP_INT2, m, i2);
    PY_TYPEDEF_REGISTER(BTP_INT4, m, i4);
    PY_TYPEDEF_REGISTER(BTP_INT8, m, i8);
    PY_TYPEDEF_REGISTER(BTP_FLOAT4, m, f4);
    PY_TYPEDEF_REGISTER(BTP_FLOAT8, m, f8);
    PY_TYPEDEF_REGISTER(BTP_TIMESTAMPTZ, m, dtz);
    PY_TYPEDEF_REGISTER(BTP_DATE, m, dt);
    PY_TYPEDEF_REGISTER(BTP_TEXT, m, tx);

    bl.def("__eq__", [](const btp::boolean& self, const btp::boolean& other){
            return self.value() == other.value();
        })
        .def("__eq__", [](const btp::boolean& self, const py::bool_& other){
            return self.value() == other.cast<bool>();
        })
        .def("__ne__", [](const btp::boolean& self, const btp::boolean& other){
            return self.value() != other.value();
        })
        .def("__ne__", [](const btp::boolean& self, const py::bool_& other){
            return self.value() != other.cast<bool>();
        })
        .def("__and__", [](const btp::boolean& self, const btp::boolean& other){
            return self.value() && other.value();
        })
        .def("__and__", [](const btp::boolean& self, const py::bool_& other){
            return self.value() && other.cast<bool>();
        })
        .def("__or__", [](const btp::boolean& self, const btp::boolean& other){
            return self.value() || other.value();
        })
        .def("__or__", [](const btp::boolean& self, const py::bool_& other){
            return self.value() || other.cast<bool>();
        })
        .def("__str__", [](const btp::boolean& self){
            return std::to_string(self.value());
        });

    // btp::int1 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::int1, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::int2, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::int4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::int8, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::float4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i1, btp::int1, btp::float8, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, btp::int1, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, btp::int1, btp::int8_);

    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int1, btp::int1);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int1, btp::int2);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int1, btp::int4);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int1, btp::int8);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", +, py::int_, btp::int1, btp::int8_);

    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::int1);
    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::int2);
    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::int4);
    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::int8);
    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::float4);
    MAKE_LOGIC_OPERABLE(i1, btp::int1, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(i1, py::int_, btp::int1, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(i1, py::float_, btp::int1, btp::float8_);

    // btp::int2 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::int2, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::int1, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::int2, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::int4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::int8, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::float4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i2, btp::int2, btp::float8, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, btp::int2, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, btp::int2, btp::int8_);

    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int2, btp::int1);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int2, btp::int2);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int2, btp::int4);
    REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, btp::int2, btp::int8);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", %, py::int_, btp::int2, btp::int8_);

    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::int1);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::int2);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::int2);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::int4);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::int8);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::float4);
    MAKE_LOGIC_OPERABLE(i2, btp::int2, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(i2, py::int_, btp::int2, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(i2, py::float_, btp::int2, btp::float8_);

    // btp::int4 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::int1, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::int2, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::int4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::int8, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::float4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i4, btp::int4, btp::float8, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::int_, btp::int4, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::float_, btp::int4, btp::int8_);

    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, btp::int4, btp::int1);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, btp::int4, btp::int2);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, btp::int4, btp::int4);
    REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, btp::int4, btp::int8);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i4, "__mod__", %, py::int_, btp::int4, btp::int8_);

    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::int1);
    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::int2);
    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::int4);
    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::int8);
    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::float4);
    MAKE_LOGIC_OPERABLE(i4, btp::int4, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(i4, py::int_, btp::int4, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(i4, py::float_, btp::int4, btp::float8_);

    // btp::int8 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::int1, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::int2, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::int4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::int8, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::float4, btp::int8_);
    MAKE_ARITHMETIC_COMPATIBLE(i8, btp::int8, btp::float8, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::int_, btp::int8, btp::int8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::float_, btp::int8, btp::int8_);

    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, btp::int8, btp::int1);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, btp::int8, btp::int2);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, btp::int8, btp::int4);
    REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, btp::int8, btp::int8);
    REGISTER_PY_ARITHMETIC_OVERLOAD(i8, "__mod__", %, py::int_, btp::int8, btp::int8_);

    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::int1);
    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::int2);
    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::int4);
    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::int8);
    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::float4);
    MAKE_LOGIC_OPERABLE(i8, btp::int8, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(i8, py::int_, btp::int8, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(i8, py::float_, btp::int8, btp::float8_);

    // btp::float4 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::int1, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::int2, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::int4, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::int8, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::float4, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f4, btp::float4, btp::float8, btp::float8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::int_, btp::float4, btp::float8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::float_, btp::float4, btp::float8_);

    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::int1);
    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::int2);
    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::int4);
    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::int8);
    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::float4);
    MAKE_LOGIC_OPERABLE(f4, btp::float4, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(f4, py::int_, btp::float4, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(f4, py::float_, btp::float4, btp::float8_);

    // btp::float8 OVERLOADS
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::int1, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::int2, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::int4, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::int8, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::float4, btp::float8_);
    MAKE_ARITHMETIC_COMPATIBLE(f8, btp::float8, btp::float8, btp::float8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::int_, btp::float8, btp::float8_);
    MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::float_, btp::float8, btp::float8_);

    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::int1);
    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::int2);
    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::int4);
    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::int8);
    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::float4);
    MAKE_LOGIC_OPERABLE(f8, btp::float8, btp::float8);
    MAKE_PY_LOGIC_OPERABLE(f8, py::int_, btp::float8, btp::int8_);
    MAKE_PY_LOGIC_OPERABLE(f8, py::float_, btp::float8, btp::float8_);

    // MAKE_PY_STRING_COMPARABLE(tz, py::str, timetz_py, std::string);
    // btp::text overloads
    MAKE_PY_STRING_COMPARABLE(tx, py::str, btp::text, std::string);

    // btp::timestamptz overloads
    MAKE_PY_STRING_COMPARABLE(dtz, py::str, btp::timestamptz, std::string);
    MAKE_LOGIC_OPERABLE(dtz, btp::timestamptz, btp::timestamptz);

    // btp::date overloads
    MAKE_PY_STRING_COMPARABLE(dt, py::str, btp::date, std::string);
    MAKE_LOGIC_OPERABLE(dt, btp::date, btp::date);
}

