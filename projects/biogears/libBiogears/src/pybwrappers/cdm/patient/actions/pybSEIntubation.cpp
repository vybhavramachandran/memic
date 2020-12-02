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
#include <biogears/cdm/patient/actions/SEIntubation.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/properties/SEScalarTimeMassPerVolume.h>
namespace py = pybind11;




PYBIND11_MODULE(pybSEIntubation, m) {


    py::class_<biogears::SEIntubation>(m, "SEIntubation")
    .def(py::init<>())
    .def("TypeTag",&biogears::SEIntubation::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEIntubation::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SEIntubation::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SEIntubation::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SEIntubation::IsActive,py::const_))
    .def("Load",&biogears::SEIntubation::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEIntubation::Unload,py::const_))
    .def("GetType",&biogears::SEIntubation::GetType)
    .def("SetType",&biogears::SEIntubation::SetType)
    .def("HasType",&biogears::SEIntubation::HasType)
    .def("InvalidateType",&biogears::SEIntubation::InvalidateType)
    


    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEIntubation::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}