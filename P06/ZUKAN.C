/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : ZUKAN MODEL                                              */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : ZUKAN.C                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <sys/file.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>
#include <inline_c.h>
#include <gtemac.h>

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
#include "../lib/istatic.h"
#include "../lib/zukan.h"
#include "../model/spadstk.h"	/* for Scratch Pad Stack */
#include "../sprite/sprite.h"
#include "../p06/pinit.h"
#include "../p06/anmdata.h"
#include "../redlib/sound.h"
#include "../redlib/sndno.h"

#define STAR_MAX (512)

typedef struct {
	u_short			counter;
	long			pos[XYZ];
} STARWORK;

/*----- Local Works           -----*/
u_char		ZuSubStatus = 0;
char		Zu_pause_flag = 0;
char		ZuPanelFlag = 0;
long		ZuLocalTimer = 0;
P_MODEL		*Zu_pp;
P_MODEL		Zu_player[2];
MODEL		Zu_model[2];
MOTION		Zu_motion[2];
MOTION_DATA	Zu_motbuf[2][FRAMEMAX];	/* モーションデータバッファ */
SPRWORK		*Zu_name[2];
long		mono_timer;
LPISTATIC	istatic = (ISTATIC_ADDR);
STARWORK	Zu_star[STAR_MAX];
int			WarpSpeed;

/*----- Local Difinitions     -----*/
int ModelSeInit();
int ModelSelect();
int ZuFadeWait();
int WarpInit();
int WarpDraw();
void Zu_SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize);
void Zu_model_sort(MODEL *mod);

PRCS_TBL zukan_tbl[] =
{
	{ ModelSeInit },
	{ ModelSelect },
	{ ZuFadeWait },
	{ WarpInit },
	{ WarpDraw },
};

#define CLEAR_FLAG 0x801ef9f1
//#define SECRET_CUT (1)
#define GET_CHECK (1)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ZUKAN                                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int Zukan()
{
#ifndef PREPRE
	if ( FioGetMachine() == FIO_MC_DEV ) {
		/* 画面キャプチャー */
		if (((PadDat[1].trg & PADRL)>0) && (PSDIDX)) {
			RECT rect;
			long fd;
			char filename[32];

			static long tim_header[] = {
				0x00000010,
				0x00000002,
				320 * 480 * 2 + 12,
				0x00000000,
				0x01e00140,
			};
			static int tim_no = 0;

			setRECT(&rect, 0, 0, 320, 480);
			StoreImage(&rect, (u_long *)0x80600000);

			DrawSync( 0 );

			sprintf(filename, "sim:timdata\\scn%04d.tim", tim_no);
			if ( (fd = open(filename, O_WRONLY|O_CREAT)) == -1 ) {
				printf("can't open file\n");
			}
			else {
				write(fd, (void *)tim_header, sizeof( tim_header));
				write(fd, (void *)0x80600000, 320 * 480 * 2);
				close( fd );
				fd = open("sim:bmp\\bmp.bmp", O_WRONLY|O_CREAT);
				write(fd, (void *)0x80600000, 320 * 480 * 2);
				close( fd );
				tim_no++;
				printf("captured %s\n", filename);
			}
		}
	}
#endif

#ifndef PREPRE
	if ((gcb.ClearMode == 0) || (Zu_pause_flag)) {
		if ((pcb.pno != PRCS_06) && (ZuSubStatus == 1) && ((PadDat[0].trg & PADST)>0)) {
			Zu_pause_flag ^= 1;
			SE_ENT(SE_PAUSE);
		}
		if (((PadDat[0].trg & PADm)==0) && (Zu_pause_flag)) {
			gcb.ClearMode = 3;
			return( 0 );
		} else gcb.ClearMode = 0;
	}
#endif

	ZuLocalTimer++;

	GsClearOt( 0, 0, &spriteot[ PSDIDX ] );
	GsSortOt( &spriteot[ PSDIDX ], &ot[ PSDIDX ]);

	zukan_tbl[ ZuSubStatus ].func();

	SpriteControll();
	Sprite3dControll();

   return( 0 );
};


const short zu_fix_tbl[] = {
	(0x100 << 5) + 483, zuk_ofs + 0,  24 - 160,  20 - 120 - 90, 3,12,
	(0x100 << 5) + 483, zuk_ofs + 1,  56 - 160,  20 - 120 - 90, 3, 8,
	(0x100 << 5) + 483, zuk_ofs + 2, 264 - 160,  20 - 120 - 90, 4,12,
	(0x100 << 5) + 483, zuk_ofs + 3, 232 - 160,  20 - 120 - 90, 4, 8,
	(0x100 << 5) + 480, zuk_ofs + 4, 256 - 160,  80 - 120 + 90, 4, 8,
	(0x100 << 5) + 482, zuk_ofs + 5, 256 - 160, 136 - 120 + 90, 4,12,
	(0x100 << 5) + 481, zuk_ofs + 6, 256 - 160, 192 - 120 + 90, 4,16,
};

