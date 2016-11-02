#pragma once

#include "nmrb.h"
#include "MrbValueType.h"

namespace nmrb {

  ref class MrbState;

  public ref class MrbValue
  {
  protected:
    mrb_state* mrb;
    mrb_value* value;

  public:
    MrbState^ climrb;

  public:
    property MrbValueType Type
    {
      MrbValueType get()
      {
        return (MrbValueType)value->tt;
      }
    }

  internal:
    MrbValue(mrb_state* mrb, mrb_value src);
    MrbValue(MrbState^ climrb, MrbValue^ src);
    ~MrbValue();
    !MrbValue();
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
    String^ ToString() override;
    virtual Dictionary<String^, MrbValue^>^ ToDictionary();

  internal:
    static MrbValue^ ToMrbValue(mrb_state* mrb, mrb_value val);
  };

  public delegate MrbValue^ MrbFuncType(array<MrbValue^>^ args);
}
