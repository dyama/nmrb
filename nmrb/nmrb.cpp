#include "nmrb.h"

namespace nmrb
{
  extern "C" mrb_value _cli(mrb_state* mrb, mrb_value self)
  {
    const char* s = mrb_sym2name(mrb, mrb->c->ci->mid);
    auto methodname = mrb_str_new_cstr(mrb, s);
    String^ mname = gcnew String(s);
    if (!State::CliMethods->ContainsKey(mname)) {
      mrb_raisef(mrb, E_NOMETHOD_ERROR, "No such CLI method: %S", methodname);
    }
#ifndef DEBUG
    try {
#endif
      FuncType^ f = State::CliMethods[mname];
      List<Value^>^ a = gcnew List<Value^>();
      mrb_value* args;
      mrb_int len;
      mrb_get_args(mrb, "*", &args, &len);
      for (int i = 0; i < len; i++) {
        a->Add(Value::ToCliValue(mrb, args[i]));
      }
      Value^ cli_res = f(a->ToArray());
      return *(cli_res->ptr);
#ifndef DEBUG
    }
    catch (Exception^ ex) {
      char* utf_message = clistr_to_utf8(ex->Message);
      auto message = mrb_str_new_cstr(mrb, utf_message);
      mrb_raisef(mrb, E_RUNTIME_ERROR, "Raise in CLI method `%S`: %S", methodname, message);
    }
    return mrb_nil_value();
#endif
  }

  char* clistr_to_utf8(String^ str)
  {
    std::string s = marshal_as<std::string>(str);
    return mrb_utf8_from_locale(s.c_str(), -1);
  }

}
