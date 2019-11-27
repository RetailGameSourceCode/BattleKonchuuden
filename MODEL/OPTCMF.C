/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : optics camouflage packet routine                         */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : OPTCMF.C                                                 */
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
#include "../p01/battle.h"

#define TEX_RGB	((0x60 << 16) | (0x60 << 8) | 0x60)

#define uv_set(n) { \
	uu = 144 + (((short)si_env[n])); \
	vv = 120 + (((short)(si_env[n]>>16))); \
}

/**************************************************************************
	PolyF3 
 ***************************************************************************/
PACKET *OpticsF3(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x24 << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyF4 
 ***************************************************************************/
PACKET *OpticsF4(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2c << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT3 
 ***************************************************************************/
PACKET *OpticsFT3(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x24 << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT4 
 ***************************************************************************/
PACKET *OpticsFT4(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2c << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG3 
 ***************************************************************************/
PACKET *OpticsG3(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x24 << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		uv_set(4);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		uv_set(6);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG4 
 ***************************************************************************/
PACKET *OpticsG4(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2c << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		uv_set(4);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		uv_set(6);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		uv_set(8);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT3 
 ***************************************************************************/
PACKET *OpticsGT3(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x24 << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		uv_set(4);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		uv_set(6);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 8;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT4 
 ***************************************************************************/
PACKET *OpticsGT4(op, vp, np, pk, n, shift, ot)
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
	int uu, vv;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2c << 24) | TEX_RGB);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		uv_set(2);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[3] = (long)((vv << 8) | uu);

		/* 2nd vertex */
		uv_set(4);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[5] = (long)((2 << 23) | (vv << 8) | uu);
		if (PSDIDX==0) si_env[5] |= (1 << 20);

		/* 3rd vertex */
		uv_set(6);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		uv_set(8);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	return (PACKET *) si_env;
}


