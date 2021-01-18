#include <biogears/cdm/patient/actions/SEPupillaryResponse.h>
#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarAmountPerTime.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarFlowResistance.h>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarHeatCapacitancePerMass.h>
#include <biogears/cdm/properties/SEScalarMass.h>
#include <biogears/cdm/properties/SEScalarMassPerTime.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarPressureTimePerVolumeArea.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarVolumePerTimeArea.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/system/SESystem.h>

#include <biogears/cdm/system/physiology/SEEndocrineSystem.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

#include <biogears/schema/cdm/Physiology.hxx>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEEndocrineSystem, m)
{
  py::module_::import("pybSESystem");

  py::class_<biogears::SEEndocrineSystem, biogears::SESystem>(m, "SEEndocrineSystem")
    .def(py::init<biogears::Logger*>())
    .def("HasInsulinSynthesisRate", &biogears::SEEndocrineSystem::HasInsulinSynthesisRate)
    .def("GetInsulinSynthesisRate", py::overload_cast<>(&biogears::SEEndocrineSystem::GetInsulinSynthesisRate))
    .def("GetInsulinSynthesisRate", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEEndocrineSystem::GetInsulinSynthesisRate, py::const_))
    .def("HasGlucagonSynthesisRate", &biogears::SEEndocrineSystem::HasGlucagonSynthesisRate)
    .def("GetGlucagonSynthesisRate", py::overload_cast<>(&biogears::SEEndocrineSystem::GetGlucagonSynthesisRate))
    .def("GetGlucagonSynthesisRate", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEEndocrineSystem::GetGlucagonSynthesisRate, py::const_));
 

#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}