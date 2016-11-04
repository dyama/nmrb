#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class NilValue : Value
  {
  public:
    NilValue() : Value()
    {
      ;
    }
  };
}