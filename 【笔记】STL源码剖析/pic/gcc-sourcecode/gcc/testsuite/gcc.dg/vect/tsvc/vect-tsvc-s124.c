/*  This file is distributed under the University of Illinois Open Source
    License. See license.txt for details.  */

/* { dg-additional-options "--param vect-epilogues-nomask=0" } */
/* { dg-require-effective-target vect_float } */

#include "tsvc.h"

real_t s124(struct args_t * func_args)
{
//    induction variable recognition
//    induction variable under both sides of if (same value)

    initialise_arrays(__func__);

    int j;
    for (int nl = 0; nl < iterations; nl++) {
        j = -1;
        for (int i = 0; i < LEN_1D; i++) {
            if (b[i] > (real_t)0.) {
                j++;
                a[j] = b[i] + d[i] * e[i];
            } else {
                j++;
                a[j] = c[i] + d[i] * e[i];
            }
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
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

  run(&s124, "s124", NULL);

  return 0;
}

/* { dg-final { scan-tree-dump "vectorized 1 loops" "vect" { xfail { ! aarch64_sve }  } } } */
