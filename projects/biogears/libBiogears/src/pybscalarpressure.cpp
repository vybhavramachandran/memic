#include "../include/biogears/cdm/properties/SEScalarPressure.h"

#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybscalarpresssure, m) {

    py::class_<biogears::SEScalarPressure>(m, "SEScalarPressure")
    .def(py::init<>())

 
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}