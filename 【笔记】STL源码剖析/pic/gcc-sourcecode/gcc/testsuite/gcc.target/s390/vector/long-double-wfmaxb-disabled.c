/* { dg-do compile } */
/* { dg-options "-O3 -march=z14 -mzarch" } */
#include "long-double-wf.h"

LONG_DOUBLE_WF (MUL_ADD);

/* { dg-final { scan-assembler {\n\twfmxb\t} } } */
/* { dg-final { scan-assembler {\n\twfaxb\t} } } */
