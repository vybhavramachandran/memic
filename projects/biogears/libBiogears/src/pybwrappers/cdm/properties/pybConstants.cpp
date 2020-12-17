#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <biogears/cdm/properties/SEScalarAmount.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybConstants, m)
{

  //    .def_property_readonly_static("foo", [](py::object /* self */) { return Foo(); });
  //    py::module_::import("pybLogger");

  py::class_<biogears::AmountUnit>(m, "AmountUnit")
    .def_readonly_static("mol", &biogears::AmountUnit::mol)
    .def_readonly_static("pmol", &biogears::AmountUnit::pmol);

  py::class_<biogears::VolumePerTimeUnit>(m, "VolumePerTimeUnit")
    .def_readonly_static("L_Per_s", &biogears::VolumePerTimeUnit::L_Per_s)
    .def_readonly_static("L_Per_day", &biogears::VolumePerTimeUnit::L_Per_day)
    .def_readonly_static("mL_Per_s", &biogears::VolumePerTimeUnit::mL_Per_s)
    .def_readonly_static("mL_Per_day", &biogears::VolumePerTimeUnit::mL_Per_day)
    .def_readonly_static("L_Per_min", &biogears::VolumePerTimeUnit::L_Per_min)
    .def_readonly_static("m3_Per_s", &biogears::VolumePerTimeUnit::m3_Per_s)
    .def_readonly_static("mL_Per_min", &biogears::VolumePerTimeUnit::mL_Per_min)
    .def_readonly_static("mL_Per_hr", &biogears::VolumePerTimeUnit::mL_Per_hr);

#ifdef VERSION_INFO
      m.attr("__version__")
    = VERSION_INFO;
#else
      m.attr("__version__")
    = "dev";
#endif
}