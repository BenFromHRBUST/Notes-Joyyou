/* { dg-do compile } */
/* { dg-options "-O3 -funroll-loops -fdump-tree-lim2-details" } */
/* { dg-additional-options "--param max-completely-peeled-insns=200" { target { s390*-*-* } } } */

#define TYPE int

#include "pr83403.h"

/* { dg-final { scan-tree-dump-times "Executing store motion of" 10 "lim2" } } */
