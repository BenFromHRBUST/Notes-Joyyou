/* { dg-do assemble { target aarch64_asm_sve_ok } } */
/* { dg-options "-O -msve-vector-bits=2048 -mlittle-endian --save-temps" } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned char v128qi __attribute__((vector_size(128)));
typedef unsigned char v64qi __attribute__((vector_size(64)));
typedef unsigned char v32qi __attribute__((vector_size(32)));
typedef unsigned short v64hi __attribute__((vector_size(128)));
typedef unsigned short v32hi __attribute__((vector_size(64)));
typedef _Float16 v64hf __attribute__((vector_size(128)));
typedef _Float16 v32hf __attribute__((vector_size(64)));
typedef __bf16 v64bf __attribute__((vector_size(128)));
typedef __bf16 v32bf __attribute__((vector_size(64)));
typedef unsigned int v32si __attribute__((vector_size(128)));
typedef float v32sf __attribute__((vector_size(128)));

#define PERM0(B) B, B + 2
#define PERM1(B) PERM0 (B), PERM0 (B + 4)
#define PERM2(B) PERM1 (B), PERM1 (B + 8)
#define PERM3(B) PERM2 (B), PERM2 (B + 16)
#define PERM4(B) PERM3 (B), PERM3 (B + 32)
#define PERM5(B) PERM4 (B), PERM4 (B + 64)
#define PERM6(B) PERM5 (B), PERM5 (B + 128)

/*
** qi_uzp1_h:
**	ptrue	(p[0-7])\.b, vl256
**	ld1b	(z[0-9]+)\.h, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.h, \2\.h, \2\.h
**	st1b	\3\.h, \1, \[x8\]
**	ret
*/
v128qi
qi_uzp1_h (v128qi x)
{
  return __builtin_shuffle (x, x, (v128qi) { PERM6 (0) });
}

/*
** qi_uzp1_h_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1b	(z[0-9]+)\.h, \1/z, \[x1\]
**	ld1b	(z[0-9]+)\.h, \1/z, \[x0\]
**	uzp1	\3\.h, \3\.h, \2\.h
**	st1b	\3\.h, \1, \[x8\]
** |
**	ld1b	(z[0-9]+)\.h, \1/z, \[x0\]
**	ld1b	(z[0-9]+)\.h, \1/z, \[x1\]
**	uzp1	\4\.h, \4\.h, \5\.h
**	st1b	\4\.h, \1, \[x8\]
** )
**	ret
*/
v128qi
qi_uzp1_h_two_op (v128qi x, v128qi y)
{
  return __builtin_shuffle (x, y, (v128qi) { PERM6 (0) });
}

/*
** qi_uzp1_s:
**	ptrue	(p[0-7])\.b, vl256
**	ld1b	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.s, \2\.s, \2\.s
**	st1b	\3\.s, \1, \[x8\]
**	ret
*/
v64qi
qi_uzp1_s (v64qi x)
{
  return __builtin_shuffle (x, x, (v64qi) { PERM5 (0) });
}

/*
** qi_uzp1_s_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1b	(z[0-9]+)\.s, \1/z, \[x1\]
**	ld1b	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	\3\.s, \3\.s, \2\.s
**	st1b	\3\.s, \1, \[x8\]
** |
**	ld1b	(z[0-9]+)\.s, \1/z, \[x0\]
**	ld1b	(z[0-9]+)\.s, \1/z, \[x1\]
**	uzp1	\4\.s, \4\.s, \5\.s
**	st1b	\4\.s, \1, \[x8\]
** )
**	ret
*/
v64qi
qi_uzp1_s_two_op (v64qi x, v64qi y)
{
  return __builtin_shuffle (x, y, (v64qi) { PERM5 (0) });
}

/*
** qi_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1b	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1b	\3\.d, \1, \[x8\]
**	ret
*/
v32qi
qi_uzp1_d (v32qi x)
{
  return __builtin_shuffle (x, x, (v32qi) { PERM4 (0) });
}

/*
** qi_uzp1_d_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1b	(z[0-9]+)\.d, \1/z, \[x1\]
**	ld1b	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	\3\.d, \3\.d, \2\.d
**	st1b	\3\.d, \1, \[x8\]
** |
**	ld1b	(z[0-9]+)\.d, \1/z, \[x0\]
**	ld1b	(z[0-9]+)\.d, \1/z, \[x1\]
**	uzp1	\4\.d, \4\.d, \5\.d
**	st1b	\4\.d, \1, \[x8\]
** )
**	ret
*/
v32qi
qi_uzp1_d_two_op (v32qi x, v32qi y)
{
  return __builtin_shuffle (x, y, (v32qi) { PERM4 (0) });
}

