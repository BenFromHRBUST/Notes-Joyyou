/* { dg-do compile } */
/* { dg-additional-options "--param hwasan-instrument-reads=0 --param hwasan-instrument-writes=0" } */

#include "param-instrument-reads.c"

/* { dg-final { scan-assembler-not "__hwasan_load" } } */
/* { dg-final { scan-assembler-not "__hwasan_store" } } */
