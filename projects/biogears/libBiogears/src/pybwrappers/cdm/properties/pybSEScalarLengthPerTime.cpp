#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarLengthPerTime.h>
#include <biogears/cdm/properties/SEUnitScalar.h>
#include <biogears/cdm/utils/unitconversion/CompoundUnit.h>
#include <biogears/cdm/properties/SEScalarQuantity.h>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pybSEScalarLengthPerTime, m)
{
  py::module_::import("pybSEScalarQuantity");

  py::class_<biogears::SEScalarLengthPerTime, biogears::SEScalarQuantity<biogears::LengthPerTimeUnit>>(m, "SEScalarLengthPerTime");
#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}