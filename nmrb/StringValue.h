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
#if 1
      System::Text::UTF8Encoding^ e = gcnew System::Text::UTF8Encoding(false);
      if (mrb_string_p(*value)) {
        return e->GetString((unsigned char*)RSTRING_PTR(*value), mrb_string_value_len(mrb->ptr, *value));
      }
      else {
        mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
        return e->GetString((unsigned char*)RSTRING_PTR(res), mrb_string_value_len(mrb->ptr, res));
      }
#else
      if (mrb_string_p(*value)) {
        return gcnew String((char*)RSTRING_PTR(*value));
      }
      else {
        mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
        return gcnew String((char*)RSTRING_PTR(res));
      }
#endif
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
