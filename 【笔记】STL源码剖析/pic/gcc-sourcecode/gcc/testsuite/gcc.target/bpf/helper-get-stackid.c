/* { dg-do compile } */
/* { dg-options "-std=gnu99" } */

#include <stdint.h>
#include <bpf-helpers.h>

void
foo ()
{
  int ret;
  void *ctx, *map;
  uint64_t flags;

  ret = bpf_get_stackid (ctx, map, flags);
}

/* { dg-final { scan-assembler "call\t27" } } */
