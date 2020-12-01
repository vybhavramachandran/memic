#include <biogears/cdm/scenario/requests/SEDataRequest.h>
// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <string>
#include <biogears/cdm/properties/SEDecimalFormat.h>
#include <biogears/cdm/utils/unitconversion/CompoundUnit.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>
#include <biogears/cdm/scenario/requests/SEPhysiologyDataRequest.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEPhysiologyDataRequest, m) {


    py::class_<biogears::SEPhysiologyDataRequest, biogears::SEDataRequest>(m, "SEPhysiologyDataRequest")
    .def("Clear",&biogears::SEPhysiologyDataRequest::Clear)
    .def("Load",&biogears::SEPhysiologyDataRequest::Load)
    .def("HashCode",py::overload_cast<>(&biogears::SEPhysiologyDataRequest::HashCode,py::const_))
    .def("Unload",py::overload_cast<>(&biogears::SEPhysiologyDataRequest::Unload,py::const_));


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}