#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarFlowResistance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerMass.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarPressureTimePerVolumeArea.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeArea.h>
#include <biogears/cdm/system/SESystem.h>
#include <biogears/cdm/system/physiology/SEEnergySystem.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

#include <biogears/schema/cdm/Physiology.hxx>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEEnergySystem, m)
{
  py::module_::import("pybSESystem");

  py::class_<biogears::SEEnergySystem, biogears::SESystem>(m, "SEEnergySystem")
    .def(py::init<biogears::Logger*>())
    .def("GetTotalMetabolicRate", py::overload_cast<>(&biogears::SEEnergySystem::GetTotalMetabolicRate))
    .def("GetTotalMetabolicRate", py::overload_cast<const biogears::PowerUnit&>(&biogears::SEEnergySystem::GetTotalMetabolicRate,py::const_))
    .def("GetCoreTemperature", py::overload_cast<>(&biogears::SEEnergySystem::GetCoreTemperature))
    .def("GetCoreTemperature", py::overload_cast<const biogears::TemperatureUnit&>(&biogears::SEEnergySystem::GetCoreTemperature,py::const_))
    .def("GetAchievedExerciseLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetAchievedExerciseLevel))
    .def("GetAchievedExerciseLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetAchievedExerciseLevel,py::const_))
    .def("GetFatigueLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetFatigueLevel))
    .def("GetFatigueLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetFatigueLevel,py::const_))
    .def("GetTotalWorkRateLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetTotalWorkRateLevel))
    .def("GetTotalWorkRateLevel", py::overload_cast<>(&biogears::SEEnergySystem::GetTotalWorkRateLevel,py::const_));

#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}