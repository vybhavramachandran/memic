// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/exports.h>
#include <pybind11/pybind11.h>
#include <string>
// #include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
// #include <biogears/cdm/CommonDataModel.h>
// #include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/assessments/SEUrinalysisMicroscopic.h>
#include <biogears/schema/cdm/PatientAssessments.hxx>
#include <biogears/cdm/properties/SEScalarAmount.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEUrinalysisMicroscopic, m)
{

  py::class_<biogears::SEUrinalysisMicroscopic, biogears::SEPatientAssessment>(m, "SEUrinalysisMicroscopic")
    .def(py::init<>())
    .def("TypeTag", &biogears::SEUrinalysisMicroscopic::TypeTag)
    .def("classname", py::overload_cast<>(&biogears::SEUrinalysisMicroscopic::classname, py::const_))
    .def("Reset", &biogears::SEUrinalysisMicroscopic::Reset)
    .def("Clear", &biogears::SEUrinalysisMicroscopic::Clear)
    .def("Load", &biogears::SEUrinalysisMicroscopic::Load)
    .def("Unload", py::overload_cast<>(&biogears::SEUrinalysisMicroscopic::Unload))
    .def("GetObservationType", &biogears::SEUrinalysisMicroscopic::GetObservationType)
    .def("SetObservationType", &biogears::SEUrinalysisMicroscopic::SetObservationType)
    .def("InvalidateObservationType", &biogears::SEUrinalysisMicroscopic::InvalidateObservationType)
    .def("HasRedBloodCellsResult", &biogears::SEUrinalysisMicroscopic::HasRedBloodCellsResult)
    .def("GetRedBloodCellsResult", &biogears::SEUrinalysisMicroscopic::GetRedBloodCellsResult)
    .def("HasWhiteBloodCellsResult", &biogears::SEUrinalysisMicroscopic::HasWhiteBloodCellsResult)
    .def("GetWhiteBloodCellsResult", &biogears::SEUrinalysisMicroscopic::GetWhiteBloodCellsResult)
    .def("HasEpithelialCellsResult", &biogears::SEUrinalysisMicroscopic::HasEpithelialCellsResult)
    .def("GetEpithelialCellsResult", &biogears::SEUrinalysisMicroscopic::GetEpithelialCellsResult)
    .def("SetEpithelialCellsResult", &biogears::SEUrinalysisMicroscopic::SetEpithelialCellsResult)
    .def("InvalidateEpithelialCellsResult", &biogears::SEUrinalysisMicroscopic::InvalidateEpithelialCellsResult)
    .def("HasCastsResult", &biogears::SEUrinalysisMicroscopic::HasCastsResult)
    .def("GetCastsResult", &biogears::SEUrinalysisMicroscopic::GetCastsResult)
    .def("HasCrystalsResult", &biogears::SEUrinalysisMicroscopic::HasCrystalsResult)
    .def("GetCrystalsResult", &biogears::SEUrinalysisMicroscopic::GetCrystalsResult)
    .def("SetCrystalsResult", &biogears::SEUrinalysisMicroscopic::SetCrystalsResult)
    .def("InvalidateCrystalsResult", &biogears::SEUrinalysisMicroscopic::InvalidateCrystalsResult)
    .def("HasBacteriaResult", &biogears::SEUrinalysisMicroscopic::HasBacteriaResult)
    .def("GetBacteriaResult", &biogears::SEUrinalysisMicroscopic::GetBacteriaResult)
    .def("SetBacteriaResult", &biogears::SEUrinalysisMicroscopic::SetBacteriaResult)
    .def("InvalidateBacteriaResult", &biogears::SEUrinalysisMicroscopic::InvalidateBacteriaResult)
    .def("HasTrichomonadsResult", &biogears::SEUrinalysisMicroscopic::HasTrichomonadsResult)
    .def("GetTrichomonadsResult", &biogears::SEUrinalysisMicroscopic::GetTrichomonadsResult)
    .def("SetTrichomonadsResult", &biogears::SEUrinalysisMicroscopic::SetTrichomonadsResult)
    .def("InvalidateTrichomonadsResult", &biogears::SEUrinalysisMicroscopic::InvalidateTrichomonadsResult)
    .def("HasYeastResult", &biogears::SEUrinalysisMicroscopic::HasYeastResult)
    .def("GetYeastResult", &biogears::SEUrinalysisMicroscopic::GetYeastResult)
    .def("SetYeastResult", &biogears::SEUrinalysisMicroscopic::SetYeastResult)
    .def("InvalidateYeastResult", &biogears::SEUrinalysisMicroscopic::InvalidateYeastResult);
  // .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECompleteBloodCount::ToString,py::const_))

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}