/* { dg-require-effective-target arm_v8_1m_mve_ok } */
/* { dg-add-options arm_v8_1m_mve } */
/* { dg-additional-options "-O2" } */

#include "arm_mve.h"

int32x4_t
foo1 (int32_t * base, uint32x4_t offset)
{
  return vldrwq_gather_offset (base, offset);
}

/* { dg-final { scan-assembler-not "__ARM_undef" } } */
