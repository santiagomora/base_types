#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/interface.hpp"
#include "test_app/types.hpp"
#include "test_app/definition.hpp"


namespace py = pybind11;


// DEBUG clear && g++ -P -E -I/usr/include/boost -I/home/smora/sgs/dev/python/core/include/ -I/home/smora/.pyenv/versions/3.12.0/include/python3.12/ -I./include wrapper.cpp

PYBIND11_MODULE (wrapper, m) 
{
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_AUTHOR, m);
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_AUTHORED, m);
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_WITH_TIMESTAMPS, m);
CT_ENUMDEF_REGISTER_INSTANCEABLE(TEST_APP_POST_STATUS, m);
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_POST, m);
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_COMMENT, m);
CT_CLASSDEF_REGISTER_INSTANCEABLE(TEST_APP_COMMENT_POST, m);
CT_TYPE_ALIASDEF_REGISTER_INSTANCEABLE(TEST_APP_DOMAIN, m, TEST_APP_DOMAIN_CONSTRUCTORS);

// m.def("test_function_receives_author_correctly", &test_app::test_function_receives_author_correctly);
// m.def("test_function_receives_comment_post_correctly", &test_app::test_function_receives_comment_post_correctly);
// m.def("test_function_receives_wt_subclass_correctly", &test_app::test_function_receives_wt_subclass_correctly);
}

