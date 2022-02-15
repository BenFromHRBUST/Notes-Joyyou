/* Test the vqdmlsls_lane_s32 AArch64 SIMD intrinsic.  */

/* { dg-do compile } */
/* { dg-options "-save-temps -O3 -fno-inline" } */

#include "arm_neon.h"

int64_t
t_vqdmlsls_lane_s32 (int64_t a, int32_t b, int32x2_t c)
{
  return vqdmlsls_lane_s32 (a, b, c, 0);
}

/* { dg-final { scan-assembler-times "sqdmlsl\[ \t\]+\[dD\]\[0-9\]+, ?\[sS\]\[0-9\]+, ?\[sS\]\[0-9\]\n" 1 } } */
