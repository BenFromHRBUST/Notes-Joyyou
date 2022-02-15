/* { dg-do compile } */
/* { dg-options "-mavx512f -O2" } */
/* { dg-final { scan-assembler-times "(?:vpcmpgtd\[ \\t\]+|vpcmpd\[ \\t\]+\\\$6)\[^\{\n\]*%zmm\[0-9\]+\[^\n^k\]*%k\[0-7\](?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "(?:vpcmpgtd\[ \\t\]+|vpcmpd\[ \\t\]+\\\$6)\[^\{\n\]*%zmm\[0-9\]+\[^\n^k\]*%k\[0-7\]\{%k\[0-7\]\}(?:\n|\[ \\t\]+#)" 1 } } */

#include <immintrin.h>

volatile __m512i x;
volatile __mmask16 m;

void extern
avx512f_test (void)
{
  m = _mm512_cmpgt_epi32_mask (x, x);
  m = _mm512_mask_cmpgt_epi32_mask (3, x, x);
}
