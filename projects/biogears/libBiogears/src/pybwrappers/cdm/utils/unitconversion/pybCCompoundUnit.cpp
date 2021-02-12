#include <biogears/cdm/utils/Logger.h>
#include <biogears/cdm/properties/SEScalarTime.h>

#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybCCompoundUnit, m) {

    std::cout<<"pybCCompoundUnit called";
    py::class_<biogears::CCompoundUnit>(m, "CCompoundUnit");



 
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}