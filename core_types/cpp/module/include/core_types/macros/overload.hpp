# ifndef BT_DEFINITION_OVERLOAD
# define BT_DEFINITION_OVERLOAD

// W is the desired return type
// T is the first parameter spec type (T in numeric_wrapper)
// U is the second parameter spec type (T in numeric_wrapper)
// V is the second parameter spec type (V in numeric_wrapper)

# define REGISTER_ARITHMETIC_OVERLOAD(CLS, PY_OP_NAME, OP, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const U& other){ \
        return T(self.value() OP other.value());                \
    }))

# define REGISTER_PY_ARITHMETIC_OVERLOAD(CLS, PY_OP_NAME, OP, PY, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const PY& other){    \
        return T(self.value() OP other.cast<U>());                  \
    }))


# define MAKE_ARITHMETIC_COMPATIBLE(CLS, T, U, V)\
    REGISTER_ARITHMETIC_OVERLOAD((CLS), "__add__", +, T, U);\
    REGISTER_ARITHMETIC_OVERLOAD((CLS), "__sub__", -, T, U);\
    REGISTER_ARITHMETIC_OVERLOAD((CLS), "__truediv__", /, T, U);\
    REGISTER_ARITHMETIC_OVERLOAD((CLS), "__mul__", *, T, U)

# define MAKE_PY_ARITHMETIC_COMPATIBLE(CLS, PY, T, U)\
    REGISTER_PY_ARITHMETIC_OVERLOAD((CLS), "__add__", +, PY, T, U);\
    REGISTER_PY_ARITHMETIC_OVERLOAD((CLS), "__sub__", -, PY, T, U);\
    REGISTER_PY_ARITHMETIC_OVERLOAD((CLS), "__truediv__", /, PY, T, U);\
    REGISTER_PY_ARITHMETIC_OVERLOAD((CLS), "__mul__", *, PY, T, U)

// W is the desired return type
// T is the first parameter spec type (T in builtin_numeric)
// U is the second parameter spec type (T in builtin_numeric)
// V is the second parameter spec type (V in builtin_numeric)
# define REGISTER_LOGIC_OVERLOAD(CLS, PY_OP_NAME, OP, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const U& other){  \
        return self.value() OP other.value();                    \
    }))

# define REGISTER_PY_LOGIC_OVERLOAD(CLS, PY_OP_NAME, OP, PY, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const PY& other){  \
        return self.value() OP other.cast<U>();                   \
    }))

# define REGISTER_PY_STR_LOGIC_OVERLOAD(CLS, PY_OP_NAME, OP, PY, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const PY& other){  \
        return self.to_string() OP other.cast<U>();                   \
    }))

#define MAKE_LOGIC_OPERABLE(CLS, T, U)\
    REGISTER_LOGIC_OVERLOAD((CLS), "__lt__", <, T, U);\
    REGISTER_LOGIC_OVERLOAD((CLS), "__gt__", >, T, U);\
    REGISTER_LOGIC_OVERLOAD((CLS), "__le__", <=, T, U);\
    REGISTER_LOGIC_OVERLOAD((CLS), "__ge__", >=, T, U);\
    REGISTER_LOGIC_OVERLOAD((CLS), "__eq__", ==, T, U);\
    REGISTER_LOGIC_OVERLOAD((CLS), "__ne__", !=, T, U)


#define MAKE_PY_LOGIC_OPERABLE(CLS, PY, T, U)\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__lt__", <, PY, T, U);\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__gt__", >, PY, T, U);\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__le__", <=, PY, T, U);\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__ge__", >=, PY, T, U);\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__eq__", ==, PY, T, U);\
    REGISTER_PY_LOGIC_OVERLOAD((CLS), "__ne__", !=, PY, T, U)


#define MAKE_PY_STRING_COMPARABLE(CLS, PY, T, U)\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__lt__", <, PY, T, U);\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__gt__", >, PY, T, U);\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__le__", <=, PY, T, U);\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__ge__", >=, PY, T, U);\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__eq__", ==, PY, T, U);\
    REGISTER_PY_STR_LOGIC_OVERLOAD((CLS), "__ne__", !=, PY, T, U)

    // bl.def("__eq__", [](const core_types::boolean& self, const core_types::boolean& other){
    //         return self.value() == other.value();
    //     })
    //     .def("__eq__", [](const core_types::boolean& self, const py::bool_& other){
    //         return self.value() == other.cast<bool>();
    //     })
    //     .def("__ne__", [](const core_types::boolean& self, const core_types::boolean& other){
    //         return self.value() != other.value();
    //     })
    //     .def("__ne__", [](const core_types::boolean& self, const py::bool_& other){
    //         return self.value() != other.cast<bool>();
    //     })
    //     .def("__and__", [](const core_types::boolean& self, const core_types::boolean& other){
    //         return self.value() && other.value();
    //     })
    //     .def("__and__", [](const core_types::boolean& self, const py::bool_& other){
    //         return self.value() && other.cast<bool>();
    //     })
    //     .def("__or__", [](const core_types::boolean& self, const core_types::boolean& other){
    //         return self.value() || other.value();
    //     })
    //     .def("__or__", [](const core_types::boolean& self, const py::bool_& other){
    //         return self.value() || other.cast<bool>();
    //     })
    //     .def("__str__", [](const core_types::boolean& self){
    //         return std::to_string(self.value());
    //     });
    
    // core_types::int1 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::int1, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::int2, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::int4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::int8, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::float4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i1, core_types::int1, core_types::float8, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, core_types::int1, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, core_types::int1, core_types::int8_);
