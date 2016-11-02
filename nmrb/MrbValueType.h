#pragma once

namespace nmrb {

  public enum class MrbValueType
  {
    FALSEVAL = 0,/*   0 */
    FREE,        /*   1 */
    TRUEVAL,     /*   2 */
    FIXNUM,      /*   3 */
    SYMBOL,      /*   4 */
    UNDEF,       /*   5 */
    FLOAT,       /*   6 */
    CPTR,        /*   7 */
    OBJECT,      /*   8 */
    CLASS,       /*   9 */
    MODULE,      /*  10 */
    ICLASS,      /*  11 */
    SCLASS,      /*  12 */
    PROC,        /*  13 */
    ARRAY,       /*  14 */
    HASH,        /*  15 */
    STRING,      /*  16 */
    RANGE,       /*  17 */
    EXCEPTION,   /*  18 */
    FILE,        /*  19 */
    ENV,         /*  20 */
    DATA,        /*  21 */
    FIBER,       /*  22 */
    MAXDEFINE    /*  23 */
  };

}
