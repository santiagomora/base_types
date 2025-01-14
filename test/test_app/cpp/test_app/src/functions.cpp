#include <cstdint>
#include <iostream>


#include "../include/types.hpp"

namespace ta = test_app;


const ta::author&
ta::test_function_receives_author_correctly(
    const ta::author& a
) {
    std::cout << "id: " << a.id.value() << std::endl;
    std::cout << "name: " << a.name.value() << std::endl;
    static ta::author d(1, std::string("hola"));
    return d;
}


const ta::comment_post&
ta::test_function_receives_comment_post_correctly(
    const ta::comment_post& cp
) {
    std::cout << "comment: " << cp.comment.id.value() << std::endl;
    std::cout << "post: " << cp.post.id.value() << std::endl;
    std::cout << "author: " << cp.author.id.value() << std::endl;
    std::cout << "description: " << cp.description.value() << std::endl;
    return cp;
}


const ta::with_timestamps&
ta::test_function_receives_wt_subclass_correctly(
    const ta::with_timestamps& cp
) {
    std::cout << "created_at: " << cp.created_at.to_string() << std::endl;
    std::cout << "updated_at: " << cp.updated_at.to_string() << std::endl;
    return cp;
}
