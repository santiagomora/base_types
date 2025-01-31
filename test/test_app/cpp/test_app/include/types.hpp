#ifndef TEST_APP_TYPES
#define TEST_APP_TYPES


#include "./definitions.hpp"
#include "base_types/include/types.hpp"


// DEBUG clear && g++ -P -E -I/usr/include/boost -I../../../../../base_types/cpp -I./ types.hpp

namespace test_app {

CPP_DATACLASS_DECLARATION(TEST_APP_AUTHOR);
CPP_DATACLASS_DECLARATION(TEST_APP_AUTHORED);
CPP_DATACLASS_DECLARATION(TEST_APP_WITH_TIMESTAMPS);
CPP_ENUM_DECLARATION(TEST_APP_POST_STATUS);
CPP_DATACLASS_DECLARATION(TEST_APP_POST);
CPP_DATACLASS_DECLARATION(TEST_APP_COMMENT);
CPP_DATACLASS_DECLARATION(TEST_APP_COMMENT_POST);

const author&
test_function_receives_author_correctly(const author& a);

const comment_post&
test_function_receives_comment_post_correctly(const comment_post&);


const with_timestamps&
test_function_receives_wt_subclass_correctly(const with_timestamps&);

}


#endif
