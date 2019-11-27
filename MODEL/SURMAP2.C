/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : surround mapping packet routine                          */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : SURMAP.C                                                 */
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

//						ディザ    色数     半透明   座標
#define LIGHT_TPAGE		((1 << 9)|(0 << 7)|(3 << 5)|(960 >> 6))
#define ALIGHT_TPAGE	((1 << 9)|(0 << 7)|(1 << 5)|(960 >> 6))
#define LIGHT_CLUT		(496 << 6)

#define calc_rgb() { \
	r = ((lv.vx>>4) + 0x080) & 0x1ff; \
	g = ((lv.vy>>4) + 0x140) & 0x1ff; \
	b = ((lv.vx>>5) + 0x080) & 0xff; \
	if ((r >> 8) != 0) r ^= 0x1ff; \
	if ((g >> 8) != 0) g ^= 0x1ff; \
	if ((b >> 7) != 0) b ^= 0xff; \
}

/**************************************************************************
	PolyF3
 ***************************************************************************/
PACKET *ColorCF3(op, vp, np, pk, n, shift, ot)
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
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[1]);

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
PACKET *ColorCF4(op, vp, np, pk, n, shift, ot)
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
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[1]);

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
PACKET *SurmapCG3L(op, vp, np, pk, n, shift, ot)
	TMD_P_G3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_org  = (u_long *) (si_env + 8);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x30 << 24) | rgb);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_g3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g3((u_long *) si_org);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((LIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x06000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 15;
		si_org += 15;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyG4 
 ***************************************************************************/
PACKET *SurmapCG4L(op, vp, np, pk, n, shift, ot)
	TMD_P_G4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_org  = (u_long *) (si_env + 10);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x38 << 24) | rgb);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_g4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[8]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g4((u_long *) si_org);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[7]);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((LIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x08000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 19;
		si_org += 19;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyFT3
 ***************************************************************************/
PACKET *ColorCFT3(op, vp, np, pk, n, shift, ot)
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
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[1]);

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
PACKET *ColorCFT4(op, vp, np, pk, n, shift, ot)
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
		gte_ldrgb(&si_env[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_env[1]);

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
PACKET *SurmapCGT3L(op, vp, np, pk, n, shift, ot)
	TMD_P_TG3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_org  = (u_long *) (si_env + 8);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x30 << 24) | rgb);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_g3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g3((u_long *) si_org);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((LIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x06000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 15;
		si_org += 15;
	}
	return (PACKET *) si_env;
}

/**************************************************************************
	PolyGT4 
 ***************************************************************************/
PACKET *SurmapCGT4L(op, vp, np, pk, n, shift, ot)
	TMD_P_TG4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_org  = (u_long *) (si_env + 10);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	long	rgb = (model_col[B] << 16 | model_col[G] << 8 | model_col[R]);

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x38 << 24) | rgb);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_g4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[8]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_g4((u_long *) si_org);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[7]);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((LIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x08000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 19;
		si_org += 19;
	}
	return (PACKET *) si_env;
}


