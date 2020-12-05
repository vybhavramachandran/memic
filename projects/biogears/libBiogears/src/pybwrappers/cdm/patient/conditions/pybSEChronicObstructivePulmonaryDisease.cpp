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
#include <biogears/cdm/patient/conditions/SEChronicObstructivePulmonaryDisease.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>




namespace py = pybind11;




PYBIND11_MODULE(pybSEChronicObstructivePulmonaryDisease, m) {


    py::class_<biogears::SEChronicObstructivePulmonaryDisease, biogears::SEPatientCondition>(m, "SEChronicObstructivePulmonaryDisease")
    .def(py::init<>())
    // .def("TypeTag",&biogears::SEChronicAnemia::TypeTag)
    // .def("classname",py::overload_cast<>(&biogears::SEChronicAnemia::classname,py::const_))
    // .def("Reset",&biogears::SEChronicAnemia::Reset)
    .def("Clear",&biogears::SEChronicObstructivePulmonaryDisease::Clear)
    .def("IsValid",&biogears::SEChronicObstructivePulmonaryDisease::IsValid)
    .def("Load",&biogears::SEChronicObstructivePulmonaryDisease::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEChronicObstructivePulmonaryDisease::Unload,py::const_))
    .def("GetName",&biogears::SEChronicObstructivePulmonaryDisease::GetName)
    .def("GetName_cStr",&biogears::SEChronicObstructivePulmonaryDisease::GetName_cStr)
    .def("HasBronchitisSeverity",&biogears::SEChronicObstructivePulmonaryDisease::HasBronchitisSeverity)
    .def("GetBronchitisSeverity",&biogears::SEChronicObstructivePulmonaryDisease::GetBronchitisSeverity)
    .def("HasEmphysemaSeverity",&biogears::SEChronicObstructivePulmonaryDisease::HasEmphysemaSeverity)
    .def("GetEmphysemaSeverity",&biogears::SEChronicObstructivePulmonaryDisease::GetEmphysemaSeverity)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEChronicObstructivePulmonaryDisease::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}