// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SESubstanceCompoundInfusion.h>
#include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalarTime.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/schema/cdm/Scenario.hxx>
namespace py = pybind11;




PYBIND11_MODULE(pybSESubstanceCompoundInfusion, m) {


    py::class_<biogears::SESubstanceCompoundInfusion, biogears::SESubstanceAdministration>(m, "SESubstanceCompoundInfusion")
    .def(py::init<const biogears::SESubstanceCompoundInfusion&>())
    .def("Clear",&biogears::SESubstanceCompoundInfusion::Clear)
    .def("IsValid",&biogears::SESubstanceCompoundInfusion::IsValid)
    .def("IsActive",&biogears::SESubstanceCompoundInfusion::IsActive)
    .def("Load",&biogears::SESubstanceCompoundInfusion::Load)
    .def("Unload",py::overload_cast<>(&biogears::SESubstanceCompoundInfusion::Unload,py::const_))
    .def("HasBagVolume",&biogears::SESubstanceCompoundInfusion::HasBagVolume)
    .def("GetBagVolume",&biogears::SESubstanceCompoundInfusion::GetBagVolume)
    .def("HasRate",&biogears::SESubstanceCompoundInfusion::HasRate) 
    .def("GetRate",&biogears::SESubstanceCompoundInfusion::GetRate) 
    .def("GetSubstanceCompound",&biogears::SESubstanceCompoundInfusion::GetSubstanceCompound) 
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SESubstanceCompoundInfusion::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}