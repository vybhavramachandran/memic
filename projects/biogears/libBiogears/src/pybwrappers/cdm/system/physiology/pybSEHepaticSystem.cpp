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
#include <biogears/cdm/system/physiology/SEHepaticSystem.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/exports.h>
#include <biogears/schema/biogears/BioGearsPhysiology.hxx>

#include <biogears/schema/cdm/Physiology.hxx>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEHepaticSystem, m)
{
  py::module_::import("pybSESystem");

  py::class_<biogears::SEHepaticSystem, biogears::SESystem>(m, "SEHepaticSystem")
    .def(py::init<biogears::Logger*>())
    .def("HasKetoneProductionRate",&biogears::SEHepaticSystem::HasKetoneProductionRate)
    .def("GetKetoneProductionRate", py::overload_cast<>(&biogears::SEHepaticSystem::GetKetoneProductionRate))
    .def("GetKetoneProductionRate", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEHepaticSystem::GetKetoneProductionRate, py::const_))
    .def("HasHepaticGluconeogenesisRate",&biogears::SEHepaticSystem::HasHepaticGluconeogenesisRate)
    .def("GetHepaticGluconeogenesisRate", py::overload_cast<>(&biogears::SEHepaticSystem::GetHepaticGluconeogenesisRate))
    .def("GetHepaticGluconeogenesisRate", py::overload_cast<const biogears::MassPerTimeUnit&>(&biogears::SEHepaticSystem::GetHepaticGluconeogenesisRate, py::const_));

#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}