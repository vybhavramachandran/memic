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
#include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/conditions/SEStarvation.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>
#include <biogears/cdm/properties/SEScalarArea.h>



namespace py = pybind11;




PYBIND11_MODULE(pybSEStarvation, m) {


    py::class_<biogears::SEStarvation, biogears::SEPatientCondition>(m, "SEStarvation")
    .def(py::init<>())
    .def("Clear",&biogears::SEStarvation::Clear)
    .def("IsValid",&biogears::SEStarvation::IsValid)
    .def("Load",&biogears::SEStarvation::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEStarvation::Unload,py::const_))
    .def("GetName",&biogears::SEStarvation::GetName)
    .def("GetName_cStr",&biogears::SEStarvation::GetName_cStr)
    .def("HasTimeSinceMeal",&biogears::SEStarvation::HasTimeSinceMeal)
    .def("GetTimeSinceMeal",&biogears::SEStarvation::GetTimeSinceMeal)
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEStarvation::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}