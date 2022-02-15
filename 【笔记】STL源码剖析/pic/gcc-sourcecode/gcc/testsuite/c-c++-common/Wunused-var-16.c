/* PR c++/78949 */
/* { dg-do compile } */
/* { dg-options "-Wunused -fdump-tree-optimized" } */
/* { dg-additional-options "-fno-common" { target hppa*-*-hpux* } } */

typedef unsigned char V __attribute__((vector_size(16)));
V v;

void
foo ()
{
  V y = {};
  V x = {};	// { dg-bogus "set but not used" }
  y &= ~x;
  v = y;
}

/* { dg-final { scan-tree-dump-not " ~0" "optimized" } } */
