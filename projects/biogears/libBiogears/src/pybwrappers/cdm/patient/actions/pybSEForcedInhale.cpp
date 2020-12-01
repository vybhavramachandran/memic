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
#include <biogears/cdm/patient/actions/SEForcedInhale.h>
#include <biogears/cdm/patient/actions/SEConsciousRespiration.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/properties/SEScalarTime.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEForcedInhale, m) {


    py::class_<biogears::SEForcedInhale>(m, "SEForcedInhale")
    // .def(py::init<>())    
    // .def("TypeTag",&biogears::SEForcedExhale::TypeTag)
    // .def("classname",py::overload_cast<>(&biogears::SEForcedExhale::classname,py::const_))
    .def("Clear",&biogears::SEForcedInhale::Clear)
    .def("IsValid",&biogears::SEForcedInhale::IsValid)
    .def("IsActive",&biogears::SEForcedInhale::IsActive)
    .def("Load",&biogears::SEForcedInhale::Load)
    // .def("Unload",&biogears::SEForcedExhale::Unload)
    .def("HasInspiratoryCapacityFraction",&biogears::SEForcedInhale::HasInspiratoryCapacityFraction)
    .def("GetInspiratoryCapacityFraction",&biogears::SEForcedInhale::GetInspiratoryCapacityFraction)
    .def("HasPeriod",&biogears::SEForcedInhale::HasPeriod)
    .def("GetPeriod",&biogears::SEForcedInhale::GetPeriod)


    .def("ToString",&biogears::SEForcedInhale::ToString);

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}