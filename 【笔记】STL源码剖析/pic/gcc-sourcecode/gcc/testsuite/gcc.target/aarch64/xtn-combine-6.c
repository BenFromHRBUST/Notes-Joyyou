/* { dg-do assemble } */
/* { dg-options "-O3 --save-temps --param=vect-epilogues-nomask=0" } */

#define SIGN unsigned
#define TYPE1 int
#define TYPE2 long long

void d2 (SIGN TYPE1 * restrict a, SIGN TYPE2 *b, int n)
{
    for (int i = 0; i < n; i++)
      a[i] = b[i];
}

/* { dg-final { scan-assembler-times {\tuzp1\t} 1 } } */
/* { dg-final { scan-assembler-not {\txtn\t} } } */
/* { dg-final { scan-assembler-not {\txtn2\t} } } */
