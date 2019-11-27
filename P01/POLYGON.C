/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON TEST                                             */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : POLYGON.C                                                */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <sys/file.h>
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
#include "../lib/fade.h"
#include "../lib/polygon.h"
#include "../sprite/sprite.h"
#include "../p01/pinit.h"
#include "../p01/poly_sub.h"
#include "../p01/battle.h"
#include "../p01/bg.h"
#include "../p01/anmdata.h"
#include "../redlib/sndno.h"
#include "../redlib/xano.h"

#ifndef PREPRE
#define DEBUG_ 1	// 画面キャプチャー
#endif

/*----- Local Works           -----*/
u_char		SubStatus = 0;
char		pause_flag = 0;
long		LocalTimer = 0;
long		texture_num;
long		bgm_no;
SPRWORK		*name[2];
int			XA_Status;

/*----- Local Difinitions     -----*/
int PolygonInit();
int PolygonMain();
int ScreenCrush();
int VsTester();
//int ModelSeInit2();
//int ModelSelect2();

PRCS_TBL polygon_tbl[] =
{
	{ PolygonInit },
	{ ScreenCrush },
	{ ScreenCrush },
	{ Battle },
	{ PolygonMain },
	{ VsTester },
//	{ ModelSeInit2 },
//	{ ModelSelect2 },
};