int ModelSeInit()
{
	int i, j;
	SVECTOR avec;
	u_short pal,chr,mode,wait;
	RECT            rect;

	GsInitGraph2( 320, 480, GsINTER | GsOFSGPU, 1, 0 ); /* Initialize Graphic System     */
	GsDefDispBuff2( 0, 0, 0, 0 );           /* Double Buffer Setting         */
	setRECT( &rect, 0, 0, 320, 480 );
	GsSetClip2D( &rect );                    /* Display Masking               */
	POSITION.offx = 160;
	POSITION.offy = 240;

	SOUND_I();
	SE_LOAD(0);
	BGM_LOAD(BGM_SEL);
	BGM_ENT(0);
	camera_init();
	light_init();

	SpriteInit((CzAnimData *) Zu_SequenceTbl);

	/* モデルデータ */
	FioReadFile((Uint8 *) "DT\\MONO.M", (Uint8 *) BGMODEL_ADDR);
	model_init( (long *) BGMODEL_ADDR, (MODEL *) &Zu_model[1] );
	GsInitCoordinate2(WORLD, &Zu_model[1].objpos[0]);
	Zu_model[1].object[0].coord2 = &Zu_model[1].objpos[0];
	Zu_model[1].object[0].attribute = 0;
	Zu_model[1].objang[0].vx = 0;
	Zu_model[1].objang[0].vy = 0;
	Zu_model[1].objang[0].vz = 0;
	Zu_model[1].pos[X] = 0;
	Zu_model[1].pos[Y] = (160 << 12);
	Zu_model[1].pos[Z] = 0;
	Zu_model[1].ang[X] = 0;
	Zu_model[1].ang[Y] = 0;
	Zu_model[1].ang[Z] = 0;

	{
		long i, cmp, num;

		FioReadFile((Uint8 *) "DT\\ZUKAN.TEX", (Uint8 *) LOAD_ADDR);
		num = *(u_long *) LOAD_ADDR;
		for (i = 0; i < num; i++) {
			cmp = NumToAddrMcr( i, LOAD_ADDR );
			LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
			LzDecB();
			Zu_texture_init( TENKAI_ADDR );
			DrawSync(0);
		}
	}
#if 0
	{
		FioReadFile((Uint8 *) "BACK.TIM", (Uint8 *) LOAD_ADDR);
		Zu_texture_init( LOAD_ADDR );
		DrawSync(0);
	}
#endif

	Zu_pp = Zu_player;

	Zu_pp->mod = &Zu_model[0];
	Zu_pp->mot = &Zu_motion[0];
	Zu_pp->mot->bufp = Zu_motbuf[0];
	Zu_pp->motd = (char *) PLAYER1_ADDR;
	Zu_pp->buf = (P_BUFF *) MODEL1_ADDR;

	Zu_pp->chrno = 0;

	Zu_player_init( 0, Zu_pp);
	motion_init( Zu_pp->motd, Zu_pp->mot, 0, -1 );
	Zu_pp->mod->pos[X] = Zu_pp->mod->pos[Y] = Zu_pp->mod->pos[Z] = 0;
	Zu_pp->mod->ang[X] = -1024;
	Zu_pp->mod->ang[Y] = Zu_pp->mod->ang[Z] = 0;

	cam.view.vpx = 0;
	cam.view.vpy = -50;
	cam.view.vpz = 4500;
	cam.view.vrx = 0;
	cam.view.vry = -50;
	cam.view.vrz = 0;
	Projection = 900;

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
	GsSetAmbient(ONE/8, ONE/8, ONE/8);

	avec.vz = 2;
	for (i = 0, j = 0; i < 7; i++) {
		pal = zu_fix_tbl[j++];
		chr = zu_fix_tbl[j++];
		avec.vx = zu_fix_tbl[j++];
		avec.vy = zu_fix_tbl[j++];
		mode = zu_fix_tbl[j++];
		wait = zu_fix_tbl[j++];
		SpriteEntry(pal, chr, &avec, NULL, mode, wait);
	}

	avec.vz = 2;
	avec.vx = 48 - 160;
	avec.vy = 40 - 120 - 90;
	Zu_name[0] = SpriteEntry((0x010 << 5) + 487, zu_namevs_ofs+0, &avec, NULL, 1, 0);

	FadeInit( FADE_IN, 0x10);

	mono_timer = 0;
	ZuSubStatus++;
	return (0);
}


