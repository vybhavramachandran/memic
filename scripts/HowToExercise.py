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
import pybConstants
import pybSEEnergySystem
import pybSERespiratorySystem

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
bgCardioSystem = bg.GetCardiovascularSystem()
bgEnergySystem = bg.GetEnergySystem()
bgRespiratorySystem = bg.GetRespiratorySystem()

bg.GetLogger().Info("Cardiac Output : "+str(bgCardioSystem.GetCardiacOutput(pybConstants.VolumePerTimeUnit.mL_Per_min))+str(pybConstants.VolumePerTimeUnit.mL_Per_min))
bg.GetLogger().Info("Mean Arterial Pressure : "+str(bgCardioSystem.GetMeanArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Systolic Pressure : "+str(bgCardioSystem.GetSystolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Diastolic Pressure : "+str(bgCardioSystem.GetDiastolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Heart Rate : "+str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.kcal_Per_day))+str(pybConstants.PowerUnit.kcal_Per_day))
bg.GetLogger().Info("Core Temperature : "+str(bgEnergySystem.GetCoreTemperature(pybConstants.TemperatureUnit.C))+str(pybConstants.TemperatureUnit.C))
bg.GetLogger().Info("RespirationRate : "+str(bgRespiratorySystem.GetRespirationRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.W))+str(pybConstants.PowerUnit.W))

ge = pybSEExercise.SEExerciseSEGeneric()
ge.Intensity.SetValue(0.2)

exG = pybSEExercise.SEExercise(ge)
bg.ProcessAction(exG)
bg.AdvanceModelTime(5.0)

bgCardioSystem = bg.GetCardiovascularSystem()
bgEnergySystem = bg.GetEnergySystem()
bgRespiratorySystem = bg.GetRespiratorySystem()
bg.GetLogger().Info("Cardiac Output : "+str(bgCardioSystem.GetCardiacOutput(pybConstants.VolumePerTimeUnit.mL_Per_min))+str(pybConstants.VolumePerTimeUnit.mL_Per_min))
bg.GetLogger().Info("Mean Arterial Pressure : "+str(bgCardioSystem.GetMeanArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Systolic Pressure : "+str(bgCardioSystem.GetSystolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Diastolic Pressure : "+str(bgCardioSystem.GetDiastolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Heart Rate : "+str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.kcal_Per_day))+str(pybConstants.PowerUnit.kcal_Per_day))
bg.GetLogger().Info("Core Temperature : "+str(bgEnergySystem.GetCoreTemperature(pybConstants.TemperatureUnit.C))+str(pybConstants.TemperatureUnit.C))
bg.GetLogger().Info("RespirationRate : "+str(bgRespiratorySystem.GetRespirationRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.W))+str(pybConstants.PowerUnit.W))
#Additional stuff below
counter = 0

while counter<5:
    bg.AdvanceModelTime(5.0)
    bgCardioSystem = bg.GetCardiovascularSystem()
    bg.GetLogger().Info("Heart Rate : "+str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
    counter+=1

#Additional stuff above
ge.Intensity.SetValue(0.0)
exGStop = pybSEExercise.SEExercise(ge)
bg.ProcessAction(exGStop)
bg.AdvanceModelTime(30.0)


bg.GetLogger().Info("Cardiac Output : "+str(bgCardioSystem.GetCardiacOutput(pybConstants.VolumePerTimeUnit.mL_Per_min))+str(pybConstants.VolumePerTimeUnit.mL_Per_min))
bg.GetLogger().Info("Mean Arterial Pressure : "+str(bgCardioSystem.GetMeanArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Systolic Pressure : "+str(bgCardioSystem.GetSystolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Diastolic Pressure : "+str(bgCardioSystem.GetDiastolicArterialPressure(pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
bg.GetLogger().Info("Heart Rate : "+str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.kcal_Per_day))+str(pybConstants.PowerUnit.kcal_Per_day))
bg.GetLogger().Info("Core Temperature : "+str(bgEnergySystem.GetCoreTemperature(pybConstants.TemperatureUnit.C))+str(pybConstants.TemperatureUnit.C))
bg.GetLogger().Info("RespirationRate : "+str(bgRespiratorySystem.GetRespirationRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.W))+str(pybConstants.PowerUnit.W))