extern CzAnimData *SequenceTbl[];

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  POLYGON TEST TASK                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int Polygon()
{
	int vcount;

#ifdef DEBUG_
	if ( FioGetMachine() == FIO_MC_DEV ) {
		/* 画面キャプチャー */
		if ((PadDat[1].trg & PADRL)>0) {
			RECT rect;
			long fd;
			char filename[32];

			static long tim_header[] = {
				0x00000010,
				0x00000002,
				320 * 240 * 2 + 12,
				0x00000000,
				0x00f00140,
			};
			static int tim_no = 0;

			if ( !PSDIDX ) {
				setRECT(&rect, 0, 0, 320, 240);
				StoreImage(&rect, (u_long *)0x80600000);
			}
			else {
				setRECT(&rect, 0, 240, 320, 240);
				StoreImage(&rect, (u_long *)0x80600000);
			}

			DrawSync( 0 );

			sprintf(filename, "sim:timdata\\scn%04d.tim", tim_no);
			if ( (fd = open(filename, O_WRONLY|O_CREAT)) == -1 ) {
				printf("can't open file\n");
			}
			else {
				write(fd, (void *)tim_header, sizeof( tim_header));
				write(fd, (void *)0x80600000, 320 * 240 * 2);
				close( fd );
				fd = open("sim:bmp\\bmp.bmp", O_WRONLY|O_CREAT);
				write(fd, (void *)0x80600000, 320 * 240 * 2);
				close( fd );
				tim_no++;
				printf("captured %s\n", filename);
			}
		}
	}
#endif

#if 0
#ifndef PREPRE
	if ((gcb.ClearMode == 0) || (pause_flag)) {
		if ((pcb.pno != PRCS_01) && (SubStatus == 3) && ((PadDat[0].trg & PADST)>0)) {
			if (BattleStatus != _command) {
				pause_flag ^= 1;
				SE_ENT(SE_PAUSE);
			}
		}
		if (((PadDat[0].trg & PADm)==0) && (pause_flag)) {
			gcb.ClearMode = 3;
			return( 0 );
		} else gcb.ClearMode = 0;
	}
#endif
#endif

	LocalTimer++;

	GsClearOt( 0, 0, &spriteot[ PSDIDX ] );
	GsSortOt( &spriteot[ PSDIDX ], &ot[ PSDIDX ]);
	if (SubStatus >= 3) {
		GsClearOt( 0, (1<<OT_LENGTH) - (1<<BGOT_LENGTH), &bgot[ PSDIDX ] );
		GsSortOt( &bgot[ PSDIDX ], &ot[ PSDIDX ] );
		if (XA_Status == 0) {
			XA_Status = XA_SYNC();
		} else XA_CLR();
	}

	polygon_tbl[ SubStatus ].func();

	vcount = VSync(1);
	SpriteControll();
	Sprite3dControll();
	EffectControll();
	PolyefeControll();

	FntPrint("spr=%d 3dsp=%d efe=%d mod=%d\n", SpriteCounter, Sprite3dCounter, EffectCounter, PolyefeCounter);
	FntPrint("Load = %d\n",VSync(1)-vcount);
	FntPrint("packet = %d%%\n",(((GsOUT_PACKET_P - packet[ PSDIDX ]) / 24) * 100) / PACKETMAX);

   return( 0 );
};


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  POLYGON TEST INIT                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int PolygonInit()
{
	SetDefDrawEnv(&env[0], 0, 240, 320, 240);
	SetDefDrawEnv(&env[1], 0,   0, 320, 240);

	XA_CLR();
	DATA_CLOSE(1);
	SOUND_I();
	SE_LOAD(0);

	camera_init();
	light_init();
	jt_init4();
	SpriteInit((CzAnimData *) SequenceTbl);
	if (pcb.pno == PRCS_02) gcb.bg_no = 4;	// テストＢＧ
	bg_init();

	FioReadFile((Uint8 *) "DT\\EFE.LZ", (Uint8 *) LOAD_ADDR);
	LzDecInit( (u_char *) LOAD_ADDR, (u_char *) EFMODEL_ADDR, 0);
	LzDecB();
	FioReadFile2((Uint8 *) "DT\\BATTLE.TEX", (Uint8 *) LOAD_ADDR);
	texture_num = 0;
	if (gcb.bg_no == 8) texture_num++;	// 葉っぱ飛ばす

	pp = player;
	ep = player + 1;

	/* キャラナンバー */
	if (pcb.pno == PRCS_02) {	// テスト
		pp->chrno = MODEL_JP;
		ep->chrno = MODEL_JP;
		pp->lv = 60;
		ep->lv = 50;
		pp->hp =
		ep->hp =
		pp->dp =
		ep->dp =
		pp->hpmax =
		ep->hpmax =
		pp->dpmax =
		ep->dpmax = 2000;
		pp->aura = 50;
		ep->aura = 0;
		pp->attack = 500;
		ep->attack = 500;
		pp->deffence = 20;
		ep->deffence = 20;
		pp->hitrate = 120;
		ep->hitrate = 120;
		pp->evasion = 50;
		ep->evasion = 50;
		pp->crank = 4;
		ep->crank = 4;
		pp->arank = 2;
		ep->arank = 1;
	} else {
		pp->chrno = gcb.chrno[0];
		pp->lv = gcb.lv[0];
		pp->hp = gcb.hp[0];
		pp->dp = gcb.dp[0];
		pp->hpmax = gcb.hpmax[0];
		pp->dpmax = gcb.dpmax[0];
		pp->aura = gcb.ap[0];
		pp->attack = gcb.at[0];
		pp->deffence = gcb.df[0];
		pp->hitrate = gcb.hrate[0];
		pp->evasion = gcb.erate[0];
		pp->crank = gcb.crank[0];
		pp->arank = gcb.arank[0];
		ep->chrno = gcb.chrno[1];
		ep->lv = gcb.lv[1];
		ep->hp = gcb.hp[1];
		ep->dp = gcb.dp[1];
		ep->hpmax = gcb.hpmax[1];
		ep->dpmax = gcb.dpmax[1];
		ep->aura = gcb.ap[1];
		ep->attack = gcb.at[1];
		ep->deffence = gcb.df[1];
		ep->hitrate = gcb.hrate[1];
		ep->evasion = gcb.erate[1];
		ep->crank = gcb.crank[1];
		ep->arank = gcb.arank[1];
	}

	pp->mod = &model[0];
	pp->mot = &motion[0];
	pp->mot->bufp = motbuf[0];
	pp->motd = (char *) PLAYER1_ADDR;
	pp->buf = (P_BUFF *) MODEL1_ADDR;
	ep->mod = &model[1];
	ep->mot = &motion[1];
	ep->mot->bufp = motbuf[1];
	ep->motd = (char *) PLAYER2_ADDR;
	ep->buf = (P_BUFF *) MODEL2_ADDR;

	pp->mod->pos[X] = pp->mod->pos[Y] = pp->mod->pos[Z] = 0;
	ep->mod->pos[X] = ep->mod->pos[Y] = ep->mod->pos[Z] = 0;

	pp->mod->pos[X] = toFIXED(1300);
	pp->mod->ang[Y] = 1024;
	ep->mod->pos[X] = toFIXED(-1300);
	ep->mod->ang[Y] = -1024;

	pp->hpdisp =
	pp->dpdisp =
	pp->apdisp =
	ep->hpdisp =
	ep->dpdisp =
	ep->apdisp = 0;
	if (pp->aura >= 100) pp->hyper = 1;
	else pp->hyper = 0;
	if (ep->aura >= 100) ep->hyper = 1;
	else ep->hyper = 0;

	LightPos[X] = 0;
	LightPos[Y] = 0;
	LightPos[Z] = 0;
	pslt[2].r = 0x00; pslt[2].g = 0x00; pslt[2].b = 0x00;

	get_parts_ws_val(&pp->mod->objpos[1], NULL, NULL, &pos[0]);
	get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[1]);
	cam.view.vrx = (pos[0].vx - ((pos[0].vx - pos[1].vx) / 2)) / 4096;
	cam.view.vry = (pos[0].vy - ((pos[0].vy - pos[1].vy) / 2)) / 4096;
	cam.view.vrz = (pos[0].vz - ((pos[0].vz - pos[1].vz) / 2)) / 4096;

	pcb.dbg = 0;
	gcb.ClearMode = 3;
	bg_col[R] = bg_col[G] = bg_col[B] = 0x00;
	DemoPlayTimer = 0;
	SubStatus++;

   return( 0 );
};


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TEXTURE INIT                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/* テクスチャデータをVRAMにロードする */
void texture_init(addr)
u_long addr;
{
  RECT rect1;
  GsIMAGE tim1;

  /* TIMデータのヘッダからテクスチャのデータタイプの情報を得る */  
  GsGetTimInfo((u_long *)(addr+4),&tim1);
  
  rect1.x=tim1.px;		/* テクスチャ左上のVRAMでのX座標 */
  rect1.y=tim1.py;		/* テクスチャ左上のVRAMでのY座標 */
  rect1.w=tim1.pw;		/* テクスチャ幅 */
  rect1.h=tim1.ph;		/* テクスチャ高さ */
  
  /* VRAMにテクスチャをロードする */
  LoadImage(&rect1,tim1.pixel);
  
  /* カラールックアップテーブルが存在する */  
  if((tim1.pmode>>3)&0x01)
    {
      rect1.x=tim1.cx;		/* クラット左上のVRAMでのX座標 */
      rect1.y=tim1.cy;		/* クラット左上のVRAMでのY座標 */
      rect1.w=tim1.cw;		/* クラットの幅 */
      rect1.h=tim1.ch;		/* クラットの高さ */

      /* VRAMにクラットをロードする */
      LoadImage(&rect1,tim1.clut);
    }
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  POLYGON TEST MAIN                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int PolygonMain()
{
#ifndef PREPRE
	int i;
	int vcount;
	VECTOR vec;
	SVECTOR avec;
	CVECTOR cvec;
	GsCOORDINATE2 coord;

	vcount = VSync(1);

	jt_init4();

	obj_interactive();

	for (i = 0; i < 3; i++) {
		if (eflt[i] >= 0x600) eflt[i] -= 0x600;
		else if (eflt[i] <= -0x600) eflt[i] += 0x600;
		else eflt[i] = 0;
	}
	get_parts_ws_val(&player[0].mod->objpos[1], NULL, NULL, &pos[0]);
	get_parts_ws_val(&player[1].mod->objpos[1], NULL, NULL, &pos[1]);
	cam.view.vrx = (pos[0].vx - ((pos[0].vx - pos[1].vx) / 2)) / 4096;
	cam.view.vry = (pos[0].vy - ((pos[0].vy - pos[1].vy) / 2)) / 4096;
	cam.view.vrz = (pos[0].vz - ((pos[0].vz - pos[1].vz) / 2)) / 4096;
    camera_move();

	FntPrint("Load = %d\n",VSync(1)-vcount);
	vcount = VSync(1);

	/* エフェクト反射テスト */
	if((PadDat[1].trg & PADRR)>0) {
		player[0].render = jt_opticsset;					/* 光学迷彩の登録 */
//		pslt[0].r += 0x10;
//		pslt[1].r += 0x10;
//		pslt[2].r = 0xff;
#if 0
		trans.vx = 0;
		trans.vy = -60;
		trans.vz = -140;
		get_parts_ws_val(&player[0].mod->objpos[2], &trans, NULL, &vec);
		LightPos[X] = vec.vx >> 12;
		LightPos[Y] = vec.vy >> 12;
		LightPos[Z] = vec.vz >> 12;
		Sprite3dEntry( 1, (511 << 6), 1, &vec);
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 2; i++) {
			EffectEntry(4, &vec, NULL, &cvec );		// 集中線
		}
#endif

		PushMatrix();
		GsInitCoordinate2(WORLD,&coord);
		avec.vx = player[0].mod->ang[X];
		avec.vy = player[0].mod->ang[Y];
		avec.vz = player[0].mod->ang[Z];
		RotMatrixYXZ_gte(&avec, &coord.coord);
		SetRotMatrix(&coord.coord);
		vec.vx = 0;
		vec.vy = (-200 << 12);
		vec.vz = (-700 << 12);
		ApplyRotMatrixLV(&vec, &trans);
		pos[0].vx = player[0].mod->pos[X] + trans.vx;
		pos[0].vy = player[0].mod->pos[Y] + trans.vy;
		pos[0].vz = player[0].mod->pos[Z] + trans.vz;
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 15; i++) {
			avec.vx = ((rand() << 20) >> 23) + ((rand() & 512) * 3) + 2304 + player[0].mod->ang[X];
			avec.vy = player[0].mod->ang[Y];
			avec.vz = ((rand() << 20) >> 21) + player[0].mod->ang[Z];
//			EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
		}
		cvec.r = 0;
		cvec.g = 1;
		cvec.b = 1;
		avec.vx = player[0].mod->ang[X];
		avec.vy = player[0].mod->ang[Y];
		avec.vz = player[0].mod->ang[Z];
//			EffectEntry(27, &pos[0], &avec, &cvec);					// 破片
		if ((gcb.GlobalTimer & 0x01) == 0) {
//			EffectEntry(8, &pos[0], &player[0].mod->ang[X], NULL);		// ＡＴフィールド
		}

#if 1
		GsInitCoordinate2(WORLD,&coord);
		avec.vx = player[0].mod->ang[X];
		avec.vy = player[0].mod->ang[Y];
		avec.vz = player[0].mod->ang[Z];
		RotMatrixYXZ_gte(&avec, &coord.coord);
		SetRotMatrix(&coord.coord);
		vec.vx = 0;
		vec.vy = (-100 << 12);
		vec.vz = -player[0].length;
		ApplyRotMatrixLV(&vec, &trans);
		pos[0].vx = player[0].mod->pos[X] + trans.vx;
		pos[0].vy = player[0].mod->pos[Y] + trans.vy;
		pos[0].vz = player[0].mod->pos[Z] + trans.vz;
		pp_distance = 4096;
		avec.vx = -1024;
		avec.vy = 0;
		avec.vz = -player[0].mod->ang[Y];
		PolyefeEntry( 3, 2, &pos[0], &avec);
#endif

#if 0
		if ((gcb.GlobalTimer & 0x03) == 0) {
			get_parts_ws_val(&player[0].mod->objpos[7], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&player[0].mod->objpos[11], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&player[0].mod->objpos[16], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&player[0].mod->objpos[20], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&player[0].mod->objpos[24], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&player[0].mod->objpos[28], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
		}
#endif
		PopMatrix();

//		Sprite3dEntry( 3, (510 << 6), 7, &vec);
	}
	if((PadDat[1].dat & PADRU)>0) {
		pslt[0].g += 0x10;
		pslt[1].g += 0x10;
		pslt[2].g = 0xff;
		player[0].render =
		player[1].render = jt_wire2set;	// ワイヤーフレーム処理登録
	}
	model_col[R] =
	model_col[B] = 0;
	model_col[G] = (gcb.GlobalTimer << 1) & 0x7f;
	if (model_col[G] >= 0x40) model_col[G] = 0x80 - model_col[G];
#if 1
		zp = *(((Z_POS **) zpos) + player[0].chrno);
		cvec.r = 1;
		cvec.g = 1;
		cvec.b = 0;
		if((PadDat[1].dat & PADRR)>0) {
			if((PadDat[1].trg & PADLL)>0) zp->ofs1.vx += 10;
			if((PadDat[1].trg & PADLR)>0) zp->ofs1.vx -= 10;
			if((PadDat[1].trg & PADLD)>0) zp->ofs1.vy += 10;
			if((PadDat[1].trg & PADLU)>0) zp->ofs1.vy -= 10;
			if((PadDat[1].trg & PADL1)>0) zp->ofs1.vz -= 10;
			if((PadDat[1].trg & PADL2)>0) zp->ofs1.vz += 10;
		} else {
			if((PadDat[1].trg & PADLL)>0) zp->ofs0.vx += 10;
			if((PadDat[1].trg & PADLR)>0) zp->ofs0.vx -= 10;
			if((PadDat[1].trg & PADLD)>0) zp->ofs0.vy += 10;
			if((PadDat[1].trg & PADLU)>0) zp->ofs0.vy -= 10;
			if((PadDat[1].trg & PADL1)>0) zp->ofs0.vz -= 10;
			if((PadDat[1].trg & PADL2)>0) zp->ofs0.vz += 10;
		}
		FntPrint("ofs0 = %d %d %d\n",zp->ofs0.vx,zp->ofs0.vy,zp->ofs0.vz);
		FntPrint("ofs1 = %d %d %d\n",zp->ofs1.vx,zp->ofs1.vy,zp->ofs1.vz);
		for (i = 0; i < player[0].hitpos; i++, zp++) {
			get_parts_ws_val(&player[0].mod->objpos[zp->no], &zp->ofs0, NULL, &pos[i]);
			get_parts_ws_val(&player[0].mod->objpos[zp->no], &zp->ofs1, NULL, &trans);
			zanzo_entry( i, &pos[i], &trans, &cvec);
		}
#endif
	if((PadDat[1].dat & PADRD)>0) {
#if 0
//		if((PadDat[1].trg & PADRD)>0) {
			pos[0].vx = player[0].mod->pos[X];
			pos[0].vy = player[0].mod->pos[Y];
			pos[0].vz = player[0].mod->pos[Z];
			cvec.r = 0;
			cvec.g = 1;
			cvec.b = 0;
			avec.vx = player[0].mod->ang[X] - 1024;
			avec.vy = player[0].mod->ang[Y];
			avec.vz = player[0].mod->ang[Z];
			EffectEntry_R(10, &pos[0], &avec, &cvec, (EFEWORK *) efe+EFFECTMAX-1);	// サンダー
//		}
#endif
#if 0
			if ((gcb.GlobalTimer & 0x03) == 0) {
				pos[0].vx = player[0].mod->pos[X];
				pos[0].vy = player[0].mod->pos[Y];
				pos[0].vz = player[0].mod->pos[Z];
				cvec.r = 0;
				cvec.g = 0;
				cvec.b = 0;
				avec.vx = (rand() << 20) >> 20;
				avec.vy = (rand() << 20) >> 20;
				avec.vz = (rand() << 20) >> 20;
				EffectEntry(25, &pos[0], &avec, &cvec);						// 円形エフェクト
			}
	} else {
		zanzo_first[0] = 0;
		zanzo_first[1] = 0;
		zanzo_first[2] = 0;
		zanzo_first[3] = 0;
#endif
	}
//	GsSetFlatLight(0,&pslt[0]);
//	GsSetFlatLight(1,&pslt[1]);


#if 0
	if((PadDat[1].dat & PADRL)>0) {
		vec.vx = player[0].mod->pos[X];
		vec.vy = player[0].mod->pos[Y];
		vec.vz = player[0].mod->pos[Z];
		for (i = 0; i < 4; i++) Sprite3dEntry( 2, (511 << 6), 110, &vec);
	}
#endif
	for (i = 0, pp = player; i < 2; i++, pp++) {
		if(pp->mot->frame == 0) {
			if (pp->mot->num == 1) motion_init( pp->motd, pp->mot, 2, -1 );
			else if (pp->mot->num ==  3) motion_init( pp->motd, pp->mot, 4,  1 );
			else if (pp->mot->num ==  5) motion_init( pp->motd, pp->mot, 6,  1 );
			else if (pp->mot->num ==  7) motion_init( pp->motd, pp->mot, 8,  1 );
			else if (pp->mot->num ==  8) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 10) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 12) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 14) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 16) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 24) motion_init( pp->motd, pp->mot, 0, -1 );
			else if (pp->mot->num == 26) motion_init( pp->motd, pp->mot,27, -1 );
		}
		if (pp->mot->frame) motion_test( pp->mod, pp->mot );
		pslt[2].vx = (pp->mod->pos[X] >> 12) - LightPos[X];
		pslt[2].vy = (pp->mod->pos[Y] >> 12) - LightPos[Y];
		pslt[2].vz = (pp->mod->pos[Z] >> 12) - LightPos[Z];
		GsSetFlatLight(2,&pslt[2]);
		{
			MATRIX m;

			ReadColorMatrix(&m);
			m.m[R][2] = eflt[R];
			m.m[G][2] = eflt[G];
			m.m[B][2] = eflt[B];
			SetColorMatrix(&m);
		}
		pp->render();
		model_sort( pp->mod, pp->reflect );
		kage_set( pp->mod , &bgot[ PSDIDX ]);
		if (pp->ap > pp->apmax) pp->ap = 0;
		if (pp->ap < pp->apdisp) pp->apdisp += (((pp->ap - pp->apdisp) / 4) - 1);
		if (pp->ap > pp->apdisp) pp->apdisp += (((pp->ap - pp->apdisp) / 4) + 1);
		{
			int j, flag;
			short chrno;

			for (j = 0; j < 2; j++) {
				sprite[i * 10 + 8 + j].chr = fix_ofs + 14 + ((pp->lv / keta4[j + 2]) % 10);
			}
			for (j = 0, flag = 0; j < 4; j++) {
				chrno = ((pp->hpdisp / keta4[j]) % 10);
				if ((chrno == 0) && (flag == 0)) chrno = 10;
				else flag = 1;
				sprite[i * 10 + j].chr = fix_ofs + 3 + chrno;
			}
			for (j = 0, flag = 0; j < 4; j++) {
				chrno = ((pp->dpdisp / keta4[j]) % 10);
				if ((chrno == 0) && (flag == 0)) chrno = 10;
				else flag = 1;
				sprite[i * 10 + 4 + j].chr = fix_ofs + 3 + chrno;
			}
		}
		if (sprite[22].vzoomsp == 0)
		{
			long ll;
			POL4 pol4;

			if (pp->hp > pp->hpmax) pp->hp = 0;
			if (pp->dp > pp->dpmax) pp->dp = 0;
			if (pp->hp < pp->hpdisp) pp->hpdisp += (((pp->hp - pp->hpdisp) / 4) - 1);
			if (pp->hp > pp->hpdisp) pp->hpdisp += (((pp->hp - pp->hpdisp) / 4) + 1);
			if (pp->dp < pp->dpdisp) pp->dpdisp += (((pp->dp - pp->dpdisp) / 4) - 1);
			if (pp->dp > pp->dpdisp) pp->dpdisp += (((pp->dp - pp->dpdisp) / 4) + 1);

			pol4.code = 0x38;
			ll = ((pp->hpdisp % (pp->hpmax + 1)) * 55) / pp->hpmax;
			pol4.sxy[0][X] =
			pol4.sxy[2][X] = 47 - 160 + i * 160;
			pol4.sxy[1][X] =
			pol4.sxy[3][X] = 47 - 160 + i * 160 + ll;
			pol4.sxy[0][Y] =
			pol4.sxy[1][Y] = 30 - 120;
			pol4.sxy[2][Y] =
			pol4.sxy[3][Y] = 38 - 120;
			pol4.sz[0][0] = (1 << SPRITEOT_LENGTH) - 1;
			pol4.rgb[0][R] =
			pol4.rgb[1][R] =
			pol4.rgb[2][R] =
			pol4.rgb[3][R] = 0x00;
			pol4.rgb[0][G] =
			pol4.rgb[1][G] = 0xf0;
			pol4.rgb[2][G] =
			pol4.rgb[3][G] = 0x40;
			pol4.rgb[0][B] =
			pol4.rgb[1][B] =
			pol4.rgb[2][B] =
			pol4.rgb[3][B] = 0x00;
			Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &spriteot[ PSDIDX ]);

			pol4.code = 0x38;
			ll = ((pp->dpdisp % (pp->dpmax + 1)) * 55) / pp->dpmax;
			pol4.sxy[0][X] =
			pol4.sxy[2][X] = 47 - 160 + i * 160;
			pol4.sxy[1][X] =
			pol4.sxy[3][X] = 47 - 160 + i * 160 + ll;
			pol4.sxy[0][Y] =
			pol4.sxy[1][Y] = 42 - 120;
			pol4.sxy[2][Y] =
			pol4.sxy[3][Y] = 50 - 120;
			pol4.sz[0][0] = (1 << SPRITEOT_LENGTH) - 1;
			pol4.rgb[0][R] =
			pol4.rgb[1][R] =
			pol4.rgb[2][R] =
			pol4.rgb[3][R] = 0x00;
			pol4.rgb[0][G] =
			pol4.rgb[1][G] =
			pol4.rgb[2][G] =
			pol4.rgb[3][G] = 0x00;
			pol4.rgb[0][B] =
			pol4.rgb[1][B] = 0xf0;
			pol4.rgb[2][B] =
			pol4.rgb[3][B] = 0x40;
			Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &spriteot[ PSDIDX ]);
		}
		FntPrint("Load = %d\n",VSync(1)-vcount);
		vcount = VSync(1);
	}
