/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON MODEL/MOTION ENGINE                              */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : MODEL.C                                                  */
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
#include "../lib/aki_def.h"
#include "../lib/address.h"
#include "../lib/lz.h"
#include "../lib/grpara.h"
#include "../lib/model.h"
#include "../p01/battle.h"
#include "../model/spadstk.h"	/* for Scratch Pad Stack */

/*----- User Works            -----*/
GsF_LIGHT	pslt[3];				/* 平行光源を設定するための構造体 */
u_short		Projection;				/* プロジェクション */
u_char		reflect;				/* 反射率 */
CAMERA		cam;					/* カメラ */
u_char		model_col[RGB];			/* カラーポリゴン色指定 */
u_short		tpage;					/* テクスチャページ指定 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL SORT                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void model_sort(MODEL *mod, u_char rfl)
{
	struct {
		SVECTOR	Rotx;
		MATRIX  tmpmatls,tmpmatws;
		VECTOR	Trnsx;
		VECTOR	Scalx;
	} *sc = (void *)getScratchAddr(0);

	register int	i;
	register GsDOBJ2 *objp;
	register GsCOORDINATE2 *coord;

	reflect = rfl;
	for(i = 0, objp = mod->object, coord = mod->objpos; i < mod->Objnum; i++, objp++, coord++)	{
		/* Rotate */
		if(coord->super == NULL) {
			sc->Rotx.vx = mod->objang[i].vx + mod->ang[X];
			sc->Rotx.vy = mod->objang[i].vy + mod->ang[Y];
			sc->Rotx.vz = mod->objang[i].vz + mod->ang[Z];
			RotMatrixYZX(&sc->Rotx, &(coord->coord));
		} else {
			sc->Rotx.vx = mod->objang[i].vx;
			sc->Rotx.vy = mod->objang[i].vy;
			sc->Rotx.vz = mod->objang[i].vz;
			RotMatrixZYX(&sc->Rotx, &(coord->coord));
		}
		/* Transrate */
		if(coord->super == NULL) {
			SetRotMatrix(&(coord->coord));
			sc->Trnsx.vx = mod->trans[X];
			sc->Trnsx.vy = mod->trans[Y];
			sc->Trnsx.vz = mod->trans[Z];
			ApplyRotMatrixLV(&sc->Trnsx, &sc->Scalx);
			sc->Trnsx.vx = (mod->pos[X] + sc->Scalx.vx) / 4096;
			sc->Trnsx.vy = (mod->pos[Y] + sc->Scalx.vy) / 4096;
			sc->Trnsx.vz = (mod->pos[Z] + sc->Scalx.vz) / 4096;
			TransMatrix(&(coord->coord), &sc->Trnsx);
		}
		TransMatrix(&(coord->coord), (VECTOR *)(coord->coord.t));
#if 0
		/* Scale */
		if(coord->super == NULL) {
			sc->Scalx.vx = mod->scl[X];
			sc->Scalx.vy = mod->scl[Y];
			sc->Scalx.vz = mod->scl[Z];
			ScaleMatrix( &(coord->coord), &sc->Scalx);

			sc->Scalx.vx = mod->objscl[i].vx;
			sc->Scalx.vy = mod->objscl[i].vy;
			sc->Scalx.vz = mod->objscl[i].vz;
		} else {
			sc->Scalx.vx = mod->objscl[i].vx;
			sc->Scalx.vy = mod->objscl[i].vy;
			sc->Scalx.vz = mod->objscl[i].vz;
		}
		ScaleMatrix( &(coord->coord), &sc->Scalx);
