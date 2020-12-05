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
#include <biogears/cdm/patient/conditions/SEDiabetesType1.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>




namespace py = pybind11;




PYBIND11_MODULE(pybSEDiabetesType1, m) {


    py::class_<biogears::SEDiabetesType1, biogears::SEPatientCondition>(m, "SEDiabetesType1")
    .def(py::init<>())
    .def("Clear",&biogears::SEDiabetesType1::Clear)
    .def("IsValid",&biogears::SEDiabetesType1::IsValid)
    .def("Load",&biogears::SEDiabetesType1::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEDiabetesType1::Unload,py::const_))
    .def("GetName",&biogears::SEDiabetesType1::GetName)
    .def("GetName_cStr",&biogears::SEDiabetesType1::GetName_cStr)
    .def("HasInsulinProductionSeverity",&biogears::SEDiabetesType1::HasInsulinProductionSeverity)
    .def("GetInsulinProductionSeverity",&biogears::SEDiabetesType1::GetInsulinProductionSeverity)

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEDiabetesType1::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}