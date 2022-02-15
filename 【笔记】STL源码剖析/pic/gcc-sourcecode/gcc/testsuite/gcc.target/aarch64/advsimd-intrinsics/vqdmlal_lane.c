#include <arm_neon.h>
#include "arm-neon-ref.h"
#include "compute-ref-data.h"

#define INSN_NAME vqdmlal_lane
#define TEST_MSG "VQDMLAL_LANE"

/* Expected results.  */
VECT_VAR_DECL(expected,int,32,4) [] = { 0x7c1e, 0x7c1f, 0x7c20, 0x7c21 };
VECT_VAR_DECL(expected,int,64,2) [] = { 0x7c1e, 0x7c1f };

/* Expected values when multiplying with 0.  */
VECT_VAR_DECL(expected2,int,32,4) [] = { 0xfffffff0, 0xfffffff1,
					 0xfffffff2, 0xfffffff3 };
VECT_VAR_DECL(expected2,int,64,2) [] = { 0xfffffffffffffff0,
					 0xfffffffffffffff1 };

/* Expected values when multiplication saturates.  */
VECT_VAR_DECL(expected3,int,32,4) [] = { 0x7fffffef, 0x7ffffff0,
					 0x7ffffff1, 0x7ffffff2 };
VECT_VAR_DECL(expected3,int,64,2) [] = { 0x7fffffffffffffef,
					 0x7ffffffffffffff0 };

#include "vqdmlXl_lane.inc"
