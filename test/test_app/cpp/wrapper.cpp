#include <pybind11/pybind11.h>
#include "test_app/include/types.hpp"
#include "base_types/include/macros/helper/register.hpp"


namespace py = pybind11;


PYBIND11_MODULE(wrapper, m) {
    PY_PLAIN_CLASS_DEFINITION(AUTHOR, m);
    PY_PLAIN_CLASS_DEFINITION(AUTHORED, m);
    PY_PLAIN_CLASS_DEFINITION(WITH_TIMESTAMPS, m);
    PY_ENUM_DEFINITION(POST_STATUS, m);
    PY_COMPOSED_CLASS_DEFINITION(POST, m);
    PY_COMPOSED_CLASS_DEFINITION(COMMENT, m);
    PY_PLAIN_CLASS_DEFINITION(COMMENT_POST, m);
    PY_ALIAS_DEFINITION(DOMAIN, m);
}

