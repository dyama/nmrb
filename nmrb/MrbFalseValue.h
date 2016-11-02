#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbFalseValue : MrbValue
  {
  public:
    MrbFalseValue(MrbState^ cli_mrb) : MrbValue(cli_mrb->ptr, mrb_false_value())
    {
      ;
    }
  internal:
    MrbFalseValue(mrb_state* mrb) : MrbValue(mrb, mrb_false_value())
    {
      ;
    }
  };

}