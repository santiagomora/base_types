# ifndef BT_DEFINITION_OVERLOAD
# define BT_DEFINITION_OVERLOAD

// W is the desired return type
// T is the first parameter spec type (T in numeric_wrapper)
// U is the second parameter spec type (T in numeric_wrapper)
// V is the second parameter spec type (V in numeric_wrapper)

# define REGISTER_CONSTRUCTOR(CLS, T, U, V)\
    ((CLS).def(py::init([](const U& other){       \
        return std::unique_ptr<T>(                \
            new T(static_cast<V>(other.value())));\
    })))

# define REGISTER_ARITHMETIC_OVERLOAD(CLS, PY_OP_NAME, OP, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const U& other){ \
        return T(self.value() OP other.value());                \
    }))

# define REGISTER_PY_ARITHMETIC_OVERLOAD(CLS, PY_OP_NAME, OP, PY, T, U)\
    ((CLS).def((PY_OP_NAME), [](const T& self, const PY& other){    \
        return T(self.value() OP other.cast<U>());                  \
    }))


# define MAKE_ARITHMETIC_COMPATIBLE(CLS, T, U, V)\
    REGISTER_CONSTRUCTOR(CLS, T, U, V);\
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

# endif
