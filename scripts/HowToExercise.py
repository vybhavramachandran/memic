import pybLogger
import pybBioGearsEngine
import pybBioGearsEngineHeader
import pybPhysiologyEngineTrack
import pybSEDataRequest
import pybSEDataRequestManager
import pybSEPhysiologyDataRequest
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


bg.GetEngineTrack().GetDataRequestManager().SetResultsFileName('HowToExercise.csv')

bg.AdvanceModelTime(20, src_cdm_properties_constants["TimeUnit::s"])




