// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SETensionPneumothorax.h>
#include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
// #include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/schema/cdm/Scenario.hxx>
namespace py = pybind11;




PYBIND11_MODULE(pybSETensionPneumothorax, m) {


    py::class_<biogears::SETensionPneumothorax, biogears::SEPatientAction>(m, "SETensionPneumothorax")
    .def(py::init<>())
    .def("TypeTag",&biogears::SETensionPneumothorax::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SETensionPneumothorax::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SETensionPneumothorax::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SETensionPneumothorax::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SETensionPneumothorax::IsActive,py::const_))
    .def("Load",&biogears::SETensionPneumothorax::Load)
    .def("Unload",py::overload_cast<>(&biogears::SETensionPneumothorax::Unload,py::const_))
    .def("GetType",&biogears::SETensionPneumothorax::GetType)
    .def("SetType",&biogears::SETensionPneumothorax::SetType)
    .def("HasType",&biogears::SETensionPneumothorax::HasType) 
    .def("InvalidateType",&biogears::SETensionPneumothorax::InvalidateType) 
    .def("HasSeverity",&biogears::SETensionPneumothorax::HasSeverity)
    .def("GetSeverity",&biogears::SETensionPneumothorax::GetSeverity)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SETensionPneumothorax::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}