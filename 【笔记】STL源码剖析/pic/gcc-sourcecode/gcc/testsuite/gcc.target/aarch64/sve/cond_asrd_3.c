/* { dg-do compile } */
/* { dg-options "-O2 -ftree-vectorize" } */

#include <stdint.h>

#define DEF_LOOP(TYPE1, TYPE2, COUNT)				\
  void __attribute__ ((noipa))					\
  test_##TYPE1##_##TYPE2 (TYPE2 *__restrict r,			\
			  TYPE1 *__restrict a,			\
			  TYPE2 *__restrict b)			\
  {								\
    for (int i = 0; i < COUNT; ++i)				\
      r[i] = a[i] == 0 ? b[i] / 16 : 0;				\
  }

#define TEST_ALL(T) \
  T (int16_t, int8_t, 7) \
  T (int32_t, int8_t, 3) \
  T (int32_t, int16_t, 3) \
  T (int64_t, int8_t, 5) \
  T (int64_t, int16_t, 5) \
  T (int64_t, int32_t, 5)

TEST_ALL (DEF_LOOP)

/* { dg-final { scan-assembler-times {\tasrd\tz[0-9]+\.b, p[0-7]/m, z[0-9]+\.b, #4\n} 3 } } */
/* { dg-final { scan-assembler-times {\tasrd\tz[0-9]+\.h, p[0-7]/m, z[0-9]+\.h, #4\n} 2 } } */
/* { dg-final { scan-assembler-times {\tasrd\tz[0-9]+\.s, p[0-7]/m, z[0-9]+\.s, #4\n} 1 } } */

/* { dg-final { scan-assembler-times {\tmovprfx\tz[0-9]+\.b, p[0-7]/z, z[0-9]+\.b\n} 3 { xfail *-*-* } } } */
/* { dg-final { scan-assembler-times {\tmovprfx\tz[0-9]+\.h, p[0-7]/z, z[0-9]+\.h\n} 2 { xfail *-*-* } } } */
/* { dg-final { scan-assembler-times {\tmovprfx\tz[0-9]+\.s, p[0-7]/z, z[0-9]+\.s\n} 1 { xfail *-*-* } } } */

/* { dg-final { scan-assembler-not {\tmov\tz} { xfail *-*-* } } } */
/* { dg-final { scan-assembler-not {\tsel\t} { xfail *-*-* } } } */
