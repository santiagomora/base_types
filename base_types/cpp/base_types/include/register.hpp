# ifndef PG_DEFINITION_BUILTIN_REGISTRY
# define PG_DEFINITION_BUILTIN_REGISTRY


#include <pybind11/pybind11.h>
#include "./types.hpp"


using namespace btp;


template <typename T> 
py::class_<T, std::unique_ptr<T>>& register_int(
    py::module_& m, const char* name
){
    static py::class_<T, std::unique_ptr<T>> c = py::class_<T, std::unique_ptr<T>>(m, name)
        .def(py::init<long int>())
        .def(py::pickle(
            [](const T& a) { return py::make_tuple(a.value()); },
            [](py::tuple t) { return T(t[0].cast<long int>()); }
        ))
        .def("__str__", [](const T& self){
            return std::to_string(self.value());
        })
        .def_static("set_py_cls", &T::set_py_cls);
    return c;
}

template <typename T>
py::class_<T, std::unique_ptr<T>>& register_float(
    py::module_& m, const char* name
){
    static py::class_<T, std::unique_ptr<T>> c = py::class_<T, std::unique_ptr<T>>(m, name)
        .def(py::init<double>())
        .def(py::pickle(
            [](const T& a) { return py::make_tuple(a.value()); },
            [](py::tuple t) { return T(t[0].cast<double>()); }
        ))
        .def("__str__", [](const T& self){
            return std::to_string(self.value());
        })
        .def_static("set_py_cls", &T::set_py_cls);
    return c;
}


py::class_<bool_py, std::unique_ptr<bool_py>>& register_bool(
    py::module_& m, const char* name
){
    static py::class_<bool_py, std::unique_ptr<bool_py>> c = py::class_<bool_py, std::unique_ptr<bool_py>>(m, name)
        .def(py::init([](const bool_py& other) {
            return std::unique_ptr<bool_py>(new bool_py(other));
        }))
        .def(py::init<bool>())
        .def(py::pickle(
            [](const bool_py& a) { return py::make_tuple(a.value());},
            [](py::tuple t) { return bool_py(t[0].cast<bool>());}
        ))
        .def("__eq__", [](const bool_py& self, const bool_py& other){
            return self.value() == other.value();
        })
        .def("__eq__", [](const bool_py& self, const py::bool_& other){
            return self.value() == other.cast<bool>();
        })
        .def("__ne__", [](const bool_py& self, const bool_py& other){
            return self.value() != other.value();
        })
        .def("__ne__", [](const bool_py& self, const py::bool_& other){
            return self.value() != other.cast<bool>();
        })
        .def("__and__", [](const bool_py& self, const bool_py& other){
            return self.value() && other.value();
        })
        .def("__and__", [](const bool_py& self, const py::bool_& other){
            return self.value() && other.cast<bool>();
        })
        .def("__or__", [](const bool_py& self, const bool_py& other){
            return self.value() || other.value();
        })
        .def("__or__", [](const bool_py& self, const py::bool_& other){
            return self.value() || other.cast<bool>();
        })
        .def("__str__", [](const bool_py& self){
            return std::to_string(self.value());
        })
        .def_static("set_py_cls", &bool_py::set_py_cls);
    return c;
}


py::class_<timestamptz_py, std::unique_ptr<timestamptz_py>>& register_timestamptz(
    py::module_& m, const char* name
){
    static py::class_<timestamptz_py, std::unique_ptr<timestamptz_py>> c = py::class_<timestamptz_py, std::unique_ptr<timestamptz_py>>(m, name)
        .def(py::init([](const timestamptz_py& other) {
            return std::unique_ptr<timestamptz_py>(new timestamptz_py(other));
        }))
        .def(py::init<std::string>())
        .def("__str__", [](const timestamptz_py& self){
            return self.to_string();
        })
        .def_static("set_py_cls", &timestamptz_py::set_py_cls);
    return c;
}


py::class_<timetz_py, std::unique_ptr<timetz_py>>& register_timetz(
    py::module_& m, const char* name
){
    static py::class_<timetz_py, std::unique_ptr<timetz_py>> c = py::class_<timetz_py, std::unique_ptr<timetz_py>>(m, name)
        .def(py::init([](const timetz_py& other) {
            return std::unique_ptr<timetz_py>(new timetz_py(other));
        }))
        .def(py::init<std::string>())
        .def("__str__", [](const timetz_py& self){
            return self.to_string();
        })
        .def_static("set_py_cls", &timetz_py::set_py_cls);
    return c;
}


py::class_<date_py, std::unique_ptr<date_py>>& register_date(
    py::module_& m, const char* name
){
    static py::class_<date_py, std::unique_ptr<date_py>> c = py::class_<date_py, std::unique_ptr<date_py>>(m, name)
        .def(py::init([](const date_py& other) {
            return std::unique_ptr<date_py>(new date_py(other));
        }))
        .def(py::init<std::string>())
        .def("__str__", [](const date_py& self){
            return self.to_string();
        })
        .def_static("set_py_cls", &date_py::set_py_cls);
    return c;
}


py::class_<text_py, std::unique_ptr<text_py>>& register_text(
    py::module_& m, const char* name
){
    static py::class_<text_py, std::unique_ptr<text_py>> c = py::class_<text_py, std::unique_ptr<text_py>>(m, name)
        .def(py::init([](const text_py& other) {
            return std::unique_ptr<text_py>(new text_py(other));
        }))
        .def(py::init<std::string>())
        .def("__str__", [](const text_py& self){
            return self.value();
        })
        .def_static("set_py_cls", &text_py::set_py_cls);
    return c;
}


# endif
