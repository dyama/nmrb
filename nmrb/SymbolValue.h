#pragma once
#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class SymbolValue : Value
  {
  protected:
    char* s = nullptr;
  public:
    SymbolValue(State^ cli_mrb, String^ symname)
      : Value()
    {
      s = clistr_to_utf8(symname);
      *value = mrb_symbol_value(mrb_intern_cstr(cli_mrb->ptr, s));
    }
    ~SymbolValue() { this->!SymbolValue(); }
    !SymbolValue() { if (s) mrb_utf8_free(s); };
  internal:
    SymbolValue(mrb_state* mrb, const char* symname)
      : Value(mrb_symbol_value(mrb_intern_cstr(mrb, symname)))
    {
      ;
    }
    SymbolValue(mrb_value sym) : Value(sym)
    {
      ;
    }
  public:
    // String^ ToString() override
    // {
    //   const char* name = mrb_sym2name(mrb, mrb_symbol(*value));
    //   String^ res = gcnew String(name);
    //   return res;
    // }
  };
}
