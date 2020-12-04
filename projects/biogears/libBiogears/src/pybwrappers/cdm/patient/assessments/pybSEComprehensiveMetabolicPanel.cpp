// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/cdm/patient/actions/SEUrinate.h>
// #include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
// #include <biogears/cdm/CommonDataModel.h>
// #include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/patient/assessments/SEComprehensiveMetabolicPanel.h>
#include <biogears/cdm/properties/SEScalarMassPerAmount.h>
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include <biogears/schema/cdm/PatientAssessments.hxx>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarVolume.h>
#include <biogears/cdm/system/physiology/SEBloodChemistrySystem.h>

namespace py = pybind11;




PYBIND11_MODULE(pybSEComprehensiveMetabolicPanel, m) {


    py::class_<biogears::SEComprehensiveMetabolicPanel, biogears::SEPatientAssessment>(m, "SEComprehensiveMetabolicPanel")
    .def(py::init<>())
    .def("TypeTag",&biogears::SEComprehensiveMetabolicPanel::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SEComprehensiveMetabolicPanel::classname,py::const_))
    .def("Reset",&biogears::SEComprehensiveMetabolicPanel::Reset)
    .def("Clear",&biogears::SEComprehensiveMetabolicPanel::Clear)
    .def("Load",&biogears::SEComprehensiveMetabolicPanel::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEComprehensiveMetabolicPanel::Unload))
    .def("HasAlbumin",&biogears::SEComprehensiveMetabolicPanel::HasAlbumin)
    .def("GetAlbumin",&biogears::SEComprehensiveMetabolicPanel::GetAlbumin)
    .def("HasALP",&biogears::SEComprehensiveMetabolicPanel::HasALP)
    .def("GetALP",&biogears::SEComprehensiveMetabolicPanel::GetALP)
    .def("HasALT",&biogears::SEComprehensiveMetabolicPanel::HasALT)
    .def("GetALT",&biogears::SEComprehensiveMetabolicPanel::GetALT)
    .def("HasAST",&biogears::SEComprehensiveMetabolicPanel::HasAST)
    .def("GetAST",&biogears::SEComprehensiveMetabolicPanel::GetAST)
    .def("HasBUN",&biogears::SEComprehensiveMetabolicPanel::HasBUN)
    .def("GetBUN",&biogears::SEComprehensiveMetabolicPanel::GetBUN)
    .def("HasCalcium",&biogears::SEComprehensiveMetabolicPanel::HasCalcium)
    .def("GetCalcium",&biogears::SEComprehensiveMetabolicPanel::GetCalcium)
    .def("HasChloride",&biogears::SEComprehensiveMetabolicPanel::HasChloride)
    .def("GetChloride",&biogears::SEComprehensiveMetabolicPanel::GetChloride)
    .def("HasCO2",&biogears::SEComprehensiveMetabolicPanel::HasCO2)
    .def("GetCO2",&biogears::SEComprehensiveMetabolicPanel::GetCO2)
    .def("HasCreatinine",&biogears::SEComprehensiveMetabolicPanel::HasCreatinine)
    .def("GetCreatinine",&biogears::SEComprehensiveMetabolicPanel::GetCreatinine)
    .def("HasGlucose",&biogears::SEComprehensiveMetabolicPanel::HasGlucose)
    .def("GetGlucose",&biogears::SEComprehensiveMetabolicPanel::GetGlucose)
    
    .def("HasPotassium",&biogears::SEComprehensiveMetabolicPanel::HasPotassium)
    .def("GetPotassium",&biogears::SEComprehensiveMetabolicPanel::GetPotassium)
    .def("HasSodium",&biogears::SEComprehensiveMetabolicPanel::HasSodium)
    .def("GetSodium",&biogears::SEComprehensiveMetabolicPanel::GetSodium)

    .def("HasTotalBilirubin",&biogears::SEComprehensiveMetabolicPanel::HasTotalBilirubin)
    .def("GetTotalBilirubin",&biogears::SEComprehensiveMetabolicPanel::GetTotalBilirubin)
    .def("HasTotalProtein",&biogears::SEComprehensiveMetabolicPanel::HasTotalProtein)
    .def("GetTotalProtein",&biogears::SEComprehensiveMetabolicPanel::GetTotalProtein);

    
    // .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECompleteBloodCount::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}