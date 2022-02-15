/* { dg-do run } */
/* { dg-require-effective-target long_double_ibm128 } */
/* { dg-options "-std=c99 -O2" } */
/* { dg-add-options long_double_ibm128 } */

#include <float.h>

#ifndef __LONG_DOUBLE_IBM128__
#error "long double must be IBM 128-bit"
#endif

union gl_long_double_union
{
  struct { double hi; double lo; } dd;
  long double ld;
};

/* This is gnulib's LDBL_MAX which, being 107 bits in precision, is
   slightly larger than gcc's 106 bit precision LDBL_MAX.  */
volatile union gl_long_double_union gl_LDBL_MAX =
  { { DBL_MAX, DBL_MAX / (double)134217728UL / (double)134217728UL } };

volatile double min_denorm = 0x1p-1074;
volatile double ld_low = 0x1p-969;
volatile double dinf = 1.0/0.0;
volatile double dnan = 0.0/0.0;

int
main (void)
{
  long double ld;

  ld = gl_LDBL_MAX.ld;
  if (__builtin_isinf (ld))
    __builtin_abort ();
  ld = -gl_LDBL_MAX.ld;
  if (__builtin_isinf (ld))
    __builtin_abort ();

  ld = gl_LDBL_MAX.ld;
  if (!__builtin_isfinite (ld))
    __builtin_abort ();
  ld = -gl_LDBL_MAX.ld;
  if (!__builtin_isfinite (ld))
    __builtin_abort ();

  ld = ld_low;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -ld_low;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();

  ld = -min_denorm;
  ld += ld_low;
  if (__builtin_isnormal (ld))
    __builtin_abort ();
  ld = min_denorm;
  ld -= ld_low;
  if (__builtin_isnormal (ld))
    __builtin_abort ();

  ld = 0.0;
  if (__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -0.0;
  if (__builtin_isnormal (ld))
    __builtin_abort ();

  ld = LDBL_MAX;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -LDBL_MAX;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();

  ld = gl_LDBL_MAX.ld;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -gl_LDBL_MAX.ld;
  if (!__builtin_isnormal (ld))
    __builtin_abort ();

  ld = dinf;
  if (__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -dinf;
  if (__builtin_isnormal (ld))
    __builtin_abort ();

  ld = dnan;
  if (__builtin_isnormal (ld))
    __builtin_abort ();
  ld = -dnan;
  if (__builtin_isnormal (ld))
    __builtin_abort ();
  return 0;
}
