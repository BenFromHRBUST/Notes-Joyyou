/* Verify that overloaded built-ins for vec_orc and vec_nand with int
 * inputs produce the right results.  These intrinsics (vec_orc, 
 * vec_nand) were added as part of ISA 2.07 (P8).  */

/* { dg-do compile } */
/* { dg-require-effective-target powerpc_p8vector_ok } */
/* { dg-options "-mpower8-vector -O1" } */

#include <altivec.h>

vector signed int
test1_orc (vector bool int x, vector signed int y)
{
  vector signed int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector signed int
test1_nand (vector bool int x, vector signed int y)
{
  vector signed int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

vector signed int
test2_orc (vector signed int x, vector bool int y)
{
  vector signed int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector signed int
test2_nand (vector signed int x, vector bool int y)
{
  vector signed int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

vector signed int
test3_orc (vector signed int x, vector signed int y)
{
  vector signed int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector signed int
test3_nand (vector signed int x, vector signed int y)
{
  vector signed int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

vector unsigned int
test4_orc (vector bool int x, vector unsigned int y)
{
  vector unsigned int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector unsigned int
test4_nand (vector bool int x, vector unsigned int y)
{
  vector unsigned int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

vector unsigned int
test5_orc (vector unsigned int x, vector bool int y)
{
  vector unsigned int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector unsigned int
test5_nand (vector unsigned int x, vector bool int y)
{
  vector unsigned int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

vector unsigned int
test6_orc (vector unsigned int x, vector unsigned int y)
{
  vector unsigned int *foo;
  *foo += vec_orc (x, y);
  return *foo;
}

vector unsigned int
test6_nand (vector unsigned int x, vector unsigned int y)
{
  vector unsigned int *foo;
  *foo += vec_nand (x, y);
  return *foo;
}

/* { dg-final { scan-assembler-times {\mxxlnand\M} 3 } } */
/* { dg-final { scan-assembler-times {\mxxlorc\M} 6 } } */
