// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/cdm/patient/actions/SEUrinate.h>
// #include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
// #include <biogears/cdm/CommonDataModel.h>
// #include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/assessments/SEPulmonaryFunctionTest.h>
#include <biogears/cdm/properties/SEScalarMassPerAmount.h>
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include <biogears/schema/cdm/PatientAssessments.hxx>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/properties/SEFunctionVolumeVsTime.h>
#include <biogears/cdm/system/physiology/SEBloodChemistrySystem.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/system/physiology/SERespiratorySystem.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEPulmonaryFunctionTest, m) {


    py::class_<biogears::SEPulmonaryFunctionTest, biogears::SEPatientAssessment>(m, "SEPulmonaryFunctionTest")
    .def(py::init<>())
    .def("TypeTag",&biogears::SEPulmonaryFunctionTest::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEPulmonaryFunctionTest::classname,py::const_))
    .def("Reset",&biogears::SEPulmonaryFunctionTest::Reset)
    .def("Clear",&biogears::SEPulmonaryFunctionTest::Clear)
    .def("Load",&biogears::SEPulmonaryFunctionTest::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEPulmonaryFunctionTest::Unload))
    .def("GetNumberOfPlotPoints",&biogears::SEPulmonaryFunctionTest::GetNumberOfPlotPoints)
    .def("SetNumberOfPlotPoints",&biogears::SEPulmonaryFunctionTest::SetNumberOfPlotPoints)
    .def("HasExpiratoryReserveVolume",&biogears::SEPulmonaryFunctionTest::HasExpiratoryReserveVolume)
    .def("GetExpiratoryReserveVolume",&biogears::SEPulmonaryFunctionTest::GetExpiratoryReserveVolume)
    .def("HasForcedVitalCapacity",&biogears::SEPulmonaryFunctionTest::HasForcedVitalCapacity)
    .def("GetForcedVitalCapacity",&biogears::SEPulmonaryFunctionTest::GetForcedVitalCapacity)
    .def("HasForcedExpiratoryVolume",&biogears::SEPulmonaryFunctionTest::HasForcedExpiratoryVolume)
    .def("GetForcedExpiratoryVolume",&biogears::SEPulmonaryFunctionTest::GetForcedExpiratoryVolume)
    .def("HasForcedExpiratoryFlow",&biogears::SEPulmonaryFunctionTest::HasForcedExpiratoryFlow)
    .def("GetForcedExpiratoryFlow",&biogears::SEPulmonaryFunctionTest::GetForcedExpiratoryFlow)
    .def("HasFunctionalResidualCapacity",&biogears::SEPulmonaryFunctionTest::HasFunctionalResidualCapacity)
    .def("GetFunctionalResidualCapacity",&biogears::SEPulmonaryFunctionTest::GetFunctionalResidualCapacity)
    .def("HasInspiratoryCapacity",&biogears::SEPulmonaryFunctionTest::HasInspiratoryCapacity)
    .def("GetInspiratoryCapacity",&biogears::SEPulmonaryFunctionTest::GetInspiratoryCapacity)
    .def("HasInspiratoryReserveVolume",&biogears::SEPulmonaryFunctionTest::HasInspiratoryReserveVolume)
    .def("GetInspiratoryReserveVolume",&biogears::SEPulmonaryFunctionTest::GetInspiratoryReserveVolume)
    .def("HasMaximumVoluntaryVentilation",&biogears::SEPulmonaryFunctionTest::HasMaximumVoluntaryVentilation)
    .def("GetMaximumVoluntaryVentilation",&biogears::SEPulmonaryFunctionTest::GetMaximumVoluntaryVentilation)
    .def("HasPeakExpiratoryFlow",&biogears::SEPulmonaryFunctionTest::HasPeakExpiratoryFlow)
    .def("GetPeakExpiratoryFlow",&biogears::SEPulmonaryFunctionTest::GetPeakExpiratoryFlow)
    
    .def("HasResidualVolume",&biogears::SEPulmonaryFunctionTest::HasResidualVolume)
    .def("GetResidualVolume",&biogears::SEPulmonaryFunctionTest::GetResidualVolume)
    .def("HasSlowVitalCapacity",&biogears::SEPulmonaryFunctionTest::HasSlowVitalCapacity)
    .def("GetSlowVitalCapacity",&biogears::SEPulmonaryFunctionTest::GetSlowVitalCapacity)

    .def("HasTotalLungCapacity",&biogears::SEPulmonaryFunctionTest::HasTotalLungCapacity)
    .def("GetTotalLungCapacity",&biogears::SEPulmonaryFunctionTest::GetTotalLungCapacity)
    .def("HasVitalCapacity",&biogears::SEPulmonaryFunctionTest::HasVitalCapacity)
    .def("GetVitalCapacity",&biogears::SEPulmonaryFunctionTest::GetVitalCapacity)
    .def("HasLungVolumePlot",&biogears::SEPulmonaryFunctionTest::HasLungVolumePlot)
    .def("GetLungVolumePlot",&biogears::SEPulmonaryFunctionTest::GetLungVolumePlot);

    
    // .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECompleteBloodCount::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}