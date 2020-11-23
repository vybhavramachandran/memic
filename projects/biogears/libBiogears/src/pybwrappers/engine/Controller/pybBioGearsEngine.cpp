// #include "../include/biogears/cdm/system/physiology/SECardiovascularSystem.h"
// #include "../include/biogears/cdm/system/SESystem.h"
// #include "../include/biogears/cdm/properties/SEScalarPressure.h"


#include <biogears/engine/Controller/BioGearsEngine.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybBioGearsEngine, m) {

    py::class_<biogears::BioGearsEngine>(m, "BioGearsEngine")
    .def(py::init<biogears::Logger *>())
    .def(py::init<const char*>())
    .def(py::init<std::string&>())
    .def(py::init<biogears::Logger*, std::string&>())
    .def(py::init<biogears::Logger*, const char* >())
    .def(py::init<std::string&, std::string&>())
    .def(py::init<char*, char*>());
    // .def(py::init<std::string* *>());
}    