const short Zu_next_motion[] = {
	-1, -1,	//  0 jpiki.lz
	 2, -1,	//  1 jptob0.lz
	 0, -1,	//  2 jptob1.lz
	 4,  1,	//  3 jpdmg2.lz
	 0, -1,	//  4 jpdmg4.lz
	 6,  1,	//  5 jpdmg0.lz
	 0, -1,	//  6 jpdmg1.lz
	 8,  1,	//  7 jpdmg3.lz
	 0, -1,	//  8 jpdmg5.lz
	-1, -1,	//  9 jpido0.lz
	 0, -1,	// 10 jpido1.lz
	12,  1,	// 11 jpkgk0.lz
	 0, -1,	// 12 jpkgk1.lz
	14,  1,	// 13 jphri0.lz
	 0, -1,	// 14 jphri1.lz
	16,  1,	// 15 jptki0.lz
	 0, -1,	// 16 jptki1.lz
	19,  1,	// 17 cmb0.lz
	 0, -1,	// 18 cmb0m.lz
	21,  1,	// 19 cmb1.lz
	 0, -1,	// 20 cmb1m.lz
	22,  1,	// 21 cmb2.lz
	 0, -1,	// 22 cmb2m.lz
	-1, -1,	// 23 ttkn.lz
	33,  1,	// 24 ngrr0.lz
	-1, -1,	// 25 sasi.lz
	33,  1,	// 26 nj_jp0.lz
	 0, -1,	// 27 hm_jp0.lz
	 0, -1,	// 28 tos2.lz
	-1, -1,	// 29 bkstp.lz
	-1, -1,	// 30 cyg.lz
	32,  1, // 31 hrftb0.lz
	 0, -1,	// 32 hrftb1.lz
	 0, -1,	// 33 ngrr1.lz
	 0, -1,	// 34 a2.lz 欠番
	-1, -1,	// 35 hrnag.lz 欠番
	33,  1,	// 36 hrdkn.lz
	38,  1,	// 37 hrnr0x.lz
	 0, -1,	// 38 hrnr1x.lz
	40,  1,	// 39 mynr0s.lz
	 0, -1,	// 40 mynr1s.lz
};

