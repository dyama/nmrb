#include "Value.h"
#include "NilValue.h"
#include "SymbolValue.h"
#include "TrueValue.h"
#include "FalseValue.h"
#include "FixnumValue.h"
#include "FloatValue.h"
#include "StringValue.h"
#include "ArrayValue.h"
#include "HashValue.h"

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

  Boolean Value::IsTrue()
  {
    return mrb_type(*value) == MRB_TT_TRUE;
  }

  Boolean Value::IsFalse()
  {
    return mrb_type(*value) == MRB_TT_FALSE;
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

  Int32 Value::ToInteger()
  {
    return mrb_fixnum(*value);
  }

  Double Value::ToDouble()
  {
    return mrb_float(*value);
  }

  String^ Value::ToString(State^ mrb)
  {
    if (this->IsString()) {
      return safe_cast<StringValue^>(this)->ToString(mrb);
    }
    return (gcnew StringValue(mrb->ptr, mrb_funcall(mrb->ptr, *value, "to_s", 0)))->ToString(mrb);
  }

  array<Value^>^ Value::ToArray(State^ mrb)
  {
    if (!this->IsArray()) {
      return array<Value^>::Empty<Value^>();
    }
    return safe_cast<ArrayValue^>(this)->ToArray(mrb);
  }

  Dictionary<Value^, Value^>^ Value::ToDictionary(State^ mrb)
  {
    if (!this->IsHash()) {
      return gcnew Dictionary<Value^, Value^>();
    }
    return safe_cast<HashValue^>(this)->ToDictionary(mrb);
  }

#if 0
  Value^ Value::ToCliValue(State^ mrb, Object^ obj)
  {
    if (obj == nullptr) {
      return gcnew NilValue();
    }
    else if (obj->GetType() == String::typeid) {
      String^ s = safe_cast<String^>(obj);
      if (s->Length == 0) {
        return gcnew StringValue(mrb->ptr, "");
      }
      if (s[0] == ':') {
        return gcnew SymbolValue(mrb, s->Substring(1));
      }
      return gcnew StringValue(mrb, s);
    }
    else if (obj->GetType() == Boolean::typeid) {
      if (safe_cast<Boolean>(obj) == true) {
        return gcnew TrueValue();
      }
      return gcnew FalseValue();
    }
    else if (obj->GetType() == Int32::typeid) {
      return gcnew FixnumValue(safe_cast<Int32>(obj));
    }
    else if (obj->GetType() == Double::typeid) {
      return gcnew FloatValue(mrb, safe_cast<Double>(obj));
    }
  }
#endif

  Value^ Value::ToCliValue(mrb_state* mrb, mrb_value val)
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
      return gcnew ArrayValue(mrb, val);
    }
    else if (mrb_hash_p(val)) {
      return gcnew HashValue(mrb, val);
    }
    return gcnew Value(val);
  }

}
