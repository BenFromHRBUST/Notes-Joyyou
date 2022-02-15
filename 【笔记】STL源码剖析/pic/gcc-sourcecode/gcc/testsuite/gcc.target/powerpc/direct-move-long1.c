/* { dg-do compile { target lp64 } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } } */
/* { dg-require-effective-target powerpc_p8vector_ok } */
/* { dg-options "-mdejagnu-cpu=power8 -O2" } */
/* { dg-final { scan-assembler "mtvsrd" } } */
/* { dg-final { scan-assembler "mfvsrd" } } */

/* Check code generation for direct move for long types.  */

#define TYPE long
#define IS_INT 1
#define NO_ALTIVEC 1
#define VSX_REG_ATTR "d"

#include "direct-move.h"