#if 0
			if (sprite[28].spd[Y] == 0) {
				pol4.code = 0x38;
				ll = ((pp->apdisp % (pp->apmax + 1)) * 174) / pp->apmax;
				pol4.sxy[0][X] =
				pol4.sxy[2][X] = 73 - 160;
				pol4.sxy[1][X] =
				pol4.sxy[3][X] = 73 - 160 + ll;
				pol4.sxy[0][Y] =
				pol4.sxy[1][Y] = 185 - 120;
				pol4.sxy[2][Y] =
				pol4.sxy[3][Y] = 195 - 120;
				pol4.sz[0][0] = (1 << SPRITEOT_LENGTH) - 1;
				pol4.rgb[0][R] =
				pol4.rgb[1][R] = 0xf0;
				pol4.rgb[2][R] =
				pol4.rgb[3][R] = 0x40;
				pol4.rgb[0][G] =
				pol4.rgb[1][G] =
				pol4.rgb[2][G] =
				pol4.rgb[3][G] = 0x00;
				pol4.rgb[0][B] =
				pol4.rgb[1][B] =
				pol4.rgb[2][B] =
				pol4.rgb[3][B] = 0x00;
				Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &spriteot[ PSDIDX ]);
			}
#endif

	jt_init4();

	pslt[2].r = 0x00; pslt[2].g = 0x00; pslt[2].b = 0x00;
	GsSetFlatLight(2,&pslt[2]);
	if (gcb.ClearMode == 0) bg_main();

	FntPrint("Load = %d\n",VSync(1)-vcount);
	vcount = VSync(1);

