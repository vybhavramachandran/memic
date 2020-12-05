// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
// #include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
// #include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/conditions/SELobarPneumonia.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>
#include <biogears/cdm/properties/SEScalarArea.h>



namespace py = pybind11;




PYBIND11_MODULE(pybSELobarPneumonia, m) {


    py::class_<biogears::SELobarPneumonia, biogears::SEPatientCondition>(m, "SELobarPneumonia")
    .def(py::init<>())
    .def("Clear",&biogears::SELobarPneumonia::Clear)
    .def("IsValid",&biogears::SELobarPneumonia::IsValid)
    .def("Load",&biogears::SELobarPneumonia::Load)
    .def("Unload",py::overload_cast<>(&biogears::SELobarPneumonia::Unload,py::const_))
    .def("GetName",&biogears::SELobarPneumonia::GetName)
    .def("GetName_cStr",&biogears::SELobarPneumonia::GetName_cStr)
    .def("HasSeverity",&biogears::SELobarPneumonia::HasSeverity)
    .def("GetSeverity",&biogears::SELobarPneumonia::GetSeverity)
    .def("HasLeftLungAffected",&biogears::SELobarPneumonia::HasLeftLungAffected)
    .def("GetLeftLungAffected",&biogears::SELobarPneumonia::GetLeftLungAffected)
    .def("HasRightLungAffected",&biogears::SELobarPneumonia::HasRightLungAffected)
    .def("GetRightLungAffected",&biogears::SELobarPneumonia::GetRightLungAffected)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SELobarPneumonia::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}