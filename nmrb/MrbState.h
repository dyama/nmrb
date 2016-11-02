#pragma once

#include "nmrb.h"

namespace nmrb {

  ref class MrbValue;
  ref class MrbFuncType;

  public ref class MrbState
  {
  protected:
    mrb_state* mrb;
    int ai;
    struct mrb_parser_state *parser;
    mrbc_context *cxt;
    unsigned int stack_keep = 1;

  internal:
    property mrb_state* ptr { mrb_state* get() { return mrb; } }

  public:
    String^ LastErrorMessage;
    Boolean HasError;
    property MrbValue^ default[String^]
    {
      MrbValue^ get(String^ key)
      {
        return this->Do(key);
      }
    }
    static Dictionary<String^, MrbFuncType^>^ CliMethods;

  public:
    MrbState();
    ~MrbState();
    !MrbState();

  public:
    MrbValue^ Do(String^ script);
    MrbValue^ DoFile(String^ path);
    void DefineCliMethod(String^ name, MrbFuncType^ a);
    MrbValue^ FunCall(String^ func, ... array<MrbValue^>^ args);

  };
}
