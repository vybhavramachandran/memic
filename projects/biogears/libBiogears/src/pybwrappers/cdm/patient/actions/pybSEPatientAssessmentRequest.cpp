// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEPatientAssessmentRequest.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/properties/SEScalarTimeMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarTime.h>
namespace py = pybind11;




PYBIND11_MODULE(pybSEPatientAssessmentRequest, m) {


    py::class_<biogears::SEPatientAssessmentRequest, biogears::SEPatientAction>(m, "SEPatientAssessmentRequest")
    .def(py::init<>())
    .def("TypeTag",&biogears::SEPatientAssessmentRequest::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEPatientAssessmentRequest::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SEPatientAssessmentRequest::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SEPatientAssessmentRequest::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SEPatientAssessmentRequest::IsActive,py::const_))
    .def("Load",&biogears::SEPatientAssessmentRequest::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEPatientAssessmentRequest::Unload,py::const_))
    .def("GetType",&biogears::SEPatientAssessmentRequest::GetType)
    .def("SetType",&biogears::SEPatientAssessmentRequest::SetType)
    .def("HasType",&biogears::SEPatientAssessmentRequest::HasType)
    .def("InvalidateType",&biogears::SEPatientAssessmentRequest::InvalidateType)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEPatientAssessmentRequest::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}