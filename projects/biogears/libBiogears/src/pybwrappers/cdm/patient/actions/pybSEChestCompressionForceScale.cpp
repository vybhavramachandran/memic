// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/properties/SEScalarForce.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEChestCompression.h>
#include <biogears/cdm/patient/actions/SEChestCompressionForceScale.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarTime.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEChestCompressionForceScale, m) {


    py::class_<biogears::SEChestCompressionForceScale, biogears::SEChestCompression>(m, "SEChestCompressionForceScale")
    .def(py::init<>())
    .def("Clear",&biogears::SEChestCompressionForceScale::Clear)
    .def("IsValid",&biogears::SEChestCompressionForceScale::IsValid)
    .def("IsActive",&biogears::SEChestCompressionForceScale::IsActive)
    .def("Load",&biogears::SEChestCompressionForceScale::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEChestCompressionForceScale::Unload,py::const_))
    .def("HasForceScale",&biogears::SEChestCompressionForceScale::HasForceScale)
    .def("GetForceScale",&biogears::SEChestCompressionForceScale::GetForceScale)
    .def("HasForcePeriod",&biogears::SEChestCompressionForceScale::HasForcePeriod)
    .def("GetForcePeriod",&biogears::SEChestCompressionForceScale::GetForcePeriod)
    
    .def("ToString",&biogears::SEChestCompressionForceScale::ToString);


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}