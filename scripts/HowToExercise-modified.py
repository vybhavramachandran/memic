import pybConstants
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
import pybSEEnergySystem
import pybSERespiratorySystem
import sys
import json
from src_cdm_properties_constants import *


def logStuff(bg, bgCardioSystem, bgEnergySystem, bgRespiratorySystem):
    # print(type(pybConstants.VolumePerTimeUnit.mL_Per_min))
    # print(str(pybConstants.VolumePerTimeUnit.mL_Per_min.GetString()))
    bg.GetLogger().Info("Cardiac Output : "+str(bgCardioSystem.GetCardiacOutput(
        pybConstants.VolumePerTimeUnit.mL_Per_min))+str(pybConstants.VolumePerTimeUnit.mL_Per_min))
    bg.GetLogger().Info("Mean Arterial Pressure : "+str(bgCardioSystem.GetMeanArterialPressure(
        pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
    bg.GetLogger().Info("Systolic Pressure : "+str(bgCardioSystem.GetSystolicArterialPressure(
        pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
    bg.GetLogger().Info("Diastolic Pressure : "+str(bgCardioSystem.GetDiastolicArterialPressure(
        pybConstants.PressureUnit.mmHg))+str(pybConstants.PressureUnit.mmHg))
    bg.GetLogger().Info("Heart Rate : " +
                        str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
    bg.GetLogger().Info("Total Metabolic Rate : "+str(bgEnergySystem.GetTotalMetabolicRate(
        pybConstants.PowerUnit.kcal_Per_day))+str(pybConstants.PowerUnit.kcal_Per_day))
    bg.GetLogger().Info("Core Temperature : "+str(bgEnergySystem.GetCoreTemperature(
        pybConstants.TemperatureUnit.C))+str(pybConstants.TemperatureUnit.C))
    bg.GetLogger().Info("RespirationRate : " +
                        str(bgRespiratorySystem.GetRespirationRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
    bg.GetLogger().Info("Total Metabolic Rate : " +
                        str(bgEnergySystem.GetTotalMetabolicRate(pybConstants.PowerUnit.W))+str(pybConstants.PowerUnit.W))
    print("Test logStuff")


def second_function(bg):
    bg.LoadState("./states/StandardMale@0s.xml")
    et = bg.GetEngineTrack()
    etgdrm = et.GetDataRequestManager()
    with open('./physiology.json') as f:
        physiology_dict = json.load(f)
    for key in physiology_dict:
        # print(key)
        for key2 in physiology_dict[key]:
            print(f"{key}:{key2}:{physiology_dict[key][key2]}")
            if physiology_dict[key][key2] != "ScalarData" and physiology_dict[key][key2] != "ScalarFractionData" and physiology_dict[key][key2] != "ScalarNeg1To1Data" and physiology_dict[key][key2] != "enumOnOff" and physiology_dict[key][key2] != "Scalar0To1Data" and physiology_dict[key][key2] != "enumInflammationSource" and physiology_dict[key][key2] != "InflammatoryResponseData" and physiology_dict[key][key2] != "enumHeartRhythm" and physiology_dict[key][key2] != "NutritionData" and physiology_dict[key][key2] != "DrugTransitStateData"  and physiology_dict[key][key2] != "PupillaryResponseData" and physiology_dict[key][key2] != "enumSleepState":
                etgdrm.CreatePhysiologyDataRequest().Set(
                    key2, src_cdm_properties_constants[physiology_dict[key][key2]])
            else:
                etgdrm.CreatePhysiologyDataRequest().Set(key2)

    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'HeartRate', src_cdm_properties_constants["FrequencyUnit::Per_min"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'CardiacOutput', src_cdm_properties_constants["VolumePerTimeUnit::mL_Per_min"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'MeanArterialPressure', src_cdm_properties_constants["PressureUnit::mmHg"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'SystolicArterialPressure', src_cdm_properties_constants["PressureUnit::mmHg"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'DiastolicArterialPressure', src_cdm_properties_constants["PressureUnit::mmHg"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'TotalMetabolicRate', src_cdm_properties_constants["PowerUnit::kcal_Per_day"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'CoreTemperature', src_cdm_properties_constants["TemperatureUnit::C"])
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'RespirationRate', src_cdm_properties_constants["FrequencyUnit::Per_min"])
    # etgdrm.CreatePhysiologyDataRequest().Set('AchievedExerciseLevel')
    # etgdrm.CreatePhysiologyDataRequest().Set('FatigueLevel')
    # etgdrm.CreatePhysiologyDataRequest().Set(
    #     'TotalMetabolicRate', src_cdm_properties_constants["PowerUnit::W"])
    # etgdrm.CreatePhysiologyDataRequest().Set('TotalWorkRateLevel')
    etgdrm.SetResultsFilename('HowToExercise.csv')

    # bg.AdvanceModelTime(20.0, src_cdm_properties_constants["TimeUnit::s"])

    bg.AdvanceModelTime(20.0)

    bg.GetLogger().Info("The patient is nice and healthy")
    bgCardioSystem = bg.GetCardiovascularSystem()
    bgEnergySystem = bg.GetEnergySystem()
    bgRespiratorySystem = bg.GetRespiratorySystem()

    logStuff(bg, bgCardioSystem, bgEnergySystem, bgRespiratorySystem)
    ge = pybSEExercise.SEExerciseSEGeneric()
    ge.Intensity.SetValue(0.2)

    exG = pybSEExercise.SEExercise(ge)
    bg.ProcessAction(exG)
    bg.AdvanceModelTime(5.0)

    bgCardioSystem = bg.GetCardiovascularSystem()
    bgEnergySystem = bg.GetEnergySystem()
    bgRespiratorySystem = bg.GetRespiratorySystem()
    logStuff(bg, bgCardioSystem, bgEnergySystem, bgRespiratorySystem)

    # Additional stuff below
    counter = 0

    while counter < 5:
        bg.AdvanceModelTime(5.0)
        # bgCardioSystem = bg.GetCardiovascularSystem()
        bg.GetLogger().Info("Heart Rate : " +
                            str(bgCardioSystem.GetHeartRate(pybConstants.FrequencyUnit.Per_min))+"bpm")
        counter += 1

    # Additional stuff above
    ge.Intensity.SetValue(0.0)
    exGStop = pybSEExercise.SEExercise(ge)
    bg.ProcessAction(exGStop)
    bg.AdvanceModelTime(30.0)
    bgCardioSystem = bg.GetCardiovascularSystem()
    bgEnergySystem = bg.GetEnergySystem()
    bgRespiratorySystem = bg.GetRespiratorySystem()

    logStuff(bg, bgCardioSystem, bgEnergySystem, bgRespiratorySystem)
    print("Test")
    print("Test")


def main():

    var_logger = pybLogger.Logger("HowToExercise.log", "")
    # bg = pybBioGearsEngine.CreateBioGearsEngine(var_logger)
    bg = pybBioGearsEngine.CreateBioGearsEngine(var_logger)
    print(type(bg))
    second_function(bg)
    del(bg)


if __name__ == "__main__":
    main()
