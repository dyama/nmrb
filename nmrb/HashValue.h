#pragma once

#include "Value.h"
#include "State.h"

namespace nmrb {

  public ref class HashValue : Value //, IDictionary<Value^, Value^>
  {
  public:
    HashValue(State^ cli_mrb) : Value(mrb_hash_new(cli_mrb->ptr))
    { 
    }
  public:
    void Set(State^ cli_mrb, SymbolValue^ key, Value^ cli_value)
    {
      mrb_hash_set(cli_mrb->ptr, *value, *key->ptr, *cli_value->ptr);
    }
    void Set(State^ cli_mrb, IEnumerable<KeyValuePair<SymbolValue^, Value^>>^ src)
    {
      for each (auto pair in src) {
        mrb_hash_set(cli_mrb->ptr, *value, *pair.Key->ptr, *pair.Value->ptr);
      }
    }
    Value^ Get(State^ cli_mrb, SymbolValue^ key)
    {
      mrb_value res = mrb_hash_get(cli_mrb->ptr, *value, *key->ptr);
      return gcnew Value(res);
    }
    void Remove(State^ cli_mrb, SymbolValue^ key)
    {
      mrb_hash_delete_key(cli_mrb->ptr, *value, *key->ptr);
    }
    void Clear(State^ cli_mrb, SymbolValue^ key)
    {
      mrb_hash_clear(cli_mrb->ptr, *value);
    }

    Value^ Keys(State^ cli_mrb)
    {
      auto res = gcnew List<SymbolValue^>();
      auto ary = mrb_hash_keys(cli_mrb->ptr, *value);
      return Value::ToCliValue(cli_mrb->ptr, ary);
    }

    Value^ Values(State^ cli_mrb)
    {
      auto res = gcnew List<Value^>();
      auto ary = mrb_hash_values(cli_mrb->ptr, *value);
      return Value::ToCliValue(cli_mrb->ptr, ary);
    }
    Dictionary<Value^, Value^>^ ToDictionary(State^ cli_mrb) override
    {
#if 0
      khash_t(ht) *h = RHASH_TBL(*value);
      if (!h) {
        return gcnew Dictionary<SymbolValue^, Value^>();
      }
      khiter_t k;
      auto res = gcnew Dictionary<SymbolValue^, Value^>();
      for (k = kh_begin(h); k != kh_end(h); k++) {
        if (kh_exist(h, k)) {
          mrb_value key = kh_key(h, k);
          mrb_value val = kh_value(h, k).v;
          res->Add(gcnew SymbolValue(key), gcnew Value(val));
        }
      }
      return res;
#else
      auto res = gcnew Dictionary<Value^, Value^>();
      auto keys = this->Keys(cli_mrb)->ToArray(cli_mrb);
      auto vals = this->Values(cli_mrb)->ToArray(cli_mrb);
      for (int i = 0; i < keys->Length; i++) {
        res->Add(keys[i], vals[i]);
      }
      return res;
#endif
    }
  internal:
    HashValue(mrb_state* mrb) : Value(mrb_hash_new(mrb))
    {
      ;
    }
    HashValue(mrb_state* mrb, mrb_value srchash) : Value(mrb_hash_new(mrb))
    {
      auto keys = mrb_hash_keys(mrb, srchash);
      auto vals = mrb_hash_values(mrb, srchash);
      for (int i = 0; i < mrb_ary_len(mrb, keys); i++) {
        auto kitem = gcnew SymbolValue(mrb_ary_ref(mrb, keys, i));
        auto vitem = gcnew Value(mrb_ary_ref(mrb, vals, i));
        this->Set(gcnew State(mrb), kitem, vitem);
      }
    }
  };
}
