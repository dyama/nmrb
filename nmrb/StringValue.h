#pragma once
#include "nmrb.h"

namespace nmrb {

  public ref class StringValue : Value
  {
  protected:
    char* s = nullptr;
  public:
    StringValue(State^ cli_mrb, String^ val)
      : Value()
    { 
      s = clistr_to_utf8(val);
      *value = mrb_str_new_cstr(cli_mrb->ptr, s);
    }
    ~StringValue() { this->!StringValue(); }
    !StringValue() { if (s) mrb_utf8_free(s); };
  internal:
    StringValue(mrb_state* mrb, const char* s) : Value()
    {
      *value = mrb_str_new_cstr(mrb, s);
    }
  };

}
