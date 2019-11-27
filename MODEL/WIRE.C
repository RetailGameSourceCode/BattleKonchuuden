/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : wire frame packet routine                                */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : WIRE.C                                                   */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <inline_c.h>
#include <gtemac.h>
#include <libgpu.h>
#include <libgs.h>
#include <asm.h>

#include "../lib/aki_def.h"
#include "../lib/model.h"

#define hide_line	(1)				/* 陰線処理 */
#define back_clip	(1)				/* バッククリップ */
#define light_calc	(0)				/* 光源計算 */
#define normal_draw	(0)				/* 法線表示 */
#define vertex_draw	(0)				/* 法線表示 */
#define norm_len	(256)			/* 法線長さ(1/n) */
#define col_R		(0x20)
#define col_G		(0xc0)
#define col_B		(0x20)

/**************************************************************************
	PolyF3 
 ***************************************************************************/
PACKET *WireF3(op, vp, np, pk, n, shift, ot)
	TMD_P_F3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3c((u_long *) &si_env[2]);
		si_env[5] = si_env[2];
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x04000000);
		si_env[8] = (u_long)((0x20 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[9] = si_env[2];
		si_env[10] = si_env[3];
		si_env[11] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 12;
#else
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
#endif
#if normal_draw
	{
		SVECTOR nv;

		si_env[1] = (long)((0x40 << 24) | (0x00 << 16) | (0x00 << 8) | 0xc0);
		nv.vx = (vp[op->v0].vx + vp[op->v1].vx + vp[op->v2].vx) / 3;
		nv.vy = (vp[op->v0].vy + vp[op->v1].vy + vp[op->v2].vy) / 3;
		nv.vz = (vp[op->v0].vz + vp[op->v1].vz + vp[op->v2].vz) / 3;
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[2]);
		nv.vx += (np[op->n0].vx / norm_len);
		nv.vy += (np[op->n0].vy / norm_len);
		nv.vz += (np[op->n0].vz / norm_len);
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[3]);
		gte_stszotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 4;
	}
#endif
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyF4 
 ***************************************************************************/
PACKET *WireF4(op, vp, np, pk, n, shift, ot)
	TMD_P_F4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_stsxy3(&si_env[2], &si_env[3], &si_env[5]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[4]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		si_env[11] = (u_long)((((u_long) &si_env[7] << 8) >> 8) | 0x05000000);
		si_env[12] = (u_long)((0x28 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[13] = si_env[2];
		si_env[14] = si_env[3];
		si_env[15] = si_env[5];
		si_env[16] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[11] << 8) >> 8;
		si_env += 17;
#else
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 11;
#endif
#if normal_draw
	{
		SVECTOR nv;

		si_env[1] = (long)((0x40 << 24) | (0x00 << 16) | (0x00 << 8) | 0xc0);
		nv.vx = (vp[op->v0].vx + vp[op->v1].vx + vp[op->v2].vx + vp[op->v3].vx) / 4;
		nv.vy = (vp[op->v0].vy + vp[op->v1].vy + vp[op->v2].vy + vp[op->v3].vy) / 4;
		nv.vz = (vp[op->v0].vz + vp[op->v1].vz + vp[op->v2].vz + vp[op->v3].vz) / 4;
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[2]);
		nv.vx += (np[op->n0].vx / norm_len);
		nv.vy += (np[op->n0].vy / norm_len);
		nv.vz += (np[op->n0].vz / norm_len);
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[3]);
		gte_stszotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 4;
	}
#endif
	}
	return (PACKET *) si_env;
}


/**************************************************************************
	PolyG3 
 ***************************************************************************/
