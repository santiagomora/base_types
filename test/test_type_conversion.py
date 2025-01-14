import sys
import base_types as bt
from datetime import datetime, timezone
sys.path.append('.')
import test_app.types as tat
import test_app.cpp.wrapper as tw


def test_types_get_instanced_correctly() -> None:
    try:
        tat.domain(-1)
    except ValueError as e:
        assert str(e) == 'test: constraint validation failed for value "-1"'
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

    # DOESNT WORK!
    # post = tat.post(1, 'test post title', tat.post_status.waiting_approval, 1, 'test post content', datetime.now().isoformat(), datetime.now().isoformat())
    # w = tw.test_function_receives_wt_subclass_correctly(post)
    # print(w)