int ModelSelect()
{
	int i, rr;
	SVECTOR avec;
	POL4 pol4;
	P_DATA *pd;

    camera_move();
	i = 0;
	Zu_pp = Zu_player;
	if (Zu_pp->status) {
		Zu_player_init_NB( i, Zu_pp);
		if (Zu_pp->status == 0) {
			avec.vz = 2;
			avec.vx = 48 - 160;
			avec.vy = 40 - 120 - 90;
			Zu_name[i] = SpriteEntry((0x010 << 5) + 487, zu_namevs_ofs+i, &avec, NULL, 5, 0);
		}
	} else {
		pslt[2].r =
		pslt[2].g =
		pslt[2].b = 0;
		GsSetFlatLight(0,&pslt[2]);
		GsSetFlatLight(1,&pslt[2]);
		GsSetFlatLight(2,&pslt[2]);
		pslt[2].vx = 0;//(Zu_pp->mod->pos[X] >> 12) - 512;
		pslt[2].vy = 0;//(Zu_pp->mod->pos[Y] >> 12) - 64;
		pslt[2].vz = -100;//(Zu_pp->mod->pos[Z] >> 12) - 256;
		pslt[2].r =
		pslt[2].g =
		pslt[2].b = 0x70;
		GsSetFlatLight(2,&pslt[2]);
		pslt[i].vx = (Zu_pp->mod->pos[X] >> 12);
		pslt[i].vy = (Zu_pp->mod->pos[Y] >> 12) + 300;
		pslt[i].vz = (Zu_pp->mod->pos[Z] >> 12);
		pslt[i].r =
		pslt[i].g =
		pslt[i].b = 0xa0;
		GsSetFlatLight(i,&pslt[i]);
		if ((Zu_pp->mot->frame == 0) && (Zu_next_motion[Zu_pp->mot->num * 2] != -1))
			motion_init( Zu_pp->motd, Zu_pp->mot, Zu_next_motion[Zu_pp->mot->num * 2], Zu_next_motion[Zu_pp->mot->num * 2 + 1]);
		if ((ZuLocalTimer & 1) && (Zu_pp->mot->frame)) motion_test( Zu_pp->mod, Zu_pp->mot );
		Zu_pp->model_col[R] =
		Zu_pp->model_col[G] =
		Zu_pp->model_col[B] = 0xff;
		if (*Zu_pp->render == &jt_wire2set) {
			Zu_pp->model_col[R] =
			Zu_pp->model_col[B] = 0;
			Zu_pp->model_col[G] = (gcb.GlobalTimer) & 0x7f;
			if (Zu_pp->model_col[G] >= 0x40) Zu_pp->model_col[G] = 0x80 - Zu_pp->model_col[G];
		}
		Zu_pp->render();
		model_col[R] = Zu_pp->model_col[R];
		model_col[G] = Zu_pp->model_col[G];
		model_col[B] = Zu_pp->model_col[B];
		model_sort( Zu_pp->mod, Zu_pp->reflect );
#if 1
		if((PadDat[i].trg & PADl)>0) {
			if (++Zu_pp->chrno == MODEL_MAX) Zu_pp->chrno = 0;
			while ((Zu_pp->chrno == MODEL_KB) ||
				   (Zu_pp->chrno == MODEL_RB) ||
#ifdef SECRET_CUT
				   (Zu_pp->chrno == MODEL_SP) ||
				   (Zu_pp->chrno == MODEL_MK) ||
				   (Zu_pp->chrno == MODEL_ME) ||
				   (Zu_pp->chrno == MODEL_PC) ||
				   (Zu_pp->chrno == MODEL_CK) ||
				   (Zu_pp->chrno == MODEL_SO) ||
#endif
#ifdef GET_CHECK
				   ((*(char *) CLEAR_FLAG == 0) &&
				   ((istatic+Zu_pp->chrno)->lv == 0) &&
				   ((istatic+Zu_pp->chrno)->pad == 0)) ||	// ゲットした？
#endif
				   (Zu_pp->chrno == MODEL_BE))
					if (++Zu_pp->chrno == MODEL_MAX) Zu_pp->chrno = 0;
			Zu_pp->timer = 0;
			Zu_pp->totaltime = 32;
			Zu_pp->start.vx = 0;
			Zu_pp->start.vy = Zu_pp->mod->pos[Y];
			Zu_pp->start.vz = Zu_pp->mod->pos[Z];
			Zu_pp->terminal.vx = -(3000 << 12);
			Zu_pp->terminal.vy = Zu_pp->mod->pos[Y];
			Zu_pp->terminal.vz = Zu_pp->mod->pos[Z];
			Zu_name[i]->hzoomac =
			Zu_name[i]->vzoomac = acceleration;
			ZuPanelFlag = 0;
			mono_timer = 0;
			SE_CLR(SE_CHARGE1);
			SE_ENT(SE_CHARGE1);
		} else
		if((PadDat[i].trg & PADn)>0) {
			if (--Zu_pp->chrno < 0) Zu_pp->chrno = MODEL_MAX - 1;
			while ((Zu_pp->chrno == MODEL_KB) ||
				   (Zu_pp->chrno == MODEL_RB) ||
#ifdef SECRET_CUT
				   (Zu_pp->chrno == MODEL_SP) ||
				   (Zu_pp->chrno == MODEL_MK) ||
				   (Zu_pp->chrno == MODEL_ME) ||
				   (Zu_pp->chrno == MODEL_PC) ||
				   (Zu_pp->chrno == MODEL_CK) ||
				   (Zu_pp->chrno == MODEL_SO) ||
#endif
#ifdef GET_CHECK
				   ((*(char *) CLEAR_FLAG == 0) &&
				   ((istatic+Zu_pp->chrno)->lv == 0) &&
				   ((istatic+Zu_pp->chrno)->pad == 0)) ||	// ゲットした？
#endif
				   (Zu_pp->chrno == MODEL_BE))
					if (--Zu_pp->chrno < 0) Zu_pp->chrno = MODEL_MAX - 1;
			Zu_pp->timer = 0;
			Zu_pp->totaltime = 32;
			Zu_pp->start.vx = 0;
			Zu_pp->start.vy = Zu_pp->mod->pos[Y];
			Zu_pp->start.vz = Zu_pp->mod->pos[Z];
			Zu_pp->terminal.vx = (3000 << 12);
			Zu_pp->terminal.vy = Zu_pp->mod->pos[Y];
			Zu_pp->terminal.vz = Zu_pp->mod->pos[Z];
			Zu_name[i]->hzoomac =
			Zu_name[i]->vzoomac = acceleration;
			ZuPanelFlag = 0;
			mono_timer = 0;
			SE_CLR(SE_CHARGE1);
			SE_ENT(SE_CHARGE1);
		}
#endif
		if (Zu_pp->totaltime) {
			rr = rsin((++Zu_pp->timer * 1024) / Zu_pp->totaltime);
			Zu_pp->mod->pos[X] = Zu_pp->start.vx + (((Zu_pp->terminal.vx - Zu_pp->start.vx) / 4096) * rr);
			Zu_pp->mod->pos[Y] = Zu_pp->start.vy + (((Zu_pp->terminal.vy - Zu_pp->start.vy) / 4096) * rr);
			Zu_pp->mod->pos[Z] = Zu_pp->start.vz + (((Zu_pp->terminal.vz - Zu_pp->start.vz) / 4096) * rr);
			if (Zu_pp->timer == Zu_pp->totaltime) {
				if (Zu_pp->mod->pos[X]) {
					pd = (P_DATA *) Zu_player_data + Zu_pp->chrno;
					Zu_pp->status = 1;
					Zu_pp->timer = 0;
					Zu_pp->totaltime = 32;
					if (Zu_pp->mod->pos[X] > 0) Zu_pp->start.vx = -(3000 << 12);
					else Zu_pp->start.vx = (3000 << 12);
					Zu_pp->start.vy = Zu_pp->mod->pos[Y];
					Zu_pp->start.vz = Zu_pp->mod->pos[Z];
					Zu_pp->terminal.vx = 0;
					Zu_pp->terminal.vy = Zu_pp->mod->pos[Y];
					Zu_pp->terminal.vz = Zu_pp->mod->pos[Z];
				} else Zu_pp->totaltime = 0;
			}
		} else if (Zu_name[i]->hzoomac == 0) {
			/* オブジェクトをY軸回転させる */
			if((PadDat[i].dat & PADLR)>0) Zu_pp->mod->ang[Y] -= 32;
			else if((PadDat[i].dat & PADLL)>0) Zu_pp->mod->ang[Y] += 32;
			/* オブジェクトをX軸回転させる */
			if((PadDat[i].dat & PADLU)>0) Zu_pp->mod->ang[X] += 32;
			else if((PadDat[i].dat & PADLD)>0) Zu_pp->mod->ang[X] -= 32;
			/* ズーム */
			if((PadDat[i].dat & PADm)>0) {
				if (cam.view.vpz > 2400) {
					cam.view.vpz -= 75;
				}
			} else if((PadDat[i].dat & PADo)>0) {
				if (cam.view.vpz < 12000) {
					cam.view.vpz += 75;
				}
			}
			if((PadDat[i].dat & PADl)>0) {
				if (++Zu_pp->chrno == MODEL_MAX) Zu_pp->chrno = 0;
				while ((Zu_pp->chrno == MODEL_KB) ||
					   (Zu_pp->chrno == MODEL_RB) ||
#ifdef SECRET_CUT
					   (Zu_pp->chrno == MODEL_SP) ||
					   (Zu_pp->chrno == MODEL_MK) ||
					   (Zu_pp->chrno == MODEL_ME) ||
					   (Zu_pp->chrno == MODEL_PC) ||
					   (Zu_pp->chrno == MODEL_CK) ||
					   (Zu_pp->chrno == MODEL_SO) ||
#endif
#ifdef GET_CHECK
					   ((*(char *) CLEAR_FLAG == 0) &&
					   ((istatic+Zu_pp->chrno)->lv == 0) &&
					   ((istatic+Zu_pp->chrno)->pad == 0)) ||	// ゲットした？
#endif
					   (Zu_pp->chrno == MODEL_BE))
						if (++Zu_pp->chrno == MODEL_MAX) Zu_pp->chrno = 0;
				Zu_pp->timer = 0;
				Zu_pp->totaltime = 32;
				Zu_pp->start.vx = 0;
				Zu_pp->start.vy = Zu_pp->mod->pos[Y];
				Zu_pp->start.vz = Zu_pp->mod->pos[Z];
				Zu_pp->terminal.vx = -(3000 << 12);
				Zu_pp->terminal.vy = Zu_pp->mod->pos[Y];
				Zu_pp->terminal.vz = Zu_pp->mod->pos[Z];
				Zu_name[i]->hzoomac =
				Zu_name[i]->vzoomac = acceleration;
				ZuPanelFlag = 0;
				mono_timer = 0;
				SE_CLR(SE_CHARGE1);
				SE_ENT(SE_CHARGE1);
			} else
			if((PadDat[i].dat & PADn)>0) {
				if (--Zu_pp->chrno < 0) Zu_pp->chrno = MODEL_MAX - 1;
				while ((Zu_pp->chrno == MODEL_KB) ||
					   (Zu_pp->chrno == MODEL_RB) ||
#ifdef SECRET_CUT
					   (Zu_pp->chrno == MODEL_SP) ||
					   (Zu_pp->chrno == MODEL_MK) ||
					   (Zu_pp->chrno == MODEL_ME) ||
					   (Zu_pp->chrno == MODEL_PC) ||
					   (Zu_pp->chrno == MODEL_CK) ||
					   (Zu_pp->chrno == MODEL_SO) ||
#endif
#ifdef GET_CHECK
					   ((*(char *) CLEAR_FLAG == 0) &&
					   ((istatic+Zu_pp->chrno)->lv == 0) &&
					   ((istatic+Zu_pp->chrno)->pad == 0)) ||	// ゲットした？
#endif
					   (Zu_pp->chrno == MODEL_BE))
						if (--Zu_pp->chrno < 0) Zu_pp->chrno = MODEL_MAX - 1;
				Zu_pp->timer = 0;
				Zu_pp->totaltime = 32;
				Zu_pp->start.vx = 0;
				Zu_pp->start.vy = Zu_pp->mod->pos[Y];
				Zu_pp->start.vz = Zu_pp->mod->pos[Z];
				Zu_pp->terminal.vx = (3000 << 12);
				Zu_pp->terminal.vy = Zu_pp->mod->pos[Y];
				Zu_pp->terminal.vz = Zu_pp->mod->pos[Z];
				Zu_name[i]->hzoomac =
				Zu_name[i]->vzoomac = acceleration;
				ZuPanelFlag = 0;
				mono_timer = 0;
				SE_CLR(SE_CHARGE1);
				SE_ENT(SE_CHARGE1);
			} else if((PadDat[i].trg & PADRD)>0) {
				SE_ENT(SE_CANCEL);
				FadeInit( FADE_OUT, 0x10);
				BGM_FADE( BGM_DOWN, 0,5);
				ZuSubStatus++;
			} else if((PadDat[i].trg & PADRR)>0) {
				model_init( (long *) Zu_pp->buf->tmd,  Zu_pp->mod );
				coord_init( (KAISOU *) (Zu_pp->buf->cls + 8), Zu_pp->mod );
				motion_init( Zu_pp->motd, Zu_pp->mot, 17, 1 );	// 攻撃モーション
				if (ZuLocalTimer & 1) motion_test( Zu_pp->mod, Zu_pp->mot );
			} else if((PadDat[i].trg & PADRU)>0) {
				if ((Zu_pp->chrno == MODEL_TC) || (Zu_pp->chrno == MODEL_SP)) {
					model_init( (long *) Zu_pp->buf->tmd,  Zu_pp->mod );
					coord_init( (KAISOU *) (Zu_pp->buf->cls + 8), Zu_pp->mod );
					motion_init( Zu_pp->motd, Zu_pp->mot, 17, 1 );	// 攻撃モーション
				} else {
					model_init( (long *) (Zu_pp->buf + 1)->tmd,  Zu_pp->mod );
					coord_init( (KAISOU *) ((Zu_pp->buf + 1)->cls + 8), Zu_pp->mod );
					motion_init( Zu_pp->motd, Zu_pp->mot, 1, 1 );	// 飛びモーション
				}
				if (ZuLocalTimer & 1) motion_test( Zu_pp->mod, Zu_pp->mot );
			} else if((PadDat[i].trg & PADRL)>0) {
				SE_ENT(SE_OK2);
				ZuPanelFlag ^= 1;
#ifndef PREPRE
			} else if((PadDat[i].trg & PADST)>0) {
				ZuSubStatus = 3;
#endif
			}
			if (mono_timer < (60 * 5)) mono_timer++;
		}
	}
	/* 解説パネル */
	if (ZuPanelFlag) {
		avec.vz = 2;
		avec.vx = 16 - 160;
		avec.vy = 152 - 120;
		SpriteEntry((0x110 << 5) + 480, zu_panel_ofs, &avec, NULL, 16, 0);
	} else {
		if (mono_timer < (60 * 5)) {
			jt_init4();
			Zu_model_sort( &Zu_model[1] );
		}
	}
	/* 壁紙グラデーション */
	pol4.code = 0x38;
	pol4.sxy[0][X] =
	pol4.sxy[2][X] = -160;
	pol4.sxy[1][X] =
	pol4.sxy[3][X] = 160;
	pol4.sxy[0][Y] =
	pol4.sxy[1][Y] = -240;
	pol4.sxy[2][Y] =
	pol4.sxy[3][Y] = 240;
	pol4.sz[0][0] = (1 <<  OT_LENGTH) - 1;
	pol4.rgb[0][B] =
	pol4.rgb[1][B] = 0xff;
	pol4.rgb[2][B] =
	pol4.rgb[3][B] = 0x60;
#if 1
	pol4.rgb[0][R] =
	pol4.rgb[1][R] = 0x80;
	pol4.rgb[2][R] =
	pol4.rgb[3][R] = 0x10;
	pol4.rgb[0][G] =
	pol4.rgb[1][G] = 0x80;
	pol4.rgb[2][G] =
	pol4.rgb[3][G] = 0x10;
	Zu_Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &ot[ PSDIDX ]);
