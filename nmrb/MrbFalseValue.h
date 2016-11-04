#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbFalseValue : MrbValue
  {
  public:
    MrbFalseValue() : MrbValue(mrb_false_value())
    {
      ;
    }
  };

}