/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** clz_u8_m_tied12:
**	clz	z0\.b, p0/m, z0\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_m_tied12, svuint8_t,
		z0 = svclz_u8_m (z0, p0, z0),
		z0 = svclz_m (z0, p0, z0))

/*
** clz_u8_m_tied1:
**	clz	z0\.b, p0/m, z1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_m_tied1, svuint8_t,
		z0 = svclz_u8_m (z0, p0, z1),
		z0 = svclz_m (z0, p0, z1))

/*
** clz_u8_m_tied2:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	clz	z0\.b, p0/m, \1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_m_tied2, svuint8_t,
		z0 = svclz_u8_m (z1, p0, z0),
		z0 = svclz_m (z1, p0, z0))

/*
** clz_u8_m_untied:
**	movprfx	z0, z2
**	clz	z0\.b, p0/m, z1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_m_untied, svuint8_t,
		z0 = svclz_u8_m (z2, p0, z1),
		z0 = svclz_m (z2, p0, z1))

/*
** clz_u8_z_tied1:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0\.b, p0/z, \1\.b
**	clz	z0\.b, p0/m, \1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_z_tied1, svuint8_t,
		z0 = svclz_u8_z (p0, z0),
		z0 = svclz_z (p0, z0))

/*
** clz_u8_z_untied:
**	movprfx	z0\.b, p0/z, z1\.b
**	clz	z0\.b, p0/m, z1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_z_untied, svuint8_t,
		z0 = svclz_u8_z (p0, z1),
		z0 = svclz_z (p0, z1))

/*
** clz_u8_x_tied1:
**	clz	z0\.b, p0/m, z0\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_x_tied1, svuint8_t,
		z0 = svclz_u8_x (p0, z0),
		z0 = svclz_x (p0, z0))

/*
** clz_u8_x_untied:
**	movprfx	z0, z1
**	clz	z0\.b, p0/m, z1\.b
**	ret
*/
TEST_UNIFORM_Z (clz_u8_x_untied, svuint8_t,
		z0 = svclz_u8_x (p0, z1),
		z0 = svclz_x (p0, z1))
