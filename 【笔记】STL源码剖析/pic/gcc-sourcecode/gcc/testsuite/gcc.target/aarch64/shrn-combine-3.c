/* { dg-do assemble } */
/* { dg-options "-O3 --save-temps --param=vect-epilogues-nomask=0" } */

#pragma GCC target "+nosve"

#define TYPE int

void foo (unsigned long long * restrict a, TYPE * restrict d, int n)
{
    for( int i = 0; i < n; i++ )
      d[i] = a[i] >> 3;
}

/* { dg-final { scan-assembler-times {\tshrn\t} 1 } } */
/* { dg-final { scan-assembler-times {\tshrn2\t} 1 } } */
