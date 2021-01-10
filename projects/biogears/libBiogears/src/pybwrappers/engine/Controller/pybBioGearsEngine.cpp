// #include "../include/biogears/cdm/system/physiology/SECardiovascularSystem.h"
// #include "../include/biogears/cdm/system/SESystem.h"
// #include "../include/biogears/cdm/properties/SEScalarPressure.h"

#include <memory>
#include <biogears/cdm/Serializer.h>
#include <biogears/cdm/circuit/SECircuit.h>
#include <biogears/cdm/compartment/SECompartmentManager.h>
#include <biogears/cdm/engine/PhysiologyEngineStabilization.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/cdm/patient/actions/SEPatientAssessmentRequest.h>
#include <biogears/cdm/patient/assessments/SECompleteBloodCount.h>
#include <biogears/cdm/patient/assessments/SEComprehensiveMetabolicPanel.h>
#include <biogears/cdm/patient/assessments/SEPulmonaryFunctionTest.h>
#include <biogears/cdm/patient/assessments/SESequentialOrganFailureAssessment.h>
#include <biogears/cdm/patient/assessments/SEUrinalysis.h>
#include <biogears/cdm/scenario/SECondition.h>
#include <biogears/cdm/scenario/SEScenario.h>
#include <biogears/cdm/scenario/SESerializeState.h>
#include <biogears/cdm/substance/SESubstanceCompound.h>
#include <biogears/cdm/utils/FileUtils.h>
#include <biogears/container/Tree.tci.h>
#include <biogears/engine/BioGearsPhysiologyEngine.h>
#include <biogears/engine/Controller/BioGears.h>
#include <biogears/engine/Equipment/ECG.h>
#include <biogears/cdm/utils/Logger.h>
#include <biogears/container/Tree.tci.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;



PYBIND11_MODULE(pybBioGearsEngine, m) {
    // m.def("CreateBioGearsEngine")
    //testing
    m.def("CreateBioGearsEngine",py::overload_cast<biogears::Logger*>(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const std::string>(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const char* >(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const std::string, const std::string >(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const char*, const char*>(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const std::string, biogears::Logger*>(&biogears::CreateBioGearsEngine));
    m.def("CreateBioGearsEngine",py::overload_cast<const char*, biogears::Logger*>(&biogears::CreateBioGearsEngine));

    py::class_<biogears::PhysiologyEngine>(m, "PhysiologyEngine");
}