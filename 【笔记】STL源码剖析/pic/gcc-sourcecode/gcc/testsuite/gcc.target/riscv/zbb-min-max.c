/* { dg-do compile } */
/* { dg-options "-march=rv64gc_zbb -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-g" } } */

long
foo1 (long i, long j)
{
  return i < j ? i : j;
}

long
foo2 (long i, long j)
{
  return i > j ? i : j;
}

unsigned long
foo3 (unsigned long i, unsigned long j)
{
  return i < j ? i : j;
}

unsigned long
foo4 (unsigned long i, unsigned long j)
{
  return i > j ? i : j;
}

/* { dg-final { scan-assembler-times "min" 3 } } */
/* { dg-final { scan-assembler-times "max" 3 } } */
/* { dg-final { scan-assembler-times "minu" 1 } } */
/* { dg-final { scan-assembler-times "maxu" 1 } } */
