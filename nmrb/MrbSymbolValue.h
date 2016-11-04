#pragma once
#pragma once

#include "MrbValue.h"
#include "MrbState.h"

namespace nmrb {

  public ref class MrbSymbolValue : MrbValue
  {
  protected:
    char* s = nullptr;
  public:
    MrbSymbolValue(MrbState^ cli_mrb, String^ symname)
      : MrbValue()
    {
      s = clistr_to_utf8(symname);
      *value = mrb_symbol_value(mrb_intern_cstr(cli_mrb->ptr, s));
    }
    ~MrbSymbolValue() { this->!MrbSymbolValue(); }
    !MrbSymbolValue() { if (s) mrb_utf8_free(s); };
  internal:
    MrbSymbolValue(mrb_state* mrb, const char* symname)
      : MrbValue(mrb_symbol_value(mrb_intern_cstr(mrb, symname)))
    {
      ;
    }
    MrbSymbolValue(mrb_value sym) : MrbValue(sym)
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