#if 0
	if ((gcb.GlobalTimer & 0x07) == 0) {
		vec.vx = ((rand() % 5000) - 2500) << 12;
		vec.vy = -2000 << 12;
		vec.vz = ((rand() % 5000) - 2500) << 12;
		EffectEntry(2, &vec, NULL, NULL);		// さくら
	}
#endif

#if 0
	for (i = 0; i < 8; i++) {
		pos[0].vx = ((rand() % 4000) - 2000) << 12;
		pos[0].vy = -1200 << 12;
		pos[0].vz = ((rand() % 4000) - 2000) << 12;
		avec.vx = ((rand() << 20) >> 24);
		avec.vy = 0;
		avec.vz = ((rand() << 20) >> 24);
		EffectEntry(7, &pos[0], &avec, NULL);		// 雨
	}
#endif

#endif
   return( 0 );
};


#ifndef PREPRE
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  OBJECT/CAMERA MOVE                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
const char *mode_mes[] = {
	"PLAYER 1",
	"PLAYER 2",
	"CAMERA",
};

const char *att_name[] = {
	"CENTER",
	"PLAYER1",
	"PLAYER2",
};

int obj_interactive()
{
static int move_mode, model_no, attention_pos;
	int p_no;

  if((PadDat[0].trg & PADST)>0) move_mode = ((move_mode + 1) % 3);
  p_no = move_mode;

  FntPrint(">%s<\n", mode_mes[move_mode]);
	switch(move_mode) {
		case 0:
		case 1:
		  /* モデルセレクタ */
		  if((PadDat[1].trg & PADl)>0) {
			if (++model_no == MODEL_MAX) model_no = 0;
		  } else
		  if((PadDat[1].trg & PADm)>0) {
			if (--model_no < 0) model_no = MODEL_MAX - 1;
		  } else
		  if((PadDat[1].trg & PADSL)>0) {
			player[p_no].chrno = model_no;
			player_init(p_no, &player[p_no]);
			motion_init( player[p_no].motd, player[p_no].mot, 0, -1 );	// 仮
		  }
		  if (player[p_no].chrno == model_no)  FntPrint("*",0);
		  else FntPrint(" ",0);
		  FntPrint("%s\n", model_name[model_no]);

		  /* オブジェクトをY軸回転させる */
		  if((PadDat[0].dat & PADRright)>0) player[p_no].mod->ang[Y] -=64;

		  /* オブジェクトをY軸回転させる */
		  if((PadDat[0].dat & PADRleft)>0) player[p_no].mod->ang[Y] +=64;

		  /* オブジェクトをX軸回転させる */
		  if((PadDat[0].dat & PADRup)>0) player[p_no].mod->ang[X] +=64;

		  /* オブジェクトをX軸回転させる */
		  if((PadDat[0].dat & PADRdown)>0) player[p_no].mod->ang[X] -=64;

		  /* オブジェクトをZ軸にそって動かす */
		  if((PadDat[0].dat & PADm)>0) player[p_no].mod->pos[Z] -=toFIXED(50);

		  /* オブジェクトをZ軸にそって動かす */
		  if((PadDat[0].dat & PADl)>0) player[p_no].mod->pos[Z] +=toFIXED(50);

		  /* オブジェクトをX軸にそって動かす */
		  if((PadDat[0].dat & PADLleft)>0) player[p_no].mod->pos[X] +=toFIXED(20);

		  /* オブジェクトをX軸にそって動かす */
		  if((PadDat[0].dat & PADLright)>0) player[p_no].mod->pos[X] -=toFIXED(20);

		  /* オブジェクトをY軸にそって動かす */
		  if((PadDat[0].dat & PADLdown)>0) player[p_no].mod->pos[Y]+=toFIXED(20);

		  /* オブジェクトをY軸にそって動かす */
		  if((PadDat[0].dat & PADLup)>0) player[p_no].mod->pos[Y]-=toFIXED(20);
		  FntPrint("px = %d\n", player[p_no].mod->pos[X] >> 12);
		  FntPrint("py = %d\n", player[p_no].mod->pos[Y] >> 12);
		  FntPrint("pz = %d\n", player[p_no].mod->pos[Z] >> 12);
		  FntPrint("ax = %d\n", player[p_no].mod->ang[X] % 4096);
		  FntPrint("ay = %d\n", player[p_no].mod->ang[Y] % 4096);
		  FntPrint("az = %d\n", player[p_no].mod->ang[Z] % 4096);
		  if((PadDat[0].trg & PADn)>0) {
			pp = player + move_mode;
			model_init( (long *) (pp->buf + 1)->tmd,  pp->mod );
			coord_init( (KAISOU *) ((pp->buf + 1)->cls + 8), pp->mod );
			motion_init( pp->motd, pp->mot, 1, 1 );	// 仮
		  }
		  if((PadDat[0].trg & PADo)>0) {
			pp = player + move_mode;
			model_init( (long *) pp->buf->tmd,  pp->mod );
			coord_init( (KAISOU *) (pp->buf->cls + 8), pp->mod );
			motion_init( pp->motd, pp->mot, 3, 1 );	// 仮
		  }
		  break;
		case 2:
		  if ((PadDat[0].dat & PADLU)>0) if (cam.view.vpy > -50000) cam.view.vpy -= (100);
		  if ((PadDat[0].dat & PADLD)>0) if (cam.view.vpy <  10000) cam.view.vpy += (100);
		  if ((PadDat[0].dat & PADLR)>0) cam.view.vpx += (100);
		  if ((PadDat[0].dat & PADLL)>0) cam.view.vpx -= (100);
		  if ((PadDat[0].dat & PADm)>0) cam.view.vpz -= (100);
		  if ((PadDat[0].dat & PADl)>0) cam.view.vpz += (100);
		  if ((PadDat[0].dat & PADn)>0) Projection++;
		  if ((PadDat[0].dat & PADo)>0) Projection--;
		  if ((PadDat[0].trg & PADRU)>0) gcb.ClearMode = (gcb.ClearMode + 1) % 3;
		  if (gcb.ClearMode == 0) {
			bg_col[R] = bg_col[G] = bg_col[B] = 0x00;
		  } else {
			bg_col[R] = bg_col[G] = bg_col[B] = 0x10;
		  }
		  if ((PadDat[0].trg & PADRR)>0) {
		  	if (++attention_pos > 2) attention_pos = 0;
		  } else if ((PadDat[0].trg & PADRL)>0) {
		  	if (--attention_pos < 0) attention_pos = 2;
		  }
		  switch (attention_pos) {
			case 0:
				cam.work = NULL;
				break;
			case 1:
				cam.work = &player[0].mod->pos[X];
				break;
			case 2:
				cam.work = &player[1].mod->pos[X];
				break;
		  }
		  FntPrint("vpx = %d\n", cam.view.vpx);
		  FntPrint("vpy = %d\n", cam.view.vpy);
		  FntPrint("vpz = %d\n", cam.view.vpz);
		  FntPrint("x = %d\n", cam.DView.coord.t[X]);
		  FntPrint("y = %d\n", cam.DView.coord.t[Y]);
		  FntPrint("z = %d\n", cam.DView.coord.t[Z]);
		  FntPrint("projection = %d\n", Projection);
		  FntPrint("attention = %s\n", att_name[attention_pos]);

			if((PadDat[1].dat & PADl)>0) {
				SubStatus++;
			}
		  break;
	}

  return 1;

}
#endif



