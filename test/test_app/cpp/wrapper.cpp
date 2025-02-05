#include <pybind11/pybind11.h>

#include "base_types/macros/register.hpp"
#include "base_types/compare.hpp"

#include "test_app/types.hpp"
#include "test_app/definition.hpp"


namespace py = pybind11;


// DEBUG clear && g++ -P -E -I/usr/include/boost -I../../../base_types/cpp -I./ wrapper.cpp


PYBIND11_MODULE (wrapper, m) {

    PY_CLASSDEF_REGISTER(TEST_APP_AUTHOR, m);
    PY_CLASSDEF_REGISTER(TEST_APP_AUTHORED, m);
    PY_CLASSDEF_REGISTER(TEST_APP_WITH_TIMESTAMPS, m);
    PY_ENUMDEF_REGISTER(TEST_APP_POST_STATUS, m);
    PY_CLASSDEF_REGISTER(TEST_APP_POST, m);
    PY_CLASSDEF_REGISTER(TEST_APP_COMMENT, m);
    PY_CLASSDEF_REGISTER(TEST_APP_COMMENT_POST, m);
    PY_REGISTER_TYPE_ALIASDEF(TEST_APP_DOMAIN, m, dm, TEST_APP_DOMAIN_CONSTRUCTORS);

    m.def("test_function_receives_author_correctly", &test_app::test_function_receives_author_correctly);
    m.def("test_function_receives_comment_post_correctly", &test_app::test_function_receives_comment_post_correctly);
    m.def("test_function_receives_wt_subclass_correctly", &test_app::test_function_receives_wt_subclass_correctly);
}

