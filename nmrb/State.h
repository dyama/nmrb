#pragma once

#include "nmrb.h"

namespace nmrb {

  ref class Value;
  ref class FuncType;

  public ref class State
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
    property Value^ default[String^]
    {
      Value^ get(String^ key)
      {
        return this->Do(key);
      }
    }
    static Dictionary<String^, FuncType^>^ CliMethods;

  public:
    State();
    State(mrb_state* src);
    ~State();
    !State();

  public:
    Value^ Do(String^ script);
    Value^ DoFile(String^ path);
    void DefineCliMethod(String^ name, FuncType^ a);
    Value^ FunCall(String^ func, ... array<Value^>^ args);

  };
}