const long bgm_no_tbl[] = {
XA_BAT1,XA_BAT2,XA_BAT3,XA_BAT4,XA_BAT5,
};



int ScreenCrush()
{
	int i, vcount;
	VECTOR vec;
	SVECTOR svec;
	CVECTOR cvec;
	long cmp, num;

	pp = player;
	ep = player + 1;
	if (SubStatus == 1) {
//		SpriteInit((CzAnimData *) SequenceTbl);		// スプライトの初期化
#if 0
		for (i = 0; i < 4; i++) {
			svec.vx = -32 + (i * 16);
			svec.vy = 0;
			svec.vz = (1<<OT_LENGTH) - 1;
			svec.vz = 0;
			cvec.r =
			cvec.g =
			cvec.b = 0xff;
			SpriteEntry(510, tama_ofs + i + 2, &svec, &cvec, 0, 0);
		}
#endif
		for (i = 0; i < 70; i++) {
			vec.vx = (1439 - ((i % 10) * 320)) << 12;
			vec.vy = (-2239 + ((i / 10) * 320)) << 12;
			vec.vz = 0;
			EffectEntry(5, &vec, NULL, NULL);		// 画面飛び散り
		}
		/*	フレームバッファをコピー	*/
		{
			RECT rect;
			long i;
			u_short *p = (u_short *) TENKAI_ADDR;

			rect.x = 0;
			rect.y = (PSDIDX * 240) + 8;
			rect.w = 320;
			rect.h = 225;
			StoreImage(&rect, (u_long *) TENKAI_ADDR);
			DrawSync(0);
			for (i = 0; i < 0x11800; i++, p++) {
				*p |= 0x8000;
				if ((*p & 0x7fff) == 0) *p |= ((1 << 10) | (1 << 5) | 1);
			}
			rect.x = 320;
			rect.y = 0;
			LoadImage(&rect, (u_long *) TENKAI_ADDR);
			DrawSync(0);
		}
#if 0
		cam.view.vpx = 30000;
		cam.view.vpy = -1280;
		cam.view.vpz = 6000;
		cam.view.vrx = 0;
		cam.view.vry = -1280;
		cam.view.vrz = 4000;
#else
		cam.view.vpx = 0;
		cam.view.vpy = -1280;
		cam.view.vpz = 10000;
		cam.view.vrx = 0;
		cam.view.vry = -1280;
		cam.view.vrz = 0;
#endif
		cam.view.rz = 0;
		GsSetRefView2L((GsRVIEW2 *)&cam);
		GsSetProjection(1000);	/* プロジェクション設定 */
		gcb.ClearMode = 0;
//		gcb.ClearMode = 1;
//		bg_col[R] = bg_col[G] = bg_col[B] = 0x08;

		SubStatus++;
	}

//	SpriteBgSet( 5, 480, -160, -112, CLUT8, 320, 224);

//	SE_ENT(SE_BREAK);

	num = -1;
	if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
		num = *(u_long *) LOAD_ADDR;
		if (texture_num < num) {
			cmp = NumToAddrMcr( texture_num++, LOAD_ADDR );
			LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
			LzDecB();
			texture_init( TENKAI_ADDR );
		}
	}

	if ((texture_num == num) && (EffectCounter == 0)) {
//		SpriteInit((CzAnimData *) SequenceTbl);		// スプライトの初期化
		player_init(0, pp);
		player_init(1, ep);
		motion_init( pp->motd, pp->mot, 0, -1 );	// 仮
		motion_init( ep->motd, ep->mot, 0, -1 );	// 仮
		FadeInit( FADE_IN, 0x10);
		bgm_no = bgm_no_tbl[rand() % 5];
		if (gcb.TitleSelect != 2) {
			XA_CLR();/*本当はポーズ*/
			XA_Status = 0;
			XA_LOAD(bgm_no);
		}
		SubStatus++;
	}

	vcount = VSync(1);
	FntPrint("Load = %d\n",VSync(1)-vcount);

	return( 0 );
};


