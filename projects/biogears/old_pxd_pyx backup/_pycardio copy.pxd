from libcpp cimport bool
from libcpp.string cimport string



cdef extern from "SEScalar.h" namespace "biogears":
    cdef cppclass SEScalar:
        pass

cdef extern from "Physiology.hxx":
    cdef cppclass CardiovascularSystemData:
        pass

cdef extern from "Tree.h":
    cdef cppclass Tree:
        pass

cdef extern from "SEScalarPressure.h":
    cdef cppclass PressureUnit:
        pass
    cdef cppclass SEScalarPressure:
        pass

cdef extern from "Logger.h" namespace "biogears":
    cdef cppclass Logger:
        pass

cdef extern from "SECardiovascularSystem.h" namespace "biogears":
    cdef cppclass SECardiovascularSystem:
        SECardiovascularSystem(Logger *logger)
        
        const SEScalar* GetScalar(const char* name)
        # const SEScalar* GetScalar(const std::string& name)
        # const SEScalar* GetScalar(const char* name) 
        # const SEScalar* GetScalar(const std::string& name) 

        bool Load(const CardiovascularSystemData& data)
        CardiovascularSystemData* Unload() 

        #Tree[const char*] GetPhysiologyRequestGraph(self) 

        bool HasArterialPressure() 
        SEScalarPressure& GetArterialPressure()
        #double GetArterialPressure(self, const PressureUnit& unit) 

        bool HasBloodVolume() 
        # SEScalarVolume& GetBloodVolume()
        # double GetBloodVolume(const VolumeUnit& unit) 

        # bool HasCardiacIndex() 
        # SEScalarVolumePerTimeArea& GetCardiacIndex()
        # double GetCardiacIndex(const VolumePerTimeAreaUnit& unit) 

        # bool HasCardiacOutput() 
        # SEScalarVolumePerTime& GetCardiacOutput()
        # double GetCardiacOutput(const VolumePerTimeUnit& unit) 

        # bool HasCentralVenousPressure() 
        # SEScalarPressure& GetCentralVenousPressure()
        # double GetCentralVenousPressure(const PressureUnit& unit) 

        # bool HasCerebralBloodFlow() 
        # SEScalarVolumePerTime& GetCerebralBloodFlow()
        # double GetCerebralBloodFlow(const VolumePerTimeUnit& unit) 

        # bool HasCerebralPerfusionPressure() 
        # SEScalarPressure& GetCerebralPerfusionPressure()
        # double GetCerebralPerfusionPressure(const PressureUnit& unit) 

        # bool HasDiastolicArterialPressure() 
        # SEScalarPressure& GetDiastolicArterialPressure()
        # double GetDiastolicArterialPressure(const PressureUnit& unit) 

        # bool HasHeartEjectionFraction() 
        # SEScalarFraction& GetHeartEjectionFraction()
        # double GetHeartEjectionFraction() 

        # bool HasHeartRate() 
        # SEScalarFrequency& GetHeartRate()
        # double GetHeartRate(const FrequencyUnit& unit) 

        # CDM::enumHeartRhythm::value GetHeartRhythm() 
        # void SetHeartRhythm(CDM::enumHeartRhythm::value Rhythm)
        # bool HasHeartRhythm() 
        # void InvalidateHeartRhythm()

        # bool HasHeartStrokeVolume() 
        # SEScalarVolume& GetHeartStrokeVolume()
        # double GetHeartStrokeVolume(const VolumeUnit& unit) 

        # bool HasIntracranialPressure() 
        # SEScalarPressure& GetIntracranialPressure()
        # double GetIntracranialPressure(const PressureUnit& unit) 

        # bool HasMeanArterialPressure() 
        # SEScalarPressure& GetMeanArterialPressure()
        # double GetMeanArterialPressure(const PressureUnit& unit) 

        # bool HasMeanArterialCarbonDioxidePartialPressure() 
        # SEScalarPressure& GetMeanArterialCarbonDioxidePartialPressure()
        # double GetMeanArterialCarbonDioxidePartialPressure(const PressureUnit& unit) 

        # bool HasMeanArterialCarbonDioxidePartialPressureDelta() 
        # SEScalarPressure& GetMeanArterialCarbonDioxidePartialPressureDelta()
        # double GetMeanArterialCarbonDioxidePartialPressureDelta(const PressureUnit& unit) 

        # bool HasMeanCentralVenousPressure() 
        # SEScalarPressure& GetMeanCentralVenousPressure()
        # double GetMeanCentralVenousPressure(const PressureUnit& unit) 

        # bool HasMeanSkinFlow() 
        # SEScalarVolumePerTime& GetMeanSkinFlow()
        # double GetMeanSkinFlow(const VolumePerTimeUnit& unit) 

        # bool HasPulmonaryArterialPressure() 
        # SEScalarPressure& GetPulmonaryArterialPressure()
        # double GetPulmonaryArterialPressure(const PressureUnit& unit) 

        # bool HasPulmonaryCapillariesWedgePressure() 
        # SEScalarPressure& GetPulmonaryCapillariesWedgePressure()
        # double GetPulmonaryCapillariesWedgePressure(const PressureUnit& unit) 

        # bool HasPulmonaryDiastolicArterialPressure() 
        # SEScalarPressure& GetPulmonaryDiastolicArterialPressure()
        # double GetPulmonaryDiastolicArterialPressure(const PressureUnit& unit) 

        # bool HasPulmonaryMeanArterialPressure() 
        # SEScalarPressure& GetPulmonaryMeanArterialPressure()
        # double GetPulmonaryMeanArterialPressure(const PressureUnit& unit) 

        # bool HasPulmonaryMeanCapillaryFlow() 
        # SEScalarVolumePerTime& GetPulmonaryMeanCapillaryFlow()
        # double GetPulmonaryMeanCapillaryFlow(const VolumePerTimeUnit& unit) 

        # bool HasPulmonaryMeanShuntFlow() 
        # SEScalarVolumePerTime& GetPulmonaryMeanShuntFlow()
        # double GetPulmonaryMeanShuntFlow(const VolumePerTimeUnit& unit) 

        # bool HasPulmonarySystolicArterialPressure() 
        # SEScalarPressure& GetPulmonarySystolicArterialPressure()
        # double GetPulmonarySystolicArterialPressure(const PressureUnit& unit) 

        # bool HasPulmonaryVascularResistance() 
        # SEScalarFlowResistance& GetPulmonaryVascularResistance()
        # double GetPulmonaryVascularResistance(const FlowResistanceUnit& unit) 

        # bool HasPulmonaryVascularResistanceIndex() 
        # SEScalarPressureTimePerVolumeArea& GetPulmonaryVascularResistanceIndex()
        # double GetPulmonaryVascularResistanceIndex(const PressureTimePerVolumeAreaUnit& unit) 

        # bool HasPulsePressure() 
        # SEScalarPressure& GetPulsePressure()
        # double GetPulsePressure(const PressureUnit& unit) 

        # bool HasSystolicArterialPressure() 
        # SEScalarPressure& GetSystolicArterialPressure()
        # double GetSystolicArterialPressure(const PressureUnit& unit) 

        # bool HasSystemicVascularResistance() 
        # SEScalarFlowResistance& GetSystemicVascularResistance()
        # double GetSystemicVascularResistance(const FlowResistanceUnit& unit) 

