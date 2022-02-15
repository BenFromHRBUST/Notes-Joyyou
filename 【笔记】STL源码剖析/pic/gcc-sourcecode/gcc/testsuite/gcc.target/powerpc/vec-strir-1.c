/* { dg-do run { target { power10_hw } } } */
/* { dg-do link { target { ! power10_hw } } } */
/* { dg-require-effective-target power10_ok } */
/* { dg-options "-mdejagnu-cpu=power10" } */

#include <altivec.h>

extern void abort (void);

/* Vector string isolate right-justified on array of unsigned char.  */
vector unsigned char
sirj (vector unsigned char arg)
{
  return vec_strir (arg);
}

int main (int argc, char *argv [])
{
  vector unsigned char input1 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };
  vector unsigned char expected1 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };
  vector unsigned char input2 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };
  vector unsigned char expected2 =
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x11 };
  vector unsigned char input3 =
    { 0x1, 0x2, 0x0, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };
  vector unsigned char expected3 =
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x11 };
  vector unsigned char input4 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };
  vector unsigned char expected4 =
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x11 };

  if (!vec_all_eq (sirj (input1), expected1))
    abort ();
  if (!vec_all_eq (sirj (input2), expected2))
    abort ();
  if (!vec_all_eq (sirj (input3), expected3))
    abort ();
  if (!vec_all_eq (sirj (input4), expected4))
    abort ();

}
