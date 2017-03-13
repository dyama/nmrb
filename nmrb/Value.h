#pragma once

#include "nmrb.h"
#include "ValueType.h"

namespace nmrb {

  ref class State;

  public ref class Value
  {
  protected:
    mrb_value* value;

  public:
    property ValueType Type
    {
      ValueType get()
      {
        return (ValueType)value->tt;
      }
    }

  internal:
    Value();
    Value(mrb_value src);
    Value(Value^ src);
    ~Value();
    !Value();
    property mrb_value* ptr { mrb_value* get() { return value; } }

  public:
    Boolean IsNill();
    Boolean IsSymbol();
    Boolean IsFixnum();
    Boolean IsFloat();
    Boolean IsString();
    Boolean IsArray();
    Boolean IsHash();
    Boolean ToBoolean();
    String^ ToString(State^ mrb);
    virtual Dictionary<Value^, Value^>^ ToDictionary(State^ mrb);

  internal:
    static Value^ ToCliValue(mrb_state* mrb, mrb_value val);
  };

  public delegate Value^ FuncType(array<Value^>^ args);
}
