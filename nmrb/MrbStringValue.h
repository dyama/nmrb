#pragma once
#include "nmrb.h"

namespace nmrb {

  public ref class MrbStringValue : MrbValue
  {
  protected:
    char* s = nullptr;
  public:
    MrbStringValue(MrbState^ cli_mrb, String^ val)
      : MrbValue()
    { 
      s = clistr_to_utf8(val);
      *value = mrb_str_new_cstr(cli_mrb->ptr, s);
    }
    ~MrbStringValue() { this->!MrbStringValue(); }
    !MrbStringValue() { if (s) mrb_utf8_free(s); };
  internal:
    MrbStringValue(mrb_state* mrb, const char* s) : MrbValue()
    {
      *value = mrb_str_new_cstr(mrb, s);
    }
  };

}
