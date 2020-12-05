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
#include <biogears/cdm/patient/conditions/SEImpairedAlveolarExchange.h>
#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/schema/cdm/PatientConditions.hxx>
#include <biogears/cdm/properties/SEScalarArea.h>



namespace py = pybind11;




PYBIND11_MODULE(pybSEImpairedAlveolarExchange, m) {


    py::class_<biogears::SEImpairedAlveolarExchange, biogears::SEPatientCondition>(m, "SEImpairedAlveolarExchange")
    .def(py::init<>())
    .def("Clear",&biogears::SEImpairedAlveolarExchange::Clear)
    .def("IsValid",&biogears::SEImpairedAlveolarExchange::IsValid)
    .def("Load",&biogears::SEImpairedAlveolarExchange::Load)
    .def("Unload",py::overload_cast<>(&biogears::SEImpairedAlveolarExchange::Unload,py::const_))
    .def("GetName",&biogears::SEImpairedAlveolarExchange::GetName)
    .def("GetName_cStr",&biogears::SEImpairedAlveolarExchange::GetName_cStr)
    .def("HasImpairedSurfaceArea",&biogears::SEImpairedAlveolarExchange::HasImpairedSurfaceArea)
    .def("GetImpairedSurfaceArea",py::overload_cast<>(&biogears::SEImpairedAlveolarExchange::GetImpairedSurfaceArea))
    .def("GetImpairedSurfaceArea",py::overload_cast<const biogears::AreaUnit&>(&biogears::SEImpairedAlveolarExchange::GetImpairedSurfaceArea,py::const_))
    .def("HasImpairedFraction",&biogears::SEImpairedAlveolarExchange::HasImpairedFraction)
    .def("GetImpairedFraction",py::overload_cast<>(&biogears::SEImpairedAlveolarExchange::GetImpairedFraction))
    .def("GetImpairedFraction",py::overload_cast<>(&biogears::SEImpairedAlveolarExchange::GetImpairedFraction,py::const_))



    .def("ToString",py::overload_cast<std::ostream&>(&biogears::SEImpairedAlveolarExchange::ToString,py::const_));

  
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}