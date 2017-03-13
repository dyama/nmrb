#pragma once

#include "nmrb.h"
#include "ValueType.h"

namespace nmrb {

  ref class State;
  ref class SymbolValue;

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
    Boolean IsTrue();
    Boolean IsFalse();
    Boolean IsSymbol();
    Boolean IsFixnum();
    Boolean IsFloat();
    Boolean IsString();
    Boolean IsArray();
    Boolean IsHash();
    Boolean ToBoolean();
    Int32 ToInteger();
    Double ToDouble();
    virtual String^ ToString(State^ mrb);
    virtual array<Value^>^ ToArray(State^ mrb);
    virtual Dictionary<Value^, Value^>^ ToDictionary(State^ mrb);

#if 0
    static Value^ ToCliValue(State^ mrb, Object^ obj);
#endif
  internal:
    static Value^ ToCliValue(mrb_state* mrb, mrb_value val);
  };

  public delegate Value^ FuncType(array<Value^>^ args);
}