#else
	pol4.rgb[1][R] =
	pol4.rgb[2][R] = 0xa0;
	pol4.rgb[3][R] =
	pol4.rgb[0][R] = 0x20;
	pol4.rgb[2][G] =
	pol4.rgb[3][G] = 0xa0;
	pol4.rgb[0][G] =
	pol4.rgb[1][G] = 0x20;
	Zu_SpriteBgSet( 21, 511, -160, -120, CLUT8, 320, 240);
#endif
	return (0);
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	ポリゴンセット
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void Zu_Poly4Set(u_long tpage, short clut, POL4 *pol4, GsOT *ot)
{
	register	long *tag;
	register	u_long *packet  = (u_long *) GsOUT_PACKET_P;
	int i = 1;

	packet[i++] = (u_long)((pol4->code << 24) | (pol4->rgb[0][B] << 16) | (pol4->rgb[0][G] << 8) | pol4->rgb[0][R]);
	tag = (u_long *) (ot->org + (pol4->sz[0][0] >> (14 - ot->length)));
	switch (pol4->code & 0x7c) {
		case 0x28:	// POLY_F4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[i] << 8) >> 8;
			packet[i++] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
			packet[i++] = (u_long)((0xe1 << 24) | tpage);
			break;
		case 0x38:	// POLY_G4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[1][B] << 16) | (pol4->rgb[1][G] << 8) | pol4->rgb[1][R]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[2][B] << 16) | (pol4->rgb[2][G] << 8) | pol4->rgb[2][R]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[3][B] << 16) | (pol4->rgb[3][G] << 8) | pol4->rgb[3][R]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[i] << 8) >> 8;
			packet[i++] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
			packet[i++] = (u_long)((0xe1 << 24) | tpage);
			break;
		case 0x2c:	// POLY_FT4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((clut << 16) | (pol4->uv[0][1] << 8) | pol4->uv[0][0]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((tpage << 16) | (pol4->uv[1][1] << 8) | pol4->uv[1][0]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[2][1] << 8) | pol4->uv[2][0]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[3][1] << 8) | pol4->uv[3][0]);
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[0] << 8) >> 8;
			break;
		case 0x3c:	// POLY_GT4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((clut << 16) | (pol4->uv[0][1] << 8) | pol4->uv[0][0]);
			packet[i++] = (u_long)((pol4->rgb[1][B] << 16) | (pol4->rgb[1][G] << 8) | pol4->rgb[1][R]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((tpage << 16) | (pol4->uv[1][1] << 8) | pol4->uv[1][0]);
			packet[i++] = (u_long)((pol4->rgb[2][B] << 16) | (pol4->rgb[2][G] << 8) | pol4->rgb[2][R]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[2][1] << 8) | pol4->uv[2][0]);
			packet[i++] = (u_long)((pol4->rgb[3][B] << 16) | (pol4->rgb[3][G] << 8) | pol4->rgb[3][R]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[3][1] << 8) | pol4->uv[3][0]);
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[0] << 8) >> 8;
			break;
	}
	GsOUT_PACKET_P = (PACKET *) &packet[i];
}


