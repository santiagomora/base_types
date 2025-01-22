import sys
import base_types as bt
from datetime import datetime, timezone
from dataclasses import dataclass
sys.path.append('.')
import test_app.types as tat
import test_app.cpp.wrapper as tw


def test_types_get_instanced_correctly() -> None:
    try:
        tat.domain(-1)
        assert False
    except ValueError as e:
        pass
    def test_create() -> tat.author:
        id = 1
        name = 'test_author'
        return tat.author(id, name)
    test_author = test_create()
    created_at = datetime.now(timezone.utc).isoformat()
    updated_at = datetime.now(timezone.utc).isoformat()
    test_post = tat.post(1, 'test title', tat.post_status.waiting_approval, test_author.id, 'test content', created_at, updated_at)
    assert test_post.id == 1
    assert test_post.title == 'test title'
    assert test_post.content == 'test content'
    assert test_post.created_at == f'{created_at.split("+")[0]}UTC+00'
    assert test_post.updated_at == f'{updated_at.split("+")[0]}UTC+00'

    def test_create_comment_post_from_instances() -> tat.comment_post:
        author = tat.author(1, 'test author')
        post = tat.post(1, 'test post title', tat.post_status.waiting_approval, author.id, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        comment = tat.comment(1, post.id, author.id, 'comment content', datetime.now().isoformat(), datetime.now().isoformat())
        description = 'test'
        return tat.comment_post(author=author, comment=comment, post=post, description=description)

    cp_test1 = test_create_comment_post_from_instances()
    assert hasattr(cp_test1, 'comment')
    assert isinstance(cp_test1.comment, tat.comment)
    assert hasattr(cp_test1, 'author')
    assert isinstance(cp_test1.author, tat.author)
    assert hasattr(cp_test1, 'post')
    assert isinstance(cp_test1.post, tat.post)
    assert hasattr(cp_test1, 'description')
    assert isinstance(cp_test1.description, bt.text)

    def test_create_comment_post_from_dicts() -> tat.comment_post:
        author = {'id': 1, 'name': 'test author'}
        post = tat.post(1, 'test post title', tat.post_status.waiting_approval, author['id'], 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        comment = {'id': 1, 'post_id': post.id, 'author_id': author['id'], 'content': 'comment content', 'created_at': datetime.now().isoformat(), 'updated_at': datetime.now().isoformat()}
        description = 'test'
        return tat.comment_post(author=author, comment=comment, post=post, description=description)

    cp_test1 = test_create_comment_post_from_dicts()
    assert hasattr(cp_test1, 'comment')
    assert isinstance(cp_test1.comment, tat.comment)
    assert hasattr(cp_test1, 'author')
    assert isinstance(cp_test1.author, tat.author)
    assert hasattr(cp_test1, 'post')
    assert isinstance(cp_test1.post, tat.post)
    assert hasattr(cp_test1, 'description')
    assert isinstance(cp_test1.description, bt.text)


def test_functions_gets_called_correctly() -> None:
    def test_create() -> tat.author:
        id = 1
        name = 'test_author'
        return tat.author(id, name)
    a = tw.test_function_receives_author_correctly(test_create()).to_py()
    assert isinstance(a, tat.author)
    assert a.id == 1
    assert a.name == 'hola'

    def test_create_comment_post_from_instances() -> tat.comment_post:
        author = tat.author(1, 'test author')
        post = tat.post(1, 'test post title', tat.post_status.waiting_approval, author.id, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        comment = tat.comment(1, post.id, author.id, 'comment content', datetime.now().isoformat(), datetime.now().isoformat())
        description = 'test'
        return tat.comment_post(author=author, comment=comment, post=post, description=description)

    cp = tw.test_function_receives_comment_post_correctly(test_create_comment_post_from_instances())

    # DOESNT WORK DOESNT DOWNCAST TO WITH_TIMESTAMPS TYPE!
    # post = tat.post(1, 'test post title', tat.post_status.waiting_approval, 1, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
    # w = tw.test_function_receives_wt_subclass_correctly(post)
    # print(w)


def test_functions_gets_called_correctly() -> None:
    try:
        a = tat.authored(-1, 'test content')
        assert False
    except ValueError:
        pass
    try:
        a = tat.authored(1, 'test content')
    except ValueError:
        assert False
    try:
        b = tat.post(1, 'test post title', tat.post_status.waiting_approval, -1, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        assert False
    except ValueError:
        pass
    try:
        b = tat.post(1, 'test post title', tat.post_status.waiting_approval, -1, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        assert False
    except ValueError:
        pass
    try:
        b = tat.post(1, 'test post title', tat.post_status.waiting_approval, 11, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
        assert False
    except ValueError:
        pass
    try:
        b = tat.post(1, 'test post title', tat.post_status.waiting_approval, 5, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
    except ValueError:
        assert False


def test_defaults_are_applied_correctly() -> None:
    @dataclass
    class base:
        f1: tat.post_status
        f2: tat.domain
        @classmethod
        def set_py_cls(cls, *args):
            pass
        @classmethod
        @property
        def _cpp_field_names(cls):
            return ('f1', 'f2', )
        @classmethod
        @property
        def _cpp_field_types(cls):
            return (tw.post_status, bt.int8, )

    class test(base, metaclass=bt.compound):
        f1: tat.post_status
        f2: tat.domain
    t = test()
    assert hasattr(t, 'f1')
    assert t.f1 == tat.post_status.waiting_approval
    assert hasattr(t, 'f2')
    assert t.f2 == tat.domain(1)

    try:
        t2 = test(f2=-1)
        assert False
    except ValueError:
        pass
    print(type(bt.int8(3) % bt.int1(5)))


def test_incomplete_inheritance_is_detected() -> None:
    try:
        @bt.inherits(tat.with_timestamps, tat.authored)
        class comment(tw.comment, metaclass=bt.compound):
            id: bt.int8
            post_id: bt.int8
            author_id: bt.int8
            content: bt.text
        assert False
    except TypeError:
        pass
    try:
        @bt.inherits(tat.with_timestamps, tat.authored)
        class comment(tw.comment, metaclass=bt.compound):
            id: bt.int8
            post_id: bt.int8
            author_id: bt.int8
            content: bt.text
            created_at: bt.timestamptz
        assert False
    except TypeError:
        pass
    try:
        @bt.inherits(tat.with_timestamps, tat.authored)
        class comment(tw.comment, metaclass=bt.compound):
            id: bt.int8
            post_id: bt.int8
            author_id: bt.int8
            content: bt.text
            created_at: bt.timestamptz
            updated_at: bt.timestamptz
    except TypeError:
        assert False
    try:
        @bt.inherits(tat.with_timestamps, tat.authored)
        class comment(tw.comment, metaclass=bt.compound):
            id: bt.int8
            post_id: bt.int8
            author_id: bt.int8
            content: bt.text
            created_at: bt.int8
            updated_at: bt.timestamptz
        assert False
    except TypeError:
        pass

