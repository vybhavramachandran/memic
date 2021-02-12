#include <biogears/cdm/properties/SEScalar.h>
#include <biogears/cdm/properties/SEScalar0To1.h>
#include <biogears/cdm/properties/SEScalarLengthPerTime.h>
#include <biogears/cdm/properties/SEUnitScalar.h>
#include <biogears/cdm/properties/SEScalarQuantity.h>
#include <biogears/cdm/utils/unitconversion/CompoundUnit.h>
// #include <biogears/biogears/schema/cdm/Properties.hxx>
#include <pybind11/pybind11.h>

namespace py = pybind11;



PYBIND11_MODULE(pybSEScalarQuantity, m)
{
  py::class_<biogears::SEScalarQuantity<biogears::LengthPerTimeUnit>>(m, "SEScalarQuantity")
      .def("SetValue",&biogears::SEScalarQuantity<biogears::LengthPerTimeUnit>::SetValue);


}