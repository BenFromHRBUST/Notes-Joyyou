/* { dg-do run } */
/* { dg-options "-O2 -mavx512vl -mprefer-vector-width=256 -DTYPE=uint32" } */
/* { dg-require-effective-target avx512vl } */

#include "cond_op_maxmin_d-2.c"
