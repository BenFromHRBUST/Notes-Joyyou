/* { dg-do compile } */
/* { dg-options "-O2 -mdejagnu-cpu=power10" } */

#define NAME ge
#define CODE >=

#include "setbc.h"

/* "x >= 0" is done without setbc.
   The generic code sometimes transforms "x >= A" to "x > A-1"; we allow
   either here.  */
/* { dg-final { scan-assembler-times {\msetbcr?\M} 16 } } */
