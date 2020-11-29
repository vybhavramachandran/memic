// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEAirwayObstruction.h>
#include <biogears/schema/cdm/Scenario.hxx>


namespace py = pybind11;




PYBIND11_MODULE(pybSEAirwayObstruction, m) {


    py::class_<biogears::SEAirwayObstruction>(m, "SEAirwayObstruction")
    .def(py::init<>())    
    .def("TypeTag",&biogears::SEAirwayObstruction::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEAirwayObstruction::classname,py::const_))
    .def("Clear",py::overload_cast<>(&biogears::SEAirwayObstruction::Clear))
    .def("IsValid",py::overload_cast<>(&biogears::SEAirwayObstruction::IsValid,py::const_))
    .def("IsActive",py::overload_cast<>(&biogears::SEAirwayObstruction::IsActive,py::const_))
    .def("Load",&biogears::SEAirwayObstruction::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEAirwayObstruction::Unload,py::const_))
    .def("HasSeverity",&biogears::SEAirwayObstruction::HasSeverity)
    .def("GetSeverity",&biogears::SEAirwayObstruction::GetSeverity)
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEAirwayObstruction::ToString,py::const_));


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}