PACKET *WireG3(op, vp, np, pk, n, shift, ot)
	TMD_P_G3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3c((u_long *) &si_env[2]);
		si_env[5] = si_env[2];
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x04000000);
		si_env[8] = (u_long)((0x20 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[9] = si_env[2];
		si_env[10] = si_env[3];
		si_env[11] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 12;
#else
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
#endif
#if vertex_draw
	{
		SVECTOR nv[3];

		si_env[1] =
		si_env[5] =
		si_env[9] = (long)((0x40 << 24) | (0xe0 << 16) | (0x20 << 8) | 0x20);
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		gte_stsxy3((u_long *) &si_env[2], (u_long *) &si_env[6], (u_long *) &si_env[10]);
		nv[0].vx = vp[op->v0].vx + (np[op->n0].vx / norm_len);
		nv[0].vy = vp[op->v0].vy + (np[op->n0].vy / norm_len);
		nv[0].vz = vp[op->v0].vz + (np[op->n0].vz / norm_len);
		nv[1].vx = vp[op->v1].vx + (np[op->n1].vx / norm_len);
		nv[1].vy = vp[op->v1].vy + (np[op->n1].vy / norm_len);
		nv[1].vz = vp[op->v1].vz + (np[op->n1].vz / norm_len);
		nv[2].vx = vp[op->v2].vx + (np[op->n2].vx / norm_len);
		nv[2].vy = vp[op->v2].vy + (np[op->n2].vy / norm_len);
		nv[2].vz = vp[op->v2].vz + (np[op->n2].vz / norm_len);
		gte_ldv3(&nv[0], &nv[1], &nv[2]);
		gte_rtpt();
		gte_stsxy3((u_long *) &si_env[3], (u_long *) &si_env[7], (u_long *) &si_env[11]);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[4] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = (u_long)((((u_long) &si_env[4] << 8) >> 8) | 0x03000000);
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) &si_env[8] << 8) >> 8;
		si_env += 12;
	}
#endif
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG4 
 ***************************************************************************/
PACKET *WireG4(op, vp, np, pk, n, shift, ot)
	TMD_P_G4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_stsxy3(&si_env[2], &si_env[3], &si_env[5]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[4]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		si_env[11] = (u_long)((((u_long) &si_env[7] << 8) >> 8) | 0x05000000);
		si_env[12] = (u_long)((0x28 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[13] = si_env[2];
		si_env[14] = si_env[3];
		si_env[15] = si_env[5];
		si_env[16] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[11] << 8) >> 8;
		si_env += 17;
#else
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 11;
#endif
#if vertex_draw
	{
		SVECTOR nv[4];

		si_env[1] =
		si_env[5] =
		si_env[9] =
		si_env[13] = (long)((0x40 << 24) | (0xe0 << 16) | (0x20 << 8) | 0x20);
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		gte_stsxy3((u_long *) &si_env[2], (u_long *) &si_env[6], (u_long *) &si_env[10]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[14]);
		nv[0].vx = vp[op->v0].vx + (np[op->n0].vx / norm_len);
		nv[0].vy = vp[op->v0].vy + (np[op->n0].vy / norm_len);
		nv[0].vz = vp[op->v0].vz + (np[op->n0].vz / norm_len);
		nv[1].vx = vp[op->v1].vx + (np[op->n1].vx / norm_len);
		nv[1].vy = vp[op->v1].vy + (np[op->n1].vy / norm_len);
		nv[1].vz = vp[op->v1].vz + (np[op->n1].vz / norm_len);
		nv[2].vx = vp[op->v2].vx + (np[op->n2].vx / norm_len);
		nv[2].vy = vp[op->v2].vy + (np[op->n2].vy / norm_len);
		nv[2].vz = vp[op->v2].vz + (np[op->n2].vz / norm_len);
		nv[3].vx = vp[op->v3].vx + (np[op->n3].vx / norm_len);
		nv[3].vy = vp[op->v3].vy + (np[op->n3].vy / norm_len);
		nv[3].vz = vp[op->v3].vz + (np[op->n3].vz / norm_len);
		gte_ldv3(&nv[0], &nv[1], &nv[2]);
		gte_rtpt();
		gte_stsxy3((u_long *) &si_env[3], (u_long *) &si_env[7], (u_long *) &si_env[11]);
		gte_ldv0(&nv[3]);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[15]);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[4] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = (u_long)((((u_long) &si_env[4] << 8) >> 8) | 0x03000000);
		si_env[12] = (u_long)((((u_long) &si_env[8] << 8) >> 8) | 0x03000000);
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) &si_env[12] << 8) >> 8;
		si_env += 16;
	}
#endif
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT3 
 ***************************************************************************/
