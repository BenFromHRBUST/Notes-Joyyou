/* { dg-do run } */
/* { dg-require-effective-target noinit } */
/* { dg-skip-if "data LMA != VMA" { msp430-*-* } { "-mlarge" } } */
/* { dg-options "-save-temps" } */
/* { dg-final { scan-assembler ".section\t.noinit,\"aw\"\n" } } */

#include "attr-noinit-main.inc"
