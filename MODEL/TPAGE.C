/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : tpage polygon packet routine                             */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : TPAGE.C                                                  */
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

/**************************************************************************
	PolyF3
 ***************************************************************************/
PACKET *TPageF3(op, vp, np, pk, n, shift, ot)
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
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = op->r0 - model_col[R];
		if (r < 0) r = 0;
		g = op->g0 - model_col[G];
		if (g < 0) g = 0;
		b = op->b0 - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x22 << 24) | (b << 16) | (g << 8) | r);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[5] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x01000000);
		si_env[6] = (u_long)((0xe1 << 24) | tpage);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x04000000);
		*tag = ((u_long) &si_env[5] << 8) >> 8;
		si_env += 7;
	}
	return (PACKET *) si_env;
}

PACKET *TPageNF3(op, vp, np, pk, n, shift, ot)
	TMD_P_NF3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0x80 - model_col[R];
		if (r < 0) r = 0;
		g = 0x80 - model_col[G];
		if (g < 0) g = 0;
		b = 0x80 - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x22 << 24) | (b << 16) | (g << 8) | r);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_f3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[5] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x01000000);
		si_env[6] = (u_long)((0xe1 << 24) | tpage);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x04000000);
		*tag = ((u_long) &si_env[5] << 8) >> 8;
		si_env += 7;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyF4
 ***************************************************************************/
PACKET *TPageF4(op, vp, np, pk, n, shift, ot)
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
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = op->r0 - model_col[R];
		if (r < 0) r = 0;
		g = op->g0 - model_col[G];
		if (g < 0) g = 0;
		b = op->b0 - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x2a << 24) | (b << 16) | (g << 8) | r);
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
		si_env[6] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x01000000);
		si_env[7] = (u_long)((0xe1 << 24) | tpage);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x05000000);
		*tag = ((u_long) &si_env[6] << 8) >> 8;
		si_env += 8;
	}
	return (PACKET *) si_env;
}

PACKET *TPageNF4(op, vp, np, pk, n, shift, ot)
	TMD_P_NF4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0x80 - model_col[R];
		if (r < 0) r = 0;
		g = 0x80 - model_col[G];
		if (g < 0) g = 0;
		b = 0x80 - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x2a << 24) | (b << 16) | (g << 8) | r);
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
		si_env[6] = (u_long)((((u_long) &si_env[0] << 8) >> 8) | 0x01000000);
		si_env[7] = (u_long)((0xe1 << 24) | tpage);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x05000000);
		*tag = ((u_long) &si_env[6] << 8) >> 8;
		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT3
 ***************************************************************************/
PACKET *TPageFT3(op, vp, np, pk, n, shift, ot)
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
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0xff - model_col[R];
		if (r < 0) r = 0;
		g = 0xff - model_col[G];
		if (g < 0) g = 0;
		b = 0xff - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x26 << 24) | (b << 16) | (g << 8) | r);
		si_env[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_env[5] = (long)(((op->tpage | tpage) << 16) | (op->tv1 << 8) | op->tu1);
		si_env[7] = (long)((op->tv2 << 8) | op->tu2);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_ft3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) &si_env[0] << 8) >> 8;
		si_env += 8;
	}
	return (PACKET *) si_env;
}

PACKET *TPageNFT3(op, vp, np, pk, n, shift, ot)
	TMD_P_TNF3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0xff - model_col[R];
		if (r < 0) r = 0;
		g = 0xff - model_col[G];
		if (g < 0) g = 0;
		b = 0xff - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x26 << 24) | (b << 16) | (g << 8) | r);
		si_env[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_env[5] = (long)(((op->tpage | tpage) << 16) | (op->tv1 << 8) | op->tu1);
		si_env[7] = (long)((op->tv2 << 8) | op->tu2);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_ft3((u_long *) si_env);
		gte_avsz3();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) &si_env[0] << 8) >> 8;
		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT4
 ***************************************************************************/
PACKET *TPageFT4(op, vp, np, pk, n, shift, ot)
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
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0xff - model_col[R];
		if (r < 0) r = 0;
		g = 0xff - model_col[G];
		if (g < 0) g = 0;
		b = 0xff - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x2e << 24) | (b << 16) | (g << 8) | r);
		si_env[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_env[5] = (long)(((op->tpage | tpage) << 16) | (op->tv1 << 8) | op->tu1);
		si_env[7] = (long)((op->tv2 << 8) | op->tu2);
		si_env[9] = (long)((op->tv3 << 8) | op->tu3);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_ft4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);
		gte_avsz4();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) &si_env[0] << 8) >> 8;
		si_env += 10;
	}
	return (PACKET *) si_env;
}

PACKET *TPageNFT4(op, vp, np, pk, n, shift, ot)
	TMD_P_TNF4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	long	flg, otz;
	short	r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */
		r = 0xff - model_col[R];
		if (r < 0) r = 0;
		g = 0xff - model_col[G];
		if (g < 0) g = 0;
		b = 0xff - model_col[B];
		if (b < 0) b = 0;
		si_env[1] = (long)((0x2e << 24) | (b << 16) | (g << 8) | r);
		si_env[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_env[5] = (long)(((op->tpage | tpage) << 16) | (op->tv1 << 8) | op->tu1);
		si_env[7] = (long)((op->tv2 << 8) | op->tu2);
		si_env[9] = (long)((op->tv3 << 8) | op->tu3);
		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;
		gte_stsxy3_ft4((u_long *) si_env);
		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);
		gte_avsz4();
		gte_stotz(&otz);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) &si_env[0] << 8) >> 8;
		si_env += 10;
	}
	return (PACKET *) si_env;
}


