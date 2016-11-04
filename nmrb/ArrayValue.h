#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class ArrayValue : Value
  {
  public:
    ArrayValue(State^ cli_mrb, array<Value^>^ src)
      : Value(mrb_ary_new(cli_mrb->ptr))
    {
      this->AddRange(cli_mrb, src);
    }
    void Add(State^ mrb, Value^ val)
    {
      mrb_ary_push(mrb->ptr, *value, *(val->ptr));
    }
    void AddRange(State^ mrb, array<Value^>^ src)
    {
      for each (Value^ val in src) {
        mrb_ary_push(mrb->ptr, *value, *(val->ptr));
      }
    }
    Int32 Count(State^ mrb)
    {
      return mrb_ary_len(mrb->ptr, *value);
    }
    Value^ Get(State^ mrb, Int32 index)
    {
      return gcnew Value(mrb_ary_ref(mrb->ptr, *value, index));
    }
    array<Value^>^ ToArray(State^ mrb)
    {
      List<Value^>^ list = gcnew List<Value^>();
      for (int i = 0; i < this->Count(mrb); i++) {
        list->Add(Get(mrb, i));
      }
      return list->ToArray();
    }
  internal:
    ArrayValue(mrb_state* mrb) : Value(mrb_ary_new(mrb))
    {
      ;
    }
  };

}