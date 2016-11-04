#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbFixnumValue : MrbValue
  {
  public:
    MrbFixnumValue(Int32 val)
      : MrbValue(mrb_fixnum_value(val))
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
  };

}
