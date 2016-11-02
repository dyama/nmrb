#include "MrbValue.h"
#include "MrbNilValue.h"
#include "MrbSymbolValue.h"
#include "MrbTrueValue.h"
#include "MrbFalseValue.h"
#include "MrbFixnumValue.h"
#include "MrbFloatValue.h"
#include "MrbStringValue.h"
#include "MrbArrayValue.h"

namespace nmrb {

  MrbValue::MrbValue(mrb_state* mrb, mrb_value src)
  {
    this->mrb = mrb;
    this->value = new mrb_value;
    *this->value = src;
  }

  MrbValue::MrbValue(MrbState^ climrb, MrbValue^ src)
  {
    this->mrb = climrb->ptr;
    this->climrb = climrb;
    this->value = new mrb_value;
    *this->value = *(src->ptr);
  }

  MrbValue::~MrbValue()
  {
    this->!MrbValue();
  }

  MrbValue::!MrbValue()
  {
    if (this->value) {
      delete this->value;
    }
  }

  Boolean MrbValue::IsNill()
  {
    return mrb_nil_p(*value);
  }

  Boolean MrbValue::IsSymbol()
  {
    return mrb_symbol_p(*value);
  }

  Boolean MrbValue::IsFixnum()
  {
    return mrb_fixnum_p(*value);
  }

  Boolean MrbValue::IsFloat()
  {
    return mrb_float_p(*value);
  }

  Boolean MrbValue::IsString()
  {
    return mrb_string_p(*value);
  }

  Boolean MrbValue::IsArray()
  {
    return mrb_array_p(*value);
  }

  Boolean MrbValue::IsHash()
  {
    return mrb_hash_p(*value);
  }

  Boolean MrbValue::ToBoolean()
  {
    return mrb_bool(*value);
  }

  String^ MrbValue::ToString()
  {
    if (mrb_string_p(*value)) {
      return gcnew String(RSTRING_PTR(*value));
    }
    mrb_value res = mrb_funcall(mrb, *value, "to_s", 0);
    return gcnew String(RSTRING_PTR(res));
  }

  Dictionary<String^, MrbValue^>^ MrbValue::ToDictionary()
  {
    khash_t(ht) *h = RHASH_TBL(*value);
    if (!h) {
      return gcnew Dictionary<String^, MrbValue^>();
    }
    khiter_t k;
    Dictionary<String^, MrbValue^>^ res = gcnew Dictionary<String^, MrbValue^>();
    for (k = kh_begin(h); k != kh_end(h); k++) {
      if (kh_exist(h, k)) {
        mrb_value key = kh_key(h, k);
        mrb_value val = kh_value(h, k).v;
        res->Add((gcnew MrbValue(mrb, key))->ToString(), gcnew MrbValue(mrb, val));
      }
    }
    return res;
  }

  MrbValue^ MrbValue::ToMrbValue(mrb_state* mrb, mrb_value val)
  {
    if (mrb_nil_p(val)) {
      return gcnew MrbNilValue(mrb);
    }
    else if (mrb_symbol_p(val)) {
      return gcnew MrbSymbolValue(mrb, val);
    }
    else if (mrb_type(val) == MRB_TT_TRUE) {
      return gcnew MrbTrueValue(mrb);
    }
    else if (mrb_type(val) == MRB_TT_FALSE) {
      return gcnew MrbFalseValue(mrb);
    }
    else if (mrb_fixnum_p(val)) {
      return gcnew MrbFixnumValue(mrb, mrb_fixnum(val));
    }
    else if (mrb_float_p(val)) {
      return gcnew MrbFloatValue(mrb, mrb_float(val));
    }
    else if (mrb_string_p(val)) {
      return gcnew MrbStringValue(mrb, mrb_string_value_cstr(mrb, &val));
    }
    else if (mrb_array_p(val)) {
      MrbArrayValue^ ary = gcnew MrbArrayValue(mrb);
      for (int i = 0; i < mrb_ary_len(mrb, val); i++) {
        mrb_value item = mrb_ary_ref(mrb, val, i);
        ary->Add(MrbValue::ToMrbValue(mrb, item));
      }
      return ary;
    }
    return gcnew MrbValue(mrb, val);
  }

}
