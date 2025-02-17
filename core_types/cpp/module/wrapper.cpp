#include <pybind11/pybind11.h>
#include "core_types/typing/types.hpp"
#include "core_types/typing/compare.hpp"
#include "core_types/macros/declaration.hpp"
#include "core_types/macros/register/instanceable.hpp"


namespace py = pybind11;


// clear && g++ -P -E -I/usr/include/boost -I/home/smora/sgs/dev/python/core/include/ -I/home/smora/.pyenv/versions/3.12.0/include/python3.12/ -I./include wrapper.cpp


PYBIND11_MODULE(wrapper, m) {
    py::class_<py::object>(m, "ct_pybind_base", py::module_local());
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_BOOLEAN, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT1, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT2, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT4, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT8, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_FLOAT4, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_FLOAT8, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_TIMESTAMPTZ, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_DATE, m);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_TEXT, m);
    // std::cout << core_types::determine_container_name<std::vector<int>>::value << std::endl;
}

