/* { dg-skip-if "" { arm*-*-* } } */

#include <arm_neon.h>
#include "arm-neon-ref.h"
#include "compute-ref-data.h"

#if defined(__cplusplus)
#include <cstdint>
#else
#include <stdint.h>
#endif

#define INSN_NAME vsubhn_high
#define TEST_MSG "VSUBHN_HIGH"

/* Expected results.  */
VECT_VAR_DECL(expected, int, 8, 16) [] = { 0x5, 0x5, 0x5, 0x5,
				           0x5, 0x5, 0x5, 0x5,
					   0x31, 0x31, 0x31, 0x31,
					   0x31, 0x31, 0x31, 0x31 };
VECT_VAR_DECL(expected, int, 16, 8) [] = { 0x5, 0x5, 0x5, 0x5,
					   0x31, 0x31, 0x31, 0x31 };
VECT_VAR_DECL(expected, int, 32, 4) [] = { 0x5, 0x5, 0x17, 0x17 };
VECT_VAR_DECL(expected, uint, 8, 16) [] = { 0x5, 0x5, 0x5, 0x5,
					    0x5, 0x5, 0x5, 0x5,
					    0x2, 0x2, 0x2, 0x2,
					    0x2, 0x2, 0x2, 0x2 };
VECT_VAR_DECL(expected, uint, 16, 8) [] = { 0x5, 0x5, 0x5, 0x5,
					    0x36, 0x36, 0x36, 0x36 };
VECT_VAR_DECL(expected, uint, 32, 4) [] = { 0x5, 0x5, 0x2, 0x2 };

#include "vXXXhn_high.inc"
