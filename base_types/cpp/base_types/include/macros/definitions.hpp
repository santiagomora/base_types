#ifndef BASE_TYPES_TYPES
#define BASE_TYPES_TYPES


#include "./helper/base.hpp"


#define BOOL_PY BASE_TYPE_DEFINITION(\
    (btp, bool_py),\
    ((*_value))\
)


#define INT1_PY BASE_TYPE_DEFINITION(\
    (btp, int1_py),\
    ((*_value))\
)


#define INT2_PY BASE_TYPE_DEFINITION(\
    (btp, int2_py),\
    ((*_value))\
)


#define INT4_PY BASE_TYPE_DEFINITION(\
    (btp, int4_py),\
    ((*_value))\
)


#define INT8_PY BASE_TYPE_DEFINITION(\
    (btp, int8_py),\
    ((*_value))\
)


#define FLOAT4_PY BASE_TYPE_DEFINITION(\
    (btp, float4_py),\
    ((*_value))\
)


#define FLOAT8_PY BASE_TYPE_DEFINITION(\
    (btp, float8_py),\
    ((*_value))\
)


#define TEXT_PY BASE_TYPE_DEFINITION(\
    (btp, text_py),\
    ((*_value))\
)


#define TIMESTAMPTZ_PY BASE_TYPE_DEFINITION(\
    (btp, timestamptz_py),\
    ((*_value))\
)


#define TIMETZ_PY BASE_TYPE_DEFINITION(\
    (btp, timetz_py),\
    ((*_value))\
)


#define DATE_PY BASE_TYPE_DEFINITION(\
    (btp, date_py),\
    ((*_value))\
)



#endif
