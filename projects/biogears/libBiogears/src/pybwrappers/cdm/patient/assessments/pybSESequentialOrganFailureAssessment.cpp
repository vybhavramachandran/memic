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
#include <biogears/cdm/patient/assessments/SESequentialOrganFailureAssessment.h>
#include <biogears/cdm/properties/SEScalarMassPerAmount.h>
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include <biogears/schema/cdm/PatientAssessments.hxx>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalar.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSESequentialOrganFailureAssessment, m) {


    py::class_<biogears::SESequentialOrganFailureAssessment, biogears::SEPatientAssessment>(m, "SESequentialOrganFailureAssessment")
    .def(py::init<>())
    .def("TypeTag",&biogears::SESequentialOrganFailureAssessment::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SESequentialOrganFailureAssessment::classname,py::const_))
    .def("Reset",&biogears::SESequentialOrganFailureAssessment::Reset)
    .def("Clear",&biogears::SESequentialOrganFailureAssessment::Clear)
    .def("Load",&biogears::SESequentialOrganFailureAssessment::Load)
    .def("Unload",py::overload_cast<>(&biogears::SESequentialOrganFailureAssessment::Unload))
    .def("HasRespirationSOFA",&biogears::SESequentialOrganFailureAssessment::HasRespirationSOFA)
    .def("GetRespirationSOFA",&biogears::SESequentialOrganFailureAssessment::GetRespirationSOFA)
    .def("HasCoagulationSOFA",&biogears::SESequentialOrganFailureAssessment::HasCoagulationSOFA)
    .def("GetCoagulationSOFA",&biogears::SESequentialOrganFailureAssessment::GetCoagulationSOFA)
    .def("HasLiverSOFA",&biogears::SESequentialOrganFailureAssessment::HasLiverSOFA)
    .def("GetLiverSOFA",&biogears::SESequentialOrganFailureAssessment::GetLiverSOFA)
    .def("HasCardiovascularSOFA",&biogears::SESequentialOrganFailureAssessment::HasCardiovascularSOFA)
    .def("GetCardiovascularSOFA",&biogears::SESequentialOrganFailureAssessment::GetCardiovascularSOFA)
    .def("HasCentralNervousSOFA",&biogears::SESequentialOrganFailureAssessment::HasCentralNervousSOFA)
    .def("GetCentralNervousSOFA",&biogears::SESequentialOrganFailureAssessment::GetCentralNervousSOFA)
    .def("HasRenalSOFA",&biogears::SESequentialOrganFailureAssessment::HasRenalSOFA)
    .def("GetRenalSOFA",&biogears::SESequentialOrganFailureAssessment::GetRenalSOFA);

    
    // .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECompleteBloodCount::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}