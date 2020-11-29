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
#include <biogears/cdm/patient/actions/SEChestCompressionForce.h>
#include <biogears/schema/cdm/Scenario.hxx>


namespace py = pybind11;




PYBIND11_MODULE(pybSEChestCompressionForce, m) {


    py::class_<biogears::SEChestCompressionForce, biogears::SEChestCompression>(m, "SEChestCompressionForce")
    .def(py::init<>())
    .def("Clear",&biogears::SEChestCompressionForce::Clear)
    .def("IsValid",&biogears::SEChestCompressionForce::IsValid)
    .def("IsActive",&biogears::SEChestCompressionForce::IsActive)
    .def("Load",&biogears::SEChestCompressionForce::Load)
    // .def("Unload",&biogears::SEChestCompressionForce::Unload)
    .def("HasForce",&biogears::SEChestCompressionForce::HasForce)
    .def("GetForce",&biogears::SEChestCompressionForce::GetForce)
    
    .def("ToString",&biogears::SEChestCompressionForce::ToString);


    
  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}