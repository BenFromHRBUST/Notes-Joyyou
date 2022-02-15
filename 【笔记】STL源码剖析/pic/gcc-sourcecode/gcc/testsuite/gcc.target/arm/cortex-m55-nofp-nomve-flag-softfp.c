/* { dg-do assemble } */
/* { dg-require-effective-target arm_v8_1m_mve_fp_ok } */
/* { dg-additional-options "-mcpu=cortex-m55+nomve+nofp -mthumb -mfloat-abi=softfp -mfpu=auto --save-temps" } */
/* { dg-final { scan-assembler "\.fpu softvfp" } } */
/* { dg-final { scan-assembler-not "\.arch_extension mve" } } */
/* { dg-final { scan-assembler-not "\.arch_extension mve.fp" } } */
/* { dg-final { scan-assembler-not "\.arch_extension fp" } } */
/* { dg-final { scan-assembler-not "\.arch_extension fp.dp" } } */
/* { dg-final { scan-assembler "\.arch_extension dsp" } } */

int
f ()
{
  return 1;
}