int ZuFadeWait()
{
	RECT            rect;

	if (fade.status == 0) {
		SpriteInit((CzAnimData *) Zu_SequenceTbl);
		GsInitGraph2( 320, 240, GsNONINTER | GsOFSGPU, 1, 0 ); /* Initialize Graphic System     */
		GsDefDispBuff2( 0, 0, 0, 240 );           /* Double Buffer Setting         */
		setRECT( &rect, 0, 8, 320, 224 );
		GsSetClip2D( &rect );                    /* Display Masking               */
		POSITION.offx = 160;
		POSITION.offy = 120;
		pcb.req = pcb.pno;
	}
}


#define	max_width	64
void Zu_SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize)
{
	Uint32	pri;
	GsSPRITE	sp,sprite;

		pri = (1 << OT_LENGTH) - 1;
		sprite.attribute = attr | ZOOM_OFF | LIGHT_OFF;
		sprite.tpage = tpage;
		sprite.x = x;
		sprite.y = y;
		sprite.u = 0;
		sprite.v = 0;
		sprite.cx = 0;
		sprite.cy = pal;
		sprite.r =
		sprite.g =
		sprite.b = BGFadeOffset;
		sprite.mx =
		sprite.my = 0;
		sprite.scalex =
		sprite.scaley = ONE;
		while(wsize > 0) {
			if (wsize >= max_width)
				sprite.w = max_width;
			else
				sprite.w = wsize;
			if (hsize <= 256)
				sprite.h = hsize;
			else
				sprite.h = 256;
			if ((sprite.x > -160 - max_width) && (sprite.x <160)) {
				sp = sprite;

				if (sp.x + sp.w > 160)
					sp.w = 160 - sp.x;
				GsSortSprite(&sp, &ot[ PSDIDX ], pri);			// Sprite Entry
				if (hsize > 256) {
					sprite.tpage += 16;
					sprite.y += 256;
					sprite.h = hsize - 256;
					sp = sprite;
					GsSortSprite(&sp, &ot[ PSDIDX ], pri);			// Sprite Entry
					sprite.tpage -= 16;
					sprite.y -= 256;
				}
			}
			sprite.x += max_width;
			sprite.u += max_width;
			if (sprite.u == 0) {
				if ((attr & DIRECT15) == DIRECT15)
					sprite.tpage += 4;
				else if ((attr & CLUT8) == CLUT8)
					sprite.tpage += 2;
				else
					sprite.tpage++;
			}
			wsize -= sprite.w;
		}
}


