/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : BG TEST                                                  */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : BG.C                                                     */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>

/*----- User Header     Files -----*/
#include "../lib/libctl.h"
#include "../lib/libfio.h"
#include "../lib/aki_def.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/mainsys.h"
#include "../lib/model.h"
#include "../lib/polygon.h"
#include "../lib/fade.h"
#include "../model/spadstk.h"	/* for Scratch Pad Stack */
#include "../sprite/sprite.h"
#include "../p01/anmdata.h"
#include "../p01/battle.h"
#include "../p01/poly_sub.h"
#include "../p01/bg.h"

u_short		bg_no;
GsOT        bgot[2];						/* Ordering Table                  */
GsOT_TAG    bgot_tag[2][1<<BGOT_LENGTH];	/* オーダリングテーブル実体        */
BGMODEL		bgmodel[2];
short		bg_x, bg_y;
VECTOR		sunpos;
long		BgTimer;

void bgmodel_sort(BGMODEL *mod);
void bgmodel_sort2(BGMODEL *mod);

const u_short bg_sector[] = {
#include "bg/bg.rep"
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BG TEST MAIN                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
const CVECTOR far_color[] = {
	{	   0,   0,   0,	},	// kirikabu
	{	 224, 248, 248,	},	// bg03
	{	   0,   0,   0,	},	// bg04y
	{	 168, 216, 224,	},	// bg05
	{	 168, 216, 224,	},	// bg06
	{	 168, 216, 224,	},	// bg07
	{	   0,   0,   0,	},	// bg08
	{	 208, 248, 248,	},	// bg09
	{	 216,  88,   0,	},	// bg03y
	{	 192, 192, 192,	},	// bg05y
	{	 192, 192, 192,	},	// bg06y
	{	 219, 104,  46,	},	// bg07y
	{	   0,   0,   0,	},	// bg10(nemoto)
	{	 168, 216, 224,	},	// bg11(maruta)
	{	   0,   0,   0,	},	// bg12(footstep)
	{	   0,   0,   0,	},	// bg13(bg04)
	{	   0,   0,   0,	},	// bg99
	{	 240, 176,  64,	},	// bg09y
	{	 120, 120, 150,	},	// bg98
	{	  40,  56,  72,	},	// bglast
	{	   0,   0,   0,	},	// bg97
	{	   0,   0,   0,	},	// bg02y(kirikabu)
	{	   0,   0,   0,	},	// bg10y
	{	 152,  48,   0,	},	// bg11y
	{	 200, 208, 208,	},	// bgmachi
	{	   0,   0,   0,	},	// bg08y
	{	   8,   8,   8,	},	// bgsp
};

void bg_main()
{
	VECTOR lv0, h, r;
	long d, dxz, bx, by;
	SVECTOR angle, p0, p1;
	MATRIX m;
	VECTOR vec;

	BgTimer++;
	bg_col[R] = far_color[bg_no].r;
	bg_col[G] = far_color[bg_no].g;
	bg_col[B] = far_color[bg_no].b;

	bgmodel_sort( &bgmodel[0] );

	/* 遠景ＢＧ処理 */
	switch (bg_no) {
		case 0:		// 切り株
			if ((gcb.GlobalTimer & 0x0f) == 0) {
				vec.vx = (((rand() % 20) * 200) - 2000) << 12;
				vec.vy = -(rand() % 300) << 12;
				vec.vz = (((rand() % 20) * 200) - 2000) << 12;
//				EffectEntry(9, &vec, NULL, NULL);		//	木漏れ日
			}
		case 21:	// bg02y
		case 15:	// bg13(bg04)
		case 20:	// bg97
			lv0.vx = (cam.view.vrx - cam.view.vpx) >> 1;
			lv0.vy = (cam.view.vry - cam.view.vpy) >> 1;
			lv0.vz = (cam.view.vrz - cam.view.vpz) >> 1;
			d = VectorNormal(&lv0, &lv0);
			angle.vy = ratan2(lv0.vx, lv0.vz);
			dxz = SquareRoot0( lv0.vx * lv0.vx + lv0.vz * lv0.vz );
			angle.vx = ratan2(lv0.vy / 2, dxz);

			bx = -((angle.vy >> 2) & 511);

			h.vx = 0;
			h.vy = -cam.view.vpy;
			h.vz = 65535;

			PushMatrix();
			m = GsIDMATRIX;
			RotMatrixX(angle.vx, &m);
			ApplyMatrixLV(&m, &h, &r);
			PopMatrix();

			by = (r.vy * 1024 / r.vz) - 121;

			bg_x = bx;
			bg_y = by;

			bg_x = (bg_x & 511) - 672;
			if (bg_y > -120) bg_y = -120;
			if (bg_y < -360) bg_y = -360;
			SpriteBgSet( 21, 497, bg_x, bg_y, CLUT8, 512, 256);
			if (bg_x < -352) SpriteBgSet( 21, 497, bg_x + 512, bg_y, CLUT8, 512, 256);
			break;
		case 1:		// 木の上 bg03
		case 8:		// 木の上(夕方)
			bgmodel_sort( &bgmodel[1] );
			if ((LocalTimer & 0x1f) == 0) {
				vec.vx = ((rand() % 1000) + 100) << 12;
				vec.vy = -4500 << 12;
				vec.vz = ((rand() % 4000) - 2000) << 12;
				EffectEntry(26, &vec, NULL, NULL);		// さくら
			}
			break;
		case 2:		// 夕日 bg04
			lv0.vx = (cam.view.vrx - cam.view.vpx) >> 1;
			lv0.vy = (cam.view.vry - cam.view.vpy) >> 1;
			lv0.vz = (cam.view.vrz - cam.view.vpz) >> 1;
			d = VectorNormal(&lv0, &lv0);
			angle.vy = ratan2(lv0.vx, lv0.vz);
			dxz = SquareRoot0( lv0.vx * lv0.vx + lv0.vz * lv0.vz );
			angle.vx = ratan2(lv0.vy / 2, dxz);

			bx = -((angle.vy >> 2) & 511);

			h.vx = 0;
			h.vy = -cam.view.vpy;
			h.vz = 65535;

			PushMatrix();
			m = GsIDMATRIX;
			RotMatrixX(angle.vx, &m);
			ApplyMatrixLV(&m, &h, &r);
			PopMatrix();

			by = (r.vy * 1024 / r.vz) - 121;

			bg_x = bx;
			bg_y = by;

			if (bg_y > -120) bg_y = -120;
			if (bg_y < -360) bg_y = -360;
			bg_x = -((angle.vy >> 1) & 511);
			bg_x = (bg_x & 511) - 672;
			SpriteBgSet( 25, 499, bg_x, bg_y, CLUT4, 256, 256);
			SpriteBgSet( 26, 500, bg_x + 256, bg_y, CLUT4, 256, 256);
			if (bg_x < -352) {
				SpriteBgSet( 25, 499, bg_x + 512, bg_y, CLUT4, 256, 256);
				SpriteBgSet( 26, 500, bg_x + 768, bg_y, CLUT4, 256, 256);
			}

			h.vx = 0;
			h.vy = -cam.view.vpy;
			h.vz = 49152;

			PushMatrix();
			m = GsIDMATRIX;
			RotMatrixX(angle.vx, &m);
			ApplyMatrixLV(&m, &h, &r);
			PopMatrix();

			by = (r.vy * 1024 / r.vz) - 121;

			bg_y = by;


			if (bg_y > -120) bg_y = -120;
			if (bg_y < -360) bg_y = -360;
			bg_x = -((angle.vy >> 2) & 511);
			bg_x = (bg_x & 511) - 672;
			SpriteBgSet( 21, 497, bg_x, bg_y, CLUT8, 512, 256);
			if (bg_x < -352) {
				SpriteBgSet( 21, 497, bg_x + 512, bg_y, CLUT8, 512, 256);
			}
			break;
		case 13:	// bg11
		case 23:	// bg11y
			bgmodel_sort( &bgmodel[1] );
			break;
		case 3:		// 茂み bg05
		case 9:		// 茂み(夕方)
		case 6:		// 森 bg08
		case 25:	// 森 bg08y
		case 18:	// bg98
		case 24:	// bgmachi
			bgmodel_sort2( &bgmodel[1] );
			break;
		case 4:		// 木蔭 bg06
		case 10:	// 木蔭(夕方)
		case 7:		// 丘 bg09
		case 17:	// 丘(夕方)
			bgmodel_sort2( &bgmodel[1] );
			lensflare(&sunpos);
			break;
		case 5:		// 池 bg07
		case 11:	// 池(夕方)
			lensflare(&sunpos);
			break;
		case 12:	// bg10
		case 22:	// bg10y
		case 14:	// 足跡 bg12
		case 16:	// bg99
			break;
		case 19:	// bglast
			if (LocalTimer & 1) bgmodel_sort( &bgmodel[1] );
			if ((fade.status == 0) && ((rand() & 0x7f) == 0)) {
				LightPos[X] = -5000;
				LightPos[Y] = -20000;
				LightPos[Z] = 0;
				eflt[R] = 0x4000; eflt[G] = 0x4000; eflt[B] = 0x4000;	// 反射光
				FadeInit( WHITE_IN, 0x20);
			}
			break;
		case 26:	// bgsp
//			bgmodel_sort( &bgmodel[1] );
			if ((LocalTimer & 0x0f) == 0) {
				{
					long *tmd;
					register	POLYEFE	*spp;

					vec.vx =
					vec.vy = 0;
					vec.vz = ((rand() % 3500) + 3000) << 12;
					angle.vx =
					angle.vz = 0;
					angle.vy = rand() % 4096;
					PushMatrix();
					m = GsIDMATRIX;
					RotMatrixYXZ(&angle, &m);
					ApplyMatrixLV(&m, &vec, &pos[0]);
					PopMatrix();
					pos[0].vy = 2000 << 12;
					spp = PolyefeEntry( 16, 0, &pos[0], NULL);
					tmd = NumToAddrMcr( 2, BGMODEL_ADDR );
					tmd++;			/* hedder skip */
					GsMapModelingData(tmd);	/* モデリングデータ（TMDフォーマット）を実アドレスにマップする*/
					tmd++;
					tmd++;			/* GsLinkObject4でリンクするためにTMDのオブジェクトの先頭にもってくる */
					GsLinkObject4( (u_long)tmd, &spp->object, 0);
				}
			}

			lv0.vx = (cam.view.vrx - cam.view.vpx) >> 1;
			lv0.vy = (cam.view.vry - cam.view.vpy) >> 1;
			lv0.vz = (cam.view.vrz - cam.view.vpz) >> 1;
			d = VectorNormal(&lv0, &lv0);
			angle.vy = ratan2(lv0.vx, lv0.vz) + BgTimer;
			dxz = SquareRoot0( lv0.vx * lv0.vx + lv0.vz * lv0.vz );
			angle.vx = ratan2(lv0.vy / 2, dxz);

			bx = -((angle.vy >> 2) & 511);

			h.vx = 0;
			h.vy = -cam.view.vpy;
			h.vz = 20000;

			PushMatrix();
			m = GsIDMATRIX;
			RotMatrixX(angle.vx, &m);
			ApplyMatrixLV(&m, &h, &r);
			PopMatrix();

			by = (r.vy * 1024 / r.vz) - 181; //121

			bg_x = bx;
			bg_y = by;

			bg_x = (bg_x & 511) - 672;
			if (bg_y > -120) bg_y = -120;
			if (bg_y < -360) bg_y = -360;
			SpriteBgSet( 21, 497, bg_x, bg_y, CLUT8, 512, 256);
			if (bg_x < -352) SpriteBgSet( 21, 497, bg_x + 512, bg_y, CLUT8, 512, 256);

			p0.vx = bg_x + 232;
			if (p0.vx < -256) p0.vx += 512;
			p0.vy = bg_y + 144;
			p0.vz = 1;
			lensflare_y(&p0);
			break;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BGMODEL SORT                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void bgmodel_sort(BGMODEL *mod)
{
	struct {
		SVECTOR	Rotx;
		MATRIX  tmpmatls,tmpmatws;
		VECTOR	Trnsx;
	} *sc = (void *)getScratchAddr(0);

	register GsDOBJ2 *objp;
	register GsCOORDINATE2 *coord;

	objp = mod->object;
	coord = mod->objpos;
	/* Transrate */
	sc->Trnsx.vx = ((mod->pos[X] + mod->trans[X]) >> 12);
	sc->Trnsx.vy = ((mod->pos[Y] + mod->trans[Y]) >> 12);
	sc->Trnsx.vz = ((mod->pos[Z] + mod->trans[Z]) >> 12);
	TransMatrix(&(coord->coord), &sc->Trnsx);
	TransMatrix(&(coord->coord), (VECTOR *)(coord->coord.t));
	/* Rotate */
	sc->Rotx.vz = mod->objang[0].vz + mod->ang[Z];
	sc->Rotx.vy = mod->objang[0].vy + mod->ang[Y];
	sc->Rotx.vx = mod->objang[0].vx + mod->ang[X];
	RotMatrixYXZ(&sc->Rotx, &(coord->coord));
	coord->flg = 0;

	GsGetLws(coord, &sc->tmpmatws, &sc->tmpmatls);
	GsSetLightMatrix2(&sc->tmpmatws);
	GsSetLsMatrix(&sc->tmpmatls);

//	objp->attribute = mod->attribute;
	SetSpadStack(SPAD_STACK_ADDR);
	GsSortObject4J(objp, &bgot[ PSDIDX ], 14 - BGOT_LENGTH, getScratchAddr(0));
	ResetSpadStack();
}

void bgmodel_sort2(BGMODEL *mod)
{
	struct {
		SVECTOR	Rotx;
		MATRIX  tmpmatls,tmpmatws;
		VECTOR	Trnsx;
	} *sc = (void *)getScratchAddr(0);

	register GsDOBJ2 *objp;
	register GsCOORDINATE2 *coord;

	objp = mod->object;
	coord = mod->objpos;
	/* Transrate */
	sc->Trnsx.vx = ((mod->pos[X] + mod->trans[X]) >> 12);
	sc->Trnsx.vy = ((mod->pos[Y] + mod->trans[Y]) >> 12);
	sc->Trnsx.vz = ((mod->pos[Z] + mod->trans[Z]) >> 12);
	TransMatrix(&(coord->coord), &sc->Trnsx);
	TransMatrix(&(coord->coord), (VECTOR *)(coord->coord.t));
	/* Rotate */
	sc->Rotx.vz = mod->objang[0].vz + mod->ang[Z];
	sc->Rotx.vy = mod->objang[0].vy + mod->ang[Y];
	sc->Rotx.vx = mod->objang[0].vx + mod->ang[X];
	RotMatrixYXZ(&sc->Rotx, &(coord->coord));
	coord->flg = 0;

	GsGetLws(coord, &sc->tmpmatws, &sc->tmpmatls);
	GsSetLightMatrix2(&sc->tmpmatws);
	GsSetLsMatrix(&sc->tmpmatls);

//	objp->attribute = mod->attribute;
	SetSpadStack(SPAD_STACK_ADDR);
	GsSortObject4J(objp, &ot[ PSDIDX ], 14 - OT_LENGTH, getScratchAddr(0));
	ResetSpadStack();
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BG INITILYZE                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
const GsF_LIGHT bg_flight[] = {
//		   vx    vy    vz	   r     g     b
	{	    0,  100,   10,	 0xa0, 0xa0, 0xa0,	},	// kirikabu
	{	  -50,   25, -100,	 0x80, 0x80, 0x80,	},
	{	  100,   80,   10,	 0x90, 0x90, 0x90,	},	// bg03
	{	  -10,  -50,  -30,	 0x70, 0x70, 0x70,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg04
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg05
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg06
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg07
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   20,  100,   10,	 0x90, 0x90, 0x90,	},	// bg08
	{	  -10,  -50,  -30,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg09
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	  100,   80,   10,	 0xa0, 0x80, 0x40,	},	// bg03y
	{	  -10,  -50,  -30,	 0x40, 0x10, 0x10,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg05y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg06y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg07y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	   30,  -20,  100,	 0x90, 0x90, 0x90,	},	// bg10
	{	    0,  -80,  -20,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg11
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg13
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bg13
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	   10,  100,   20,	 0x30, 0x30, 0x40,	},	// bg99
	{	  -50,   25, -100,	 0x20, 0x20, 0x20,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg09y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	   10,  100,   20,	 0x50, 0x50, 0x60,	},	// bg98
	{	  -50,   25, -100,	 0x20, 0x20, 0x30,	},
	{	   10,  100,   20,	 0x40, 0x40, 0x50,	},	// bglast
	{	  -30, -100,   20,	 0x70, 0x70, 0x30,	},
	{	   10,  100,   20,	 0x50, 0x50, 0x60,	},	// bg97
	{	  -50,   25, -100,	 0x20, 0x20, 0x30,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg02y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg10y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg11y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	   10,  100,   20,	 0x90, 0x90, 0x90,	},	// bgmachi
	{	  -50,   25, -100,	 0x70, 0x70, 0x70,	},
	{	    0,    0,  100,	 0xa0, 0x80, 0x40,	},	// bg08y
	{	    0,  100,  -10,	 0x40, 0x10, 0x10,	},
	{	   10,  100,   20,	 0x70, 0x70, 0x70,	},	// bgsp
	{	  -50,   25, -100,	 0x30, 0x30, 0x30,	},
};

const SVECTOR bg_ambient[] = {
//		   r	   g	   b
	{	ONE/8,	ONE/8,	ONE/8,	},	// kirikabu
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg03
	{	ONE/32,	    0,	    0,	},	// bg04
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg05
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg06
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg07
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg08
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg09
	{	ONE/32,	    0,	    0,	},	// bg03y
	{	ONE/32,	    0,	    0	},	// bg05y
	{	ONE/32,	    0,	    0,	},	// bg06y
	{	ONE/32,	    0,	    0,	},	// bg07y
	{	ONE/16,	ONE/8,	ONE/16,	},	// bg10
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg11
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg12
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg13
	{	    0,	    0,	    0,	},	// bg99
	{	ONE/32,	    0,	    0,	},	// bg09y
	{	ONE/16,	ONE/16,	ONE/8,	},	// bg98
	{	    0,	    0,	    0,	},	// bglast
	{	ONE/8,	ONE/8,	ONE/8,	},	// bg97
	{	ONE/32,	    0,	    0,	},	// bg02y
	{	ONE/32,	    0,	    0,	},	// bg10y
	{	ONE/32,	    0,	    0,	},	// bg11y
	{	    0,	    0,	    0,	},	// bgmachi
	{	ONE/32,	    0,	    0,	},	// bg08y
	{	ONE/8,	ONE/8,	ONE/8,	},	// bgsp
};

void bg_init()
{
	bgot[0].length = BGOT_LENGTH;
	bgot[0].org    = bgot_tag[0];
	bgot[1].length = BGOT_LENGTH;
	bgot[1].org    = bgot_tag[1];

	bg_no = gcb.bg_no;
	BgTimer = 0;

	bg_init1(bg_no);

	switch (bg_no) {
		case 0:
			break;
		case 1:
		case 8:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			sunpos.vx = (2500 << 12);
			sunpos.vy = (-2000 << 12);
			sunpos.vz = (-10500 << 12);
			break;
		case 5:
			sunpos.vx = (2500 << 12);
			sunpos.vy = (-2000 << 12);
			sunpos.vz = (-10500 << 12);
			break;
		case 6:
			break;
		case 7:
		case 17:
			sunpos.vx = (2500 << 12);
			sunpos.vy = (-4000 << 12);
			sunpos.vz = (-10500 << 12);
			break;
		case 9:
			break;
		case 10:
			sunpos.vx = (2500 << 12);
			sunpos.vy = (-2000 << 12);
			sunpos.vz = (-10500 << 12);
			break;
		case 11:
			sunpos.vx = (2500 << 12);
			sunpos.vy = (-2000 << 12);
			sunpos.vz = (-10500 << 12);
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			break;
		case 18:
			break;
		case 19:
			break;
		case 20:
			break;
		case 21:
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			break;
		case 25:
			break;
		case 26:
			break;
	}

	GsSetFlatLight(0,&bg_flight[bg_no * 2]);
	GsSetFlatLight(1,&bg_flight[bg_no * 2 + 1]);
	GsSetAmbient( bg_ambient[bg_no].vx, bg_ambient[bg_no].vy, bg_ambient[bg_no].vz );
	GsSetAzwh(1500,256,256);

	BGFadeOffset = 0x80;
}


void bg_init1(int bg_no)
{
	long i, cmp, num;
	short sector = bg_no * 4;

#ifndef PREPRE
	printf("bginit = %d\n", bg_no);
#endif
	/* モデルデータ */
	FioDivReadFile( "DT\\BG.DAT", (Uint8 *) LOAD_ADDR, bg_sector[sector], bg_sector[sector + 1] );
	LzDecInit( (u_char *) LOAD_ADDR, BGMODEL_ADDR, 0);
	LzDecB();
	num = *(u_long *) BGMODEL_ADDR;
	for (i = 0; i < num; i++) {
		model_init( (long *) NumToAddrMcr( i, BGMODEL_ADDR), (MODEL *) &bgmodel[i] );
		GsInitCoordinate2(WORLD, &bgmodel[i].objpos[0]);
		bgmodel[i].object[0].coord2 = &bgmodel[i].objpos[0];
		bgmodel[i].object[0].attribute = GsDIV1;	// 自動分割ＯＮ
		bgmodel[i].objang[0].vx = 0;
		bgmodel[i].objang[0].vy = 0;
		bgmodel[i].objang[0].vz = 0;
		bgmodel[i].pos[X] = 0;
		bgmodel[i].pos[Y] = 0;
		bgmodel[i].pos[Z] = 0;
		bgmodel[i].ang[X] = 0;
		bgmodel[i].ang[Y] = 0;
		bgmodel[i].ang[Z] = 0;
	}

	/* テクスチャ */
	FioDivReadFile( "DT\\BG.DAT", (Uint8 *) LOAD_ADDR, bg_sector[sector + 2], bg_sector[sector + 3] );
	num = *(u_long *) LOAD_ADDR;
	for (i = 0; i < num; i++) {
		cmp = NumToAddrMcr( i, LOAD_ADDR );
		LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
		LzDecB();
		texture_init( TENKAI_ADDR );
		DrawSync(0);
	}
}

