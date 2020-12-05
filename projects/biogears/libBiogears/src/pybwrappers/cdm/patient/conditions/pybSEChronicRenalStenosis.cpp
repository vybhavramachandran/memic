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
#include <biogears/cdm/patient/conditions/SEChronicRenalStenosis.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>




namespace py = pybind11;




PYBIND11_MODULE(pybSEChronicRenalStenosis, m) {


    py::class_<biogears::SEChronicRenalStenosis, biogears::SEPatientCondition>(m, "SEChronicRenalStenosis")
    .def(py::init<>())
    // .def("TypeTag",&biogears::SEChronicAnemia::TypeTag)
    // .def("classname",py::overload_cast<>(&biogears::SEChronicAnemia::classname,py::const_))
    // .def("Reset",&biogears::SEChronicAnemia::Reset)
    .def("Clear",&biogears::SEChronicRenalStenosis::Clear)
    .def("IsValid",&biogears::SEChronicRenalStenosis::IsValid)
    .def("Load",&biogears::SEChronicRenalStenosis::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEChronicRenalStenosis::Unload,py::const_))
    .def("GetName",&biogears::SEChronicRenalStenosis::GetName)
    .def("GetName_cStr",&biogears::SEChronicRenalStenosis::GetName_cStr)
    .def("HasLeftKidneySeverity",&biogears::SEChronicRenalStenosis::HasLeftKidneySeverity)
    .def("GetLeftKidneySeverity",&biogears::SEChronicRenalStenosis::GetLeftKidneySeverity)

    .def("HasRightKidneySeverity",&biogears::SEChronicRenalStenosis::HasRightKidneySeverity)
    .def("GetRightKidneySeverity",&biogears::SEChronicRenalStenosis::GetRightKidneySeverity)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEChronicRenalStenosis::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}