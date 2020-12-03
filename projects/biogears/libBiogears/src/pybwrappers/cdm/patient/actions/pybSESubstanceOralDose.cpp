// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SESubstanceOralDose.h>
#include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarMass.h>
// #include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/substance/SESubstance.h>
// #include <biogears/schema/cdm/Scenario.hxx>
namespace py = pybind11;




PYBIND11_MODULE(pybSESubstanceOralDose, m) {

    py::class_<biogears::SESubstanceOralDose, biogears::SESubstanceAdministration>(m, "SESubstanceOralDose")
    .def(py::init<const biogears::SESubstance&>())
    .def("Clear",&biogears::SESubstanceOralDose::Clear)
    .def("IsValid",&biogears::SESubstanceOralDose::IsValid)
    .def("IsActive",&biogears::SESubstanceOralDose::IsActive)
    .def("Load",&biogears::SESubstanceOralDose::Load)
    .def("Unload",py::overload_cast<>(&biogears::SESubstanceOralDose::Unload,py::const_))
    .def("GetAdminRoute",&biogears::SESubstanceOralDose::GetAdminRoute)
    .def("SetAdminRoute",&biogears::SESubstanceOralDose::SetAdminRoute)
    .def("HasAdminRoute",&biogears::SESubstanceOralDose::HasAdminRoute) 
    .def("HasDose",&biogears::SESubstanceOralDose::HasDose) 
    .def("GetDose",&biogears::SESubstanceOralDose::GetDose) 
    .def("GetSubstance",&biogears::SESubstanceOralDose::GetSubstance) 

    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SESubstanceOralDose::ToString,py::const_));


   py::class_<biogears::SETransmucosalState>(m, "SETransmucosalState")
    .def(py::init<const biogears::SESubstance&>())
    .def("Clear",&biogears::SETransmucosalState::Clear)
    .def("Load",&biogears::SETransmucosalState::Load)
    .def("Unload",py::overload_cast<>(&biogears::SETransmucosalState::Unload,py::const_))
    .def("Initialize",&biogears::SETransmucosalState::Initialize)
    .def("GetMouthSolidMass",&biogears::SETransmucosalState::GetMouthSolidMass)
    .def("GetSalivaConcentration",&biogears::SETransmucosalState::GetSalivaConcentration) 
    .def("GetBuccalConcentrations",py::overload_cast<>(&biogears::SETransmucosalState::GetBuccalConcentrations))
    .def("GetSublingualConcentrations",py::overload_cast<>(&biogears::SETransmucosalState::GetSublingualConcentrations))
    .def("GetBuccalConcentrations",py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SETransmucosalState::GetBuccalConcentrations))
    .def("GetSublingualConcentrations",py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SETransmucosalState::GetSublingualConcentrations))
    .def("SetBuccalConcentrations",&biogears::SETransmucosalState::SetBuccalConcentrations) 
    .def("SetSublingualConcentrations",&biogears::SETransmucosalState::SetSublingualConcentrations);



    
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}