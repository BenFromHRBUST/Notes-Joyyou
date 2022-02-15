/* { dg-do compile { target int128 } } */
/* { dg-options "-O3 -march=skylake-avx512" } */

#include "pr100865-11a.c"

/* { dg-final { scan-assembler-times "movabsq" 1 } } */
/* { dg-final { scan-assembler-times "vpbroadcastq\[\\t \]+%(?:r|e)\[^\n\]*, %xmm\[0-9\]+" 1 } } */
/* { dg-final { scan-assembler-times "vmovdqa64\[\\t \]%xmm\[0-9\]+, " 16 } } */
