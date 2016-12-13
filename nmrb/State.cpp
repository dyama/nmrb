#include "State.h"

namespace nmrb {

  extern "C" mrb_value _cli(mrb_state* mrb, mrb_value self);

  State::State()
  {
    LastErrorMessage = String::Empty;
    HasError = false;
    mrb = mrb_open();
    cxt = mrbc_context_new(mrb);
    cxt->capture_errors = TRUE;
    cxt->lineno = 1;
    mrbc_filename(mrb, cxt, "(mirb)");
    ai = mrb_gc_arena_save(mrb);
  }

  State::State(mrb_state* src)
  {
    LastErrorMessage = String::Empty;
    HasError = false;
    mrb = src;
  }

  State::~State()
  {
    this->!State();
  }

  State::!State()
  {
    //if (parser) {
    //  delete parser;
    //}
    //if (cxt) {
    //  mrbc_context_free(mrb, cxt);
    //}
    //if (mrb) {
    //  try {
    //    mrb_close(mrb);
    //  }
    //  catch (...) {}
    //}
  }

  Value^ State::Do(String^ script)
  {
    mrb_value result = mrb_nil_value();
    char* utf8 = nmrb::clistr_to_utf8(script);
    if (!utf8) {
      abort();
    }
    parser = mrb_parser_new(mrb);
    try {
      if (parser == NULL) {
        throw gcnew Exception("create paser state error");
      }
      parser->s = utf8;
      parser->send = utf8 + strlen(utf8);
      parser->lineno = cxt->lineno;
      mrb_parser_parse(parser, cxt);
      mrb_utf8_free(utf8);
      if (0 < parser->nerr) {
        throw gcnew Exception(gcnew String(parser->error_buffer[0].message));
      }
      else {
        struct RProc *proc = mrb_generate_code(mrb, parser);
        if (proc == NULL) {
          throw gcnew Exception("codegen error");
        }
        result = mrb_vm_run(mrb,
          proc,
          mrb_top_self(mrb),
          stack_keep);
        stack_keep = proc->body.irep->nlocals;
        if (mrb->exc) {
          // mrb_p(mrb, mrb_obj_value(mrb->exc));
          mrb->exc = 0;
        }
        else {
          if (!mrb_respond_to(mrb, result, mrb_intern_lit(mrb, "inspect"))) {
            result = mrb_any_to_s(mrb, result);
          }
          // mrb_p(mrb, result);
        }
      }
      if (mrb_exception_p(result)) {
        mrb_value mstr = mrb_funcall(mrb, result, "to_s", 0);
        const char* cstr = mrb_string_value_cstr(mrb, &mstr);
        LastErrorMessage = 
        String::Format("{0}:{1} {2}", gcnew String(parser->filename), parser->lineno, gcnew String(cstr));
        HasError = true;
      }
      else {
        LastErrorMessage = String::Empty;
        HasError = false;
      }
    }
    catch (Exception^ ex) {
      LastErrorMessage = ex->Message;
      HasError = true;
    }
    finally {
      mrb_gc_arena_restore(mrb, ai);
      mrb_parser_free(parser);
      cxt->lineno++;
    }
    return Value::ToMrbValue(ptr, result);
  }

  Value^ State::DoFile(String^ path)
  {
    Value^ res = gcnew Value(mrb_nil_value());
    Do(IO::File::ReadAllText(path));
    return res;
  }

  void State::DefineCliMethod(String^ name, FuncType^ a)
  {
    char* utf8 = clistr_to_utf8(name);
    if (utf8) {
      RObject* pobj = mrb_obj_ptr(mrb_obj_value(mrb->kernel_module));
      mrb_define_method(mrb, mrb->kernel_module, utf8, _cli, MRB_ARGS_NONE());
      if (!CliMethods) {
        CliMethods = gcnew Dictionary<String^, FuncType^>();
      }
      if (CliMethods->ContainsKey(name)) {
        CliMethods->Remove(name);
      }
      CliMethods->Add(name, a);
      mrb_utf8_free(utf8);
    }
  }

  Value^ State::FunCall(String^ func, ... array<Value^>^ args)
  {
    mrb_value* aa;
    aa = (mrb_value*)malloc(sizeof(mrb_value) * args->Length);
    for (int i = 0; i < args->Length; i++) {
      aa[i] = *(args[i]->ptr);
    }
    char* utf8 = clistr_to_utf8(func);
    mrb_value res = mrb_funcall_argv(mrb,
      mrb_obj_value(mrb->kernel_module),
      mrb_intern_cstr(mrb, utf8), args->Length, aa);
    mrb_utf8_free(utf8);
    // for (int i = 0; i < args->Length; i++) {
    //   mrb_free(mrb, aa+i);
    // }
    free(aa);
    return Value::ToMrbValue(mrb, res);
  }

}