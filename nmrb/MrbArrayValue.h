#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbArrayValue : MrbValue
  {
  public:
    MrbArrayValue(MrbState^ cli_mrb, array<MrbValue^>^ src)
      : MrbValue(mrb_ary_new(cli_mrb->ptr))
    {
      this->AddRange(cli_mrb, src);
    }
    void Add(MrbState^ mrb, MrbValue^ val)
    {
      mrb_ary_push(mrb->ptr, *value, *(val->ptr));
    }
    void AddRange(MrbState^ mrb, array<MrbValue^>^ src)
    {
      for each (MrbValue^ val in src) {
        mrb_ary_push(mrb->ptr, *value, *(val->ptr));
      }
    }
    Int32 Count(MrbState^ mrb)
    {
      return mrb_ary_len(mrb->ptr, *value);
    }
    MrbValue^ Get(MrbState^ mrb, Int32 index)
    {
      return gcnew MrbValue(mrb_ary_ref(mrb->ptr, *value, index));
    }
    array<MrbValue^>^ ToArray(MrbState^ mrb)
    {
      List<MrbValue^>^ list = gcnew List<MrbValue^>();
      for (int i = 0; i < this->Count(mrb); i++) {
        list->Add(Get(mrb, i));
      }
      return list->ToArray();
    }
  internal:
    MrbArrayValue(mrb_state* mrb) : MrbValue(mrb_ary_new(mrb))
    {
      ;
    }
  };

}