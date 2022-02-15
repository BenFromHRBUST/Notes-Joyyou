/* { dg-require-effective-target arm_v8_1m_mve_fp_ok } */
/* { dg-add-options arm_v8_1m_mve_fp } */
/* { dg-additional-options "-O2" } */

#include "arm_mve.h"

float16x8_t
foo (float16x8_t a, int32_t b)
{
  return vbrsrq_n_f16 (a, b);
}

/* { dg-final { scan-assembler "vbrsr.16"  }  } */

float16x8_t
foo1 (float16x8_t a, int32_t b)
{
  return vbrsrq (a, b);
}

/* { dg-final { scan-assembler "vbrsr.16"  }  } */