PACKET *WireFT3(op, vp, np, pk, n, shift, ot)
	TMD_P_TF3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3c((u_long *) &si_env[2]);
		si_env[5] = si_env[2];
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x04000000);
		si_env[8] = (u_long)((0x20 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[9] = si_env[2];
		si_env[10] = si_env[3];
		si_env[11] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 12;
#else
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
#endif
#if normal_draw
	{
		SVECTOR nv;

		si_env[1] = (long)((0x40 << 24) | (0x00 << 16) | (0x00 << 8) | 0xc0);
		nv.vx = (vp[op->v0].vx + vp[op->v1].vx + vp[op->v2].vx) / 3;
		nv.vy = (vp[op->v0].vy + vp[op->v1].vy + vp[op->v2].vy) / 3;
		nv.vz = (vp[op->v0].vz + vp[op->v1].vz + vp[op->v2].vz) / 3;
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[2]);
		nv.vx += (np[op->n0].vx / norm_len);
		nv.vy += (np[op->n0].vy / norm_len);
		nv.vz += (np[op->n0].vz / norm_len);
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[3]);
		gte_stszotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 4;
	}
#endif
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT4 
 ***************************************************************************/
PACKET *WireFT4(op, vp, np, pk, n, shift, ot)
	TMD_P_TF4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_stsxy3(&si_env[2], &si_env[3], &si_env[5]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[4]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		si_env[11] = (u_long)((((u_long) &si_env[7] << 8) >> 8) | 0x05000000);
		si_env[12] = (u_long)((0x28 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[13] = si_env[2];
		si_env[14] = si_env[3];
		si_env[15] = si_env[5];
		si_env[16] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[11] << 8) >> 8;
		si_env += 17;
#else
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 11;
#endif
#if normal_draw
	{
		SVECTOR nv;

		si_env[1] = (long)((0x40 << 24) | (0x00 << 16) | (0x00 << 8) | 0xc0);
		nv.vx = (vp[op->v0].vx + vp[op->v1].vx + vp[op->v2].vx + vp[op->v3].vx) / 4;
		nv.vy = (vp[op->v0].vy + vp[op->v1].vy + vp[op->v2].vy + vp[op->v3].vy) / 4;
		nv.vz = (vp[op->v0].vz + vp[op->v1].vz + vp[op->v2].vz + vp[op->v3].vz) / 4;
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[2]);
		nv.vx += (np[op->n0].vx / norm_len);
		nv.vy += (np[op->n0].vy / norm_len);
		nv.vz += (np[op->n0].vz / norm_len);
		gte_ldv0(&nv);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[3]);
		gte_stszotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 4;
	}
#endif
	}
	return (PACKET *) si_env;
}


/**************************************************************************
	PolyGT3 
 ***************************************************************************/
PACKET *WireGT3(op, vp, np, pk, n, shift, ot)
	TMD_P_TG3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3c((u_long *) &si_env[2]);
		si_env[5] = si_env[2];
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x04000000);
		si_env[8] = (u_long)((0x20 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[9] = si_env[2];
		si_env[10] = si_env[3];
		si_env[11] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 12;
#else
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
#endif
#if vertex_draw
	{
		SVECTOR nv[3];

		si_env[1] =
		si_env[5] =
		si_env[9] = (long)((0x40 << 24) | (0xe0 << 16) | (0x20 << 8) | 0x20);
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		gte_stsxy3((u_long *) &si_env[2], (u_long *) &si_env[6], (u_long *) &si_env[10]);
		nv[0].vx = vp[op->v0].vx + (np[op->n0].vx / norm_len);
		nv[0].vy = vp[op->v0].vy + (np[op->n0].vy / norm_len);
		nv[0].vz = vp[op->v0].vz + (np[op->n0].vz / norm_len);
		nv[1].vx = vp[op->v1].vx + (np[op->n1].vx / norm_len);
		nv[1].vy = vp[op->v1].vy + (np[op->n1].vy / norm_len);
		nv[1].vz = vp[op->v1].vz + (np[op->n1].vz / norm_len);
		nv[2].vx = vp[op->v2].vx + (np[op->n2].vx / norm_len);
		nv[2].vy = vp[op->v2].vy + (np[op->n2].vy / norm_len);
		nv[2].vz = vp[op->v2].vz + (np[op->n2].vz / norm_len);
		gte_ldv3(&nv[0], &nv[1], &nv[2]);
		gte_rtpt();
		gte_stsxy3((u_long *) &si_env[3], (u_long *) &si_env[7], (u_long *) &si_env[11]);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[4] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = (u_long)((((u_long) &si_env[4] << 8) >> 8) | 0x03000000);
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) &si_env[8] << 8) >> 8;
		si_env += 12;
	}
