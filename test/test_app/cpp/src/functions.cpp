// #include <cstdint>
// #include <iostream>
// 
// 
// #include "test_app/types.hpp"
// 
// 
// namespace ta = test_app;
// namespace ct = core_types;
// 
// 
// const ta::author&
// ta::test_function_receives_author_correctly(
//     const ta::author& a
// ) {
//     if (a.id.has_value())
//     {
//         std::cout << "id: " << a.id.value().value() << std::endl;
//     }
//     std::cout << "name: " << a.name.value() << std::endl;
//     static ta::author d(1, std::string("hola"));
//     return d;
// }
// 
// 
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
