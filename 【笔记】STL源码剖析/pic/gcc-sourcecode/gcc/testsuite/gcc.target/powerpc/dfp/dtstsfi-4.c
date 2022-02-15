/* { dg-do compile } */
/* { dg-require-effective-target powerpc_p9vector_ok } */
/* { dg-options "-mdejagnu-cpu=power9" } */

#include <altivec.h>

int doTestBCDSignificance (_Decimal64 *p, unsigned int significance)
{
  _Decimal64 source = *p;

  return __builtin_dfp_dtstsfi_lt (significance, source);	/* { dg-error "argument 1 must be a literal between 0 and 63, inclusive" } */
}

