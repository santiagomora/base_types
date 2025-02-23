#include <pybind11/pybind11.h>
#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/interface.hpp"


namespace py = pybind11;


// clear && g++ -P -E -I/usr/include/boost -I/home/smora/sgs/dev/python/core/include/ -I/home/smora/.pyenv/versions/3.12.0/include/python3.12/ -I./include wrapper.cpp

PYBIND11_MODULE(wrapper, m) 
{
    py::class_<py::object>(m, "ct_pybind_base", py::module_local());
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_BOOLEAN,     m, CT_BOOLEAN_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT1,        m, CT_INT1_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT2,        m, CT_INT2_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT4,        m, CT_INT4_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_INT8,        m, CT_INT8_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_FLOAT4,      m, CT_FLOAT4_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_FLOAT8,      m, CT_FLOAT8_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_TIMESTAMPTZ, m, CT_TIMESTAMPTZ_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_DATE,        m, CT_DATE_CONSTRUCTORS);
    CT_TYPEDEF_REGISTER_INSTANCEABLE(CT_TEXT,        m, CT_TEXT_CONSTRUCTORS);
    // std::cout << core_types::determine_container_name<std::vector<int>>::value << std::endl;
}

