from .builtin import\
    builtin,\
    Undefined
from .compound import\
    compound,\
    inherits,\
    InheritancePolicy
from .enums import enum
import base_types.cpp.wrapper as bw
from .predicate import\
    LogicOperand,\
    Operand,\
    OperandDefinitionContext,\
    this,\
    field,\
    literal
from numbers import\
    Number


__all__ = ['inherits', 'InheritancePolicy', 'this', 'field', 'literal', 'LogicOperand', 'Undefined', 'Operand', 'OperandDefinitionContext', 'builtin', 'enum', 'compound', 'int1', 'int2', 'int4', 'int8', 'float4', 'float8', 'char', 'bool', 'text', 'timestamptz', 'timetz', 'date']


LogicOperand.type_compatibility.register(bw.int8_py, Number)
LogicOperand.type_compatibility.register(bw.int4_py, Number)
LogicOperand.type_compatibility.register(bw.int2_py, Number)
LogicOperand.type_compatibility.register(bw.float8_py, Number)
LogicOperand.type_compatibility.register(bw.float4_py, Number)
# LogicOperand.type_compatibility.register(bw.date_py, bw.date_py)
LogicOperand.type_compatibility.register(bw.text_py, str)
# LogicOperand.type_compatibility.register(bw.text_py, bw.text_py)
# LogicOperand.type_compatibility.register(bw.timestamptz_py, bw.timestamptz_py)
LogicOperand.type_compatibility.register(bw.bool_py, bool)
LogicOperand.type_compatibility.register(compound, compound)


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