#if 0
int ModelSeInit2()
{
	int i;
	SVECTOR avec;

	SpriteInit((CzAnimData *) SequenceTbl);

	pp = player;
	for (i = 0; i < 2; i++, pp++) {
		pp->chrno = 0;
		player_init( i, pp);
		motion_init( pp->motd, pp->mot, 0, -1 );
		pp->mod->pos[X] = pp->mod->pos[Y] = pp->mod->pos[Z] = 0;
		pp->mod->ang[X] = pp->mod->ang[Y] = pp->mod->ang[Z] = 0;
		pp->mod->pos[Z] = (-750 + (i * 1500)) << 12;
	}

	cam.view.vpx = 0;
	cam.view.vpy = -3000;
	cam.view.vpz = 10000;
	cam.view.vrx = 0;
	cam.view.vry = -50;
	cam.view.vrz = 0;
	Projection = 2000;

	for (i = 0; i < 3; i++) {
		pslt[i].vx = 0;
		pslt[i].vy = 4096;
		pslt[i].vz = 0;
		pslt[i].r =
		pslt[i].g =
		pslt[i].b = 0;
		GsSetFlatLight(i,&pslt[i]);
	}
	pslt[0].r =
	pslt[0].g =
	pslt[0].b = 0x80;
	GsSetAmbient(0,0,0);

	avec.vz = 2;
	avec.vx = 48 - 160;
	avec.vy = 16 - 120;
	name[0] = SpriteEntry((0x010 << 5) + 495, namevs_ofs+0, &avec, NULL, 1, 0);
	avec.vx = 48 - 160;
	avec.vy = 192 - 120;
	name[1] = SpriteEntry((0x010 << 5) + 495, namevs_ofs+1, &avec, NULL, 2, 0);

	SubStatus++;
	return (0);
}


