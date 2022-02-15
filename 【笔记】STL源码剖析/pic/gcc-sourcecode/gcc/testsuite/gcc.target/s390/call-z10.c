/* { dg-do compile } */
/* { dg-options "-O3 -march=z10 -mzarch" } */

#include "call.h"

/* { dg-final { scan-assembler {brasl\t%r\d+,foo@PLT\n} { target lp64 } } } */
/* { dg-final { scan-assembler {brasl\t%r\d+,foo\n} { target { ! lp64 } } } } */
/* { dg-final { scan-assembler {larl\t%r2,foo@PLT\n} { target lp64 } } } */
/* { dg-final { scan-assembler {larl\t%r2,foo\n} { target { ! lp64 } } } } */

/* { dg-final { scan-assembler {brasl\t%r\d+,foostatic@PLT\n} { target lp64 } } } */
/* { dg-final { scan-assembler {brasl\t%r\d+,foostatic\n} { target { ! lp64 } } } } */
/* { dg-final { scan-assembler {larl\t%r2,foostatic@PLT\n} { target lp64 } } } */
/* { dg-final { scan-assembler {larl\t%r2,foostatic\n} { target { ! lp64 } } } } */

/* { dg-final { scan-assembler {brasl\t%r\d+,fooweak\n} } } */
/* { dg-final { scan-assembler {larl\t%r2,fooweak\n} } } */

/* { dg-final { scan-assembler {foos:\n\t.quad\tfoo\n\t.quad\tfoostatic\n\t.quad\tfooweak\n} { target lp64 } } } */
/* { dg-final { scan-assembler {foos:\n\t.long\tfoo\n\t.long\tfoostatic\n\t.long\tfooweak\n} { target { ! lp64 } } } } */
