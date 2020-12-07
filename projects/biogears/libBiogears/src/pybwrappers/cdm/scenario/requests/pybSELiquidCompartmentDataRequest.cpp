#include <biogears/cdm/scenario/requests/SELiquidCompartmentDataRequest.h>
#include <biogears/schema/cdm/Compartment.hxx>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>
#include <biogears/cdm/scenario/requests/SECompartmentSubstanceDataRequest.h>
#include <biogears/schema/cdm/Scenario.hxx>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <string>
#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSELiquidCompartmentDataRequest, m) {


    py::class_<biogears::SELiquidCompartmentDataRequest,biogears::SECompartmentSubstanceDataRequest>(m, "SELiquidCompartmentDataRequest")
    .def("Load",&biogears::SELiquidCompartmentDataRequest::Load)
    .def("Unload",py::overload_cast<>(&biogears::SELiquidCompartmentDataRequest::Unload,py::const_));

    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}