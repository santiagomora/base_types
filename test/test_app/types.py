import base_types as bt
import test_app.cpp.wrapper as ta


@bt.compound.set_default(
    value=bt.literal(10), field_name='id')
@bt.compound.set_default(
    value=bt.literal('test author'), field_name='name')
class author(ta.author, metaclass=bt.compound):
    pass


class with_timestamps(ta.with_timestamps, metaclass=bt.compound):
    pass


@bt.compound.set_check_predicate(
    predicate=bt.this() > bt.literal(0), field_name='author_id')
class authored(ta.authored, metaclass=bt.compound):
    pass


@bt.enum.set_default(ta.post_status.enum.waiting_approval)
class post_status(ta.post_status, metaclass=bt.enum):
    pass


@bt.compound.set_check_predicate(field_name='author_id', predicate=bt.this() < bt.literal(10))
class post(ta.post, metaclass=bt.compound):
    pass


class comment(ta.comment, metaclass=bt.compound):
    pass


class comment_post(ta.comment_post, metaclass=bt.compound):
    pass


@bt.builtin.set_default(bt.literal(1))
@bt.builtin.set_check_predicate(bt.this() > bt.literal(0))
class domain(bt.int8, metaclass=bt.builtin):
    pass
