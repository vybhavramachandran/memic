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
// #include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/conditions/SEChronicVentricularSystolicDysfunction.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/cdm/patient/conditions/SEChronicHeartFailure.h>
#include <biogears/schema/cdm/PatientConditions.hxx>




namespace py = pybind11;




PYBIND11_MODULE(pybSEChronicVentricularSystolicDysfunction, m) {


    py::class_<biogears::SEChronicVentricularSystolicDysfunction, biogears::SEChronicHeartFailure>(m, "SEChronicVentricularSystolicDysfunction")
    .def(py::init<>())
    .def("Clear",&biogears::SEChronicVentricularSystolicDysfunction::Clear)
    .def("IsValid",&biogears::SEChronicVentricularSystolicDysfunction::IsValid)
    .def("Load",&biogears::SEChronicVentricularSystolicDysfunction::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEChronicVentricularSystolicDysfunction::Unload,py::const_))
    .def("GetName",&biogears::SEChronicVentricularSystolicDysfunction::GetName)
    .def("GetName_cStr",&biogears::SEChronicVentricularSystolicDysfunction::GetName_cStr)
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEChronicVentricularSystolicDysfunction::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}