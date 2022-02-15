/* { dg-do run { target { power10_hw } } } */
/* { dg-do link { target { ! power10_hw } } } */
/* { dg-require-effective-target power10_ok } */
/* { dg-options "-mdejagnu-cpu=power10" } */

#include <altivec.h>

extern void abort (void);

/* Vector string clear right-most bytes of unsigned char.  */
vector signed char
clrr (vector signed char arg, int n)
{
  return vec_clrr (arg, n);
}

int main (int argc, char *argv [])
{
  vector signed char input0 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };
  vector signed char expected0 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x0, 0x0, 0x0,
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
  vector signed char expected1 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0x0, 0x0 };
  vector signed char expected2 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };

  if (!vec_all_eq (clrr (input0, 5), expected0))
    abort ();
  if (!vec_all_eq (clrr (input0, 13), expected1))
    abort ();
  if (!vec_all_eq (clrr (input0, 19), expected2))
    abort ();
}
