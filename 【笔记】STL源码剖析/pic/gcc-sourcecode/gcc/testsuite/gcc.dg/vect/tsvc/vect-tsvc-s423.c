/*  This file is distributed under the University of Illinois Open Source
    License. See license.txt for details.  */

/* { dg-additional-options "--param vect-epilogues-nomask=0" } */
/* { dg-require-effective-target vect_float } */

#include "tsvc.h"

real_t s423(struct args_t * func_args)
{
//    storage classes and equivalencing
//    common and equivalenced variables - with anti-dependence

    // do this again here
    int vl = 64;
    xx = flat_2d_array + vl;

    initialise_arrays(__func__);

    for (int nl = 0; nl < 4*iterations; nl++) {
        for (int i = 0; i < LEN_1D - 1; i++) {
            flat_2d_array[i+1] = xx[i] + a[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 1.);
    }

    return calc_checksum(__func__);
}

int main (int argc, char **argv)
{
  int n1 = 1;
  int n3 = 1;
  int* ip;
  real_t s1,s2;
  init(&ip, &s1, &s2);

  run(&s423, "s423", NULL);

  return 0;
}

/* { dg-final { scan-tree-dump-times "vectorized 1 loops" 1 "vect" } } */