/*
** hi_uzp1_s:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.s, \2\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
**	ret
*/
v64hi
hi_uzp1_s (v64hi x)
{
  return __builtin_shuffle (x, x, (v64hi) { PERM5 (0) });
}

/*
** hi_uzp1_s_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	\3\.s, \3\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	uzp1	\4\.s, \4\.s, \5\.s
**	st1h	\4\.s, \1, \[x8\]
** )
**	ret
*/
v64hi
hi_uzp1_s_two_op (v64hi x, v64hi y)
{
  return __builtin_shuffle (x, y, (v64hi) { PERM5 (0) });
}

/*
** hf_uzp1_s:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.s, \2\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
**	ret
*/
v64hf
hf_uzp1_s (v64hf x)
{
  return __builtin_shuffle (x, x, (v64hi) { PERM5 (0) });
}

/*
** hf_uzp1_s_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	\3\.s, \3\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	uzp1	\4\.s, \4\.s, \5\.s
**	st1h	\4\.s, \1, \[x8\]
** )
**	ret
*/
v64hf
hf_uzp1_s_two_op (v64hf x, v64hf y)
{
  return __builtin_shuffle (x, y, (v64hi) { PERM5 (0) });
}

/*
** bf_uzp1_s:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.s, \2\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
**	ret
*/
v64bf
bf_uzp1_s (v64bf x)
{
  return __builtin_shuffle (x, x, (v64hi) { PERM5 (0) });
}

/*
** bf_uzp1_s_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	uzp1	\3\.s, \3\.s, \2\.s
**	st1h	\3\.s, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.s, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.s, \1/z, \[x1\]
**	uzp1	\4\.s, \4\.s, \5\.s
**	st1h	\4\.s, \1, \[x8\]
** )
**	ret
*/
v64bf
bf_uzp1_s_two_op (v64bf x, v64bf y)
{
  return __builtin_shuffle (x, y, (v64hi) { PERM5 (0) });
}

/*
** hi_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
**	ret
*/
v32hi
hi_uzp1_d (v32hi x)
{
  return __builtin_shuffle (x, x, (v32hi) { PERM4 (0) });
}

/*
** hi_uzp1_d_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	\3\.d, \3\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	uzp1	\4\.d, \4\.d, \5\.d
**	st1h	\4\.d, \1, \[x8\]
** )
**	ret
*/
v32hi
hi_uzp1_d_two_op (v32hi x, v32hi y)
{
  return __builtin_shuffle (x, y, (v32hi) { PERM4 (0) });
}

/*
** hf_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
**	ret
*/
v32hf
hf_uzp1_d (v32hf x)
{
  return __builtin_shuffle (x, x, (v32hi) { PERM4 (0) });
}

/*
** hf_uzp1_d_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	\3\.d, \3\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	uzp1	\4\.d, \4\.d, \5\.d
**	st1h	\4\.d, \1, \[x8\]
** )
**	ret
*/
v32hf
hf_uzp1_d_two_op (v32hf x, v32hf y)
{
  return __builtin_shuffle (x, y, (v32hi) { PERM4 (0) });
}

/*
** bf_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
**	ret
*/
v32bf
bf_uzp1_d (v32bf x)
{
  return __builtin_shuffle (x, x, (v32hi) { PERM4 (0) });
}

/*
** bf_uzp1_d_two_op:
**	ptrue	(p[0-7])\.b, vl256
** (
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	\3\.d, \3\.d, \2\.d
**	st1h	\3\.d, \1, \[x8\]
** |
**	ld1h	(z[0-9]+)\.d, \1/z, \[x0\]
**	ld1h	(z[0-9]+)\.d, \1/z, \[x1\]
**	uzp1	\4\.d, \4\.d, \5\.d
**	st1h	\4\.d, \1, \[x8\]
** )
**	ret
*/
v32bf
bf_uzp1_d_two_op (v32bf x, v32bf y)
{
  return __builtin_shuffle (x, y, (v32hi) { PERM4 (0) });
}

/*
** si_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1w	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1w	\3\.d, \1, \[x8\]
**	ret
*/
v32si
si_uzp1_d (v32si x)
{
  return __builtin_shuffle (x, x, (v32si) { PERM4 (0) });
}

/*
** sf_uzp1_d:
**	ptrue	(p[0-7])\.b, vl256
**	ld1w	(z[0-9]+)\.d, \1/z, \[x0\]
**	uzp1	(z[0-9]+)\.d, \2\.d, \2\.d
**	st1w	\3\.d, \1, \[x8\]
**	ret
*/
v32sf
sf_uzp1_d (v32sf x)
{
  return __builtin_shuffle (x, x, (v32si) { PERM4 (0) });
}