void Zu_model_sort(MODEL *mod)
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

	objp->attribute = mod->attribute;
	SetSpadStack(SPAD_STACK_ADDR);
	GsSortObject4J(objp, &ot[ PSDIDX ], 14 - OT_LENGTH, getScratchAddr(0));
	ResetSpadStack();
}


int WarpInit()
{
	int i;
	RECT            rect;

	GsInitGraph2( 320, 240, GsNONINTER | GsOFSGPU, 1, 0 ); /* Initialize Graphic System     */
	GsDefDispBuff2( 0, 0, 0, 240 );           /* Double Buffer Setting         */
	setRECT( &rect, 0, 0, 320, 240 );
	GsSetClip2D( &rect );                    /* Display Masking               */
	POSITION.offx = 160;
	POSITION.offy = 120;

	camera_init();
	light_init();

	SpriteInit((CzAnimData *) Zu_SequenceTbl);

	cam.view.vpx = 0;
	cam.view.vpy = 0;
	cam.view.vpz = 10000;
	cam.view.vrx = 0;
	cam.view.vry = 0;
	cam.view.vrz = 0;
	Projection = 300;

	for (i = 0; i < 3; i++) {
		pslt[i].vx = 0;
		pslt[i].vy = 4096;
		pslt[i].vz = 0;
		pslt[i].r =
		pslt[i].g =
		pslt[i].b = 0;
		GsSetFlatLight(i,&pslt[i]);
	}
	FadeInit( FADE_IN, 0x10);
	WarpSpeed = 200;

//	gcb.ClearMode = 1;
//	bg_col[R] = bg_col[G] = bg_col[B] = 0x20;

	ZuSubStatus++;
	return (0);
}


