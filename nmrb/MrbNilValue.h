#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbNilValue : MrbValue
  {
  public:
    MrbNilValue() : MrbValue()
    {
      ;
    }
  };
}