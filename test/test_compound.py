

# test for inheritance policy
# def test_composite_domain_subclass_merges_check_constraints() -> None:
#     class test(pg.composite):
#         field_1: pg.int2
# 
#     class domain1(test):
#         field_1: Annotated[pg.int2,
#                            pg.check(name='field1_greater_than_0',
#                                     predicate=pg.this() >= pg.literal(0))]
# 
#     class domain2(domain1):
#         field_1: Annotated[pg.int2,
#                            pg.check(name='pg.field1_less_than_10',
#                                     predicate=pg.this() <= pg.literal(10))]
# 
#     class domain3(domain2):
#         pass
# 
#     try:
#         domain2(field_1=11)
#         assert False
#     except pydantic_core._pydantic_core.ValidationError as e:
#         assert str(e) == '1 validation error for domain2\n\
# field_1\n\
#   Value error, domain2_pg.field1_less_than_10: constraint validation failed for value "11" [type=value_error, input_value=11, input_type=int]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'
#     try:
#         domain2(field_1=-1)
#         assert False
#     except pydantic_core._pydantic_core.ValidationError as e:
#         assert str(e) == '1 validation error for domain1\n\
# field_1\n\
#   Value error, domain1_field1_greater_than_0: constraint validation failed for value "-1" [type=value_error, input_value=-1, input_type=int]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'
#     d2_instance = domain2(field_1=2)
#     assert d2_instance.field_1 == 2
#     try:
#         domain3(field_1=-1)
#         assert False
#     except pydantic_core._pydantic_core.ValidationError as e:
#         assert str(e) == '1 validation error for domain1\n\
# field_1\n\
#   Value error, domain1_field1_greater_than_0: constraint validation failed for value "-1" [type=value_error, input_value=-1, input_type=int]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'
#     try:
#         domain3(field_1=11)
#         assert False
#     except pydantic_core._pydantic_core.ValidationError as e:
#         assert str(e) == '1 validation error for domain2\n\
# field_1\n\
#   Value error, domain2_pg.field1_less_than_10: constraint validation failed for value "11" [type=value_error, input_value=11, input_type=int]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'

# 
# def test_composite_support_complex_type_creation() -> None:
#     class domain0(pg.int2):
#         pass
# 
#     @pg.default_value(2)
#     class domain1(domain0):
#         pass
# 
#     assert hasattr(domain1, '__pg_definition')
#     definition: dict[str, str] = getattr(domain1, '__pg_definition')()
#     assert 'default' in definition
#     assert definition['default'] is not None
#     assert isinstance(definition['default'], pg.literal)
#     assert isinstance(definition['default']._lit, domain1)
#     assert definition['default']._lit == 2
# 
#     class test1(pg.composite):
#         f1: pg.int2
#         f2: pg.timestamptz
#         f3: pg.timetz
#         f4: pg.date
# 
#     class test2(pg.composite):
#         f1: test1
#         f2: pg.int2
# 
#     d = test2(f1={'f1': 1, 'f2': '2020-10-11', 'f3': '10:20:01', 'f4': '2020-11-11'}, f2=1)
#     assert isinstance(d.f1.f1, pg.int2)
#     assert isinstance(d.f1.f2, pg.timestamptz)
#     assert isinstance(d.f1.f3, pg.timetz)
#     assert isinstance(d.f1.f4, pg.date)
#     assert isinstance(d.f2, pg.int2)
# 
#     class constrained_datetime(
#         pg.timestamptz, check_predicate=pg.check(
#             name='constrained_datetime_check', predicate=pg.this() > pg.literal('2020-10-10')
#         )
#     ):
#         pass
# 
#     class constrained_date(pg.date):
#         pass
# 
#     class test3(pg.composite):
#         f1: pg.int2
#         f2: constrained_datetime
#         f3: pg.timetz
#         f4: constrained_date
# 
#     class test4(pg.composite):
#         f1: test3
#         f2: pg.int2
# 
#     d = test4(f1={'f1': 1, 'f2': '2020-10-11', 'f3': '10:20:01', 'f4': '2020-11-11'}, f2=1)
#     assert isinstance(d.f1.f1, pg.int2)
#     assert isinstance(d.f1.f2, constrained_datetime)
#     assert isinstance(d.f1.f3, pg.timetz)
#     assert isinstance(d.f1.f4, constrained_date)
#     assert isinstance(d.f2, pg.int2)
# 
#     try:
#         d = test4(f1={'f1': 1, 'f2': '2020-10-09', 'f3': '10:20:01', 'f4': '2020-11-11'}, f2=1)
#     except pydantic_core._pydantic_core.ValidationError as e:
#         print(str(e))
#         assert str(e) == '1 validation error for test4\n\
# f1.f2\n\
#   Value error, constrained_datetime_check: constraint validation failed for value "2020-10-09 00:00:00" [type=value_error, input_value=\'2020-10-09\', input_type=str]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'

# 
# def test_composite_misc_check_tests() -> None:
#     class test(pg.composite):
#         f1: pg.int2
#         f2: pg.int2
# 
#     class domain(test):
#         f2: Annotated[pg.int2, pg.check(name='f2_gt_f1', predicate=pg.this() > pg.field('f1'))]
# 
#     try:
#         domain(f1=2, f2=1)
#         assert False
#     except pydantic_core._pydantic_core.ValidationError as e:
#         assert str(e) == '1 validation error for domain\n\
# f2\n\
#   Value error, domain_f2_gt_f1: constraint validation failed for value "1" [type=value_error, input_value=1, input_type=int]\n\
#     For further information visit https://errors.pydantic.dev/2.10/v/value_error'
# 
# 
# def test_definition_flow_detects_inconsistent_base_classes_and_fields() -> None:
# 
#     try:
#         class test1(pg.table):
#             field_1: pg.int2
# 
#         class test2(test1):
#             field_1: pg.text
# 
#     except pg.FlowException as e:
#         error: Optional[pg.NodeException] = e.get_error('table-definition-flow',
#                                                          'table-validate-consistent-base-classes-node')
#         assert error is not None
#         assert str(error) == f'Field field_1 type conflict. Declared in multiple base classes: {pg.int2}, {pg.text}' or \
#             str(error) == f'Field field_1 type conflict. Declared in multiple base classes: {pg.text}, {pg.int2}'
