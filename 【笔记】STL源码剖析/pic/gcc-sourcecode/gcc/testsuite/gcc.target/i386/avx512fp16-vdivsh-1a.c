/* { dg-do compile } */
/* { dg-options "-mavx512fp16 -O2" } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\{%k\[0-9\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\{%k\[0-9\]\}\{z\}\[^\n\r]*(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+\{rn-sae\}\[^\{\n\]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+\{rn-sae\}\[^\{\n\]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\{%k\[0-9\]\}(?:\n|\[ \\t\]+#)" 1 } } */
/* { dg-final { scan-assembler-times "vdivsh\[ \\t\]+\{rz-sae\}\[^\{\n\]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\[^\n\r]*%xmm\[0-9\]+\{%k\[0-9\]\}\{z\}\[^\n\r]*(?:\n|\[ \\t\]+#)" 1 } } */

#include <immintrin.h>

volatile __m128h res;
volatile __m128h x1, x2;
volatile __mmask16 m16;
volatile __mmask8 m8;

void extern
avx512f_test (void)
{
  res = _mm_div_sh (x1, x2);
  res = _mm_mask_div_sh (res, m8, x1, x2);
  res = _mm_maskz_div_sh (m8, x1, x2);

  res = _mm_div_round_sh (x1, x2, 8);
  res = _mm_mask_div_round_sh (res, m8, x1, x2, 8);
  res = _mm_maskz_div_round_sh (m8, x1, x2, 11);
}
