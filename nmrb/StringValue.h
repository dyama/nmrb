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
  public:
    String^ ToString(State^ mrb) override
    {
     auto target = mrb_string_p(*value) ? *value : mrb_funcall(mrb->ptr, *value, "to_s", 0);
     auto str = mrb_string_value_ptr(mrb->ptr, target);
     auto len = mrb_string_value_len(mrb->ptr, target);
     array<Byte>^ bytes = gcnew array<Byte>(len);
     for (int i = 0; i < len; i++) {
       bytes[i] = str[i];
     }
     return (gcnew System::Text::UTF8Encoding(false))->GetString(bytes);
    }
  internal:
    StringValue(mrb_state* mrb, const char* s) : Value()
    {
      *value = mrb_str_new_cstr(mrb, s);
    }
    StringValue(mrb_state* mrb, mrb_value s) : Value()
    {
      *value = s;
    }
  };

}
