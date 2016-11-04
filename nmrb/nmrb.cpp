#include "nmrb.h"

namespace nmrb
{
  extern "C" mrb_value _cli(mrb_state* mrb, mrb_value self)
  {
    const char* s = mrb_sym2name(mrb, mrb->c->ci->mid);
    String^ mname = gcnew String(s);
    if (!State::CliMethods->ContainsKey(mname)) {
      mrb_raisef(mrb, E_NOMETHOD_ERROR, "No such CLI method: %s", s);
    }
    try {
      FuncType^ f = State::CliMethods[mname];
      List<Value^>^ a = gcnew List<Value^>();
      mrb_value* args;
      mrb_int len;
      mrb_get_args(mrb, "*", &args, &len);
      for (int i = 0; i < len; i++) {
        a->Add(Value::ToMrbValue(mrb, args[i]));
      }
      Value^ cli_res = f(a->ToArray());
      return *(cli_res->ptr);
    }
    catch (Exception^ ex) {
      char* utf8 = clistr_to_utf8(ex->Message);
      mrb_raisef(mrb, E_RUNTIME_ERROR, "Raise in CLI method: %s", utf8);
      mrb_utf8_free(utf8); // okay?
    }
    return mrb_nil_value();
  }

  char* clistr_to_utf8(String^ str)
  {
    std::string s = marshal_as<std::string>(str);
    return mrb_utf8_from_locale(s.c_str(), -1);
  }

}
