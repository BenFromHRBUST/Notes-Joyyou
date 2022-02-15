/* { dg-skip-if "" { arm*-*-* } } */

#include <arm_neon.h>
#include "arm-neon-ref.h"
#include "compute-ref-data.h"

#if defined(__cplusplus)
#include <cstdint>
#else
#include <stdint.h>
#endif

#define INSN_NAME vraddhn_high
#define TEST_MSG "VRADDHN_HIGH"

/* Expected results.  */
VECT_VAR_DECL(expected, int, 8, 16) [] = { 0x5, 0x5, 0x5, 0x5,
				           0x5, 0x5, 0x5, 0x5,
					   0x33, 0x33, 0x33, 0x33,
					   0x33, 0x33, 0x33, 0x33 };
VECT_VAR_DECL(expected, int, 16, 8) [] = { 0x5, 0x5, 0x5, 0x5,
					   0x33, 0x33, 0x33, 0x33 };
VECT_VAR_DECL(expected, int, 32, 4) [] = { 0x5, 0x5, 0x19, 0x19 };
VECT_VAR_DECL(expected, uint, 8, 16) [] = { 0x5, 0x5, 0x5, 0x5,
					    0x5, 0x5, 0x5, 0x5,
					    0x4, 0x4, 0x4, 0x4,
					    0x4, 0x4, 0x4, 0x4 };
VECT_VAR_DECL(expected, uint, 16, 8) [] = { 0x5, 0x5, 0x5, 0x5,
					    0x38, 0x38, 0x38, 0x38 };
VECT_VAR_DECL(expected, uint, 32, 4) [] = { 0x5, 0x5, 0x4, 0x4 };

#include "vXXXhn_high.inc"
