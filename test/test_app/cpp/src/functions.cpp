#include <cstdint>
#include <iostream>
#include "test_app/types.hpp"


namespace ta = test_app;
namespace ct = core_types;
namespace ct_i = core_types::interface;


namespace test_app::interface
{

void test_function_receives_author_correctly() {
    ta::author t1 = ta::author(1, "test 1");
    ta::author t2 = ta::author(2, "test 2");
    ta::author t3 = ta::author(3, "test 3");
    auto r = std::make_tuple(t1, t2, t3, 2, 3.5);
    auto tx = ct_i::tp_wrap<std::tuple<author, author, author, ct_i::int1, ct_i::float4>>(r);
    std::cout << std::get<0>(tx).to_string() << std::endl;
    std::cout << std::get<1>(tx).to_string() << std::endl;
    std::cout << std::get<2>(tx).to_string() << std::endl;
    std::cout << std::get<3>(tx).to_string() << std::endl;
    std::cout << std::get<4>(tx).to_string() << std::endl;
    auto d = tp_unwrap(tx);
    std::cout << ct::tp_to_string(d) << std::endl;
}

}


// const ta::comment_post&
// ta::test_function_receives_comment_post_correctly(
//     const ta::comment_post& cp
// ) {
//     std::cout << "comment: " << cp.comment.id.value() << std::endl;
//     std::cout << "post: " << cp.post.id.value() << std::endl;
//     if (cp.author.id.has_value())
//     {
//         std::cout << "id: " << cp.author.id.value().value() << std::endl;
//     }
//     std::cout << "description: " << cp.description.value() << std::endl;
//     return cp;
// }
// 
// 
// const ta::with_timestamps&
// ta::test_function_receives_wt_subclass_correctly(
//     const ta::with_timestamps& cp
// ) {
//     if (cp.created_at.has_value())
//     {
//         std::cout << "created_at: " << cp.created_at.value().to_string() << std::endl;
//     }
//     std::cout << "updated_at: " << ct::tp_to_string(cp.updated_at) << std::endl;
//     return cp;
// }
