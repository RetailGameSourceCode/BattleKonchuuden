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
#define NLIGHT_TPAGE	((1 << 9)|(0 << 7)|(0 << 5)|(960 >> 6))
#define ALIGHT_TPAGE	((1 << 9)|(0 << 7)|(1 << 5)|(960 >> 6))
#define LIGHT_CLUT		(496 << 6)
#define BG_CLUT			(497 << 6)

#define TEX_LIGHT	0x50

#define calc_rgb() { \
	r = ((lv.vx>>4) + 0x080) & 0x1ff; \
	g = ((lv.vy>>4) + 0x140) & 0x1ff; \
	b = ((lv.vx>>5) + 0x080) & 0xff; \
	if ((r >> 8) != 0) r ^= 0x1ff; \
	if ((g >> 8) != 0) g ^= 0x1ff; \
	if ((b >> 7) != 0) b ^= 0xff; \
}

#define calc_rgb4() { \
	r = ((lv.vy>>4) + 0x180) & 0x1ff; \
	g = ((lv.vx>>5) + 0x200) & 0xff; \
	b = ((lv.vx>>5) + 0x100) & 0xff; \
	if ((r >> 8) != 0) r ^= 0x1ff; \
	r >>= 1; \
	if ((g >> 7) != 0) g ^= 0xff; \
	if ((b >> 7) != 0) b ^= 0xff; \
}


/**************************************************************************
	PolyG3 
 ***************************************************************************/
PACKET *SurmapG3NL(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x20 << 24) | ((op->b0 >> 1) << 16) | ((op->g0 >> 1) << 8) | (op->r0 >> 1));
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_f3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x04000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 13;
		si_org += 13;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG3L(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x30 << 24) | (op->b0 << 16) | (op->g0 << 8) | op->r0);
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

