/* { dg-do compile } */
/* { dg-options "-mavx512vl -O2" } */
/* { dg-final { scan-assembler-times "vmovdqu\[ \\t\]+\[^\{\n\]*\\)\[^\n\]*%xmm\[0-9\]+(?:\n|\[ \\t\]+#)" 2 } } */

#include <immintrin.h>

int *p;
long long *p1;
volatile __m128i x1, x2;

void extern
avx512vl_test (void)
{
  x1 = _mm_loadu_epi32 (p);
  x2 = _mm_loadu_epi64 (p1);
}
