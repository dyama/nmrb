#include "Value.h"
#include "NilValue.h"
#include "SymbolValue.h"
#include "TrueValue.h"
#include "FalseValue.h"
#include "FixnumValue.h"
#include "FloatValue.h"
#include "StringValue.h"
#include "ArrayValue.h"

namespace nmrb {

  Value::Value()
  {
    this->value = new mrb_value;
    *this->value = mrb_nil_value();
  }

  Value::Value(mrb_value src)
  {
    this->value = new mrb_value;
    *this->value = src;
  }

  Value::Value(Value^ src)
  {
    this->value = new mrb_value;
    *this->value = *(src->ptr);
  }

  Value::~Value()
  {
    this->!Value();
  }

  Value::!Value()
  {
    if (this->value) {
      delete this->value;
    }
  }

  Boolean Value::IsNill()
  {
    return mrb_nil_p(*value);
  }

  Boolean Value::IsSymbol()
  {
    return mrb_symbol_p(*value);
  }

  Boolean Value::IsFixnum()
  {
    return mrb_fixnum_p(*value);
  }

  Boolean Value::IsFloat()
  {
    return mrb_float_p(*value);
  }

  Boolean Value::IsString()
  {
    return mrb_string_p(*value);
  }

  Boolean Value::IsArray()
  {
    return mrb_array_p(*value);
  }

  Boolean Value::IsHash()
  {
    return mrb_hash_p(*value);
  }

  Boolean Value::ToBoolean()
  {
    return mrb_bool(*value);
  }

  String^ Value::ToString(State^ mrb)
  {
    System::Text::UTF8Encoding^ e = gcnew System::Text::UTF8Encoding(false);
    if (mrb_string_p(*value)) {
      return e->GetString((unsigned char*)RSTRING_PTR(*value), mrb_string_value_len(mrb->ptr, *value));
    }
    else {
      mrb_value res = mrb_funcall(mrb->ptr, *value, "to_s", 0);
      return e->GetString((unsigned char*)RSTRING_PTR(res), mrb_string_value_len(mrb->ptr, res));
    }
  }

  Dictionary<Value^, Value^>^ Value::ToDictionary(State^ mrb)
  {
    khash_t(ht) *h = RHASH_TBL(*value);
    if (!h) {
      return gcnew Dictionary<Value^, Value^>();
    }
    khiter_t k;
    Dictionary<Value^,Value^>^ res = gcnew Dictionary<Value^, Value^>();
    for (k = kh_begin(h); k != kh_end(h); k++) {
      if (kh_exist(h, k)) {
        mrb_value key = kh_key(h, k);
        mrb_value val = kh_value(h, k).v;
        res->Add(gcnew Value(key), gcnew Value(val));
      }
    }
    return res;
  }

  Value^ Value::ToMrbValue(mrb_state* mrb, mrb_value val)
  {
    if (mrb_nil_p(val)) {
      return gcnew NilValue();
    }
    else if (mrb_symbol_p(val)) {
      return gcnew SymbolValue(val);
    }
    else if (mrb_type(val) == MRB_TT_TRUE) {
      return gcnew TrueValue();
    }
    else if (mrb_type(val) == MRB_TT_FALSE) {
      return gcnew FalseValue();
    }
    else if (mrb_fixnum_p(val)) {
      return gcnew FixnumValue(mrb_fixnum(val));
    }
    else if (mrb_float_p(val)) {
      return gcnew FloatValue(gcnew State(mrb), mrb_float(val));
    }
    else if (mrb_string_p(val)) {
      return gcnew StringValue(mrb, mrb_string_value_cstr(mrb, &val));
    }
    else if (mrb_array_p(val)) {
      ArrayValue^ ary = gcnew ArrayValue(mrb);
      for (int i = 0; i < mrb_ary_len(mrb, val); i++) {
        mrb_value item = mrb_ary_ref(mrb, val, i);
        ary->Add(gcnew State(mrb), Value::ToMrbValue(mrb, item));
      }
      return ary;
    }
    return gcnew Value(val);
  }

}
