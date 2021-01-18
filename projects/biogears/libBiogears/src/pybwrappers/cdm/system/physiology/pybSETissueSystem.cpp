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
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarPressureTimePerVolumeArea.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeArea.h>
#include <biogears/cdm/system/SESystem.h>
#include <biogears/cdm/system/physiology/SETissueSystem.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

#include <biogears/schema/cdm/Physiology.hxx>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSETissueSystem, m)
{
  py::module_::import("pybSESystem");

  py::class_<biogears::SETissueSystem, biogears::SESystem>(m, "SETissueSystem")
    .def(py::init<biogears::Logger*>())
    .def("GetCarbonDioxideProductionRate", py::overload_cast<>(&biogears::SETissueSystem::GetCarbonDioxideProductionRate))
    .def("GetCarbonDioxideProductionRate", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SETissueSystem::GetCarbonDioxideProductionRate, py::const_))
    .def("GetDehydrationFraction", py::overload_cast<>(&biogears::SETissueSystem::GetDehydrationFraction))
    .def("GetDehydrationFraction", py::overload_cast<>(&biogears::SETissueSystem::GetDehydrationFraction, py::const_))
    .def("GetExtracellularFluidVolume", py::overload_cast<>(&biogears::SETissueSystem::GetExtracellularFluidVolume))
    .def("GetExtracellularFluidVolume", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SETissueSystem::GetExtracellularFluidVolume, py::const_))
    .def("GetExtravascularFluidVolume", py::overload_cast<>(&biogears::SETissueSystem::GetExtravascularFluidVolume))
    .def("GetExtravascularFluidVolume", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SETissueSystem::GetExtravascularFluidVolume, py::const_))
    .def("GetIntracellularFluidVolume", py::overload_cast<>(&biogears::SETissueSystem::GetIntracellularFluidVolume))
    .def("GetIntracellularFluidVolume", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SETissueSystem::GetIntracellularFluidVolume, py::const_))
    .def("GetTotalBodyFluidVolume", py::overload_cast<>(&biogears::SETissueSystem::GetTotalBodyFluidVolume))
    .def("GetTotalBodyFluidVolume", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SETissueSystem::GetTotalBodyFluidVolume, py::const_))
    .def("GetIntracellularFluidPH", py::overload_cast<>(&biogears::SETissueSystem::GetIntracellularFluidPH))
    .def("GetIntracellularFluidPH", py::overload_cast<>(&biogears::SETissueSystem::GetIntracellularFluidPH, py::const_))
    .def("GetOxygenConsumptionRate", py::overload_cast<>(&biogears::SETissueSystem::GetOxygenConsumptionRate))
    .def("GetOxygenConsumptionRate", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SETissueSystem::GetOxygenConsumptionRate, py::const_))
    .def("GetRespiratoryExchangeRatio", py::overload_cast<>(&biogears::SETissueSystem::GetRespiratoryExchangeRatio))
    .def("GetRespiratoryExchangeRatio", py::overload_cast<>(&biogears::SETissueSystem::GetRespiratoryExchangeRatio, py::const_))
    .def("GetLiverInsulinSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetLiverInsulinSetPoint))
    .def("GetLiverInsulinSetPoint", py::overload_cast<const biogears::AmountPerVolumeUnit&>(&biogears::SETissueSystem::GetLiverInsulinSetPoint, py::const_))
    .def("GetLiverGlucagonSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetLiverGlucagonSetPoint))
    .def("GetLiverGlucagonSetPoint", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SETissueSystem::GetLiverGlucagonSetPoint, py::const_))
    .def("GetMuscleInsulinSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetMuscleInsulinSetPoint))
    .def("GetMuscleInsulinSetPoint", py::overload_cast<const biogears::AmountPerVolumeUnit&>(&biogears::SETissueSystem::GetMuscleInsulinSetPoint, py::const_))
    .def("GetMuscleGlucagonSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetMuscleGlucagonSetPoint))
    .def("GetMuscleGlucagonSetPoint", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SETissueSystem::GetMuscleGlucagonSetPoint, py::const_))
    .def("GetFatInsulinSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetFatInsulinSetPoint))
    .def("GetFatInsulinSetPoint", py::overload_cast<const biogears::AmountPerVolumeUnit&>(&biogears::SETissueSystem::GetFatInsulinSetPoint, py::const_))
    .def("GetFatGlucagonSetPoint", py::overload_cast<>(&biogears::SETissueSystem::GetFatGlucagonSetPoint))
    .def("GetFatGlucagonSetPoint", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SETissueSystem::GetFatGlucagonSetPoint, py::const_))
    .def("GetLiverGlycogen", py::overload_cast<>(&biogears::SETissueSystem::GetLiverGlycogen))
    .def("GetLiverGlycogen", py::overload_cast<const biogears::MassUnit&>(&biogears::SETissueSystem::GetLiverGlycogen, py::const_))
    .def("GetMuscleGlycogen", py::overload_cast<>(&biogears::SETissueSystem::GetMuscleGlycogen))
    .def("GetMuscleGlycogen", py::overload_cast<const biogears::MassUnit&>(&biogears::SETissueSystem::GetMuscleGlycogen, py::const_))
    .def("GetStoredProtein", py::overload_cast<>(&biogears::SETissueSystem::GetStoredProtein))
    .def("GetStoredProtein", py::overload_cast<const biogears::MassUnit&>(&biogears::SETissueSystem::GetStoredProtein, py::const_))
    .def("GetStoredFat", py::overload_cast<>(&biogears::SETissueSystem::GetStoredFat))
    .def("GetStoredFat", py::overload_cast<const biogears::MassUnit&>(&biogears::SETissueSystem::GetStoredFat, py::const_));


#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}