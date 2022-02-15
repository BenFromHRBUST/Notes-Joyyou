/* Test vclz works correctly.  */
/* { dg-do run } */
/* { dg-options "-std=gnu99 -O3 -Wno-div-by-zero --save-temps" } */
#include <arm_neon.h>

extern void abort (void);

/* Tests in binary should look like:
   0
   1
   10
   101
   1010
   10101
   etc.  */

#define TEST0 0
#define TEST1 0x1
#define TEST2 0x2
#define TEST3 0x5
#define TEST4 0xa
#define TEST5 0x15
#define TEST6 0x2a
#define TEST7 0x55
#define TEST8 0xaa
#define TEST9 0x155
#define TEST10 0x2aa
#define TEST11 0x555
#define TEST12 0xaaa
#define TEST13 0x1555
#define TEST14 0x2aaa
#define TEST15 0x5555
#define TEST16 0xaaaa
#define TEST17 0x15555
#define TEST18 0x2aaaa
#define TEST19 0x55555
#define TEST20 0xaaaaa
#define TEST21 0x155555
#define TEST22 0x2aaaaa
#define TEST23 0x555555
#define TEST24 0xaaaaaa
#define TEST25 0x1555555
#define TEST26 0x2aaaaaa
#define TEST27 0x5555555
#define TEST28 0xaaaaaaa
#define TEST29 0x15555555
#define TEST30 0x2aaaaaaa
#define TEST31 0x55555555
#define TEST32 0xaaaaaaaa

#define INHIB_OPTIMIZATION asm volatile ("" : : : "memory")

#define CONCAT(a, b) a##b
#define CONCAT1(a, b) CONCAT (a, b)
#define REG_INFEX64 _
#define REG_INFEX128 q_
#define SIGNED0 u
#define SIGNED1 s
#define SIGNED(x) SIGNED##x
#define REG_INFEX(reg_len) REG_INFEX##reg_len
#define POSTFIX(reg_len, data_len, is_signed) \
  CONCAT1 (REG_INFEX (reg_len), CONCAT1 (SIGNED (is_signed), data_len))
#define DATA_TYPE(data_len) DATA_TYPE_##data_len
#define LOAD_INST(reg_len, data_len, is_signed) \
  CONCAT1 (vld1, POSTFIX (reg_len, data_len, is_signed))
#define CLZ_INST(reg_len, data_len, is_signed) \
  CONCAT1 (vclz, POSTFIX (reg_len, data_len, is_signed))

#define BUILD_TEST(type, size, lanes)			    \
int __attribute__((noipa,noinline))			    \
run_test##type##size##x##lanes (int##size##_t* test_set,    \
				int##size##_t* answ_set,    \
				int reg_len, int data_len,  \
				int n)			    \
{							    \
  int i;						    \
  INHIB_OPTIMIZATION;					    \
  int##size##x##lanes##_t a = vld1##type##size (test_set);  \
  int##size##x##lanes##_t b = vld1##type##size (answ_set);  \
  a = vclz##type##size (a);				    \
  for (i = 0; i < n; i++){				    \
    if (a [i] != b [i])					    \
      return 1;						    \
  }							    \
  return 0;						    \
}

/* unsigned inputs  */
#define U_BUILD_TEST(type, size, lanes)			    \
int __attribute__((noipa,noinline))			    \
run_test##type##size##x##lanes (uint##size##_t* test_set,   \
				uint##size##_t* answ_set,   \
				int reg_len, int data_len,  \
				int n)	                    \
{							    \
  int i;						    \
  INHIB_OPTIMIZATION;					    \
  uint##size##x##lanes##_t a = vld1##type##size (test_set); \
  uint##size##x##lanes##_t b = vld1##type##size (answ_set); \
  a = vclz##type##size (a);				    \
  for (i = 0; i < n; i++){				    \
    if (a [i] != b [i])					    \
      return 1;						    \
  }							    \
  return 0;						    \
}

BUILD_TEST (_s, 8, 8)
BUILD_TEST (_s, 16, 4)
BUILD_TEST (_s, 32, 2)
BUILD_TEST (q_s, 8, 16)
BUILD_TEST (q_s, 16, 8)
BUILD_TEST (q_s, 32, 4)

