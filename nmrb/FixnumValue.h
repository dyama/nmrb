#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class FixnumValue : Value
  {
  public:
    FixnumValue(Int32 val)
      : Value(mrb_fixnum_value(val))
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
