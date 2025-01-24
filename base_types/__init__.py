import base_types.cpp.wrapper as bw
from .predicate import\
    literal,\
    this,\
    field,\
    LogicOperand,\
    length,\
    OperandDefinitionContext
from .builtin import builtin
from .compound import compound
from .enums import enum


__all__ = ['builtin', 'compound', 'enum', 'int1', 'int2', 'int4', 'int8', 'float4', 'float8', 'bool', 'text', 'timestamptz', 'date', 'literal', 'this', 'field', 'LogicOperand', 'length', 'OperandDefinitionContext']


class int1(bw.int1_py, metaclass=builtin):
    pass


class int2(bw.int2_py, metaclass=builtin):
    pass


class int4(bw.int4_py, metaclass=builtin):
    pass


class int8(bw.int8_py, metaclass=builtin):
    pass


class float4(bw.float4_py, metaclass=builtin):
    pass


class float8(bw.float8_py, metaclass=builtin):
    pass


class bool(bw.bool_py, metaclass=builtin):
    pass


class text(bw.text_py, metaclass=builtin):
    pass


class timestamptz(bw.timestamptz_py, metaclass=builtin):
    pass


# class timetz(bw.timetz_py, metaclass=builtin):
#     pass


class date(bw.date_py, metaclass=builtin):
    pass
