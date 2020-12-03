// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>
#include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/schema/cdm/Scenario.hxx>
namespace py = pybind11;




PYBIND11_MODULE(pybSESubstanceInfusion, m) {


    py::class_<biogears::SESubstanceInfusion, biogears::SESubstanceAdministration>(m, "SESubstanceInfusion")
    .def(py::init<const biogears::SESubstance&>())
    .def("Clear",&biogears::SESubstanceInfusion::Clear)
    .def("IsValid",&biogears::SESubstanceInfusion::IsValid)
    .def("IsActive",&biogears::SESubstanceInfusion::IsActive)
    .def("Load",&biogears::SESubstanceInfusion::Load)
    .def("Unload",py::overload_cast<>(&biogears::SESubstanceInfusion::Unload,py::const_))
    .def("HasConcentration",&biogears::SESubstanceInfusion::HasConcentration)
    .def("GetConcentration",&biogears::SESubstanceInfusion::GetConcentration)
    .def("HasRate",&biogears::SESubstanceInfusion::HasRate) 
    .def("GetRate",&biogears::SESubstanceInfusion::GetRate) 
    .def("GetSubstance",&biogears::SESubstanceInfusion::GetSubstance) 
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SESubstanceInfusion::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}