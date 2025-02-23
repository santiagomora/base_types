#ifndef TEST_APP_TYPES
#define TEST_APP_TYPES
#include "core_types/macros/declaration.hpp"
#include "core_types/typing/backend.hpp"
#include "core_types/typing/interface.hpp"
#include "definition.hpp"


// DEBUG clear && g++ -P -E -I/usr/include/boost -I/home/smora/sgs/dev/python/core/include/ -I/home/smora/.pyenv/versions/3.12.0/include/python3.12/ -I./include types.hpp


namespace test_app 
{

CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHOR);
CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHORED);
CPP_CLASSDEF_DECLARATION(TEST_APP_WITH_TIMESTAMPS);
CPP_ENUMDEF_DECLARATION(TEST_APP_POST_STATUS);
CPP_CLASSDEF_DECLARATION(TEST_APP_POST);
CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT);
CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT_POST);
CPP_ALIASDEF_DECLARATION(TEST_APP_DOMAIN);

}


namespace test_app::interface
{

IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHOR);
IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHORED);
IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_WITH_TIMESTAMPS);
IFACE_CPP_ENUMDEF_DECLARATION(TEST_APP_POST_STATUS);
IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_POST);
IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT);
IFACE_CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT_POST);
IFACE_CPP_ALIASDEF_DECLARATION(TEST_APP_DOMAIN);

const author&
test_function_receives_author_correctly(const author& a);

const comment_post&
test_function_receives_comment_post_correctly(const comment_post&);


const with_timestamps&
test_function_receives_wt_subclass_correctly(const with_timestamps&);

}


#endif
