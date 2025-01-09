from .builtin import builtin
from .compound import compound
from .enums import enum
import base_types.cpp.wrapper as bw
from .check import\
    check,\
    Operand,\
    OperandDefinitionContext,\
    this,\
    field,\
    literal


__all__ = ['this', 'field', 'literal', 'check', 'Operand', 'OperandDefinitionContext', 'builtin', 'enum', 'compound', 'int1', 'int2', 'int4', 'int8', 'float4', 'float8', 'char', 'bool', 'text', 'timestamptz', 'timetz', 'date']


class int1(bw.int1, metaclass=builtin):
    pass


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


class char(bw.int1, metaclass=builtin):
    pass


class bool(bw.bool, metaclass=builtin):
    pass


class text(bw.text, metaclass=builtin):
    pass


class timestamptz(bw.timestamptz, metaclass=builtin):
    pass


class timetz(bw.timetz, metaclass=builtin):
    pass


class date(bw.date, metaclass=builtin):
    pass
