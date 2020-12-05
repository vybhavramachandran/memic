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
#include <biogears/cdm/patient/conditions/SEDehydration.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>




namespace py = pybind11;




PYBIND11_MODULE(pybSEDehydration, m) {


    py::class_<biogears::SEDehydration, biogears::SEPatientCondition>(m, "SEDehydration")
    .def(py::init<>())
    .def("Clear",&biogears::SEDehydration::Clear)
    .def("IsValid",&biogears::SEDehydration::IsValid)
    .def("Load",&biogears::SEDehydration::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEDehydration::Unload,py::const_))
    .def("GetName",&biogears::SEDehydration::GetName)
    .def("GetName_cStr",&biogears::SEDehydration::GetName_cStr)
    .def("HasDehydrationFraction",&biogears::SEDehydration::HasDehydrationFraction)
    .def("GetDehydrationFraction",&biogears::SEDehydration::GetDehydrationFraction)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEDehydration::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}