U_BUILD_TEST (_u, 8, 8)
U_BUILD_TEST (_u, 16, 4)
U_BUILD_TEST (_u, 32, 2)
U_BUILD_TEST (q_u, 8, 16)
U_BUILD_TEST (q_u, 16, 8)
U_BUILD_TEST (q_u, 32, 4)

int __attribute__ ((noinline))
test_vclz_s8 ()
{
  int8_t test_set0[8] = {
    TEST0, TEST1, TEST2, TEST3,
    TEST4, TEST5, TEST6, TEST7
  };
  int8_t test_set1[8] = {
    TEST8, TEST8, TEST8, TEST8,
    TEST8, TEST8, TEST8, TEST8
  };
  int8_t answ_set0[8] = {
    8, 7, 6, 5,
    4, 3, 2, 1
  };
  int8_t answ_set1[8] = {
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  int o1 = run_test_s8x8 (test_set0, answ_set0, 64, 8, 8);
  int o2 = run_test_s8x8 (test_set1, answ_set1, 64, 8, 1);

  return o1||o2;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.8b, v\[0-9\]+\.8b" 2 } } */

int __attribute__ ((noinline))
test_vclz_s16 ()
{
  int16_t test_set0[4] = { TEST0, TEST1, TEST2, TEST3 };
  int16_t test_set1[4] = { TEST4, TEST5, TEST6, TEST7 };
  int16_t test_set2[4] = { TEST8, TEST9, TEST10, TEST11 };
  int16_t test_set3[4] = { TEST12, TEST13, TEST14, TEST15 };
  int16_t test_set4[4] = { TEST16, TEST16, TEST16, TEST16 };

  int16_t answ_set0[4] = { 16, 15, 14, 13 };
  int16_t answ_set1[4] = { 12, 11, 10, 9 };
  int16_t answ_set2[4] = { 8, 7, 6, 5 };
  int16_t answ_set3[4] = { 4, 3, 2, 1 };
  int16_t answ_set4[4] = { 0, 0, 0, 0 };

  int o1 = run_test_s16x4 (test_set0, answ_set0, 64, 16, 4);
  int o2 = run_test_s16x4 (test_set1, answ_set1, 64, 16, 4);
  int o3 = run_test_s16x4 (test_set2, answ_set2, 64, 16, 4);
  int o4 = run_test_s16x4 (test_set3, answ_set3, 64, 16, 4);
  int o5 = run_test_s16x4 (test_set4, answ_set4, 64, 16, 1);

  return o1||o2||o3||o4||o5;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.4h, v\[0-9\]+\.4h" 2} } */

int __attribute__ ((noinline))
test_vclz_s32 ()
{
  int32_t test_set0[2] = { TEST0, TEST1 };
  int32_t test_set1[2] = { TEST2, TEST3 };
  int32_t test_set2[2] = { TEST4, TEST5 };
  int32_t test_set3[2] = { TEST6, TEST7 };
  int32_t test_set4[2] = { TEST8, TEST9 };
  int32_t test_set5[2] = { TEST10, TEST11 };
  int32_t test_set6[2] = { TEST12, TEST13 };
  int32_t test_set7[2] = { TEST14, TEST15 };
  int32_t test_set8[2] = { TEST16, TEST17 };
  int32_t test_set9[2] = { TEST18, TEST19 };
  int32_t test_set10[2] = { TEST20, TEST21 };
  int32_t test_set11[2] = { TEST22, TEST23 };
  int32_t test_set12[2] = { TEST24, TEST25 };
  int32_t test_set13[2] = { TEST26, TEST27 };
  int32_t test_set14[2] = { TEST28, TEST29 };
  int32_t test_set15[2] = { TEST30, TEST31 };
  int32_t test_set16[2] = { TEST32, TEST32 };

  int32_t answ_set0[2] = { 32, 31 };
  int32_t answ_set1[2] = { 30, 29 };
  int32_t answ_set2[2] = { 28, 27 };
  int32_t answ_set3[2] = { 26, 25 };
  int32_t answ_set4[2] = { 24, 23 };
  int32_t answ_set5[2] = { 22, 21 };
  int32_t answ_set6[2] = { 20, 19 };
  int32_t answ_set7[2] = { 18, 17 };
  int32_t answ_set8[2] = { 16, 15 };
  int32_t answ_set9[2] = { 14, 13 };
  int32_t answ_set10[2] = { 12, 11 };
  int32_t answ_set11[2] = { 10, 9 };
  int32_t answ_set12[2] = { 8, 7 };
  int32_t answ_set13[2] = { 6, 5 };
  int32_t answ_set14[2] = { 4, 3 };
  int32_t answ_set15[2] = { 2, 1 };
  int32_t answ_set16[2] = { 0, 0 };

  int o1 = run_test_s32x2 (test_set0, answ_set0, 64, 32, 2);
  int o2 = run_test_s32x2 (test_set1, answ_set1, 64, 32, 2);
  int o3 = run_test_s32x2 (test_set2, answ_set2, 64, 32, 2);
  int o4 = run_test_s32x2 (test_set3, answ_set3, 64, 32, 2);
  int o5 = run_test_s32x2 (test_set4, answ_set4, 64, 32, 2);
  int o6 = run_test_s32x2 (test_set5, answ_set5, 64, 32, 2);
  int o7 = run_test_s32x2 (test_set6, answ_set6, 64, 32, 2);
  int o8 = run_test_s32x2 (test_set7, answ_set7, 64, 32, 2);
  int o9 = run_test_s32x2 (test_set8, answ_set8, 64, 32, 2);
  int o10 = run_test_s32x2 (test_set9, answ_set9, 64, 32, 2);
  int o11 = run_test_s32x2 (test_set10, answ_set10, 64, 32, 2);
  int o12 = run_test_s32x2 (test_set11, answ_set11, 64, 32, 2);
  int o13 = run_test_s32x2 (test_set12, answ_set12, 64, 32, 2);
  int o14 = run_test_s32x2 (test_set13, answ_set13, 64, 32, 2);
  int o15 = run_test_s32x2 (test_set14, answ_set14, 64, 32, 2);
  int o16 = run_test_s32x2 (test_set15, answ_set15, 64, 32, 2);
  int o17 = run_test_s32x2 (test_set16, answ_set16, 64, 32, 1);

  return o1||o2||o3||o4||o5||o6||o7||o8||o9||o10||o11||o12||o13||o14
    ||o15||o16||o17;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.2s, v\[0-9\]+\.2s"  2 } } */

int __attribute__ ((noinline))
test_vclzq_s8 ()
{
  int8_t test_set0[16] = {
    TEST0, TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7,
    TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8
  };
  int8_t answ_set0[16] = {
    8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int o1 = run_testq_s8x16 (test_set0, answ_set0, 128, 8, 9);
  return o1;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.16b, v\[0-9\]+\.16b" 2 } } */

int __attribute__ ((noinline))
test_vclzq_s16 ()
{
  int16_t test_set0[8] = {
    TEST0, TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7
  };
  int16_t test_set1[8] = {
    TEST8, TEST9, TEST10, TEST11, TEST12, TEST13, TEST14, TEST15
  };
  int16_t test_set2[8] = {
    TEST16, TEST16, TEST16, TEST16, TEST16, TEST16, TEST16, TEST16
  };

  int16_t answ_set0[8] = {
    16, 15, 14, 13, 12, 11, 10, 9
  };
  int16_t answ_set1[8] = {
    8, 7, 6, 5, 4, 3, 2, 1
  };
  int16_t answ_set2[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
  };
  int o1 = run_testq_s16x8 (test_set0, answ_set0, 128, 16, 8);
  int o2 = run_testq_s16x8 (test_set1, answ_set1, 128, 16, 8);
  int o3 = run_testq_s16x8 (test_set2, answ_set2, 128, 16, 1);

  return o1||o2||o3;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.8h, v\[0-9\]+\.8h" 2 } } */

int __attribute__ ((noinline))
test_vclzq_s32 ()
{
  int32_t test_set0[4] = { TEST0, TEST1, TEST2, TEST3 };
  int32_t test_set1[4] = { TEST4, TEST5, TEST6, TEST7 };
  int32_t test_set2[4] = { TEST8, TEST9, TEST10, TEST11 };
  int32_t test_set3[4] = { TEST12, TEST13, TEST14, TEST15 };
  int32_t test_set4[4] = { TEST16, TEST17, TEST18, TEST19 };
  int32_t test_set5[4] = { TEST20, TEST21, TEST22, TEST23 };
  int32_t test_set6[4] = { TEST24, TEST25, TEST26, TEST27 };
  int32_t test_set7[4] = { TEST28, TEST29, TEST30, TEST31 };
  int32_t test_set8[4] = { TEST32, TEST32, TEST32, TEST32 };

  int32_t answ_set0[4] = { 32, 31, 30, 29 };
  int32_t answ_set1[4] = { 28, 27, 26, 25 };
  int32_t answ_set2[4] = { 24, 23, 22, 21 };
  int32_t answ_set3[4] = { 20, 19, 18, 17 };
  int32_t answ_set4[4] = { 16, 15, 14, 13 };
  int32_t answ_set5[4] = { 12, 11, 10, 9 };
  int32_t answ_set6[4] = { 8, 7, 6, 5 };
  int32_t answ_set7[4] = { 4, 3, 2, 1 };
  int32_t answ_set8[4] = { 0, 0, 0, 0 };

  int o1 = run_testq_s32x4 (test_set0, answ_set0, 128, 32, 4);
  int o2 = run_testq_s32x4 (test_set1, answ_set1, 128, 32, 4);
  int o3 = run_testq_s32x4 (test_set2, answ_set2, 128, 32, 4);
  int o4 = run_testq_s32x4 (test_set3, answ_set3, 128, 32, 4);
  int o5 = run_testq_s32x4 (test_set4, answ_set4, 128, 32, 1);

  return o1||o2||o3||o4||o5;
}

/* Double scan-assembler-times to take account of unsigned functions.  */
/* { dg-final { scan-assembler-times "clz\\tv\[0-9\]+\.4s, v\[0-9\]+\.4s" 2 } } */

/* Unsigned versions.  */

int __attribute__ ((noinline))
test_vclz_u8 ()
{
  uint8_t test_set0[8] = {
    TEST0, TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7
  };
  uint8_t test_set1[8] = {
    TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8
  };
  uint8_t answ_set0[8] = {
    8, 7, 6, 5, 4, 3, 2, 1
  };
  uint8_t answ_set1[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
  };

  int o1 = run_test_u8x8 (test_set0, answ_set0, 64, 8, 8);
  int o2 = run_test_u8x8 (test_set1, answ_set1, 64, 8, 1);

  return o1||o2;
}

/* ASM scan near test for signed version.  */

int __attribute__ ((noinline))
test_vclz_u16 ()
{
  uint16_t test_set0[4] = { TEST0, TEST1, TEST2, TEST3 };
  uint16_t test_set1[4] = { TEST4, TEST5, TEST6, TEST7 };
  uint16_t test_set2[4] = { TEST8, TEST9, TEST10, TEST11 };
  uint16_t test_set3[4] = { TEST12, TEST13, TEST14, TEST15 };
  uint16_t test_set4[4] = { TEST16, TEST16, TEST16, TEST16 };

  uint16_t answ_set0[4] = { 16, 15, 14, 13 };
  uint16_t answ_set1[4] = { 12, 11, 10, 9 };
  uint16_t answ_set2[4] = { 8, 7, 6, 5 };
  uint16_t answ_set3[4] = { 4, 3, 2, 1 };
  uint16_t answ_set4[4] = { 0, 0, 0, 0 };

  int o1 = run_test_u16x4 (test_set0, answ_set0, 64, 16, 4);
  int o2 = run_test_u16x4 (test_set1, answ_set1, 64, 16, 4);
  int o3 = run_test_u16x4 (test_set2, answ_set2, 64, 16, 4);
  int o4 = run_test_u16x4 (test_set3, answ_set3, 64, 16, 4);
  int o5 = run_test_u16x4 (test_set4, answ_set4, 64, 16, 1);

  return o1||o2||o3||o4||o5;
}

/* ASM scan near test for signed version.  */

int __attribute__ ((noinline))
test_vclz_u32 ()
{
  uint32_t test_set0[2] = { TEST0, TEST1 };
  uint32_t test_set1[2] = { TEST2, TEST3 };
  uint32_t test_set2[2] = { TEST4, TEST5 };
  uint32_t test_set3[2] = { TEST6, TEST7 };
  uint32_t test_set4[2] = { TEST8, TEST9 };
  uint32_t test_set5[2] = { TEST10, TEST11 };
  uint32_t test_set6[2] = { TEST12, TEST13 };
  uint32_t test_set7[2] = { TEST14, TEST15 };
  uint32_t test_set8[2] = { TEST16, TEST17 };
  uint32_t test_set9[2] = { TEST18, TEST19 };
  uint32_t test_set10[2] = { TEST20, TEST21 };
  uint32_t test_set11[2] = { TEST22, TEST23 };
  uint32_t test_set12[2] = { TEST24, TEST25 };
  uint32_t test_set13[2] = { TEST26, TEST27 };
  uint32_t test_set14[2] = { TEST28, TEST29 };
  uint32_t test_set15[2] = { TEST30, TEST31 };
  uint32_t test_set16[2] = { TEST32, TEST32 };

  uint32_t answ_set0[2] = { 32, 31 };
  uint32_t answ_set1[2] = { 30, 29 };
  uint32_t answ_set2[2] = { 28, 27 };
  uint32_t answ_set3[2] = { 26, 25 };
  uint32_t answ_set4[2] = { 24, 23 };
  uint32_t answ_set5[2] = { 22, 21 };
  uint32_t answ_set6[2] = { 20, 19 };
  uint32_t answ_set7[2] = { 18, 17 };
  uint32_t answ_set8[2] = { 16, 15 };
  uint32_t answ_set9[2] = { 14, 13 };
  uint32_t answ_set10[2] = { 12, 11 };
  uint32_t answ_set11[2] = { 10, 9 };
  uint32_t answ_set12[2] = { 8, 7 };
  uint32_t answ_set13[2] = { 6, 5 };
  uint32_t answ_set14[2] = { 4, 3 };
  uint32_t answ_set15[2] = { 2, 1 };
  uint32_t answ_set16[2] = { 0, 0 };

  int o1 = run_test_u32x2 (test_set0, answ_set0, 64, 32, 2);
  int o2 = run_test_u32x2 (test_set1, answ_set1, 64, 32, 2);
  int o3 = run_test_u32x2 (test_set2, answ_set2, 64, 32, 2);
  int o4 = run_test_u32x2 (test_set3, answ_set3, 64, 32, 2);
  int o5 = run_test_u32x2 (test_set4, answ_set4, 64, 32, 2);
  int o6 = run_test_u32x2 (test_set5, answ_set5, 64, 32, 2);
  int o7 = run_test_u32x2 (test_set6, answ_set6, 64, 32, 2);
  int o8 = run_test_u32x2 (test_set7, answ_set7, 64, 32, 2);
  int o9 = run_test_u32x2 (test_set8, answ_set8, 64, 32, 2);
  int o10 = run_test_u32x2 (test_set9, answ_set9, 64, 32, 2);
  int o11 = run_test_u32x2 (test_set10, answ_set10, 64, 32, 2);
  int o12 = run_test_u32x2 (test_set11, answ_set11, 64, 32, 2);
  int o13 = run_test_u32x2 (test_set12, answ_set12, 64, 32, 2);
  int o14 = run_test_u32x2 (test_set13, answ_set13, 64, 32, 2);
  int o15 = run_test_u32x2 (test_set14, answ_set14, 64, 32, 2);
  int o16 = run_test_u32x2 (test_set15, answ_set15, 64, 32, 2);
  int o17 = run_test_u32x2 (test_set16, answ_set16, 64, 32, 1);

  return o1||o2||o3||o4||o5||o6||o7||o8||o9||o10||o11||o12||o13||o14
        ||o15||o16||o17;
}

/* ASM scan near test for signed version.  */

int __attribute__ ((noinline))
test_vclzq_u8 ()
{
  int i;
  uint8x16_t a;
  uint8x16_t b;

  uint8_t test_set0[16] = {
    TEST0, TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7,
    TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8, TEST8
  };
  uint8_t answ_set0[16] = {
    8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int o1 = run_testq_u8x16 (test_set0, answ_set0, 128, 8, 9);

  return o1;
}

/* ASM scan near test for signed version.  */

int __attribute__ ((noinline))
test_vclzq_u16 ()
{
  int i;
  uint16x8_t a;
  uint16x8_t b;

  uint16_t test_set0[8] = {
    TEST0, TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7
  };
  uint16_t test_set1[8] = {
    TEST8, TEST9, TEST10, TEST11, TEST12, TEST13, TEST14, TEST15
  };
  uint16_t test_set2[8] = {
    TEST16, TEST16, TEST16, TEST16, TEST16, TEST16, TEST16, TEST16
  };

  uint16_t answ_set0[8] = {
    16, 15, 14, 13, 12, 11, 10, 9
  };

  uint16_t answ_set1[8] = {
    8, 7, 6, 5, 4, 3, 2, 1
  };
  uint16_t answ_set2[8] = {
    0, 0, 0, 0, 0, 0, 0, 0
  };

  int o1 = run_testq_u16x8 (test_set0, answ_set0, 128, 16, 8);
  int o2 = run_testq_u16x8 (test_set1, answ_set1, 128, 16, 8);
  int o3 = run_testq_u16x8 (test_set2, answ_set2, 128, 16, 1);

  return o1||o2||o3;
}

/* ASM scan near test for signed version.  */

int __attribute__ ((noinline))
test_vclzq_u32 ()
{
  uint32_t test_set0[4] = { TEST0, TEST1, TEST2, TEST3 };
  uint32_t test_set1[4] = { TEST4, TEST5, TEST6, TEST7 };
  uint32_t test_set2[4] = { TEST8, TEST9, TEST10, TEST11 };
  uint32_t test_set3[4] = { TEST12, TEST13, TEST14, TEST15 };
  uint32_t test_set4[4] = { TEST16, TEST17, TEST18, TEST19 };
  uint32_t test_set5[4] = { TEST20, TEST21, TEST22, TEST23 };
  uint32_t test_set6[4] = { TEST24, TEST25, TEST26, TEST27 };
  uint32_t test_set7[4] = { TEST28, TEST29, TEST30, TEST31 };
  uint32_t test_set8[4] = { TEST32, TEST32, TEST32, TEST32 };

  uint32_t answ_set0[4] = { 32, 31, 30, 29 };
  uint32_t answ_set1[4] = { 28, 27, 26, 25 };
  uint32_t answ_set2[4] = { 24, 23, 22, 21 };
  uint32_t answ_set3[4] = { 20, 19, 18, 17 };
  uint32_t answ_set4[4] = { 16, 15, 14, 13 };
  uint32_t answ_set5[4] = { 12, 11, 10, 9 };
  uint32_t answ_set6[4] = { 8, 7, 6, 5 };
  uint32_t answ_set7[4] = { 4, 3, 2, 1 };
  uint32_t answ_set8[4] = { 0, 0, 0, 0 };

  int o1 = run_testq_u32x4 (test_set0, answ_set0, 128, 32, 4);
  int o2 = run_testq_u32x4 (test_set1, answ_set1, 128, 32, 4);
  int o3 = run_testq_u32x4 (test_set2, answ_set2, 128, 32, 4);
  int o4 = run_testq_u32x4 (test_set3, answ_set3, 128, 32, 4);
  int o5 = run_testq_u32x4 (test_set4, answ_set4, 128, 32, 1);

  return o1||o2||o3||o4||o5;
}

/* ASM scan near test for signed version.  */

int
main (int argc, char **argv)
{

  if (test_vclz_s8 ())
    abort ();

  if (test_vclz_s16 ())
    abort ();

  if (test_vclz_s32 ())
    abort ();

  if (test_vclzq_s8 ())
    abort ();

  if (test_vclzq_s16 ())
    abort ();

  if (test_vclzq_s32 ())
    abort ();

  if (test_vclz_u8 ())
    abort ();

  if (test_vclz_u16 ())
    abort ();

  if (test_vclz_u32 ())
    abort ();

  if (test_vclzq_u8 ())
    abort ();

  if (test_vclzq_u16 ())
    abort ();

  if (test_vclzq_u32 ())
    abort ();

  return 0;
}

