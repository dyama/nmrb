#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class FalseValue : Value
  {
  public:
    FalseValue() : Value(mrb_false_value())
    {
      ;
    }
  };

}