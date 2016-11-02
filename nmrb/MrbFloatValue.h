#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbFloatValue : MrbValue
  {
  public:
    MrbFloatValue(MrbState^ cli_mrb, Double val)
      : MrbValue(cli_mrb->ptr, mrb_float_value(cli_mrb->ptr, val))
    {
      ;
    }

    Double ToDouble()
    {
      return mrb_float(*value);
    }

  internal:
    MrbFloatValue(mrb_state* mrb, double val) : MrbValue(mrb, mrb_float_value(mrb, val))
    {
      ;
    }
  };

}
