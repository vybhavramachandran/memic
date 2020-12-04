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
#include <biogears/cdm/patient/assessments/SECompleteBloodCount.h>
#include <biogears/cdm/properties/SEScalarMassPerAmount.h>
#include <biogears/cdm/patient/assessments/SEPatientAssessment.h>
#include <biogears/schema/cdm/PatientAssessments.hxx>
#include <biogears/cdm/properties/SEScalarFraction.h>
#include <biogears/cdm/properties/SEScalarMassPerVolume.h>
#include <biogears/cdm/properties/SEScalarAmountPerVolume.h>
#include <biogears/cdm/properties/SEScalarVolume.h>

namespace py = pybind11;




PYBIND11_MODULE(pybSECompleteBloodCount, m) {


    py::class_<biogears::SECompleteBloodCount, biogears::SEPatientAssessment>(m, "SECompleteBloodCount")
    .def(py::init<>())
    .def("TypeTag",&biogears::SECompleteBloodCount::TypeTag)
    .def("classname",py::overload_cast<>(&biogears::SECompleteBloodCount::classname,py::const_))
    .def("Reset",&biogears::SECompleteBloodCount::Reset)
    .def("Clear",&biogears::SECompleteBloodCount::Clear)
    .def("Load",&biogears::SECompleteBloodCount::Load)
    .def("Unload",py::overload_cast<>(&biogears::SECompleteBloodCount::Unload))
    .def("HasHematocrit",&biogears::SECompleteBloodCount::HasHematocrit)
    .def("GetHematocrit",&biogears::SECompleteBloodCount::GetHematocrit)
    .def("HasHemoglobin",&biogears::SECompleteBloodCount::HasHemoglobin)
    .def("GetHemoglobin",&biogears::SECompleteBloodCount::GetHemoglobin)
    .def("HasPlateletCount",&biogears::SECompleteBloodCount::HasPlateletCount)
    .def("GetPlateletCount",&biogears::SECompleteBloodCount::GetPlateletCount)
    .def("HasMeanCorpuscularHemoglobin",&biogears::SECompleteBloodCount::HasMeanCorpuscularHemoglobin)
    .def("GetMeanCorpuscularHemoglobin",&biogears::SECompleteBloodCount::GetMeanCorpuscularHemoglobin)
    .def("HasMeanCorpuscularHemoglobinConcentration",&biogears::SECompleteBloodCount::HasMeanCorpuscularHemoglobinConcentration)
    .def("GetMeanCorpuscularHemoglobinConcentration",&biogears::SECompleteBloodCount::GetMeanCorpuscularHemoglobinConcentration)
    .def("HasMeanCorpuscularVolume",&biogears::SECompleteBloodCount::HasMeanCorpuscularVolume)
    .def("GetMeanCorpuscularVolume",&biogears::SECompleteBloodCount::GetMeanCorpuscularVolume)
    .def("HasRedBloodCellCount",&biogears::SECompleteBloodCount::HasRedBloodCellCount)
    .def("GetRedBloodCellCount",&biogears::SECompleteBloodCount::GetRedBloodCellCount)
    .def("HasWhiteBloodCellCount",&biogears::SECompleteBloodCount::HasWhiteBloodCellCount)
    .def("GetWhiteBloodCellCount",&biogears::SECompleteBloodCount::GetWhiteBloodCellCount);
    
    // .def("ToString",py::overload_cast<std::ostream&>(&biogears::SECompleteBloodCount::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}