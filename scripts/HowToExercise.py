import pybLogger
import pybBioGearsEngine
import pybBioGearsEngineHeader
import pybPhysiologyEngineTrack
import pybSEDataRequest
import pybSEDataRequestManager
import pybSEPhysiologyDataRequest
import pybSEScalar0To1
import pybSEExercise
import pybSECardiovascularSystem

from src_cdm_properties_constants import *

var_logger = pybLogger.Logger("HowToExercise.log","")
bg = pybBioGearsEngine.CreateBioGearsEngine(var_logger)
bg.LoadState("./states/StandardMale@0s.xml")

bg.GetEngineTrack()
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('HeartRate',src_cdm_properties_constants["FrequencyUnit::Per_min"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('CardiacOutput',src_cdm_properties_constants["VolumePerTimeUnit::mL_Per_min"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('MeanArterialPressure',src_cdm_properties_constants["PressureUnit::mmHg"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('SystolicArterialPressure',src_cdm_properties_constants["PressureUnit::mmHg"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('DiastolicArterialPressure',src_cdm_properties_constants["PressureUnit::mmHg"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('TotalMetabolicRate',src_cdm_properties_constants["PowerUnit::kcal_Per_day"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('CoreTemperature',src_cdm_properties_constants["TemperatureUnit::C"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('RespirationRate',src_cdm_properties_constants["FrequencyUnit::Per_min"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('AchievedExerciseLevel')
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('FatigueLevel')
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('TotalMetabolicRate',src_cdm_properties_constants["PowerUnit::W"])
bg.GetEngineTrack().GetDataRequestManager().CreatePhysiologyDataRequest().Set('TotalWorkRateLevel')


bg.GetEngineTrack().GetDataRequestManager().SetResultsFilename('HowToExercise.csv')

# bg.AdvanceModelTime(20.0, src_cdm_properties_constants["TimeUnit::s"])

bg.AdvanceModelTime(20.0)

bg.GetLogger().Info("The patient is nice and healthy")
bg.GetLogger().Info(bg.GetCardiovascularSystem().GetCardiacOutput(src_cdm_properties_constants["VolumePerTimeUnit::mL_Per_min"]))
bg.GetLogger().Info(bg.GetCardiovascularSystem().GetCardiacOutput(src_cdm_properties_constants["VolumePerTimeUnit::mL_Per_min"]))

# ge = pybSEExercise.SEExerciseSEGeneric()
# ge.Intensity.SetValue(0.5)
# exG = pybSEExercise.SEExercise(ge)
# bg.ProcessAction(exG)
# bg.AdvanceModelTime(30.0)
