#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbFixnumValue : MrbValue
  {
  public:
    MrbFixnumValue(MrbState^ cli_mrb, Int32 val)
      : MrbValue(cli_mrb->ptr, mrb_fixnum_value(val))
    {
      ;
    }

    Int32 ToInteger()
    {
      return ToInt32();
    }

    Int32 ToInt32()
    {
      return mrb_fixnum(*value);
    }

  internal:
    MrbFixnumValue(mrb_state* mrb, int val) : MrbValue(mrb, mrb_fixnum_value(val))
    {
      ;
    }
  };

}
