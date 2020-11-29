// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEBrainInjury.h>
#include <biogears/schema/cdm/Scenario.hxx>


namespace py = pybind11;




PYBIND11_MODULE(pybSEBrainInjury, m) {


    py::class_<biogears::SEBrainInjury>(m, "SEBrainInjury")
    .def(py::init<>())    
    .def("TypeTag",&biogears::SEBrainInjury::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEBrainInjury::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SEBrainInjury::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SEBrainInjury::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SEBrainInjury::IsActive,py::const_))
    .def("Load",&biogears::SEBrainInjury::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEBrainInjury::Unload,py::const_))
    .def("HasSeverity",&biogears::SEBrainInjury::HasSeverity)
    .def("GetSeverity",&biogears::SEBrainInjury::GetSeverity)
    .def("GetType",&biogears::SEBrainInjury::GetType)
    .def("SetType",&biogears::SEBrainInjury::SetType)
    .def("HasType",&biogears::SEBrainInjury::HasType)
    .def("InvalidateType",&biogears::SEBrainInjury::InvalidateType)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEBrainInjury::ToString,py::const_));


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}