#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarFlowCompliance.h>
#include <biogears/cdm/properties/SEScalarFlowResistance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerMass.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarMassPerTime.h>
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarPressureTimePerVolumeArea.h>
#include <biogears/cdm/properties/SEScalarAmountPerTime.h>
#include <biogears/cdm/system/SESystem.h>
#include <biogears/cdm/system/physiology/SEGastrointestinalSystem.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

#include <biogears/schema/cdm/Physiology.hxx>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEGastrointestinalSystem, m)
{
  py::module_::import("pybSESystem");

  py::class_<biogears::SEGastrointestinalSystem, biogears::SESystem>(m, "SEGastrointestinalSystem")
    .def(py::init<biogears::Logger*>())
    .def("HasChymeAbsorptionRate",&biogears::SEGastrointestinalSystem::HasChymeAbsorptionRate)
    .def("GetChymeAbsorptionRate", py::overload_cast<>(&biogears::SEGastrointestinalSystem::GetChymeAbsorptionRate))
    .def("GetChymeAbsorptionRate", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEGastrointestinalSystem::GetChymeAbsorptionRate, py::const_))
    .def("HasStomachContents",&biogears::SEGastrointestinalSystem::HasStomachContents)
    .def("GetStomachContents", py::overload_cast<>(&biogears::SEGastrointestinalSystem::GetStomachContents))
    .def("GetStomachContents", py::overload_cast<>(&biogears::SEGastrointestinalSystem::GetStomachContents, py::const_))
    .def("RemoveStomachContents",&biogears::SEGastrointestinalSystem::RemoveStomachContents)
    .def("GetDrugTransitStates", py::overload_cast<>(&biogears::SEGastrointestinalSystem::GetDrugTransitStates))
    .def("GetDrugTransitStates", py::overload_cast<const biogears::SESubstance&>(&biogears::SEGastrointestinalSystem::GetDrugTransitStates, py::const_))
    .def("NewDrugTransitState",&biogears::SEGastrointestinalSystem::NewDrugTransitState)
    .def("GetPhysiologyRequestGraph", py::overload_cast<>(&biogears::SEGastrointestinalSystem::GetPhysiologyRequestGraph, py::const_))

#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}