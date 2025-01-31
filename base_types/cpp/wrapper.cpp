#include <pybind11/pybind11.h>


namespace py = pybind11;


// clear && g++ -P -E -I/usr/include/boost -I./base_types/cpp -I./ -I../../../pg_definition/venv/lib/python3.12/site-packages/pybind11/include wrapper.cpp


PYBIND11_MODULE(wrapper, m) {
    py::class_<py::object>(m, "base");
}

