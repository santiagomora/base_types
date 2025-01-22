import base_types as bt
import test_app.cpp.wrapper as ta
from typing_extensions import\
    Annotated


class author(ta.author, metaclass=bt.compound):
    id: bt.int8
    name: bt.text


class with_timestamps(ta.with_timestamps, metaclass=bt.compound):
    created_at: bt.timestamptz
    updated_at: bt.timestamptz


class authored(ta.authored, metaclass=bt.compound):
    author_id: Annotated[bt.int8, bt.this() > bt.literal(0)]
    content: bt.text


class post_status(
    ta.post_status, metaclass=bt.enum,
    default=ta.post_status.waiting_approval
):
    pass


@bt.inherits(with_timestamps, authored)
class post(ta.post, metaclass=bt.compound):
    id: bt.int8
    title: bt.text
    status: post_status
    author_id: Annotated[bt.int8, bt.this() < bt.literal(10)]
    content: bt.text
    created_at: bt.timestamptz
    updated_at: bt.timestamptz


@bt.inherits(with_timestamps, authored)
class comment(ta.comment, metaclass=bt.compound):
    id: bt.int8
    post_id: bt.int8
    author_id: bt.int8
    content: bt.text
    created_at: bt.timestamptz
    updated_at: bt.timestamptz


class comment_post(ta.comment_post, metaclass=bt.compound):
    comment: comment
    post: post
    description: bt.text
    author: author


class domain(
    bt.int8, metaclass=bt.builtin, default=bt.literal(1),
    check_predicate=bt.this() > bt.literal(0)
):
    pass

# 
# class culo(ta.test_function_receives_author_correctly):
#     pass