#endif
		coord->flg = 0;

		if ((objp != NULL) && (i > 1)) {
			GsGetLws(coord, &sc->tmpmatws, &sc->tmpmatls);
			GsSetLightMatrix2(&sc->tmpmatws);
			GsSetLsMatrix(&sc->tmpmatls);

			SetSpadStack(SPAD_STACK_ADDR);
			GsSortObject4J(objp, &ot[ PSDIDX ], 14 - OT_LENGTH, getScratchAddr(0));
			ResetSpadStack();
		}
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION INITIALYZE                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void motion_init(u_char *adr, MOTION *mot, u_short num, short loop)
{
	int     i;
	long	valx;
	u_long	source_adr;
	MOTION_DATA *mbuf = mot->bufp;

	source_adr = (u_long) NumToAddrMcr( num, adr );
	LzDecInit( (u_char *) source_adr, (u_char *) EXPAND_ADDR, 0);
	LzDecB();

	adr = (u_char *) EXPAND_ADDR;
	mot->num = num;
	mot->frame = *(Uint16 *)(adr);
	mot->parts = *(Uint16 *)(adr+2);
	mot->loop = loop;
	mot->count = 0;
	valx = (Uint32)(mot->parts*6+12);
	adr += 4;
	for(i = 0 ; i < mot->frame ;i++)	{
		memcpy(mbuf,adr,valx);
		adr+=valx;
		mbuf++;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION CONTROL                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void motion_test(MODEL *mod, MOTION *mot)
{
	register int i;
	register int *objno;
	register MOTION_DATA *mbuf;

	objno = mot->otbl;
	mbuf = mot->bufp + mot->count;
	mod->trans[X] = mbuf->pos[X] << 1;
	mod->trans[Y] = mbuf->pos[Y] << 1;
	mod->trans[Z] = -mbuf->pos[Z] << 1;
	for(i = 0; i < mot->parts; i++, objno++) {
		mod->objang[i].vx = mbuf->ang[i][X];
		mod->objang[i].vy = -mbuf->ang[i][Y];
		mod->objang[i].vz = -mbuf->ang[i][Z];
	}
	if (++mot->count == mot->frame) {
		if (mot->loop == -1) {
			mot->count = 0;
		} else
		if (--mot->loop > 0) {
			mot->count = 0;
		} else mot->frame = 0;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CAMERA INITIALYZE                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void camera_init()
{
	cam.view.vpx = -2100;
	cam.view.vpy = -300;
	cam.view.vpz = 200;
	cam.view.vrx = 0;
	cam.view.vry = -100;
	cam.view.vrz = 0;
//	cam.view.rz = (-0 << 12);
	cam.view.super = WORLD;
	cam.mode = 0;
	cam.work = NULL;
	GsInitCoordinate2(WORLD, &cam.DView);	/* 視点を設定する座標系の初期化 */
//	cam.view.super = &cam.DView;
	Projection = 700;
	GsSetRefView2L((GsRVIEW2 *)&cam);
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CAMERA MOVE                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void camera_wait();
void camera_path1();
void camera_path2();
void camera_y_turn();
void camera_beam();

const task_a CameraTask[] = {
	camera_wait,
	camera_path1,
	camera_path2,
	camera_y_turn,
	camera_beam,
};

void camera_move()
{
	if (cam.work != NULL) {
		cam.view.vrx = *(long *)(cam.work)>>12;
		cam.view.vry = (*(long *)(cam.work+1)>>12) - 100;
		cam.view.vrz = *(long *)(cam.work+2)>>12;
	}
	CameraTask[cam.mode]();
	GsSetRefView2L((GsRVIEW2 *)&cam);
	GsSetProjection(Projection);	/* プロジェクション設定 */
}


void camera_wait()
{
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	二点間の移動	A |-|--|---|-----|-----|---|--|-| B
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void camera_path1()
{
	int rr;

	if (++cam.timer >= cam.totaltime) cam.mode = 0;
	rr = rsin((cam.timer * 1024) / cam.totaltime);
	cam.view.vpx = cam.start.vx + (((cam.terminal.vx - cam.start.vx) * rr) / 4096);
	cam.view.vpy = cam.start.vy + (((cam.terminal.vy - cam.start.vy) * rr) / 4096);
	cam.view.vpz = cam.start.vz + (((cam.terminal.vz - cam.start.vz) * rr) / 4096);
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	二点間の移動(Bezier補完)	A |-|--|---|-----B-----|---|--|-| C
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void setBezierCof(long cp0,long cp1,long cp2,long cp3,long *co)
{
	co[0] = -cp0 + 3*(cp1-cp2) + cp3;
	co[1] = 3*(cp0+cp2) - 6*cp1;
	co[2] = 3*(-cp0+cp1);
	co[3] = cp0;
}

void camera_path2()
{
	int i,rr;
	long v[XYZ];
	long co[3][4];

	if (++cam.timer > cam.totaltime) {
		if (cam.mode == 2) cam.mode = 0;
		return;
	}
	rr = rcos(((cam.totaltime - cam.timer) * 2048) / cam.totaltime) / 2 + 2048;
	setBezierCof(cam.start.vx, cam.relay.vx, cam.terminal.vx, cam.terminal.vx, co[0]);
	setBezierCof(cam.start.vy, cam.relay.vy, cam.terminal.vy, cam.terminal.vy, co[1]);
	setBezierCof(cam.start.vz, cam.relay.vz, cam.terminal.vz, cam.terminal.vz, co[2]);
	for(i=0;i<3;i++)
		v[i] = ((((((((co[i][0]*rr)>>12)+co[i][1])*rr)>>12)+co[i][2])*rr)>>12)+co[i][3];
	cam.view.vpx = v[X];
	cam.view.vpy = v[Y];
	cam.view.vpz = v[Z];
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	Ｙ軸をぐるぐる回る
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void camera_y_turn()
{
	struct {
		MATRIX m;
		VECTOR r;
		VECTOR	Trnsx;
		SVECTOR Svec;
	} *sc = (void *)getScratchAddr(0);

	SetTransMatrix(&GsWSMATRIX);
	SetRotMatrix(&GsWSMATRIX);
	cam.angle += 4;
	sc->m = GsIDMATRIX;
	RotMatrixY(cam.angle, &sc->m);
	sc->Svec.vx = cam.svec.vx;
	sc->Svec.vy = cam.svec.vy;
	sc->Svec.vz = cam.svec.vz;
	ApplyMatrix(&sc->m, &sc->Svec, &sc->r);
	cam.view.vpx = sc->r.vx + cam.view.vrx;
	cam.view.vpy = sc->r.vy + cam.view.vry;
	cam.view.vpz = sc->r.vz + cam.view.vrz;
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	ビームを追いかける
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void camera_beam()
{
	beam_pos();
	cam.view.vrx = pos[0].vx / 4096;
	cam.view.vry = pos[0].vy / 4096;
	cam.view.vrz = pos[0].vz / 4096;
	camera_path2();
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  LIGHTING INITIALYZE                                                      */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void light_init()
{
  /* ライトID０ 設定 */
  pslt[0].vx = 0; pslt[0].vy= 100; pslt[0].vz= 10;
  pslt[0].r=0x90; pslt[0].g=0x90; pslt[0].b=0x90;
  pslt[0].vx = 0; pslt[0].vy= 0; pslt[0].vz= 100;
  pslt[0].r=0xa0; pslt[0].g=0x40; pslt[0].b=0x20;
  GsSetFlatLight(0,&pslt[0]);
  
  /* ライトID１ 設定 */
  pslt[1].vx = -50; pslt[1].vy= 25; pslt[1].vz= -100;
  pslt[1].r=0x80; pslt[1].g=0x80; pslt[1].b=0x80;
  pslt[1].vx = 0; pslt[1].vy= 100; pslt[1].vz= -10;
  pslt[1].r=0x50; pslt[1].g=0x20; pslt[1].b=0x10;
  GsSetFlatLight(1,&pslt[1]);
  
  /* ライトID２ 設定 */
  pslt[2].vx = 50; pslt[2].vy= -25; pslt[2].vz= 100;
  pslt[2].r= 0x00; pslt[2].g= 0x00; pslt[2].b= 0x00;
  GsSetFlatLight(2,&pslt[2]);
  
  /* アンビエント設定 */
  GsSetAmbient(ONE/2,ONE/2,ONE/2);
  GsSetAmbient(0,0,0);

  /* 光源計算のデフォルトの方式設定 */
  GsSetLightMode(0);
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FOG INITIALYZE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void fog_init()
{
	GsFOGPARAM fog;

	GsSetLightMode(1);

	fog.dqa = -64000*64/Projection;
	fog.dqb = 0x1400000;
	fog.rfc = 0x40;
	fog.gfc = 0x40;
	fog.bfc = 0x40;

	GsSetFogParam(&fog);
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL INITIALYZE                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void model_init(long *tmd, MODEL *mod)
{
  int i;

  tmd++;			/* hedder skip */

  GsMapModelingData(tmd);	/* モデリングデータ（TMDフォーマット）を実アドレスにマップする*/

  tmd++;
  mod->Objnum = *tmd;		/* オブジェクト数をTMDのヘッダから得る */

  tmd++;			/* GsLinkObject4でリンクするためにTMDのオブジェクトの先頭にもってくる */

  /* TMDデータとオブジェクトハンドラを接続する */
  for( i = 0; i < mod->Objnum; i++)
    GsLinkObject4( (u_long)tmd, &mod->object[i], i);
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  COORDINATE INITIALYZE                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void coord_init(KAISOU *cls, MODEL *mod)
{
	GsDOBJ2 *objp;		/* モデリングデータハンドラ */
	int     i;

	for(i = 0, objp = mod->object; i < mod->Objnum; i++, objp++, cls++) {
		/* 座標の定義 */
		GsInitCoordinate2(WORLD,&mod->objpos[i]);

		/* デフォルトのオブジェクトの座標系の設定 */
		objp->coord2 =  &mod->objpos[cls->parts_no];
		objp->attribute = 0;
		if (cls->exist != EXIST) objp->attribute |= GsDOFF;

		/* マトリックス計算ワークのローテーションベクター初期化 */
		mod->objang[i].vx = cls->ang[X];
		mod->objang[i].vy = -cls->ang[Y];
		mod->objang[i].vz = -cls->ang[Z];

		/* 親座標のポインタ */
		if (cls->super != PARENT) mod->objpos[i].super = &mod->objpos[cls->super];

		mod->objpos[i].coord.t[0] = cls->pos[X];
		mod->objpos[i].coord.t[1] = cls->pos[Y];
		mod->objpos[i].coord.t[2] = cls->pos[Z];
#if 0
		mod->objscl[i].vx = cls->scl[X];
		mod->objscl[i].vy = cls->scl[Y];
		mod->objscl[i].vz = cls->scl[Z];
#endif
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  JUMP TABLE                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
extern _GsFCALL GsFCALL4;

extern PACKET *GsTMDfastF3L(),*GsTMDfastNF3();
extern PACKET *GsTMDfastG3L(),*GsTMDfastNG3();
extern PACKET *GsTMDfastTF3L(),*GsTMDfastTNF3();
extern PACKET *GsTMDfastTG3L(),*GsTMDfastTNG3();
extern PACKET *GsTMDfastF4L(),*GsTMDfastNF4();
extern PACKET *GsTMDfastG4L(),*GsTMDfastNG4();
extern PACKET *GsTMDfastTF4L(),*GsTMDfastTNF4();
extern PACKET *GsTMDfastTG4L(),*GsTMDfastTNG4();
extern PACKET *GsA4divF3L(),*GsA4divNF3();
extern PACKET *GsA4divG3L(),*GsA4divNG3();
extern PACKET *GsA4divTF3L(),*GsA4divTNF3();
extern PACKET *GsA4divTG3L(),*GsA4divTNG3();
extern PACKET *GsA4divF4L(),*GsA4divNF4();
extern PACKET *GsA4divG4L(),*GsA4divNG4();
extern PACKET *GsA4divTF4L(),*GsA4divTNF4();
extern PACKET *GsA4divTG4L(),*GsA4divTNG4();

void jt_init4()			/* Gs SortObject4J Fook Func */
{
#if 0
  PACKET *GsTMDfastF3NL(),*GsTMDfastF3LFG(),*GsTMDfastF3L(),*GsTMDfastNF3();
  PACKET *GsA4divF3NL(),*GsA4divF3LFG(),*GsA4divF3L(),*GsA4divNF3();
  PACKET *GsTMDfastG3NL(),*GsTMDfastG3LFG(),*GsTMDfastG3L(),*GsTMDfastNG3();
  PACKET *GsA4divG3NL(),*GsA4divG3LFG(),*GsA4divG3L(),*GsA4divNG3();
  PACKET *GsTMDfastTF3NL(),*GsTMDfastTF3LFG(),*GsTMDfastTF3L(),*GsTMDfastTNF3();
  PACKET *GsA4divTF3NL(),*GsA4divTF3LFG(),*GsA4divTF3L(),*GsA4divTNF3();
  PACKET *GsTMDfastTG3NL(),*GsTMDfastTG3LFG(),*GsTMDfastTG3L(),*GsTMDfastTNG3();
  PACKET *GsA4divTG3NL(),*GsA4divTG3LFG(),*GsA4divTG3L(),*GsA4divTNG3();
  PACKET *GsTMDfastF4NL(),*GsTMDfastF4LFG(),*GsTMDfastF4L(),*GsTMDfastNF4();
  PACKET *GsA4divF4NL(),*GsA4divF4LFG(),*GsA4divF4L(),*GsA4divNF4();
  PACKET *GsTMDfastG4NL(),*GsTMDfastG4LFG(),*GsTMDfastG4L(),*GsTMDfastNG4();
  PACKET *GsA4divG4NL(),*GsA4divG4LFG(),*GsA4divG4L(),*GsA4divNG4();
  PACKET *GsTMDfastTF4NL(),*GsTMDfastTF4LFG(),*GsTMDfastTF4L(),*GsTMDfastTNF4();
  PACKET *GsA4divTF4NL(),*GsA4divTF4LFG(),*GsA4divTF4L(),*GsA4divTNF4();
  PACKET *GsTMDfastTG4NL(),*GsTMDfastTG4LFG(),*GsTMDfastTG4L(),*GsTMDfastTNG4();
  PACKET *GsA4divTG4NL(),*GsA4divTG4LFG(),*GsA4divTG4L(),*GsA4divTNG4();
  PACKET *GsA4divTF4L();
#endif
  /* flat triangle */
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
//  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastF3LFG;
//  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastF3NL;
  GsFCALL4.f3[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divF3L;
//  GsFCALL4.f3[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divF3LFG;
//  GsFCALL4.f3[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divF3NL;
  GsFCALL4.nf3[GsDivMODE_NDIV]                = GsTMDfastNF3;
  GsFCALL4.nf3[GsDivMODE_DIV]                 = GsA4divNF3;
  /* gour triangle */
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastG3L;
//  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastG3LFG;
//  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastG3NL;
  GsFCALL4.g3[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divG3L;
//  GsFCALL4.g3[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divG3LFG;
//  GsFCALL4.g3[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divG3NL;
  GsFCALL4.ng3[GsDivMODE_NDIV]                = GsTMDfastNG3;
  GsFCALL4.ng3[GsDivMODE_DIV]                 = GsA4divNG3;
  /* texture flat triangle */
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
//  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastTF3LFG;
//  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastTF3NL;
  GsFCALL4.tf3[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divTF3L;
//  GsFCALL4.tf3[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divTF3LFG;
//  GsFCALL4.tf3[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divTF3NL;
  GsFCALL4.ntf3[GsDivMODE_NDIV]                = GsTMDfastTNF3;
  GsFCALL4.ntf3[GsDivMODE_DIV]                 = GsA4divTNF3;
  /* texture gour triangle */
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTG3L;
//  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastTG3LFG;
//  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastTG3NL;
  GsFCALL4.tg3[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divTG3L;
//  GsFCALL4.tg3[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divTG3LFG;
//  GsFCALL4.tg3[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divTG3NL;
  GsFCALL4.ntg3[GsDivMODE_NDIV]                = GsTMDfastTNG3;
  GsFCALL4.ntg3[GsDivMODE_DIV]                 = GsA4divTNG3;
  /* flat quad */
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
//  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastF4LFG;
//  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastF4NL;
  GsFCALL4.f4[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divF4L;
//  GsFCALL4.f4[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divF4LFG;
//  GsFCALL4.f4[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divF4NL;
  GsFCALL4.nf4[GsDivMODE_NDIV]                = GsTMDfastNF4;
  GsFCALL4.nf4[GsDivMODE_DIV]                 = GsA4divNF4;
  /* gour quad */
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastG4L;
//  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastG4LFG;
//  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastG4NL;
  GsFCALL4.g4[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divG4L;
//  GsFCALL4.g4[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divG4LFG;
//  GsFCALL4.g4[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divG4NL;
  GsFCALL4.ng4[GsDivMODE_NDIV]                = GsTMDfastNG4;
  GsFCALL4.ng4[GsDivMODE_DIV]                 = GsA4divNG4;
  /* texture flat quad */
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
//  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastTF4LFG;
//  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastTF4NL;
  GsFCALL4.tf4[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divTF4L;
//  GsFCALL4.tf4[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divTF4LFG;
//  GsFCALL4.tf4[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divTF4NL;
  GsFCALL4.ntf4[GsDivMODE_NDIV]                = GsTMDfastTNF4;
  GsFCALL4.ntf4[GsDivMODE_DIV]                 = GsA4divTNF4;
  /* texture gour quad */
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTG4L;
//  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_FOG]    = GsTMDfastTG4LFG;
//  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_LOFF]   = GsTMDfastTG4NL;
  GsFCALL4.tg4[GsDivMODE_DIV][GsLMODE_NORMAL]  = GsA4divTG4L;
//  GsFCALL4.tg4[GsDivMODE_DIV][GsLMODE_FOG]     = GsA4divTG4LFG;
//  GsFCALL4.tg4[GsDivMODE_DIV][GsLMODE_LOFF]    = GsA4divTG4NL;
  GsFCALL4.ntg4[GsDivMODE_NDIV]                = GsTMDfastTNG4;
  GsFCALL4.ntg4[GsDivMODE_DIV]                 = GsA4divTNG4;

	reflect = 128;
}

extern PACKET *SurmapG3NL(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG4NL(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapGT3NL(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapGT4NL(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_smnlset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3NL;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT3NL;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4NL;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT4NL;
}

extern PACKET *SurmapG3L(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG4L(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapGT3L(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapGT4L(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_smlset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3L;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT3L;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4L;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT4L;
}

//extern PACKET *SurmapGT3SPL(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
//extern PACKET *SurmapGT4SPL(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG3SPL2(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG4SPL2(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_smsplset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT3L;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3SPL2;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4SPL2;
}

extern PACKET *SurmapG3SPL3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG4SPL3(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_smsp3lset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT3L;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3SPL3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4SPL3;
}

extern PACKET *SurmapG3SPL4(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapG4SPL4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_smsp4lset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT3L;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapGT4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3SPL4;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4SPL4;
}

extern PACKET *WireF3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireF4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireG3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireG4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireFT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireFT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireGT3(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *WireGT4(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_wireset()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireF3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireFT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireF4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireFT4;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireG3;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireGT3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireG4;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = WireGT4;
}

extern PACKET *ColorF3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorF4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorG3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorG4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorFT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorFT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorGT3(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorGT4(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_colorset()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorF3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorFT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorF4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorFT4;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorG3;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorGT3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorG4;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorGT4;
}

extern PACKET *ColorCF3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorCF4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapCG3L(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapCG4L(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorCFT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *ColorCFT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapCGT3L(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *SurmapCGT4L(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_colorcset()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorCF3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorCFT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorCF4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = ColorCFT4;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapCG3L;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapCGT3L;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapCG4L;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapCGT4L;
}

extern PACKET *TPageF3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageF4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageFT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageFT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageNF3(TMD_P_NF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageNF4(TMD_P_NF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageNFT3(TMD_P_TNF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *TPageNFT4(TMD_P_TNF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_tpageset()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = TPageF3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = TPageFT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = TPageF4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = TPageFT4;
#if 1
  GsFCALL4.nf3[GsDivMODE_NDIV] = TPageNF3;
  GsFCALL4.ntf3[GsDivMODE_NDIV] = TPageNFT3;
  GsFCALL4.nf4[GsDivMODE_NDIV] = TPageNF4;
  GsFCALL4.ntf4[GsDivMODE_NDIV] = TPageNFT4;
#endif
}

extern PACKET *OpticsF3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsF4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsFT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsFT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsG3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsG4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsGT3(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *OpticsGT4(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_opticsset()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsF3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsFT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsF4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsFT4;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsG3;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsGT3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsG4;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = OpticsGT4;
}

extern PACKET *Wire2F3(TMD_P_F3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2F4(TMD_P_F4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2G3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2G4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2FT3(TMD_P_TF3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2FT4(TMD_P_TF4*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2GT3(TMD_P_TG3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *Wire2GT4(TMD_P_TG4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_wire2set()			/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2F3;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2FT3;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2F4;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2FT4;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2G3;
  GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2GT3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2G4;
  GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_NORMAL] = Wire2GT4;
}

extern PACKET *GlassG3(TMD_P_G3*, VERT*, VERT*, PACKET*, int, int, GsOT*);
extern PACKET *GlassG4(TMD_P_G4*, VERT*, VERT*, PACKET*, int, int, GsOT*);

void jt_glassset()		/* Gs SortObject4J Fook Func */
{
  GsFCALL4.f3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF3L;
  GsFCALL4.tf3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF3L;
  GsFCALL4.f4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastF4L;
  GsFCALL4.tf4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GsTMDfastTF4L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG3L;
  GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_NORMAL] = GlassG3;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = SurmapG4L;
  GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_NORMAL] = GlassG4;
}