#endif
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT4 
 ***************************************************************************/
PACKET *WireGT4(op, vp, np, pk, n, shift, ot)
	TMD_P_TG4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x4c << 24) | (col_B << 16) | (col_G << 8) | col_R);
		si_env[6] = (long) 0x55555555;

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
#if back_clip
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
#endif
		gte_stsxy3(&si_env[2], &si_env[3], &si_env[5]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[4]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb(&si_env[1]);
#endif

		tag = (u_long *) (ot->org + (otz >> shift));
#if hide_line
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		si_env[11] = (u_long)((((u_long) &si_env[7] << 8) >> 8) | 0x05000000);
		si_env[12] = (u_long)((0x28 << 24) | (1 << 16) | (1 << 8) | 1);
		si_env[13] = si_env[2];
		si_env[14] = si_env[3];
		si_env[15] = si_env[5];
		si_env[16] = si_env[4];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[11] << 8) >> 8;
		si_env += 17;
#else
		si_env[7] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = ((0x40 << 24) | ((si_env[1] << 8) >> 8));
		si_env[9] = si_env[2];
		si_env[10] = si_env[5];
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) &si_env[7] << 8) >> 8;
		si_env += 11;
#endif
#if vertex_draw
	{
		SVECTOR nv[4];

		si_env[1] =
		si_env[5] =
		si_env[9] =
		si_env[13] = (long)((0x40 << 24) | (0xe0 << 16) | (0x20 << 8) | 0x20);
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		gte_stsxy3((u_long *) &si_env[2], (u_long *) &si_env[6], (u_long *) &si_env[10]);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[14]);
		nv[0].vx = vp[op->v0].vx + (np[op->n0].vx / norm_len);
		nv[0].vy = vp[op->v0].vy + (np[op->n0].vy / norm_len);
		nv[0].vz = vp[op->v0].vz + (np[op->n0].vz / norm_len);
		nv[1].vx = vp[op->v1].vx + (np[op->n1].vx / norm_len);
		nv[1].vy = vp[op->v1].vy + (np[op->n1].vy / norm_len);
		nv[1].vz = vp[op->v1].vz + (np[op->n1].vz / norm_len);
		nv[2].vx = vp[op->v2].vx + (np[op->n2].vx / norm_len);
		nv[2].vy = vp[op->v2].vy + (np[op->n2].vy / norm_len);
		nv[2].vz = vp[op->v2].vz + (np[op->n2].vz / norm_len);
		nv[3].vx = vp[op->v3].vx + (np[op->n3].vx / norm_len);
		nv[3].vy = vp[op->v3].vy + (np[op->n3].vy / norm_len);
		nv[3].vz = vp[op->v3].vz + (np[op->n3].vz / norm_len);
		gte_ldv3(&nv[0], &nv[1], &nv[2]);
		gte_rtpt();
		gte_stsxy3((u_long *) &si_env[3], (u_long *) &si_env[7], (u_long *) &si_env[11]);
		gte_ldv0(&nv[3]);
		gte_rtps();
		gte_stsxy((u_long *) &si_env[15]);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[4] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x03000000);
		si_env[8] = (u_long)((((u_long) &si_env[4] << 8) >> 8) | 0x03000000);
		si_env[12] = (u_long)((((u_long) &si_env[8] << 8) >> 8) | 0x03000000);
		*si_env = (u_long)((( *tag << 8) >> 8) | 0x03000000);
		*tag = ((u_long) &si_env[12] << 8) >> 8;
		si_env += 16;
	}
#endif
	}
	return (PACKET *) si_env;
}


