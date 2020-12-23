// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <string>
#include <vector>

#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartment.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartment.h>
#include <biogears/cdm/compartment/thermal/SEThermalCompartment.h>
#include <biogears/cdm/compartment/tissue/SETissueCompartment.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/circuit/SECircuitManager.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/schema/cdm/Compartment.hxx>
#include <pybind11/pybind11.h>
#include <biogears/cdm/compartment/SECompartment.h>
#include <string>

namespace py = pybind11;

PYBIND11_MODULE(pybSECompartment, m)
{

  py::module_::import("pybLogger");

  py::class_<biogears::SECompartment, biogears::Loggable>(m, "SECompartment")
  .def("Clear",&biogears::SECompartment::Clear)
  .def("Load",&biogears::SECompartment::Load)
  .def("GetName",&biogears::SECompartment::GetName)
  .def("GetName_cStr",&biogears::SECompartment::GetName_cStr);


#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}