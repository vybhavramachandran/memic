from libcpp cimport bool

#cimport _pycardio #_pyardio.Logger
#from _pycardio cimport Logger # Logger
from pycardio cimport * # *


cdef class SEScalar:
    cdef cpp.superclass_test * thisptr
    cdef bool delete_thisptr

    def __cinit__(self):
        self.thisptr = NULL
        self.delete_thisptr = True

    def __dealloc__(self):
        if self.delete_thisptr and self.thisptr != NULL:
            del self.thisptr

    def __init__(superclass_test self):
        self.thisptr = new cpp.superclass_test()



cdef class PySECardiovascularSystem:

    cdef SECardiovascularSystem *c_SECardiovascularSystem

    def __cinit__(self, Logger* logger):
        self.c_SECardiovascularSystem = new SECardiovascularSystem(logger)      
    
    def __dealloc__(self):
        del self.c_SECardiovascularSystem

    #cdef SECardiovascularSystem(self, Logger* logger):
    #    return self.thisptr.SECardiovascularSystem(logger)
    


    cpdef SEScalar newGetScalar(self, const char* name):
        return self.c_SECardiovascularSystem.GetScalar(name)
    
    cpdef bool Load(self, const CardiovascularSystemData& data):
        return self.c_SECardiovascularSystem.Load(data)

    cpdef CardiovascularSystemData* Unload(self):
        return self.c_SECardiovascularSystem.Unload()
    
    #cpdef Tree [const char*] GetPhysiologyRequestGraph(self):
    #    return self.thisptr.GetPhysiologyRequestGraph()
    
    cpdef bool HasArterialPressure(self):
        return self.c_SECardiovascularSystem.HasArterialPressure()
    
    #cpdef SEScalarPressure& GetArterialPressure(self):
    #    return self.c_SECardiovascularSystem.GetArterialPressure()
    
    cpdef double GetArterialPressure(self, const PressureUnit& unit):
        return self.thisptr.GetArterialPressure(unit)
    
    cpdef bool HasBloodVolume(self):
        return self.c_SECardiovascularSystem.HasBloodVolume()
