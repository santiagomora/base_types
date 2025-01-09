#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <cstdint>
#include <string>

#include "../include/types.hpp"


namespace py = pybind11;


using namespace btp;


py::object int1_py::cls = py::cast<py::none>(Py_None);
py::object int2_py::cls = py::cast<py::none>(Py_None);
py::object int4_py::cls = py::cast<py::none>(Py_None);
py::object int8_py::cls = py::cast<py::none>(Py_None);
py::object float4_py::cls = py::cast<py::none>(Py_None);
py::object float8_py::cls = py::cast<py::none>(Py_None);
py::object bool_py::cls = py::cast<py::none>(Py_None);
py::object timetz_py::cls = py::cast<py::none>(Py_None);
py::object timestamptz_py::cls = py::cast<py::none>(Py_None);
py::object date_py::cls = py::cast<py::none>(Py_None);
py::object text_py::cls = py::cast<py::none>(Py_None);


