#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbTrueValue : MrbValue
  {
  public:
    MrbTrueValue() : MrbValue(mrb_true_value())
    { 
      ;
    }
  };
}