#if 0
PACKET *SurmapG3SPL(op, vp, np, pk, n, shift, ot)
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
	u_short r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

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

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[1] = (long)((0x30 << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[3] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[3]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[3]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[5] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[5]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[5]);
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
#endif

PACKET *SurmapG3SPL2(op, vp, np, pk, n, shift, ot)
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
	register	u_long *si_ref  = (u_long *) (si_org + 5);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	u_short r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x20 << 24) | (0 << 16) | (0 << 8) | 0x08);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_f3((u_long *) si_org);
		gte_stsxy3_gt3((u_long *) si_ref);
		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[1] = (long)((0x34 << 24) | (b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[4] = (long)((b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (1 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[7] = (long)((b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		gte_ldrgb(&si_ref[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[1]);
		gte_ldrgb(&si_ref[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[4]);
		gte_ldrgb(&si_ref[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[7]);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x04000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) &si_org[0] << 8) >> 8;

		si_env += 25;
		si_org += 25;
		si_ref += 25;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG3SPL4(op, vp, np, pk, n, shift, ot)
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
	register	u_long *si_ref  = (u_long *) (si_org + 5);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	u_short r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x20 << 24) | (0 << 16) | (0 << 8) | 0x08);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_f3((u_long *) si_org);
		gte_stsxy3_gt3((u_long *) si_ref);
		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[1] = (long)((0x34 << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[4] = (long)((b << 16) | (g << 8) | r );
		gte_ldrgb(&si_ref[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[4]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (1 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[7] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[7]);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x04000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) &si_org[0] << 8) >> 8;

		si_env += 25;
		si_org += 25;
		si_ref += 25;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG3SPL3(op, vp, np, pk, n, shift, ot)
	TMD_P_G3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_ref  = (u_long *) (si_env + 8);
	register	u_long *si_org  = (u_long *) (si_ref + 10);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);
		si_org[1] = (long)((0x20 << 24) | (0 << 16) | (0 << 8) | 0x08);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_gt3((u_long *) si_ref);
		gte_stsxy3_ft3((u_long *) si_env);
		gte_stsxy3_f3((u_long *) si_org);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (0 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		si_ref[1] = (long)((0x34 << 24) | (0x28 << 16) | (0x38 << 8) | 0x28);
		gte_ldrgb3(&si_ref[1], &si_ref[1], &si_ref[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_gt3((u_long *) si_ref);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x04000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 23;
		si_ref += 23;
		si_org += 23;
	}
	return (PACKET *) si_env;
}


#if 1
PACKET *GlassG3(op, vp, np, pk, n, shift, ot)
	TMD_P_G3 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_env);

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
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 8;
	}
	return (PACKET *) si_env;
}
#endif

/**************************************************************************
	PolyG4 
 ***************************************************************************/
PACKET *SurmapG4NL(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x28 << 24) | ((op->b0 >> 1) << 16) | ((op->g0 >> 1) << 8) | (op->r0 >> 1));
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_f4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[5]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x05000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 16;
		si_org += 16;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG4L(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x38 << 24) | (op->b0 << 16) | (op->g0 << 8) | op->r0);
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

#if 0
PACKET *SurmapG4SPL(op, vp, np, pk, n, shift, ot)
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
	u_short r, g, b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

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

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[1] = (long)((0x38 << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[3] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[3]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[3]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[5] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[5]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[5]);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[7] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[7]);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[7]);
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
#endif

PACKET *SurmapG4SPL2(op, vp, np, pk, n, shift, ot)
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
	register	u_long *si_ref  = (u_long *) (si_org + 6);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	u_short r, g, b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x28 << 24) | (0 << 16) | (0 << 8) | 0x08);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_f4((u_long *) si_org);
		gte_stsxy3_gt4((u_long *) si_ref);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[5]);
		gte_stsxy((u_long *) &si_ref[11]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[1] = (long)((0x3c << 24) | (b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[4] = (long)((b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (1 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[7] = (long)((b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		calc_rgb();
		si_ref[10] = (long)((b << 16) | (g << 8) | r);
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[12] = (long)((vv << 8) | uu);
		gte_ldrgb(&si_ref[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[1]);
		gte_ldrgb(&si_ref[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[4]);
		gte_ldrgb(&si_ref[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[7]);
		gte_ldrgb(&si_ref[10]);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[10]);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x05000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x0c000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 29;
		si_org += 29;
		si_ref += 29;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG4SPL4(op, vp, np, pk, n, shift, ot)
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
	register	u_long *si_ref  = (u_long *) (si_org + 6);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;
	u_short r, g, b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x28 << 24) | (0 << 16) | (0 << 8) | 0x08);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_f4((u_long *) si_org);
		gte_stsxy3_gt4((u_long *) si_ref);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[5]);
		gte_stsxy((u_long *) &si_ref[11]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[1] = (long)((0x3c << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[4] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[4]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (1 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[7] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[7]);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		calc_rgb4();
		si_ref[10] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_ref[10]);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[10]);
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[12] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x05000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x0c000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 29;
		si_org += 29;
		si_ref += 29;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapG4SPL3(op, vp, np, pk, n, shift, ot)
	TMD_P_G4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	register	u_long *si_ref  = (u_long *) (si_env + 10);
	register	u_long *si_org  = (u_long *) (si_ref + 13);
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);
		si_org[1] = (long)((0x28 << 24) | (0 << 16) | (0 << 8) | 8);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		/* Original polygon */
		gte_stsxy3_gt4((u_long *) si_ref);
		gte_stsxy3_ft4((u_long *) si_env);
		gte_stsxy3_f4((u_long *) si_org);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_ref[11]);
		gte_stsxy((u_long *) &si_env[8]);
		gte_stsxy((u_long *) &si_org[5]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[3] = (long)((BG_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[6] = (long)((1 << 25) | (2 << 23) | (0 << 21) | (vv << 8) | uu);
		if (PSDIDX==0) si_ref[6] |= (1 << 20);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[9] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);
		if (PSDIDX==0) {
			vv -= 16;
			if(vv < 0) vv = 0;
			if(vv > 215) vv = 215;
		} else {
			if(vv < 16) vv = 16;
			if(vv > 231) vv = 231;
		}
		si_ref[12] = (long)((vv << 8) | uu);

		si_ref[1] = (long)((0x3c << 24) | (0x28 << 16) | (0x38 << 8) | 0x28);
		gte_ldrgb3(&si_ref[1], &si_ref[1], &si_ref[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_ncct();
		gte_strgb3_gt4((u_long *) si_ref);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_ref[10]);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_ref << 8) >> 8) | 0x05000000);
		si_ref[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x0c000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 29;
		si_ref += 29;
		si_org += 29;
	}
	return (PACKET *) si_env;
}


#if 1
PACKET *GlassG4(op, vp, np, pk, n, shift, ot)
	TMD_P_G4 *op;
	VERT   *vp, *np;
	PACKET *pk;
	int     n, shift;
	GsOT   *ot;
{
	register	int i;
	register	long *tag;
	register	u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	VECTOR lv;
	long	flg, otz;
	int uu, vv;
	int rfl = reflect;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

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
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	return (PACKET *) si_env;
}
#endif

/**************************************************************************
	PolyGT3 
 ***************************************************************************/
PACKET *SurmapGT3NL(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x24 << 24) | (TEX_LIGHT << 16) | (TEX_LIGHT << 8) | TEX_LIGHT);
		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[5] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[7] = (long)((op->tv2 << 8) | op->tu2);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);

		gte_stsxy3_ft3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x07000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 16;
		si_org += 16;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapGT3L(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)(0x34 << 24);
		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[6] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[9] = (long)((op->tv2 << 8) | op->tu2);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3_gt3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_nct();
		gte_strgb3_gt3((u_long *) si_org);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 18;
		si_org += 18;
	}
	return (PACKET *) si_env;
}

#if 0
PACKET *SurmapGT3SPL(op, vp, np, pk, n, shift, ot)
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
	u_short r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[6] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[9] = (long)((op->tv2 << 8) | op->tu2);
		si_env[1] = (long)((0x26 << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_avsz3();
		gte_stotz(&otz);
		gte_stsxy3_gt3((u_long *) si_org);
		gte_stsxy3_ft3((u_long *) si_env);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[1] = (long)((0x34 << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[4] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[4]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[7] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[7]);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x07000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 18;
		si_org += 18;
	}
	return (PACKET *) si_env;
}
#endif

/**************************************************************************
	PolyGT4 
 ***************************************************************************/
PACKET *SurmapGT4NL(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)((0x2c << 24) | (TEX_LIGHT << 16) | (TEX_LIGHT << 8) | TEX_LIGHT);
		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[5] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[7] = (long)((op->tv2 << 8) | op->tu2);
		si_org[9] = (long)((op->tv3 << 8) | op->tu3);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_ft4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[8]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x09000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 20;
		si_org += 20;
	}
	return (PACKET *) si_env;
}


