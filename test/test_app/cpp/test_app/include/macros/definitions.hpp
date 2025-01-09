#ifndef TEST_APP_MACROS_DEFINITIONS
#define TEST_APP_MACROS_DEFINITIONS


#include "base_types/include/macros/helper/definition.hpp"
#include "base_types/include/macros/helper/base.hpp"
#include "base_types/include/types.hpp"


#define AUTHOR PLAIN_CLASS_DEFINITION(\
    (test_app, author),\
    ((btp::int8_py, id))\
    ((btp::text_py, name))\
)


#define AUTHORED PLAIN_CLASS_DEFINITION(\
    (test_app, authored),\
    ((btp::int8_py, author_id))\
    ((btp::text_py, content))\
)


#define WITH_TIMESTAMPS PLAIN_CLASS_DEFINITION(\
    (test_app, with_timestamps),\
    ((btp::timestamptz_py, created_at))\
    ((btp::timestamptz_py, updated_at))\
)


#define POST_STATUS ENUM_CLASS_DEFINITION(\
    (test_app, post_status),\
    (published)\
    (waiting_approval)\
    (draft)\
)


#define POST COMPOSED_CLASS_DEFINITION(\
    (test_app, post),\
    ((btp::int8_py, id))\
    ((btp::text_py, title))\
    ((test_app::post_status, status)),\
    (AUTHORED)(WITH_TIMESTAMPS)\
)


#define COMMENT COMPOSED_CLASS_DEFINITION(\
    (test_app, comment),\
    ((btp::int8_py, id))\
    ((btp::int8_py, post_id)),\
    (AUTHORED)(WITH_TIMESTAMPS)\
)


#define COMMENT_POST PLAIN_CLASS_DEFINITION(\
    (test_app, comment_post),\
    ((test_app::comment, comment))\
    ((test_app::post, post))\
    ((btp::text_py, description))\
    ((test_app::author, author))\
)


#define DOMAIN ALIAS_CLASS_DEFINITION(\
    (test_app, domain),\
    INT8_PY\
)


#endif
