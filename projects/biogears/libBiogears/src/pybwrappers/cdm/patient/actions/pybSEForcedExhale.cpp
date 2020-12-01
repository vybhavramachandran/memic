// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEConsciousRespirationCommand.h>
#include <biogears/cdm/patient/actions/SEForcedExhale.h>
#include <biogears/cdm/patient/actions/SEConsciousRespiration.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/properties/SEScalarTime.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEForcedExhale, m) {


    py::class_<biogears::SEForcedExhale>(m, "SEForcedExhale")
    // .def(py::init<>())    
    // .def("TypeTag",&biogears::SEForcedExhale::TypeTag)
    // .def("classname",py::overload_cast<>(&biogears::SEForcedExhale::classname,py::const_))
    .def("Clear",&biogears::SEForcedExhale::Clear)
    .def("IsValid",&biogears::SEForcedExhale::IsValid)
    .def("IsActive",&biogears::SEForcedExhale::IsActive)
    .def("Load",&biogears::SEForcedExhale::Load)
    // .def("Unload",&biogears::SEForcedExhale::Unload)
    .def("HasExpiratoryReserveVolumeFraction",&biogears::SEForcedExhale::HasExpiratoryReserveVolumeFraction)
    .def("GetExpiratoryReserveVolumeFraction",&biogears::SEForcedExhale::GetExpiratoryReserveVolumeFraction)
    .def("HasPeriod",&biogears::SEForcedExhale::HasPeriod)
    .def("GetPeriod",&biogears::SEForcedExhale::GetPeriod)


    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEForcedExhale::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}