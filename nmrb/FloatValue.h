#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class FloatValue : Value
  {
  public:
    FloatValue(State^ cli_mrb, Double val)
      : Value(mrb_float_value(cli_mrb->ptr, val))
    {
      ;
    }

    Double ToDouble()
    {
      return mrb_float(*value);
    }
  };

}
