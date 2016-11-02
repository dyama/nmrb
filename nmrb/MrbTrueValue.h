#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbTrueValue : MrbValue
  {
  public:
    MrbTrueValue(MrbState^ cli_mrb) : MrbValue(cli_mrb->ptr, mrb_true_value())
    { 
      ;
    }
  internal:
    MrbTrueValue(mrb_state* mrb) : MrbValue(mrb, mrb_true_value())
    {
      ;
    }
  };
}
