#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>
// #include <biogears/cdm/utils/Logger.h>
// #include <biogears/cdm/substance/SESubstanceManager.h>
// #include <biogears/cdm/utils/DataTrack.h>
// #include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/cdm/CommonDataModel.h>
#include <biogears/exports.h>
#include <biogears/cdm/scenario/requests/SEEnvironmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEEquipmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEGasCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SELiquidCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SEPatientDataRequest.h>
#include <biogears/cdm/scenario/requests/SEPhysiologyDataRequest.h>
#include <biogears/cdm/scenario/requests/SESubstanceDataRequest.h>
#include <biogears/cdm/scenario/requests/SEThermalCompartmentDataRequest.h>
#include <biogears/cdm/scenario/requests/SETissueCompartmentDataRequest.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/properties/SEDecimalFormat.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>



namespace py = pybind11;




PYBIND11_MODULE(pybSEDataRequestManager, m) {

    py::class_<biogears::SEDecimalFormat>(m,"SEDecimalFormat");
    // py::class_<biogears::SEPhysiologyDataRequest>(m,"SEPhysiologyDataRequest");


    py::class_<biogears::SEDataRequestManager>(m, "SEDataRequestManager")
    .def(py::init<biogears::Logger*>())
    .def("Clear",&biogears::SEDataRequestManager::Clear)
    .def("Load",&biogears::SEDataRequestManager::Load)
    // .def("Unload",&biogears::SEDataRequestManager::Unload)
    .def("HasResultsFilename",&biogears::SEDataRequestManager::HasResultsFilename)
    .def("GetResultsFilename",&biogears::SEDataRequestManager::GetResultsFilename)
    .def("GetResultsFilename_cStr",&biogears::SEDataRequestManager::GetResultsFilename_cStr)
    .def("SetResultsFilename",py::overload_cast<const char* >(&biogears::SEDataRequestManager::SetResultsFilename))
    .def("SetResultsFilename",py::overload_cast<const std::string&>(&biogears::SEDataRequestManager::SetResultsFilename))
    .def("HasWorkingDir",&biogears::SEDataRequestManager::HasWorkingDir)
    .def("GetWorkingDir",&biogears::SEDataRequestManager::GetWorkingDir)
    .def("GetWorkingDir_cStr",&biogears::SEDataRequestManager::GetWorkingDir_cStr)
    .def("SetWorkingDir",py::overload_cast<const char* >(&biogears::SEDataRequestManager::SetWorkingDir))
    .def("SetWorkingDir",py::overload_cast<const std::string&>(&biogears::SEDataRequestManager::SetWorkingDir))
    .def("GetResovedFilePath",&biogears::SEDataRequestManager::GetResovedFilePath)
    .def("GetSamplesPerSecond",&biogears::SEDataRequestManager::GetSamplesPerSecond)
    .def("SetSamplesPerSecond",&biogears::SEDataRequestManager::SetSamplesPerSecond)
    .def("HasDataRequests",&biogears::SEDataRequestManager::HasDataRequests)
    .def("GetDataRequests",&biogears::SEDataRequestManager::GetDataRequests)
    .def("HasDefaultDecimalFormatting",&biogears::SEDataRequestManager::HasDefaultDecimalFormatting)
    .def("GetDefaultDecimalFormatting",&biogears::SEDataRequestManager::GetDefaultDecimalFormatting)
    .def("RemoveDefaultDecimalFormatting",&biogears::SEDataRequestManager::RemoveDefaultDecimalFormatting)
    .def("HasOverrideDecimalFormatting",&biogears::SEDataRequestManager::HasOverrideDecimalFormatting)
    .def("GetOverrideDecimalFormatting",&biogears::SEDataRequestManager::GetOverrideDecimalFormatting)
    .def("RemoveOverrideDecimalFormatting",&biogears::SEDataRequestManager::RemoveOverrideDecimalFormatting)
    .def("CreateEnvironmentDataRequest",&biogears::SEDataRequestManager::CreateEnvironmentDataRequest)
    .def("CreateEquipmentDataRequest",&biogears::SEDataRequestManager::CreateEquipmentDataRequest)
    .def("CreatePatientDataRequest",&biogears::SEDataRequestManager::CreatePatientDataRequest)
    // .def("CreatePhysiologyDataRequest",&biogears::SEDataRequestManager::CreatePhysiologyDataRequest, py::arg("dfault").none(true))
    .def("CreatePhysiologyDataRequest",&biogears::SEDataRequestManager::CreatePhysiologyDataRequest,py::arg("dfault") = nullptr)
    .def("CreateSubstanceDataRequest",&biogears::SEDataRequestManager::CreateSubstanceDataRequest)
    .def("CreateGasCompartmentDataRequest",&biogears::SEDataRequestManager::CreateGasCompartmentDataRequest)
    .def("CreateLiquidCompartmentDataRequest",&biogears::SEDataRequestManager::CreateLiquidCompartmentDataRequest)
    .def("CreateThermalCompartmentDataRequest",&biogears::SEDataRequestManager::CreateThermalCompartmentDataRequest)
    .def("CreateTissueCompartmentDataRequest",&biogears::SEDataRequestManager::CreateTissueCompartmentDataRequest)
    .def("CreateFromBind",&biogears::SEDataRequestManager::CreateFromBind);
 
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}