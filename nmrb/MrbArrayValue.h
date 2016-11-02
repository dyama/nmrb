#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbArrayValue : MrbValue
  {
  public:
    MrbArrayValue(MrbState^ cli_mrb, array<MrbValue^>^ src)
      : MrbValue(cli_mrb->ptr, mrb_ary_new(cli_mrb->ptr))
    {
      this->AddRange(src);
    }
    void Add(MrbValue^ val)
    {
      mrb_ary_push(mrb, *value, *(val->ptr));
    }
    void AddRange(array<MrbValue^>^ src)
    {
      for each (MrbValue^ val in src) {
        mrb_ary_push(mrb, *value, *(val->ptr));
      }
    }
    Int32 Count()
    {
      return mrb_ary_len(mrb, *value);
    }
    MrbValue^ operator[](Int32 index)
    {
      return gcnew MrbValue(mrb, mrb_ary_ref(mrb, *value, index));
    }
    array<MrbValue^>^ ToArray()
    {
      List<MrbValue^>^ list = gcnew List<MrbValue^>();
      for (int i = 0; i < this->Count(); i++) {
        list->Add(this[i]);
      }
      return list->ToArray();
    }
  internal:
    MrbArrayValue(mrb_state* mrb) : MrbValue(mrb, mrb_ary_new(mrb))
    {
      ;
    }
  };

}