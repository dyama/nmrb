#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbNilValue : MrbValue
  {
  public:
    MrbNilValue(MrbState^ cli_mrb) : MrbValue(cli_mrb->ptr, mrb_nil_value())
    {
      ;
    }
  internal:
    MrbNilValue(mrb_state* mrb) : MrbValue(mrb, mrb_nil_value())
    {
      ;
    }
  };
}