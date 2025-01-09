import sys
import base_types as bt
from datetime import datetime
sys.path.append('.')
import test_app.types as tat


def test_types() -> None:
    try:
        tat.domain(-1)
    except ValueError as e:
        assert str(e) == 'test: constraint validation failed for value "-1"'
    def test_create() -> tat.author:
        id = 1
        name = 'test_author'
        return tat.author(id, name)
    test_author = test_create()
    print(test_author)
    test_post = tat.post(test_author.id, 'test content', datetime.now().isoformat(), datetime.now().isoformat(), 1, 'test title', 1)
    print(test_post)


test_types()