//     
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int1, core_types::int1);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int1, core_types::int2);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int1, core_types::int4);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int1, core_types::int8);
//     REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", +, py::int_, core_types::int1, core_types::int8_);
//     
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::int1);
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::int2);
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::int4);
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::int8);
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::float4);
//     MAKE_LOGIC_OPERABLE(i1, core_types::int1, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(i1, py::int_, core_types::int1, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(i1, py::float_, core_types::int1, core_types::float8_);
//     
//     // core_types::int2 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::int2, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::int1, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::int2, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::int4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::int8, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::float4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i2, core_types::int2, core_types::float8, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::int_, core_types::int2, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i1, py::float_, core_types::int2, core_types::int8_);
//     
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int2, core_types::int1);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int2, core_types::int2);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int2, core_types::int4);
//     REGISTER_ARITHMETIC_OVERLOAD(i1, "__mod__", %, core_types::int2, core_types::int8);
//     REGISTER_PY_ARITHMETIC_OVERLOAD(i1, "__mod__", %, py::int_, core_types::int2, core_types::int8_);
//     
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::int1);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::int2);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::int2);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::int4);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::int8);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::float4);
//     MAKE_LOGIC_OPERABLE(i2, core_types::int2, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(i2, py::int_, core_types::int2, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(i2, py::float_, core_types::int2, core_types::float8_);
//     
//     // core_types::int4 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::int1, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::int2, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::int4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::int8, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::float4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i4, core_types::int4, core_types::float8, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::int_, core_types::int4, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i4, py::float_, core_types::int4, core_types::int8_);
//     
//     REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, core_types::int4, core_types::int1);
//     REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, core_types::int4, core_types::int2);
//     REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, core_types::int4, core_types::int4);
//     REGISTER_ARITHMETIC_OVERLOAD(i4, "__mod__", %, core_types::int4, core_types::int8);
//     REGISTER_PY_ARITHMETIC_OVERLOAD(i4, "__mod__", %, py::int_, core_types::int4, core_types::int8_);
//     
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::int1);
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::int2);
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::int4);
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::int8);
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::float4);
//     MAKE_LOGIC_OPERABLE(i4, core_types::int4, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(i4, py::int_, core_types::int4, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(i4, py::float_, core_types::int4, core_types::float8_);
//     
//     // core_types::int8 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::int1, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::int2, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::int4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::int8, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::float4, core_types::int8_);
//     MAKE_ARITHMETIC_COMPATIBLE(i8, core_types::int8, core_types::float8, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::int_, core_types::int8, core_types::int8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(i8, py::float_, core_types::int8, core_types::int8_);
//     
//     REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, core_types::int8, core_types::int1);
//     REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, core_types::int8, core_types::int2);
//     REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, core_types::int8, core_types::int4);
//     REGISTER_ARITHMETIC_OVERLOAD(i8, "__mod__", %, core_types::int8, core_types::int8);
//     REGISTER_PY_ARITHMETIC_OVERLOAD(i8, "__mod__", %, py::int_, core_types::int8, core_types::int8_);
//     
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::int1);
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::int2);
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::int4);
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::int8);
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::float4);
//     MAKE_LOGIC_OPERABLE(i8, core_types::int8, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(i8, py::int_, core_types::int8, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(i8, py::float_, core_types::int8, core_types::float8_);
//     
//     // core_types::float4 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::int1, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::int2, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::int4, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::int8, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::float4, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f4, core_types::float4, core_types::float8, core_types::float8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::int_, core_types::float4, core_types::float8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(f4, py::float_, core_types::float4, core_types::float8_);
//     
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::int1);
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::int2);
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::int4);
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::int8);
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::float4);
//     MAKE_LOGIC_OPERABLE(f4, core_types::float4, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(f4, py::int_, core_types::float4, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(f4, py::float_, core_types::float4, core_types::float8_);
//     
//     // core_types::float8 OVERLOADS
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::int1, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::int2, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::int4, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::int8, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::float4, core_types::float8_);
//     MAKE_ARITHMETIC_COMPATIBLE(f8, core_types::float8, core_types::float8, core_types::float8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::int_, core_types::float8, core_types::float8_);
//     MAKE_PY_ARITHMETIC_COMPATIBLE(f8, py::float_, core_types::float8, core_types::float8_);
//     
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::int1);
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::int2);
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::int4);
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::int8);
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::float4);
//     MAKE_LOGIC_OPERABLE(f8, core_types::float8, core_types::float8);
//     MAKE_PY_LOGIC_OPERABLE(f8, py::int_, core_types::float8, core_types::int8_);
//     MAKE_PY_LOGIC_OPERABLE(f8, py::float_, core_types::float8, core_types::float8_);
//     
//     // MAKE_PY_STRING_COMPARABLE(tz, py::str, timetz_py, std::string);
//     // core_types::text overloads
//     MAKE_PY_STRING_COMPARABLE(tx, py::str, core_types::text, std::string);
//     
//     // core_types::timestamptz overloads
//     MAKE_PY_STRING_COMPARABLE(dtz, py::str, core_types::timestamptz, std::string);
//     MAKE_LOGIC_OPERABLE(dtz, core_types::timestamptz, core_types::timestamptz);
//     
//     // core_types::date overloads
//     MAKE_PY_STRING_COMPARABLE(dt, py::str, core_types::date, std::string);
//     MAKE_LOGIC_OPERABLE(dt, core_types::date, core_types::date);

# endif
