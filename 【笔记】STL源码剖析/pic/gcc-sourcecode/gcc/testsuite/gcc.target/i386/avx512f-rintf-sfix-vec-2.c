/* { dg-do compile } */
/* { dg-options "-O2 -ffast-math -ftree-vectorize -mavx512f" } */
/* { dg-require-effective-target c99_runtime } */

#include "avx512f-rintf-sfix-vec-1.c"

/* { dg-final { scan-assembler-times "vcvtps2dq\[^\n\]+zmm\[0-9\](?:\n|\[ \\t\]+#)" 1 } } */
