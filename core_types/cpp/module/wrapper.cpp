#include <pybind11/pybind11.h>


#include "core_types/types.hpp"
#include "core_types/compare.hpp"

#include "core_types/macros/overload.hpp"
#include "core_types/macros/register.hpp"
#include "core_types/macros/definition.hpp"


namespace py = pybind11;


// clear && g++ -P -E -I/usr/include/boost -I./core_types/cpp -I./ -I../../../pg_definition/venv/lib/python3.12/site-packages/pybind11/include wrapper.cpp


PYBIND11_MODULE(wrapper, m) {
    py::class_<py::object>(m, "pybind_base");
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
}

