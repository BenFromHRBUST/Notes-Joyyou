// { dg-do compile }
// { dg-options "-O2 -w" }

__builtin_clz(int x) { x ? __builtin_clz(x) : 32; }
