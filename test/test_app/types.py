import base_types as bt
import test_app.cpp.wrapper as ta


class author(ta.author, metaclass=bt.compound):
    id: bt.int8
    name: bt.text


class with_timestamps(ta.with_timestamps, metaclass=bt.compound):
    created_at: bt.timestamptz
    updated_at: bt.timestamptz


class authored(ta.authored, metaclass=bt.compound):
    author_id: bt.int8
    content: bt.text


class post_status(ta.post_status, metaclass=bt.enum):
    pass


class post(ta.post, metaclass=bt.compound):
    author_id: bt.int8
    content: bt.text
    created_at: bt.timestamptz
    updated_at: bt.timestamptz
    id: bt.int8
    title: bt.text
    status: post_status


class comment(ta.comment, metaclass=bt.compound):
    author_id: bt.int8
    content: bt.text
    created_at: bt.timestamptz
    updated_at: bt.timestamptz
    id: bt.int8
    post_id: bt.int8


class comment_post(ta.comment_post, metaclass=bt.compound):
    comment: comment
    post: post
    description: bt.text
    author: author


class domain(
    ta.domain, metaclass=bt.builtin, default=bt.literal(1),
    validator=bt.check(name='test', predicate=bt.this() > bt.literal(0))
):
    pass
