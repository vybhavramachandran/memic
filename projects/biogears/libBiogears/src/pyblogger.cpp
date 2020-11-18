#include "../include/biogears/cdm/utils/Logger.h"

#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pyblogger, m) {

    py::class_<biogears::Logger>(m, "Logger")
    .def(py::init<std::string&, std::string&>())

    .def(py::init<char*, char*>());


 
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}