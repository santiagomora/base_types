from .cpp.module import wrapper as bw
from .metaclasses import builtin


class int2(bw.int2, metaclass=builtin):
    pass


class int4(bw.int4, metaclass=builtin):
    pass


class int8(bw.int8, metaclass=builtin):
    pass


class float4(bw.float4, metaclass=builtin):
    pass


class float8(bw.float8, metaclass=builtin):
    pass


class int1(bw.int1, metaclass=builtin):
    pass


class bool(bw.boolean, metaclass=builtin):
    pass


class text(bw.text, metaclass=builtin):
    pass


class timestamptz(bw.timestamptz, metaclass=builtin):
    pass


class date(bw.date, metaclass=builtin):
    pass
