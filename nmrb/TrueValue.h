#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class TrueValue : Value
  {
  public:
    TrueValue() : Value(mrb_true_value())
    { 
      ;
    }
  };
}