int WarpDraw()
{
	struct {
		SVECTOR wv;
	} *sc = (void *)getScratchAddr(0);
	register	long *tag;
	register	STARWORK *spp = Zu_star;
	register	u_long *packet  = (u_long *) GsOUT_PACKET_P;
	int d0;
	long otz;
	short rgb, draw_num, vcount;

	vcount = VSync(1);
	if((PadDat[0].dat & PADLU)>0) {
		if (WarpSpeed < 1100) WarpSpeed += 5;
	} else if((PadDat[0].dat & PADLD)>0) {
		if (WarpSpeed > 20) WarpSpeed -= 5;
	}
	FntPrint("speed = %dKm/s\n", WarpSpeed * 60 / 1000);
#if 0
	if((PadDat[0].dat & PADLL)>0) {
		cam.view.vrx += 100;
	} else if((PadDat[0].dat & PADLR)>0) {
		cam.view.vrx -= 100;
	}
#endif

	Projection = 600 - (WarpSpeed / 2);
	camera_move();
	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	draw_num = 0;
	for (d0 = 0; d0 < STAR_MAX; d0++, spp++) {
		if (spp->counter == 0) {
			spp->pos[X] = (rand() % 15000) - 7500;
			spp->pos[Y] = (rand() % 15000) - 7500;
			spp->pos[Z] = -(15000 + (rand() % 15000));
			spp->counter++;
		}
		spp->pos[Z] += WarpSpeed;
		if (spp->pos[Z] >= 10000) {
			spp->counter = 0;
		} else if (spp->pos[Z] < -30000) {
			spp->pos[X] = (rand() % 20000) - 10000;
			spp->pos[Y] = (rand() % 20000) - 10000;
			spp->pos[Z] += 30000;
		}
		sc->wv.vx = spp->pos[X];
		sc->wv.vy = spp->pos[Y];
		sc->wv.vz = spp->pos[Z];
		gte_ldv0(&sc->wv);
		gte_rtps();
		gte_stszotz(&otz);
		rgb = 0xff - (otz>>5);
		if (rgb > 0) {
			gte_stsxy((u_long *) &packet[2]);
			sc->wv.vz -= WarpSpeed * 3;
			gte_ldv0(&sc->wv);
			gte_rtps();
			gte_stsxy((u_long *) &packet[4]);
			packet[1] = ((0x52 << 24) | (rgb << 16) | (rgb << 8) | rgb);
			packet[3] = 0;
			tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
			*packet = (u_long)((( *tag << 8) >> 8) | 0x04000000);
			*tag = ((u_long) &packet[0] << 8) >> 8;
			packet += 5;
			draw_num++;
		}
	}
	FntPrint("draw = %d/%dline\n", draw_num, VSync(1)-vcount);
}
