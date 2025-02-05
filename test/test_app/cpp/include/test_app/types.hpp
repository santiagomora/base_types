#ifndef TEST_APP_TYPES
#define TEST_APP_TYPES


#include "base_types/macros/definition.hpp"
#include "base_types/types.hpp"
#include "test_app/definition.hpp"


// DEBUG clear && g++ -P -E -I/usr/include/boost -I../../../../../base_types/cpp -I./ types.hpp

namespace test_app {

CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHOR);
CPP_CLASSDEF_DECLARATION(TEST_APP_AUTHORED);
CPP_CLASSDEF_DECLARATION(TEST_APP_WITH_TIMESTAMPS);
CPP_ENUMDEF_DECLARATION(TEST_APP_POST_STATUS);
CPP_CLASSDEF_DECLARATION(TEST_APP_POST);
CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT);
CPP_CLASSDEF_DECLARATION(TEST_APP_COMMENT_POST);
CPP_ALIASDEF_DECLARATION(TEST_APP_DOMAIN);

const author&
test_function_receives_author_correctly(const author& a);

const comment_post&
test_function_receives_comment_post_correctly(const comment_post&);


const with_timestamps&
test_function_receives_wt_subclass_correctly(const with_timestamps&);

}


#endif
