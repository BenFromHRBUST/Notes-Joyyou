/* { dg-do compile } */
/* { dg-add-options arm_v8_3a_fp16_complex_neon } */

#define TYPE _Float16
#define N 200
#include "complex-mul-template.c"
/* { dg-final { scan-tree-dump "Found COMPLEX_MUL_CONJ" "vect" } } */
/* { dg-final { scan-tree-dump "Found COMPLEX_MUL" "vect" } } */
