/* { dg-do compile } */
/* { dg-options "-std=gnu99" } */

#include <stdint.h>
#include <bpf-helpers.h>

void
foo ()
{
  uint32_t ret;
  void *skb;

  ret = bpf_get_socket_uid (skb);
}

/* { dg-final { scan-assembler "call\t47" } } */