PACKET *SurmapGT4L(op, vp, np, pk, n, shift, ot)
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

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[1] = (long)(0x3c << 24);
		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[6] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[9] = (long)((op->tv2 << 8) | op->tu2);
		si_org[12] = (long)((op->tv3 << 8) | op->tu3);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_gt4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[11]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		gte_ldrgb(&si_org[1]);
		gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
		gte_nct();
		gte_strgb3_gt4((u_long *) si_org);
		gte_ldv0(&np[op->n3]);
		gte_ncs();
		gte_strgb((u_long *) &si_org[10]);

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
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x0c000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 23;
		si_org += 23;
	}
	return (PACKET *) si_env;
}

#if 0
PACKET *SurmapGT4SPL(op, vp, np, pk, n, shift, ot)
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
	u_short r,g,b;

	for (i = 0; i < n; i++, op++) {
		gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
		gte_rtpt();			/* RotTransPers3 */

		si_org[3] = (long)((op->clut << 16) | (op->tv0 << 8) | op->tu0);
		si_org[6] = (long)((op->tpage << 16) | (op->tv1 << 8) | op->tu1);
		si_org[9] = (long)((op->tv2 << 8) | op->tu2);
		si_org[12] = (long)((op->tv3 << 8) | op->tu3);
		si_env[1] = (long)((0x2e << 24) | (rfl << 16) | (rfl << 8) | rfl);

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_gt4((u_long *) si_org);
		gte_stsxy3_ft4((u_long *) si_env);

		gte_ldv0(&vp[op->v3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_org[11]);
		gte_stsxy((u_long *) &si_env[8]);

		gte_avsz4();
		gte_stotz(&otz);

		/* 1st vertex */
		gte_ApplyRotMatrix(&np[op->n0], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[1] = (long)((0x3c << 24) | (b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[1]);
		gte_ldv0(&np[op->n0]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[1]);
		uu = 128-((((short)si_env[2]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[2]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[3] = (long)((LIGHT_CLUT << 16) | (vv << 8) | uu);

		/* 2nd vertex */
		gte_ApplyRotMatrix(&np[op->n1], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[4] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[4]);
		gte_ldv0(&np[op->n1]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[4]);
		uu = 128-((((short)si_env[4]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[4]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[5] = (long)((ALIGHT_TPAGE << 16) | (vv << 8) | uu);

		/* 3rd vertex */
		gte_ApplyRotMatrix(&np[op->n2], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[7] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[7]);
		gte_ldv0(&np[op->n2]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[7]);
		uu = 128-((((short)si_env[6]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[6]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[7] = (long)((vv << 8) | uu);

		/* 4th vertex */
		gte_ApplyRotMatrix(&np[op->n3], &lv);   /* normal->screen coord */
		calc_rgb();
		si_org[10] = (long)((b << 16) | (g << 8) | r);
		gte_ldrgb(&si_org[10]);
		gte_ldv0(&np[op->n3]);
		gte_nccs();
		gte_strgb((u_long *) &si_org[10]);
		uu = 128-((((short)si_env[8]>>2)+((int)lv.vx>>4))>>1);
		vv = 128+((((short)si_env[8]>>18)+((int)lv.vy>>4))>>1);
		if(uu < 0) uu = 0;
		if(uu > 255) uu = 255;
		if(vv < 0) vv = 0;
		if(vv > 255) vv = 255;
		si_env[9] = (long)((vv << 8) | uu);

		tag = (u_long *) (ot->org + (otz >> shift));
		si_org[0] = (u_long)((((u_long)si_env << 8) >> 8) | 0x0c000000);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_org << 8) >> 8;

		si_env += 23;
		si_org += 23;
	}
	return (PACKET *) si_env;
}
#endif


