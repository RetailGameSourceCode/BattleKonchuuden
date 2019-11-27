/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : color polygon packet routine                             */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : COLOR.C                                                  */
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

#define light_calc	(0)				/* ŒõŒ¹ŒvŽZ */

/**************************************************************************
	PolyF3
 ***************************************************************************/
PACKET *ColorF3(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x20 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x04000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 5;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyF4
 ***************************************************************************/
PACKET *ColorF4(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x28 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[5]);
		gte_avsz4();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x05000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 6;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG3
 ***************************************************************************/
PACKET *ColorG3(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x30 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_g3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g3((u_long *) si_env);
#else
		si_env[3] =
		si_env[5] = rgb;
#endif
		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG4
 ***************************************************************************/
PACKET *ColorG4(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x38 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_g4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g4((u_long *) si_env);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[7]);
#else
		si_env[3] =
		si_env[5] =
		si_env[7] = rgb;
#endif
		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x08000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 9;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT3
 ***************************************************************************/
PACKET *ColorFT3(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x20 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x04000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 5;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT4
 ***************************************************************************/
PACKET *ColorFT4(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x28 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[5]);
		gte_avsz4();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x05000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 6;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT3
 ***************************************************************************/
PACKET *ColorGT3(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x30 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_g3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g3((u_long *) si_env);
#else
		si_env[3] =
		si_env[5] = rgb;
#endif
		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x06000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 7;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT4
 ***************************************************************************/
PACKET *ColorGT4(op, vp, np, pk, n, shift, ot)
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
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		si_env[1] = (long)((0x38 << 24) | rgb);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_g4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);
		gte_avsz4();
		gte_stotz(&otz);
#if light_calc
		gte_ldrgb(&si_env[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g4((u_long *) si_env);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[7]);
#else
		si_env[3] =
		si_env[5] =
		si_env[7] = rgb;
#endif
		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x08000000);
		*tag = ((u_long) si_env << 8) >> 8;
		si_env += 9;
	}
	return (PACKET *) si_env;
}

