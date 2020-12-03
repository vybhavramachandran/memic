// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/exports.h>
#include <string>
#include <pybind11/pybind11.h>
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>
#include <biogears/cdm/patient/actions/SEUseInhaler.h>
// #include <biogears/cdm/patient/actions/SESubstanceAdministration.h>
// #include <biogears/cdm/CommonDataModel.h>
// #include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/cdm/properties/SEScalarMassPerVolume.h>
// #include <biogears/cdm/properties/SEScalarTime.h>
// #include <biogears/cdm/properties/SEScalarVolume.h>
// #include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/substance/SESubstance.h>
#include <biogears/schema/cdm/Scenario.hxx>
#include <biogears/cdm/patient/actions/SEConsciousRespirationCommand.h>

namespace py = pybind11;




PYBIND11_MODULE(pybSEUseInhaler, m) {


    py::class_<biogears::SEUseInhaler, biogears::SEConsciousRespirationCommand>(m, "SEUseInhaler")
    // .def(py::init<>())
    .def("Clear",&biogears::SEUseInhaler::Clear)
    .def("IsValid",&biogears::SEUseInhaler::IsValid)
    .def("IsActive",&biogears::SEUseInhaler::IsActive)
    .def("Load",&biogears::SEUseInhaler::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEUseInhaler::Unload,py::const_))
    
    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEUseInhaler::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}