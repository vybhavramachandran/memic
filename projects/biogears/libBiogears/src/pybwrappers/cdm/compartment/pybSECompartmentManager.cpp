// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <string>
#include <vector>

#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/circuit/SECircuitManager.h>
#include <biogears/cdm/compartment/SECompartment.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartment.h>
#include <biogears/cdm/compartment/fluid/SEGasCompartmentGraph.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartment.h>
#include <biogears/cdm/compartment/fluid/SELiquidCompartmentGraph.h>
#include <biogears/cdm/compartment/thermal/SEThermalCompartment.h>
#include <biogears/cdm/compartment/tissue/SETissueCompartment.h>
#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/schema/cdm/Compartment.hxx>
#include <biogears/schema/cdm/Scenario.hxx>
#include <pybind11/pybind11.h>
#include <string>
#include <biogears/cdm/compartment/SECompartmentManager.h>


namespace py = pybind11;

PYBIND11_MODULE(pybSECompartmentManager, m)
{

  py::module_::import("pybLogger");

  py::class_<biogears::SECompartmentManager, biogears::Loggable>(m, "SECompartmentManager")
    .def(py::init<biogears::SESubstanceManager&>())
    .def("Clear", &biogears::SECompartmentManager::Clear)
    .def("Load", &biogears::SECompartmentManager::Load)
    .def("Unload", py::overload_cast<>(&biogears::SECompartmentManager::Unload, py::const_))
    .def("StateChange", &biogears::SECompartmentManager::StateChange)
    // .def("UpdateLinks", py::overload_cast<>(&biogears::SECompartmentManager::UpdateLinks))
    // .def("UpdateLinks", py::overload_cast<biogears::SEGasCompartmentGraph&>(&biogears::SECompartmentManager::UpdateLinks))
    // .def("UpdateLinks", py::overload_cast<biogears::SELiquidCompartmentGraph&>(&biogears::SECompartmentManager::UpdateLinks))  
    // .def("HasCompartment", py::overload_cast<CDM::enumCompartmentType::value, const char*>(&biogears::SECompartmentManager::HasCompartment, py::const_))
    // .def("HasCompartment", py::overload_cast<CDM::enumCompartmentType::value, const std::string&>(&biogears::SECompartmentManager::HasCompartment, py::const_))
    // .def("GetCompartment", py::overload_cast<CDM::enumCompartmentType::value, const char*>(&biogears::SECompartmentManager::GetCompartment))
    // .def("GetCompartment", py::overload_cast<CDM::enumCompartmentType::value, const std::string&>(&biogears::SECompartmentManager::GetCompartment))
    // .def("GetCompartment", py::overload_cast<CDM::enumCompartmentType::value, const char*>(&biogears::SECompartmentManager::GetCompartment, py::const_))
    // .def("GetCompartment", py::overload_cast<CDM::enumCompartmentType::value, const std::string&>(&biogears::SECompartmentManager::GetCompartment, py::const_));
    .def("CreateGasCompartment", py::overload_cast<const char*>(&biogears::SECompartmentManager::CreateGasCompartment))
    .def("CreateGasCompartment", py::overload_cast<const std::string&>(&biogears::SECompartmentManager::CreateGasCompartment))
    .def("HasGasCompartment", py::overload_cast<const char*>(&biogears::SECompartmentManager::HasGasCompartment,py::const_))
    .def("HasGasCompartment", py::overload_cast<const std::string&>(&biogears::SECompartmentManager::HasGasCompartment,py::const_))
    .def("GetGasCompartment", py::overload_cast<const char*>(&biogears::SECompartmentManager::GetGasCompartment))
    .def("GetGasCompartment", py::overload_cast<const std::string&>(&biogears::SECompartmentManager::GetGasCompartment))
    .def("GetGasCompartment", py::overload_cast<const char*>(&biogears::SECompartmentManager::GetGasCompartment,py::const_))
    .def("GetGasCompartment", py::overload_cast<const std::string&>(&biogears::SECompartmentManager::GetGasCompartment,py::const_))
    .def("GetGasCompartments", &biogears::SECompartmentManager::GetGasCompartments)
    .def("GetGasLeafCompartments", &biogears::SECompartmentManager::GetGasLeafCompartments)
    .def("CreateGasLink", py::overload_cast<biogears::SEGasCompartment&, biogears::SEGasCompartment&, const char*>(&biogears::SECompartmentManager::CreateGasLink))
    .def("CreateGasLink", py::overload_cast<biogears::SEGasCompartment&, biogears::SEGasCompartment&, const std::string&>(&biogears::SECompartmentManager::CreateGasLink))
    .def("DeleteGasLink", py::overload_cast<const char*>(&biogears::SECompartmentManager::DeleteGasLink))
    .def("DeleteGasLink", py::overload_cast<const std::string&>(&biogears::SECompartmentManager::DeleteGasLink));

    
#ifdef VERSION_INFO
  m.attr("__version__")
    = VERSION_INFO;
#else
  m.attr("__version__")
    = "dev";
#endif
}