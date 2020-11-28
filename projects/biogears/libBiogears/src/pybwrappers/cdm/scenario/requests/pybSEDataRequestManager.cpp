#include <biogears/cdm/scenario/requests/SEDataRequestManager.h>
#include <biogears/cdm/utils/Logger.h>

#include <pybind11/pybind11.h>


namespace py = pybind11;




PYBIND11_MODULE(pybSEDataRequestManager, m) {


    py::class_<biogears::SEDataRequestManager>(m, "SEDataRequestManager")
    .def(py::init<biogears::Logger*>())
    .def("Clear",&biogears::SEDataRequestManager::Clear);


 
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}