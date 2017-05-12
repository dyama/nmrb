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
      char* str = nullptr;
      int32_t len = -1;
      bool called_to_s = false;
      // //try {
      //   System::Text::UTF8Encoding^ e = gcnew System::Text::UTF8Encoding(false);
      //   if (mrb_string_p(*value)) {
      //     str = (char*)RSTRING_PTR(*value);
      //     len = mrb_string_value_len(mrb->ptr, *value);
      //   }
      //   else {
      //     called_to_s = true;
      //     mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
      //     str = (char*)RSTRING_PTR(res);
      //     len = mrb_string_value_len(mrb->ptr, res);
      //   }
      //   return e->GetString((unsigned char*)str, len);
      // //}
      // //catch (System::Exception^ ex) {
      // //  String^ ss = gcnew String(ex->Message);
      // //  ss = String::Format("message:{0}, called_to_s:{1}, len:{2}", ss, called_to_s, len, gcnew String(str));
      // //  throw gcnew Exception(ss);
      // //}

      // //
      // if (mrb_string_p(*value)) {
      //   return gcnew String((char*)RSTRING_PTR(*value));
      // }
      // else {
      //   mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
      //   return gcnew String((char*)RSTRING_PTR(res));
      // }

     System::Text::UTF8Encoding^ e = gcnew System::Text::UTF8Encoding(false);
     if (mrb_string_p(*value)) {
       str = (char*)RSTRING_PTR(*value);
       len = mrb_string_value_len(mrb->ptr, *value);
     }
     else {
       mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
       str = (char*)RSTRING_PTR(res);
       len = mrb_string_value_len(mrb->ptr, res);
     }
     array<unsigned char>^ bytes = gcnew array<unsigned char>(len);
     int i = 0;
     for (; i < len; i++) {
       bytes[i] = str[i];
     }
     // bytes[i] = '\0';
     return e->GetString(bytes);
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
