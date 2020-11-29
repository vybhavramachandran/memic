// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SECardiacArrest.h>
#include <biogears/schema/cdm/Scenario.hxx>


namespace py = pybind11;




PYBIND11_MODULE(pybSECardiacArrest, m) {


    py::class_<biogears::SECardiacArrest>(m, "SECardiacArrest")
    .def(py::init<>())    
    .def("TypeTag",&biogears::SECardiacArrest::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SECardiacArrest::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SECardiacArrest::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SECardiacArrest::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SECardiacArrest::IsActive,py::const_))
    .def("Load",&biogears::SECardiacArrest::Load)
    .def("Unload",py::overload_cast<>(&biogears::SECardiacArrest::Unload,py::const_))
    // .def("HasSeverity",&biogears::SECardiacArrest::HasSeverity)
    // .def("GetSeverity",&biogears::SECardiacArrest::GetSeverity)
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECardiacArrest::ToString,py::const_));


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}