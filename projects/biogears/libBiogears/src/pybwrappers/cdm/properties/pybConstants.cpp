#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <biogears/cdm/properties/SEScalarAmount.h>
#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarPressure.h>
#include <biogears/cdm/properties/SEScalarVolumePerTime.h>
#include <biogears/cdm/properties/SEScalarPower.h>
#include <biogears/cdm/properties/SEScalarTemperature.h>
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

  py::class_<biogears::PressureUnit>(m, "PressureUnit")
    .def_readonly_static("Pa", &biogears::PressureUnit::Pa)
    .def_readonly_static("mmHg", &biogears::PressureUnit::mmHg)
    .def_readonly_static("cmH2O", &biogears::PressureUnit::cmH2O)
    .def_readonly_static("psi", &biogears::PressureUnit::psi)
    .def_readonly_static("atm", &biogears::PressureUnit::atm);

  py::class_<biogears::FrequencyUnit>(m, "FrequencyUnit")
    .def_readonly_static("Per_min", &biogears::FrequencyUnit::Per_min)
    .def_readonly_static("Per_s", &biogears::FrequencyUnit::Per_s)
    .def_readonly_static("Hz", &biogears::FrequencyUnit::Hz)
    .def_readonly_static("Per_hr", &biogears::FrequencyUnit::Per_hr);

  py::class_<biogears::PowerUnit>(m, "PowerUnit")
    .def_readonly_static("W", &biogears::PowerUnit::W)
    .def_readonly_static("kcal_Per_s", &biogears::PowerUnit::kcal_Per_s)
    .def_readonly_static("kcal_Per_hr", &biogears::PowerUnit::kcal_Per_hr)
    .def_readonly_static("kcal_Per_day", &biogears::PowerUnit::kcal_Per_day)
    .def_readonly_static("J_Per_s", &biogears::PowerUnit::J_Per_s)
    .def_readonly_static("BTU_Per_hr", &biogears::PowerUnit::BTU_Per_hr);

  py::class_<biogears::TemperatureUnit>(m, "TemperatureUnit")
    .def_readonly_static("F", &biogears::TemperatureUnit::F)
    .def_readonly_static("C", &biogears::TemperatureUnit::C)
    .def_readonly_static("K", &biogears::TemperatureUnit::K)
    .def_readonly_static("R", &biogears::TemperatureUnit::R);

#ifdef VERSION_INFO
  m.attr("__version__")
    = VERSION_INFO;
#else
  m.attr("__version__")
    = "dev";
#endif
}