int ModelSelect2()
{
	int i, rr;
	SVECTOR avec;
	POL4 pol4;
	P_DATA *pd;

    camera_move();
	for (i = 0, pp = player; i < 2; i++, pp++) {
		if (pp->status) {
			player_init_NB( i, pp);
			if (pp->status == 0) {
				pp->timer = 0;
				pp->totaltime = 16;
				pp->start.vx = pp->mod->pos[X] * -1;
				pp->start.vy = pp->mod->pos[Y];
				pp->start.vz = pp->mod->pos[Z];
				pp->terminal.vx = 0;
				pp->terminal.vy = pp->mod->pos[Y];
				pp->terminal.vz = pp->mod->pos[Z];
				avec.vz = 2;
				avec.vx = 48 - 160;
				if (i == 0) {
					avec.vy = 16 - 120;
				} else {
					avec.vy = 192 - 120;
				}
				name[i] = SpriteEntry((0x010 << 5) + 495, namevs_ofs+i, &avec, NULL, i + 1, 0);
			}
		} else {
			pslt[2].r =
			pslt[2].g =
			pslt[2].b = 0;
			GsSetFlatLight(0,&pslt[2]);
			GsSetFlatLight(1,&pslt[2]);
			GsSetFlatLight(2,&pslt[2]);
			pslt[2].vx = (pp->mod->pos[X] >> 12) - 512;
			pslt[2].vy = (pp->mod->pos[Y] >> 12) - 64;
			pslt[2].vz = (pp->mod->pos[Z] >> 12) - 256;
			pslt[2].r =
			pslt[2].g =
			pslt[2].b = 0x60;
			GsSetFlatLight(2,&pslt[2]);
			pslt[i].vx = (pp->mod->pos[X] >> 12);
			pslt[i].vy = (pp->mod->pos[Y] >> 12) + 300;
			pslt[i].vz = (-abs(pp->mod->pos[Z]) >> 12);
			pslt[i].r =
			pslt[i].g =
			pslt[i].b = 0xa0;
			GsSetFlatLight(i,&pslt[i]);
			pp->mod->ang[Y] += 48;			// モデル回転
#if 0
			if ((pp->mot->frame == 0) && (next_motion[pp->mot->num * 2] != -1))
				motion_init( pp->motd, pp->mot, next_motion[pp->mot->num * 2], next_motion[pp->mot->num * 2 + 1]);
			if (pp->mot->frame) motion_test( pp->mod, pp->mot );
#endif
			pp->render();
			model_sort( pp->mod, pp->reflect );
			kage_set( pp->mod , &bgot[ PSDIDX ]);

			if (pp->totaltime) {
				if (pp->timer < pp->totaltime) pp->timer++;
				rr = rsin((pp->timer * 1024) / pp->totaltime);
				pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
				pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
				pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
				if (pp->timer == pp->totaltime) {
					if (pp->mod->pos[X]) {
						if (player[i ^ 1].status == 0) {
							pp->status = 1;
							pp->totaltime = 0;
						}
					} else pp->totaltime = 0;
				}
			}
			if ((pp->totaltime == 0) && (pp->status == 0) && (name[i]->acc[Y] == 0)) {
				if((PadDat[i].trg & PADLR)>0) {
					if (++pp->chrno == MODEL_MAX) pp->chrno = 0;
#if 1
					while ((pp->chrno == MODEL_TN) ||
						(pp->chrno == MODEL_HM) ||
						(pp->chrno == MODEL_OS) ||
						(pp->chrno == MODEL_OT) ||
						(pp->chrno == MODEL_AF) ||
						(pp->chrno == MODEL_NT) ||
						(pp->chrno == MODEL_PN))
					if (++pp->chrno == MODEL_MAX) pp->chrno = 0;
#endif
					pp->timer = 0;
					pp->totaltime = 16;
					pp->start.vx = pp->mod->pos[X];
					pp->start.vy = pp->mod->pos[Y];
					pp->start.vz = pp->mod->pos[Z];
					pp->terminal.vx = pp->mod->pos[X] - (2000 << 12);
					pp->terminal.vy = pp->mod->pos[Y];
					pp->terminal.vz = pp->mod->pos[Z];
					name[i]->acc[Y] = -acceleration * 3;
					if (i) name[i]->acc[Y] *= -1;
					SE_ENT(SE_CUR3);
				} else
				if((PadDat[i].trg & PADLL)>0) {
					if (--pp->chrno < 0) pp->chrno = MODEL_MAX - 1;
#if 1
					while ((pp->chrno == MODEL_TN) ||
						(pp->chrno == MODEL_HM) ||
						(pp->chrno == MODEL_OS) ||
						(pp->chrno == MODEL_OT) ||
						(pp->chrno == MODEL_AF) ||
						(pp->chrno == MODEL_NT) ||
						(pp->chrno == MODEL_PN))
					if (--pp->chrno < 0) pp->chrno = MODEL_MAX - 1;
#endif
					pp->timer = 0;
					pp->totaltime = 16;
					pp->start.vx = pp->mod->pos[X];
					pp->start.vy = pp->mod->pos[Y];
					pp->start.vz = pp->mod->pos[Z];
					pp->terminal.vx = pp->mod->pos[X] + (2000 << 12);
					pp->terminal.vy = pp->mod->pos[Y];
					pp->terminal.vz = pp->mod->pos[Z];
					name[i]->acc[Y] = -acceleration * 3;
					if (i) name[i]->acc[Y] *= -1;
					SE_ENT(SE_CUR3);
				}
			}
		}
	}
	/* 壁紙グラデーション */
	pol4.code = 0x38;
	pol4.sxy[0][X] =
	pol4.sxy[2][X] = -159;
	pol4.sxy[1][X] =
	pol4.sxy[3][X] = 160;
	pol4.sxy[0][Y] =
	pol4.sxy[1][Y] = -119;
	pol4.sxy[2][Y] =
	pol4.sxy[3][Y] = 0;
	pol4.sz[0][0] = (1 <<  BGOT_LENGTH) - 1;
	pol4.rgb[0][R] =
	pol4.rgb[1][R] =
	pol4.rgb[2][R] =
	pol4.rgb[3][R] =
	pol4.rgb[0][G] =
	pol4.rgb[1][G] =
	pol4.rgb[2][G] =
	pol4.rgb[3][G] = 0x10;
	pol4.rgb[0][B] =
	pol4.rgb[1][B] = 0x20;
	pol4.rgb[2][B] =
	pol4.rgb[3][B] = 0xa0;
	Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &bgot[ PSDIDX ]);
	pol4.sxy[0][Y] =
	pol4.sxy[1][Y] = 0;
	pol4.sxy[2][Y] =
	pol4.sxy[3][Y] = 120;
	pol4.rgb[0][R] =
	pol4.rgb[1][R] = 0xa0;
	pol4.rgb[2][R] =
	pol4.rgb[3][R] = 0x20;
	pol4.rgb[0][B] =
	pol4.rgb[1][B] =
	pol4.rgb[2][B] =
	pol4.rgb[3][B] = 0x10;
	Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &bgot[ PSDIDX ]);

	return (0);
}
#endif


