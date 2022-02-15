/* { dg-do assemble { target aarch64_asm_sve_ok } } */
/* { dg-options "-O2 -ftree-vectorize -fdump-tree-vect-details --save-temps" } */

#define TYPE uint64_t

#include "clastb_2.c"

/* { dg-final { scan-tree-dump "operating on partial vectors." "vect" } } */
/* { dg-final { scan-assembler {\tclastb\td[0-9]+, p[0-7], d[0-9]+, z[0-9]+\.d} } } */
