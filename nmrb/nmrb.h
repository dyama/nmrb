#pragma once

#include <stdlib.h>
#include <string.h>

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/class.h"
#include "mruby/proc.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/hash.h"
#include "mruby/khash.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

namespace nmrb {
  char* clistr_to_utf8(String^ str);
}

#include "MrbValueType.h"
#include "MrbValue.h"
#include "MrbState.h"