#ifndef PREPRE

#define BGMAX 27

const char *bg_name[BGMAX] = {
	"KIRIKABU",
	"KINOMIKI",
	"YUUHI",
	"SIGEMI",
	"KOKAGE",
	"IKE",
	"MORI",
	"OKA",
	"KINOMIKI Y",
	"SIGEMI Y",
	"KOKAGE Y",
	"IKE Y",
	"BG10",
	"BG11",
	"BG12",
	"BG13",
	"BG99",
	"OKA Y",
	"BG98",
	"BG LAST",
	"BG97",
	"BG02Y",
	"BG10Y",
	"BG11Y",
	"BG MACHI",
	"MORI Y",
	"BG SP",
};
#endif

int VsTester()
{
#ifndef PREPRE
static	short model_no[2], bg_no = 1;
	short i;

	SpriteInit((CzAnimData *) SequenceTbl);
	pcb.dbg = 1;
	gcb.ClearMode = 0;
	bg_col[R] =
	bg_col[G] =
	bg_col[B] = 0x00;
	FntPrint("VS TEST\n",0);
	for (i = 0; i < 2; i++) {
		if((PadDat[i].trg & PADRR)>0) {
			if (++bg_no == BGMAX) bg_no = 0;
		} else
		if((PadDat[i].trg & PADRL)>0) {
			if (--bg_no < 0) bg_no = BGMAX - 1;
		} else
		if((PadDat[i].trg & PADLR)>0) {
			if (++model_no[i] == MODEL_MAX) model_no[i] = 0;
		} else
		if((PadDat[i].trg & PADLL)>0) {
			if (--model_no[i] < 0) model_no[i] = MODEL_MAX - 1;
		} else
		if((PadDat[i].trg & PADST)>0) {
			gcb.chrno[0] = model_no[0];
			gcb.chrno[1] = model_no[1];
			gcb.lv[0] =
			gcb.lv[1] = 30;
			gcb.hp[0] =
			gcb.hp[1] = 1000;
			gcb.dp[0] = 1000;
			gcb.dp[1] = 200;
			gcb.hpmax[0] =
			gcb.hpmax[1] =
			gcb.dpmax[0] =
			gcb.dpmax[1] = 1000;
			gcb.ap[0] = 50;
			gcb.ap[1] = 50;
			gcb.at[0] =
			gcb.at[1] = 200;
			gcb.df[0] =
			gcb.df[1] = 20;
			gcb.hrate[0] = 150;
			gcb.hrate[1] = 150;
			gcb.erate[0] =
			gcb.erate[1] = 50;
			gcb.crank[0] = 4;
			gcb.crank[1] = 3;
			gcb.arank[0] = 2;
			gcb.arank[1] = 1;
			gcb.TitleSelect = 0;
			gcb.turn = 0;
			if (((PadDat[i].dat & PADL1)>0) && ((PadDat[i].dat & PADR1)>0)) {
				gcb.turn = 1;
			}
			gcb.bg_no = bg_no;
			ba_totalturn = 0;
			pcb.pno = PRCS_03;
			BattleStatus = 0;
			SubStatus = 0;
		}
		FntPrint("%d %s\n", model_no[i] + 1, model_name[model_no[i]]);
		if (i == 0) FntPrint("    VS\n",0);
	}
	FntPrint("\nSTAGE%d %s\n\n", bg_no, bg_name[bg_no]);
#endif
	return (0);
}

