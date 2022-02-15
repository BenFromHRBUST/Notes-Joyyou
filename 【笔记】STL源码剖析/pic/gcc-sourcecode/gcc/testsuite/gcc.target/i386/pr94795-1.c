/* PR target/94795 */
/* { dg-do compile } */
/* { dg-options "-O2" } */

char fooc (char x)
{
  return x ? -1 : 0;
}

short foos (short x)
{
  return x ? -1 : 0;
}

long fooi (long x)
{
  return x ? -1 : 0;
}

/* { dg-final { scan-assembler-not "test|cmp" } } */
/* { dg-final { scan-assembler-times "sbb" 3 } } */
