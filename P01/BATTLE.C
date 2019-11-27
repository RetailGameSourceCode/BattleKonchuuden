/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : BATTLE SCENE                                             */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : BATTLE.C                                                 */
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
#include "../lib/polygon.h"
#include "../lib/fade.h"
#include "../sprite/sprite.h"
#include "../p01/anmdata.h"
#include "../p01/poly_sub.h"
#include "../p01/battle.h"
#include "../p01/bg.h"
#include "../redlib/sndno.h"
#include "../redlib/xano.h"

/*----- Local Works           -----*/
u_char		BattleStatus = 0;
u_char		battleturn;
u_char		ba_totalturn = 0;
u_short		seq_work[100];
P_MODEL		*pp, *ep;
P_MODEL		player[2];
MODEL		model[2];
MOTION		motion[2];
MOTION_DATA	motbuf[2][FRAMEMAX];	/* モーションデータバッファ */
long		LightPos[XYZ];
short		eflt[RGB];
VECTOR		trans, pos[4];
SVECTOR		avec;
CVECTOR		cvec;
GsCOORDINATE2	coord;
P_DATA		*pd;
long		eq_timer;
SPRWORK		*button[3], *cursol, *name_status;
Z_POS		*zp;
short		cursol_pos, cursol_max;
u_short		command_no;
DRAWENV		env[2];
DR_ENV		dr_env[2][2];
u_short		camera_ofs;
POLYEFE		*beam, *beam2, *needle[5];
long		pp_distance;
int			result;
int			DemoPlayTimer;

#include "battle.tbl"

#define AT_UKE (1)
#define TAME (0)
#define _motion_sake (41)	// 27 -> 41
#define HYPER_RG (0x20)	// 0x28
#define HYPER_B (0x10)	// 0x20

extern u_char	SubStatus;
extern P_DATA player_data[];

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BATTLE SCENE TASK                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int Battle()
{
	int i, j;
	int vcount;

	vcount = VSync(1);

	if (gcb.TitleSelect == 2) {		// デモスキップ
		if ((((PadDat[0].trg & PADST)>0) && (gcb.TitleSelect == 2) && (fade.status == 0) && (BattleStatus != _fade_wait) && (BattleStatus != _win_demo)) ||
			(++DemoPlayTimer == 60 * 30)) {
			XA_CLR();/*本当はポーズ*/
			pcb.req = pcb.pno;
			FadeInit( FADE_OUT, 0x10);
		}
	}

#if 0
	POSITION.offy = 120;
	if (eq_timer) {
		if (--eq_timer & 1) POSITION.offy = 128;
	}
#else
	// 地震エフェクト
	env[PSDIDX].ofs[X] = 160;
	env[PSDIDX].ofs[Y] = 120 + ((PSDIDX ^ 1) * 240);
	env[PSDIDX].dfe = 0;
	SetDrawEnv( &dr_env[PSDIDX][0], &env[PSDIDX]);
	AddPrim( &spriteot_tag[PSDIDX][(1 << SPRITEOT_LENGTH) - 1], &dr_env[PSDIDX][0]);
	if (eq_timer) {
		if (--eq_timer & 1) {
//			env[PSDIDX].ofs[X] += 8;
			env[PSDIDX].ofs[Y] += 8;
		}
	}
	SetDrawEnv( &dr_env[PSDIDX][1], &env[PSDIDX]);
	AddPrim( &bgot_tag[PSDIDX][(1 << BGOT_LENGTH) - 1], &dr_env[PSDIDX][1]);
#endif

	pp = player + battleturn;
	ep = player + (battleturn ^ 1);
	for (i = 0; i < 3; i++) {
		if (eflt[i] > 256) eflt[i] -= (eflt[i] >> 3);
		else if (eflt[i] < -256) eflt[i] -= (eflt[i] >> 3);
		else eflt[i] = 0;
	}
	get_parts_ws_val(&pp->mod->objpos[1], NULL, NULL, &pos[0]);
	get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[1]);
	if ((cam.mode) || (BattleStatus < _vs_wait) || (BattleStatus > _fade_wait)) {
		cam.view.vrx = (pos[0].vx - ((pos[0].vx - pos[1].vx) / 2)) / 4096;
		cam.view.vry = (pos[0].vy - ((pos[0].vy - pos[1].vy) / 2)) / 4096;
		cam.view.vrz = (pos[0].vz - ((pos[0].vz - pos[1].vz) / 2)) / 4096;
	}
	if (BattleStatus == _command) {
		{
			long ll;
			POL4 pol4;

			/* 根性ゲージ */
			if ((cursol-6)->spd[Y] == 0) {
				if (pp->ap > pp->apmax) pp->ap = 0;
				if (pp->ap < pp->apdisp) pp->apdisp += (((pp->ap - pp->apdisp) / 4) - 1);
				if (pp->ap > pp->apdisp) pp->apdisp += (((pp->ap - pp->apdisp) / 4) + 1);
				pol4.code = 0x2c;
				ll = ((pp->apdisp % (pp->apmax + 1)) * 174) / pp->apmax;
				if (battleturn == 1) {
					pol4.sxy[0][X] =
					pol4.sxy[2][X] = 247 - 160 - ll;
					pol4.sxy[1][X] =
					pol4.sxy[3][X] = 247 - 160;
				} else {
					pol4.sxy[0][X] =
					pol4.sxy[2][X] = 73 - 160;
					pol4.sxy[1][X] =
					pol4.sxy[3][X] = 73 - 160 + ll;
				}
				pol4.sxy[0][Y] =
				pol4.sxy[1][Y] = 193 - 120;
				pol4.sxy[2][Y] =
				pol4.sxy[3][Y] = 203 - 120;
				pol4.uv[0][1] =
				pol4.uv[1][1] =
				pol4.uv[2][1] =
				pol4.uv[3][1] = 232;
				ll = ll * pp->crank / 4;
				if (battleturn == 1) {
					pol4.uv[0][0] =
					pol4.uv[2][0] = ll;
					pol4.uv[1][0] =
					pol4.uv[3][0] = 0;
				} else {
					pol4.uv[0][0] =
					pol4.uv[2][0] = 0;
					pol4.uv[1][0] =
					pol4.uv[3][0] = ll;
				}
				pol4.sz[0][0] = (1 << (14 - SPRITEOT_LENGTH));
				pol4.rgb[0][R] =
				pol4.rgb[1][R] =
				pol4.rgb[0][G] =
				pol4.rgb[1][G] =
				pol4.rgb[0][B] =
				pol4.rgb[1][B] = 0xc0;
				pol4.rgb[2][R] =
				pol4.rgb[3][R] =
				pol4.rgb[2][G] =
				pol4.rgb[3][G] =
				pol4.rgb[2][B] =
				pol4.rgb[3][B] = 0x20;
				Poly4Set( ((1 << 9) | (1 << 7) | (0 << 5) | 13), (509 << 6), &pol4, &spriteot[ PSDIDX ]);
			}
		}
	}
	battle_task[BattleStatus]();

    camera_move();

	/* プレイヤー処理 */
	for (i = 0, pp = player; i < 2; i++, pp++) {
		if ((pp->mot->frame == 0) && (next_motion[pp->mot->num * 2] != -1))
			motion_init( pp->motd, pp->mot, next_motion[pp->mot->num * 2], next_motion[pp->mot->num * 2 + 1]);
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
		if (pp->hyper) {
			/* はいぱぁもーど */
			pslt[2].vx = (pp->mod->pos[X] >> 12) - cam.view.vpx;
			pslt[2].vy = (pp->mod->pos[Y] >> 12) - cam.view.vpy;
			pslt[2].vz = (pp->mod->pos[Z] >> 12) - cam.view.vpz;
			GsSetFlatLight(2,&pslt[2]);
			{
				MATRIX m;
	
				ReadColorMatrix(&m);
				m.m[R][2] = 
				m.m[G][2] = 0x4000;
				m.m[B][2] = 0x3000;
				SetColorMatrix(&m);
			}
#if 0
			if ((gcb.GlobalTimer % 5) < 2) {
				pp->model_col[R] = 0xff;
				pp->model_col[G] = 0xd8;
				pp->model_col[B] = 0x40;
				pp->render = jt_colorcset;
				pp->reflect = 0xc0;
			} else {
				pd = (P_DATA *) player_data + pp->chrno;
				pp->render = pd->render;
				pp->reflect = pd->reflect;
			}
#endif
			if (BattleStatus <= _fade_wait) {
#if 1
				get_parts_ws_val(&player[i].mod->objpos[1], NULL, NULL, &pos[0]);
				if (pos[0].vx != 0) {
					for (j = 0; j < 3; j++) {
						cvec.r =
						cvec.g = 0;
						cvec.b = 1;
						EffectEntry( 3, &pos[0], NULL, &cvec);					// 拡散線
					}
//					if ((LocalTimer % 3) == 0) {
//						get_parts_ws_val(&pp->mod->objpos[1], NULL, NULL, &pos[0]);
//						EffectEntry(29, &pos[0], NULL, NULL);					// 拡散線
//					}
				}
#endif
			}
		}
		if (*pp->render == &jt_wire2set) {
			pp->model_col[R] =
			pp->model_col[B] = 0;
			pp->model_col[G] = (gcb.GlobalTimer << 1) & 0x7f;
			if (pp->model_col[G] >= 0x40) pp->model_col[G] = 0x80 - pp->model_col[G];
		}
		model_col[R] = pp->model_col[R];
		model_col[G] = pp->model_col[G];
		model_col[B] = pp->model_col[B];
		jt_init4();
		pp->render();
		model_sort( pp->mod, pp->reflect );
		kage_set( pp->mod , &bgot[ PSDIDX ]);
		{	/* 数字キャラナンバーセット */
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
		if (BattleStatus >= _command_init)
		{
			long ll, max;
			POL4 pol4;

			if (pp->hp > pp->hpmax) pp->hp = 0;
			ll = pp->hp;
			if (ll > 9999) ll = 9999;
			if (ll < pp->hpdisp) pp->hpdisp += (((ll - pp->hpdisp) / 4) - 1);
			if (ll > pp->hpdisp) pp->hpdisp += (((ll - pp->hpdisp) / 4) + 1);

			if (pp->dp > pp->dpmax) pp->dp = 0;
			ll = pp->dp;
			if (ll > 9999) ll = 9999;
			if (ll < pp->dpdisp) pp->dpdisp += (((ll - pp->dpdisp) / 4) - 1);
			if (ll > pp->dpdisp) pp->dpdisp += (((ll - pp->dpdisp) / 4) + 1);

			pol4.code = 0x38;
			max = pp->hpmax;
			if (max > 9999) max = 9999;
			ll = ((pp->hpdisp % (max + 1)) * 55) / max;
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
			max = pp->dpmax;
			if (max > 9999) max = 9999;
			ll = ((pp->dpdisp % (max + 1)) * 55) / max;
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
		FntPrint("p%dLoad = %d\n", i + 1, VSync(1)-vcount);
		vcount = VSync(1);
	}
	jt_init4();
	pslt[0].r = 0x00; pslt[0].g = 0x00; pslt[0].b = 0x00;
	GsSetFlatLight(2,&pslt[0]);
	if (fade.status == FADE_OUT) {
		gcb.ClearMode = 0;
	}
	if (gcb.ClearMode == 0) bg_main();

	FntPrint("bgLoad = %d\n",VSync(1)-vcount);

	return( 0 );
};


void dummy()
{
}


const char bg_cameranum[] = {
	0,	//  0 kirikabu
	0,	//  1 bg03
	2,	//  2 bg04y
	9,	//  3 bg05
	1,	//  4 bg06
	3,	//  5 bg07
	1,	//  6 bg08
	8,	//  7 bg09
	0,	//  8 bg03y
	9,	//  9 bg05y
	1,	// 10 bg06y
	3,	// 11 bg07y
	7,	// 12 bg10(nemoto)
	0,	// 13 bg11(maruta)
	0,	// 14 bg12(footstep)
	2,	// 15 bg13(bg04)
	0,	// 16 bg99
	8,	// 17 bg09y
	0,	// 18 bg98
	6,	// 19 bglast
	0,	// 20 bg97
	0,	// 21 bg02y(kirikabu)
	7,	// 22 bg10y
	0,	// 23 bg11y
	4,	// 24 bgmachi
	1,	// 25 bg08y
	5,	// 26 bgsp
};


void screen_set()
{
	SVECTOR svec;
	u_short pal,chr,mode,wait;
	int i, j;
	PATH3 *path;

	if (cam.mode == 0) {
		battleturn = gcb.turn;
		path = (PATH3 *) path3tbl + bg_cameranum[gcb.bg_no];
		cam.mode = 2;
		cam.timer = 0;
		cam.totaltime = path->time;
		cam.start.vx = path->p0.vx;
		cam.start.vy = path->p0.vy;
		cam.start.vz = path->p0.vz;
		cam.relay.vx = path->p1.vx;
		cam.relay.vy = path->p1.vy;
		cam.relay.vz = path->p1.vz;
		cam.terminal.vx = path->p2.vx;
		cam.terminal.vy = path->p2.vy;
		cam.terminal.vz = path->p2.vz;
		if (battleturn) {
			cam.start.vx *= -1;
			cam.relay.vx *= -1;
			cam.terminal.vx *= -1;
		}

		if (gcb.TitleSelect == 2) {
			svec.vz = 0;
			svec.vx = -64;
			svec.vy = -16;
			SpriteEntry(507, logo_ofs + 0x8000, &svec, NULL, 9, 0xff);
			svec.vx = 48;
			svec.vy = 24;
			name_status = SpriteEntry(508, logo_ofs + 0x0001, &svec, NULL, 9, 0xff);
			name_status->pmode = CLUT8 | NBLEND;
		}
		pal = (0x100 << 5) + 481;
		svec.vz = 2;
		for (j = 0; j < 6; j++) {
			svec.vy = num_pos[j * 6 + 1];
			for (i = 0; i < num_pos[j * 6]; i++) {
				svec.vx = num_pos[j * 6 + 2] + i * 7;
				chr = num_pos[j * 6 + 3];
				mode = num_pos[j * 6 + 4];
				wait = num_pos[j * 6 + 5];
				SpriteEntry(pal, chr, &svec, NULL, mode, wait);
			}
		}
		for (i = 0, j = 0; i < 5; i++) {
			pal = open_tbl[j++];
			chr = open_tbl[j++];
			svec.vx = open_tbl[j++];
			svec.vy = open_tbl[j++];
			mode = open_tbl[j++];
			wait = open_tbl[j++];
			name_status = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
		}
	}
	if (cam.timer == 30) SE_ENT(SE_DASH1);
	if (cam.timer == 52) SE_ENT(SE_CRASH);
	if (cam.timer == 92) {
		(name_status)->status =
		(name_status-1)->status =
		(name_status-2)->status = 14;	// フェードアウト
	} else
	if (cam.timer == (cam.totaltime - 1)) {
		svec.vz = 2;
		for (i = 0, j = 0; i < 9; i++) {
			if (i > 6) svec.vz = 1;
			pal = scr_tbl[j++];
			chr = scr_tbl[j++];
			svec.vx = scr_tbl[j++];
			svec.vy = scr_tbl[j++];
			mode = scr_tbl[j++];
			wait = scr_tbl[j++];
			name_status = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
		}
		BattleStatus = _vs_wait;
	}
}


void vs_wait()
{
	if (name_status->status == 0) BattleStatus = _command_init;
}


void win_demo()
{
	int i;

	cam.mode = 3;
	cam.svec.vx = 0;
	cam.svec.vy = -1200;
	cam.svec.vz = -1500;
	Projection = 500;
	if (gcb.TitleSelect) i = 0;
	else i = battleturn ^ 1;
	if (LocalTimer == 22) SE_ENT(SE_CRASH);
	if (((LocalTimer >= 40) && (gcb.TitleSelect != 2) &&
		(((PadDat[i].trg & PADST)>0) || ((PadDat[i].trg & PADRR)>0) || ((PadDat[i].trg & PADRL)>0))) ||
		(LocalTimer >= (30*10))) {
		gcb.hp[0] = player[0].hp;
		gcb.hp[1] = player[1].hp;
		gcb.dp[0] = player[0].dp;
		gcb.dp[1] = player[1].dp;
		gcb.ap[0] = player[0].aura;
		gcb.ap[1] = player[1].aura;
		XA_CLR();/*本当はポーズ*/
		pcb.req = pcb.pno;
		FadeInit( FADE_OUT, 0x10);
		BattleStatus = _dummy;
	}
}


void fade_wait()
{
	if (LocalTimer == 10) {
		gcb.hp[0] = player[0].hp;
		gcb.hp[1] = player[1].hp;
		gcb.dp[0] = player[0].dp;
		gcb.dp[1] = player[1].dp;
		gcb.ap[0] = player[0].aura;
		gcb.ap[1] = player[1].aura;
		XA_CLR();/*本当はポーズ*/
		pcb.req = pcb.pno;
		FadeInit( FADE_OUT, 0x08);
	}
}


void command_init()
{
	u_short pal,chr,mode,wait;
	int i, j;

	if ((ba_totalturn) && ((cursol+(command_no*2))->status)) return;

	ba_totalturn++;
	if (pp->hp == 0) {
//		XA_CLR();/*本当はポーズ*/
//		XA_LOAD( XA_WIN );
		avec.vz = 2;
		avec.vx = 88 - 160;
		avec.vy = 144 - 120;
		SpriteEntry((0x100 << 5) + 489, syouri_ofs, &avec, NULL,12, 22);
		SpriteEntry((0x100 << 5) + 489, syouri_ofs, &avec, NULL,13, 22);
		SpriteEntry((0x100 << 5) + 488, syouri_ofs, &avec, NULL, 9, 22);
		avec.vx = 48 - 160;
		avec.vy = 72 - 120;
		if (battleturn) {
			SpriteEntry((0x010 << 5) + 487, namevs_ofs + 0, &avec, NULL, 3, 0);
			cam.angle = 1792;
		} else {
			SpriteEntry((0x010 << 5) + 495, namevs_ofs + 1, &avec, NULL, 4, 0);
			cam.angle = -1792;
		}
		cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
		LocalTimer = 0;
		BattleStatus = _win_demo;
	} else if ((gcb.TitleSelect != 2) && (ba_totalturn > 2)) {
		/* 一回づつで終了 */
		LocalTimer = 0;
		BattleStatus = _fade_wait;
	} else {
		avec.vz = 2;
		if ((gcb.TitleSelect == 2) || ((gcb.TitleSelect) && (battleturn))) {
			i = 2;
			j = 12;
		} else {
			i = 0;
			j = 0;
		}
		if (battleturn == 1) j += 60;
		for (; i < 10; i++) {
			pal = command_tbl[j++];
			chr = command_tbl[j++];
			avec.vx = command_tbl[j++];
			avec.vy = command_tbl[j++];
			mode = command_tbl[j++];
			wait = command_tbl[j++];
			cursol = SpriteEntry(pal, chr, &avec, NULL, mode, wait);
		}
		command_no = 0;
		cursol_pos = 0;
		cursol_max = 3; // プレプレは選べない
		pp->command[0] = pp->command[1] = pp->command[2] = pp->command[3] = pp->command[4] = -1;
		pp->ap = pp->apmax = (pp->crank * 100);
		pp->apdisp = 0;

		BattleStatus = _command;
	}
}


void command()
{
	long sp;
	int i, cpu_command;

	/* ＣＰＵ */
	if ((gcb.TitleSelect == 2) || ((gcb.TitleSelect) && (battleturn))) {
		PadDat[battleturn].rpt =
		PadDat[battleturn].trg = 0;
		if ((LocalTimer & 0x07) == 0) {
			if ((pp->hyper == 1) && (pp->ap == pp->apmax) && (ep->dp < (ep->dpmax / 8))) {
				cpu_command = 3;	// オーラ
			} else if ((pp->hyper == 0) && 
						(((pp->aura > 0) && (pp->dp == pp->dpmax) && (ep->dp < ep->dpmax)) ||
						 ((pp->dp == pp->dpmax) && (ep->hp < ep->hpmax) && (pp->ap == pp->apmax)) ||
						 ((ep->dp == 0) && (ep->hp < (ep->hpmax / 4)) && (pp->ap < pp->apmax)) ) ) {
				cpu_command = 2;	// ためる
			} else if ((((pp->ap >= 200) && (command_no == 0) && (ep->dp > (ep->dpmax / 2))) ||
						((pp->crank < 4) && (pp->ap >= 200) && (ep->dp < (ep->dpmax / 2)))) &&
						 (pp->chrno != MODEL_TC) &&
						 (pp->chrno != MODEL_SP) ) {
				cpu_command = 1;	// とっしん
			} else {
				cpu_command = 0;	// つの
			}
			if (cursol_pos < cpu_command) {
				PadDat[battleturn].rpt ^= PADLD;
			} else if (cursol_pos > cpu_command) {
				PadDat[battleturn].rpt ^= PADLU;
			} else {
				PadDat[battleturn].trg ^= PADRR;
			}
			if ((pp->hp < (pp->hpmax / 2)) && (pp->dp == 0) && ((rand() % 16) == 0)) {	// ＤＦ回復
				PadDat[battleturn].trg ^= PADST;
			}
		}
	}
	/* カーソル操作 */
	cursol->pal = (0x120 << 5) + 484 + 5;
	(cursol-5)->pal =
	(cursol-4)->pal =
	(cursol-3)->pal =
	(cursol-2)->pal = (0x120 << 5) + 484;
	if (pp->hyper) (cursol-3)->pal = (0x120 << 5) + 492;
	else (cursol-2)->pal = (0x120 << 5) + 492;
	if (cursol->status == 0) {
		(cursol-7)->vzoomac =
		(cursol-6)->vzoomac =
		cursol->vzoomac = zoom_acc * 5;
		if (battleturn == 1) {
			(cursol-5)->acc[X] =
			(cursol-4)->acc[X] =
			(cursol-3)->acc[X] =
			(cursol-2)->acc[X] =
			(cursol-1)->acc[X] = acceleration * 2;
		} else {
			(cursol-5)->acc[X] =
			(cursol-4)->acc[X] =
			(cursol-3)->acc[X] =
			(cursol-2)->acc[X] =
			(cursol-1)->acc[X] = -acceleration * 2;
		}
		if ((gcb.TitleSelect != 2) && ((gcb.TitleSelect == 0) || (battleturn == 0))) {
			if (battleturn == 1) {
				(cursol-9)->acc[X] =
				(cursol-8)->acc[X] = -acceleration * 2;
				if (command_no) (cursol+1)->acc[X] = -acceleration * 2;
			} else {
				(cursol-9)->acc[X] =
				(cursol-8)->acc[X] = acceleration * 2;
				if (command_no) (cursol+1)->acc[X] = acceleration * 2;
			}
		} else if (command_no) cursol--;
		command_no = 0;
		BattleStatus = _command_analyze;
	} else if (cursol->vzoomac == 0) {
		cursol->pal = (0x120 << 5) + 484 + cursol_pal[(LocalTimer >> 1) % 6];
		if ((PadDat[battleturn].trg & PADST)>0) {
			SE_ENT(SE_OK1);
				cursol->status = 10;
				cursol->vzoomsp = 0;
				cursol->vzoomac = zoom_acc * 5;
				if (pp->ap == pp->apmax) pp->dp += ((pp->dpmax * 40) / 100);
				else if ((pp->ap == 300) && (pp->apmax == 400)) pp->dp += ((pp->dpmax * 35) / 100);
				else if ((pp->ap == 200) && (pp->apmax == 300)) pp->dp += ((pp->dpmax * 30) / 100);
				else if (pp->ap == (pp->apmax / 2)) pp->dp += ((pp->dpmax * 20) / 100);
				else if ((pp->ap == 100) && (pp->apmax == 300)) pp->dp += ((pp->dpmax * 15) / 100);
				else if ((pp->ap == 100) && (pp->apmax == 400)) pp->dp += ((pp->dpmax * 10) / 100);
				if (pp->dp > pp->dpmax) pp->dp = pp->dpmax;
				pp->ap = 0;
				pp->command[command_no] = -1;
				cursol->status = 9;
		} else if((PadDat[battleturn].rpt & PADLU)>0) {
			SE_ENT(SE_CUR1);
			cursol_pos--;
			if (cursol_pos < 0) cursol_pos = cursol_max;
			while ((cursol-5+cursol_pos)->pal == ((0x120 << 5) + 492)) {
				cursol_pos--;
				if (cursol_pos < 0) cursol_pos = cursol_max;
			}
		} else if((PadDat[battleturn].rpt & PADLD)>0) {
			SE_ENT(SE_CUR1);
			cursol_pos++;
			if (cursol_pos > cursol_max) cursol_pos = 0;
			while ((cursol-5+cursol_pos)->pal == ((0x120 << 5) + 492)) {
				cursol_pos++;
				if (cursol_pos > cursol_max) cursol_pos = 0;
			}
		} else if (((PadDat[battleturn].trg & PADRR)>0) || ((PadDat[battleturn].trg & PADRL)>0)) {
			if (((cursol_pos < 2) && (pp->ap < ((cursol_pos + 1) * 100))) || ((cursol_pos == 3) && (pp->ap < pp->apmax))) {	// ＣＰ足りないよ;
				SE_ENT(SE_PAUSE);
			} else {
				SE_ENT(SE_OK1);
				if (command_no == 0) {
					if ((gcb.TitleSelect != 2) && ((gcb.TitleSelect == 0) || (battleturn == 0))) {
						for (i = 9; i >= 8; i--) {
							sp = (cursol-i)->pos[Y];
							(cursol-i)->pos[Y] -= (24 << 16);
							(cursol-i)->acc[Y] = acceleration;
							while ((cursol-i)->pos[Y] < sp) {
								(cursol-i)->pos[Y] -= (cursol-i)->spd[Y];
								(cursol-i)->spd[Y] -= (cursol-i)->acc[Y];
							}
						}
						avec.vy = 200 - 120;
						avec.vz = 2;
						if (battleturn == 1) {
							avec.vx =  16 - 160;
							SpriteEntry((0x100 << 5) + 485, fix_ofs + 28, &avec, NULL, 3, 0);
						} else {
							avec.vx = 256 - 160;
							SpriteEntry((0x100 << 5) + 485, fix_ofs + 28, &avec, NULL, 4, 0);
						}
					}
				}
				if (battleturn == 1) {
					avec.vx = 252 - 160 - (command_no * 60);
				} else {
					avec.vx =  20 - 160 + (command_no * 60);
				}
				avec.vy = 208 - 120;
				avec.vz = 2;
				SpriteEntry((0x120 << 5) + 485, ap2_ofs + cursol_pos, &avec, NULL, 2, 0);
				SpriteEntry((0x120 << 5) + 486, ap2_ofs + cursol_pos + 5, &avec, NULL, 2, 1);
				cursol->status = 10;
				cursol->vzoomsp = 0;
				cursol->vzoomac = zoom_acc * 5;
				(cursol-5+cursol_pos)->status = 10;
				(cursol-5+cursol_pos)->vzoomsp = 0;
				(cursol-5+cursol_pos)->vzoomac = zoom_acc * 5;
				if (cursol_pos < 2) {
					pp->ap -= (cursol_pos + 1) * 100;
				} else {
					if (pp->ap == pp->apmax) pp->aura += 70;
					else if ((pp->ap == 300) && (pp->apmax == 400)) pp->aura += 60;
					else if ((pp->ap == 200) && (pp->apmax == 300)) pp->aura += 50;
					else if (pp->ap == (pp->apmax / 2)) pp->aura += 40;
					else if ((pp->ap == 100) && (pp->apmax == 300)) pp->aura += 30;
					else if ((pp->ap == 100) && (pp->apmax == 400)) pp->aura += 20;
					if (pp->aura > 100) pp->aura = 100;
					pp->ap = 0;
				}
				pp->command[command_no] = cursol_pos;
				if ((command_no++ == 4) || (pp->ap == 0)) {
					pp->command[command_no] = -1;
					cursol->status = 9;
				}
			}
		} else if (((PadDat[battleturn].trg & PADRD)>0) && (command_no)) {
			SE_ENT(SE_CANCEL);
			if (--command_no == 0) {
				if ((gcb.TitleSelect != 2) && ((gcb.TitleSelect == 0) || (battleturn == 0))) {
					for (i = 9; i >= 8; i--) {
						sp = (cursol-i)->pos[Y];
						(cursol-i)->pos[Y] += (24 << 16);
						(cursol-i)->acc[Y] = -acceleration;
						while ((cursol-i)->pos[Y] > sp) {
							(cursol-i)->pos[Y] -= (cursol-i)->spd[Y];
							(cursol-i)->spd[Y] -= (cursol-i)->acc[Y];
						}
					}
					(cursol+1)->acc[Y] = acceleration * 2;
				}
			}
			if ((gcb.TitleSelect != 2) && ((gcb.TitleSelect == 0) || (battleturn == 0))) {
				(cursol+2+(command_no*2))->acc[Y] =
				(cursol+3+(command_no*2))->acc[Y] = acceleration * 2;
			} else {
				(cursol+1+(command_no*2))->acc[Y] =
				(cursol+2+(command_no*2))->acc[Y] = acceleration * 2;
			}
			cursol->status = 10;
			cursol->vzoomsp = 0;
			cursol->vzoomac = zoom_acc * 5;
			pp->ap += (pp->command[command_no] + 1) * 100;
		}
		cursol->pos[Y] = (((144 - 120) + (cursol_pos * 16)) << 16);
		if ((gcb.TitleSelect != 2) && ((gcb.TitleSelect == 0) || (battleturn == 0))) (cursol-5+cursol_pos)->pal = (0x120 << 5) + 485;
	}

#ifndef PREPRE
	if((PadDat[0].trg & PADSL)>0) SubStatus++;		//	テストモード
	if((PadDat[0].trg & PADRU)>0) SubStatus = 5;	//	テストモード
#endif
}


const u_short cofs_tbl1[] = {
	0, 11, 16, 21,
};

const u_short cofs_tbl2[] = {
	5, 26,
};

void command_analyze()
{
	if ((command_no == 4) || (pp->command[command_no] == -1)) {
		if ((command_no == 0) && ((cursol-1)->status)) return;
//		if (((cursol+2+((command_no-1)*2))->status) || ((cursol+3+((command_no-1)*2))->status)) return;
		if (ba_totalturn == 1) {
			if (battleturn) cam.view.vpx = -2100;
			else cam.view.vpx = 2100;
			cam.view.vpy = -300;
			cam.view.vpz = 200;
		}
		battleturn ^= 1;
		BattleStatus = _command_init;
		return;
	}
	pp->totaltime = 0;
	pp->seq = seq_work;
	switch (pp->command[command_no]) {
		case 0:	// つの
			camera_ofs = cofs_tbl1[rand() % 3];
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 10;				// カメラのパス
			(*pp->seq++) = _goahead;		// 次のタスク
			(*pp->seq++) = 9;				// ダッシュモーション
			(*pp->seq++) = 0 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _attack;			// 次のタスク
			if ((command_no == 3) || (pp->command[command_no + 1] != 0)) {
				/* つの単発 */
				switch (rand() % 3) {
					case 0:
						(*pp->seq++) = 11;				// 攻撃モーション
						(*pp->seq++) = 12;				// 戻りモーション
						(*pp->seq++) = 3;				// ダメージモーション
						(*pp->seq++) = impact_flame[pp->chrno][0];	// 攻撃発生フレーム
						(*pp->seq++) = impact_pos[pp->chrno][0];	// 攻撃個所
						break;
					case 1:
						(*pp->seq++) = 13;				// 攻撃モーション
						(*pp->seq++) = 14;				// 戻りモーション
						(*pp->seq++) = 5;				// ダメージモーション
						(*pp->seq++) = impact_flame[pp->chrno][1];	// 攻撃発生フレーム
						(*pp->seq++) = impact_pos[pp->chrno][1];	// 攻撃個所
						break;
					case 2:
						(*pp->seq++) = 15;				// 攻撃モーション
						(*pp->seq++) = 16;				// 戻りモーション
						(*pp->seq++) = 7;				// ダメージモーション
						(*pp->seq++) = impact_flame[pp->chrno][2];	// 攻撃発生フレーム
						(*pp->seq++) = impact_pos[pp->chrno][2];	// 攻撃個所
						break;
				}
			} else if ((command_no == 0) &&
				(pp->command[command_no + 1] == 0) &&
				(pp->command[command_no + 2] == 0) &&
				(pp->command[command_no + 3] == 0)) {
				/* つの４連続 */
				(*pp->seq++) = 17;				// 攻撃モーション
				(*pp->seq++) = 0;				// 戻りモーション
				(*pp->seq++) = 3;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][0];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][0];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 1 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _attack;			// 次のタスク
				(*pp->seq++) = 19;				// 攻撃モーション
				(*pp->seq++) = 0;				// 戻りモーション
				(*pp->seq++) = 5;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][1];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][1];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 2 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _attack;			// 次のタスク
				(*pp->seq++) = 21;				// 攻撃モーション
				(*pp->seq++) = 22;				// 戻りモーション
				(*pp->seq++) = 7;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][2];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][2];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 3 + camera_ofs;	// カメラのパス
				if (((pp->size + 1) < ep->size) ||
					(pp->chrno == MODEL_TN) ||
					(pp->chrno == MODEL_HM) ||
					(pp->chrno == MODEL_OS) ||
					(pp->chrno == MODEL_OT) ||
					(pp->chrno == MODEL_SK) ||
					(pp->chrno == MODEL_SP) ||
					(pp->chrno == MODEL_TC) ||
					(ep->chrno == MODEL_ZO) ||
					(ep->chrno == MODEL_YA) ||
					(ep->chrno == MODEL_MA) ||
					(ep->chrno == MODEL_SP) ||
					(ep->chrno == MODEL_AZ)) {
					//	チャージ
					(*pp->seq++) = _tackle;			// 次のタスク
					(*pp->seq++) = 30;				// 攻撃モーション
					(*pp->seq++) = 0;				// 戻りモーション
					if ((pp->chrno == MODEL_TN) ||
						(pp->chrno == MODEL_HM) ||
						(pp->chrno == MODEL_OS) ||
						(pp->chrno == MODEL_OT)) {
						(*pp->seq++) = 27;				// ダメージモーション
					} else {
						(*pp->seq++) = 31;				// ダメージモーション
					}
					(*pp->seq++) = impact_flame[pp->chrno][3];	// 攻撃発生フレーム
				} else {
					//	投げ
					if ((pp->chrno == MODEL_KM) || (pp->chrno == MODEL_K2)) {	// カマキリ投げ
						(*pp->seq++) = _motion_wait;	// 次のタスク
						(*pp->seq++) = _ranbu;			// 次のタスク
						(*pp->seq++) = 23;				// 攻撃モーション
						(*pp->seq++) = 0;				// 戻りモーション
						(*pp->seq++) = 3;				// ダメージモーション
						(*pp->seq++) = 13;				// 攻撃発生フレーム
						(*pp->seq++) = 0;				// 攻撃個所
						(*pp->seq++) = 5;				// ダメージモーション
						(*pp->seq++) = 27;				// 攻撃発生フレーム
						(*pp->seq++) = 0;				// 攻撃個所
						(*pp->seq++) = 27;				// ダメージモーション
						(*pp->seq++) = 65;				// 攻撃発生フレーム
						(*pp->seq++) = 0;				// 攻撃個所
					} else {
						(*pp->seq++) = _kumi;			// 次のタスク
						(*pp->seq++) = 25;				// 差込モーション
						(*pp->seq++) = _motion_wait;	// 次のタスク
						(*pp->seq++) = _nage;			// 次のタスク
						(*pp->seq++) = 23;				// 投げモーション
						(*pp->seq++) = 4 + camera_ofs;	// カメラのパス
						if (((pp->chrno >= MODEL_EM) &&
							 (pp->chrno <= MODEL_NK)) ||
							 (pp->chrno == MODEL_PC) ||
							 (pp->chrno == MODEL_SO))
							 (*pp->seq++) = nagerare_motion2[ep->size][pp->size];	// 投げモーション
						else (*pp->seq++) = nagerare_motion[ep->size][pp->size];	// 投げモーション
						(*pp->seq++) = impact_flame[pp->chrno][4];	// 攻撃発生フレーム
					}
				}
			} else if ((command_no <= 1) &&
				(pp->command[command_no + 1] == 0) &&
				(pp->command[command_no + 2] == 0)) {
				/* つの３連続 */
				(*pp->seq++) = 17;				// 攻撃モーション
				(*pp->seq++) = 0;				// 戻りモーション
				(*pp->seq++) = 3;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][0];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][0];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 1 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _attack;			// 次のタスク
				(*pp->seq++) = 19;				// 攻撃モーション
				(*pp->seq++) = 0;				// 戻りモーション
				(*pp->seq++) = 5;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][1];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][1];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 2 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _attack;			// 次のタスク
				(*pp->seq++) = 21;				// 攻撃モーション
				(*pp->seq++) = 22;				// 戻りモーション
				(*pp->seq++) = 7;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][2];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][2];	// 攻撃個所
			} else if ((command_no <= 2) &&
				(pp->command[command_no + 1] == 0)) {
				/* つの２連続 */
				(*pp->seq++) = 17;				// 攻撃モーション
				(*pp->seq++) = 0;				// 戻りモーション
				(*pp->seq++) = 3;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][0];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][0];	// 攻撃個所
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 1 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _attack;			// 次のタスク
				(*pp->seq++) = 19;				// 攻撃モーション
				(*pp->seq++) = 20;				// 戻りモーション
				(*pp->seq++) = 5;				// ダメージモーション
				(*pp->seq++) = impact_flame[pp->chrno][1];	// 攻撃発生フレーム
				(*pp->seq++) = impact_pos[pp->chrno][1];	// 攻撃個所
			}
			(*pp->seq++) = _motion_wait;	// 次のタスク
			(*pp->seq++) = _returnset;		// 次のタスク
			(*pp->seq++) = 29;	// バックステップモーション
			break;
		case 1:	// とっしん
			camera_ofs = cofs_tbl2[rand() % 1];
			camera_ofs = cofs_tbl2[0];
			cam.work = &pp->mod->pos[X];	// 注視点－＞プレイヤー
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 0 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _floting;		// 次のタスク
			(*pp->seq++) = 1;				// 飛行モーション
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 1 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 2 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _rush;			// 次のタスク
			if (ep->dp == 0) {
				(*pp->seq++) = _rush_hit;		// 次のタスク
				(*pp->seq++) = 7;				// ダメージモーション
				(*pp->seq++) = _rush1;			// 次のタスク
				(*pp->seq++) = _rush2;			// 次のタスク
				(*pp->seq++) = 28;				// 飛行モーション
				if ((command_no <= 3) &&
					(pp->command[command_no + 1] == 1)) {
					(*pp->seq++) = _camera_set2;	// 次のタスク
					(*pp->seq++) = 3 + camera_ofs;	// カメラのパス
					(*pp->seq++) = _camera_set2;	// 次のタスク
					(*pp->seq++) = 4 + camera_ofs;	// カメラのパス
					(*pp->seq++) = _rush3;			// 次のタスク
					(*pp->seq++) = 7;				// ダメージモーション
					(*pp->seq++) = _rush4;			// 次のタスク
				}
			} else {
				(*pp->seq++) = _zoom;			// 次のタスク
				(*pp->seq++) = _renda;			// 次のタスク
				(*pp->seq++) = _rush_pass;		// 次のタスク
			}
			(*pp->seq++) = _returnset2;		// 次のタスク
			break;
		case 2:	// ためる
			cam.work = &pp->mod->pos[X];	// 注視点－＞プレイヤー
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 37;				// カメラのパス
			(*pp->seq++) = _aura_tame0;		// 次のタスク
			(*pp->seq++) = _aura_tame1;		// 次のタスク
			(*pp->seq++) = _returnset2;		// 次のタスク
			break;
		case 3:	// オーラ
			pp->aura = 0;
			pp->hyper = 0;
			pd = (P_DATA *) player_data + pp->chrno;
			pp->render = pd->render;
			pp->reflect = pd->reflect;
			/* ビーム */
#if 1
			camera_ofs = 32;
			(*pp->seq++) = _laser0;			// 次のタスク
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 0 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _laser1;			// 次のタスク
			(*pp->seq++) = _camera_set2;	// 次のタスク
			(*pp->seq++) = 1 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _laser2;			// 次のタスク
			if (ep->dp == 0) {
				(*pp->seq++) = _camera_set2;	// 次のタスク
				(*pp->seq++) = 3 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _laser4;			// 次のタスク
				(*pp->seq++) = _motion_wait2;	// 次のタスク
			} else {
				(*pp->seq++) = _camera_set4;	// 次のタスク
				(*pp->seq++) = 2 + camera_ofs;	// カメラのパス
				(*pp->seq++) = _laser3;			// 次のタスク
				(*pp->seq++) = _laser5;			// 次のタスク
			}
#else
			/* マジックミサイル */
			camera_ofs = 36;
			(*pp->seq++) = _missile0;		// 次のタスク
			(*pp->seq++) = _camera_set4;	// 次のタスク
			(*pp->seq++) = 0 + camera_ofs;	// カメラのパス
			(*pp->seq++) = _missile1;		// 次のタスク
			(*pp->seq++) = _missile2;		// 次のタスク
#endif
			(*pp->seq++) = _returnset2;		// 次のタスク
			break;
	}
	*pp->seq = _command_analyze;
	pp->seq = seq_work;
	BattleStatus = *pp->seq++;
}


void command_next()
{
	(cursol+3+(command_no*2))->status = 9;
	(cursol+3+(command_no*2))->pal = (0x120 << 5) + 486;
	if (battleturn == 1) {
		(cursol+2+(command_no*2))->acc[X] =
		(cursol+3+(command_no*2))->acc[X] = acceleration * 4;
	} else {
		(cursol+2+(command_no*2))->acc[X] =
		(cursol+3+(command_no*2))->acc[X] = -acceleration * 4;
	}
	command_no++;
}


int hit_check()
{
	int flag, hit_rate, dice;

	if (ep->hp == 0) return (0);	// 命中
	// 命中判定
	flag = pp->lv - ep->lv;		// レベル差
	if (flag > 20) flag = 20;	// 命中率
	else if (flag < -20) flag = -20;
	if (pp->hitrate <= ep->evasion) hit_rate = 0;
	else hit_rate = ((pp->hitrate - ep->evasion) * (100 + flag)) / 100;
	if (hit_rate > 100) hit_rate = 100;
	dice = rand() % 100;
	printf("hit_rate %d/%d%%\n", dice, hit_rate);
	if (dice < hit_rate) return (0);	// 命中
	else return (-1);	// 失敗
}


const short at_rate[] = {
	70, 55, 40, 20,  1,
};

int damage_set(short rate)
{
	int i, flag, chrno, damage;

	if (rate >= 0) {
		flag = ep->lv - pp->lv;		// レベル差
		if (flag > 9) flag = 9;		// ダメージ計算
		else if (flag < -9) flag = -9;
		damage = pp->attack - (((pp->attack * ep->deffence) / 100) + ((pp->attack * flag) / 100));
		if ((ep->dp > 0) && (BattleStatus != _nage) && (BattleStatus != _tackle) && (BattleStatus != _ranbu)) {
			i = ((ep->dp / (ep->dpmax / 4)));	// Ａ２防御計算
			i = 0;	// とりあえず再弱
			damage = (damage * at_rate[i]) / 100;
			ep->dp -= (damage * 70) / 100;
			damage = (damage * 30)/ 100;
		}
		damage += ((damage * rate) / 4);	// 追加ダメージ
		if (pp->hyper) damage += ((damage * 15) / 100);	// ハイパーモード追加ダメージ
		ep->hp -= damage;
		avec.vx = -16;										/* ダメージ数値の表示 */
		avec.vy = 16;
		avec.vz = 1;
		for (i = 0, flag = 0; i < 4; i++) {
			chrno = ((damage / keta4[i]) % 10);
			if ((chrno != 0) || (flag != 0) || (i == 3)) {
				SpriteEntry((0x100 << 5) + 486, fix_ofs + 29 + 19 + chrno, &avec, NULL, 7, 0);
				if (flag == 0) {
					flag = 1;
				}
				if (chrno == 1) avec.vx += 16;
				else avec.vx += 16;
			}
		}
		rate = rate * 32 + 128;
		if (rate > 255) rate = 255;
		sindo_set2( 0, rate, rate / 16);
		sindo_set2( 1, rate, rate / 16);
	} else {	// ミス！！
		avec.vx = -32;
		avec.vy = 16;
		avec.vz = 1;
		SpriteEntry((0x100 << 5) + 486, fix_ofs + 58, &avec, NULL, 7, 0);
		damage = -1;
	}
	if (ep->dp > ep->dpmax) {
		SE_ENT(SE_BREAK);
		cvec.r = 0;
		cvec.g = 1;
		cvec.b = 2;
		for (i = 0; i < 28; i++) {
			if (battleturn) trans.vx = ep->mod->pos[X] - ep->length;
			else trans.vx = ep->mod->pos[X] + ep->length;
			trans.vy = ep->mod->pos[Y] + (((rand() % 300) - 350) << 12);
			trans.vz = ep->mod->pos[Z] + (((rand() % 300) - 150) << 12);
			EffectEntry(27, &trans, &ep->mod->ang[X], &cvec);					// 破片
		}
		motion_init( ep->motd, ep->mot, 7, 1);
	}

	return (damage);
}


void camera_set2()
{
	PATH2 *path;

	if (cam.mode == 0) {
		path = (PATH2 *) path2tbl + (*pp->seq++);
		cam.mode = 2;
		cam.timer = 0;
		cam.totaltime = path->time;
		cam.start.vx = cam.view.vpx;
		cam.start.vy = cam.view.vpy;
		cam.start.vz = cam.view.vpz;
		cam.relay.vx = path->p0.vx;
		cam.relay.vy = path->p0.vy;
		cam.relay.vz = path->p0.vz;
		cam.terminal.vx = path->p1.vx;
		cam.terminal.vy = path->p1.vy;
		cam.terminal.vz = path->p1.vz;
		if (battleturn) {
			cam.relay.vx *= -1;
			cam.terminal.vx *= -1;
		}
		BattleStatus = *pp->seq++;
	}
}


void camera_set4()
{
	cam.mode = 0;
	camera_set2();
	cam.mode = 4;
}


void at_field(VECTOR *cpos)
{
	if ((ep->dp > 0) && ((LocalTimer & 0x01) == 0)) {
		PushMatrix();
		GsInitCoordinate2(WORLD,&coord);
		avec.vx = ep->mod->ang[X];
		avec.vy = ep->mod->ang[Y];
		avec.vz = ep->mod->ang[Z];
		RotMatrixYXZ_gte(&avec, &coord.coord);
		SetRotMatrix(&coord.coord);
		ApplyRotMatrixLV(cpos, &trans);
		pos[0].vx = ep->mod->pos[X] + trans.vx;
		pos[0].vy = ep->mod->pos[Y] + trans.vy;
		pos[0].vz = ep->mod->pos[Z] + trans.vz;
		PopMatrix();
		cvec.r = ((ep->dp / (ep->dpmax / 4)));
		cvec.r = 0;	// とりあえず再弱
		EffectEntry(8, &pos[0], &ep->mod->ang[X], &cvec);		// ＡＴフィールド
	}
}


void hibana(u_short flag)
{
	int i,j;

	if ((ep->dp == 0) || (BattleStatus == _tackle) || (BattleStatus == _ranbu)) {
		cvec.r = 0;
		cvec.g = 1;
		cvec.b = 2;
		for (i = 0; i < 28;) {
			for (j = 0; j < pp->hitpos; j++) {
				if (((flag >> j) & 1) == 0) {
					avec.vx = ((rand() << 20) >> 21) - 1024;
					avec.vy = ((rand() << 20) >> 20);
					avec.vz = 2048;
					EffectEntry( 7, &pos[j], &avec, &cvec);					// 火花
					i++;
				}
			}
		}
	} else {
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 28;) {
			for (j = 0; j < pp->hitpos; j++) {
				if (((flag >> j) & 1) == 0) {
					avec.vx = ((rand() << 20) >> 21) + ep->mod->ang[X];
					avec.vy = ep->mod->ang[Y] - 1024;
					avec.vz = ((rand() << 20) >> 21) + 1024 + ep->mod->ang[Z];
					EffectEntry( 7, &pos[j], &avec, &cvec);					// 火花
					i++;
				}
			}
		}
	}
}


void hit_effect(u_short flag)
{
	int j;

	if ((ep->dp == 0) || (BattleStatus == _tackle) || (BattleStatus == _ranbu)) {
		avec.vx =
		avec.vy = 0;
		avec.vz = 1024;
		cvec.r = 1;
		cvec.g = 3;
		cvec.b = 3;
		for (j = 0; j < pp->hitpos; j++) {
			if (((flag >> j) & 1) == 0) {
				EffectEntry(25, &pos[j], &avec, &cvec);					// 円形エフェクト
			}
		}
		switch (rand() % 3) {
			case 0:
				SE_ENT(SE_ATTACK1);
				break;
			case 1:
				SE_ENT(SE_ATTACK2);
				break;
			case 2:
				SE_ENT(SE_ATTACK3);
				break;
		}
	} else {
		switch (rand() % 2) {
			case 0:
				SE_ENT(SE_BARIA1);
				break;
			case 1:
				SE_ENT(SE_BARIA2);
				break;
		}
	}
	LightPos[X] =
	LightPos[Y] =
	LightPos[Z] = 0;
	for (j = 0; j < pp->hitpos; j++) {
		if (((flag >> j) & 1) == 0) {
			Sprite3dEntry( 5, (480 << 6) | (288 >> 4), gol_ofs, &pos[j]); // ヒットマーク
			LightPos[X] += pos[j].vx >> 12;
			LightPos[Y] += pos[j].vy >> 12;
			LightPos[Z] += pos[j].vz >> 12;
			if ((j > 0) && (LightPos[X] != (pos[j].vx >> 12))) {
				LightPos[X] /= 2;
				LightPos[Y] /= 2;
				LightPos[Z] /= 2;
			}
		}
	}
	eflt[R] = 0x7000; eflt[G] = 0x6000; eflt[B] = 0x6000;	// 反射光
}


void goahead()
{
	int rr;

	(cursol+3+(command_no*2))->status = 11;
	if (pp->mot->num == 0) motion_init( pp->motd, pp->mot, *pp->seq, 1 );
	if ((pp->mot->frame == 0) && (pp->totaltime == 0)) {
		pp->timer = 0;
		pp->totaltime = 16;
		pp->start.vx = pp->mod->pos[X];
		pp->start.vy = pp->mod->pos[Y];
		pp->start.vz = pp->mod->pos[Z];
		if (battleturn) pp->terminal.vx = ep->mod->pos[X] - (ep->length + pp->length);
		else pp->terminal.vx = ep->mod->pos[X] + (ep->length + pp->length);
		pp->terminal.vy = pp->mod->pos[Y];
		pp->terminal.vz = pp->mod->pos[Z];
		SE_ENT(SE_DASH1);
	}
	if (pp->totaltime != 0) {
		pp->timer++;
		if (pp->timer == 8) motion_init( pp->motd, pp->mot, (*pp->seq++) + 1, 1 );
		rr = rsin((pp->timer * 1024) / pp->totaltime);
		pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
		pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
		pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
		if (pp->timer == pp->totaltime) {
			pp->totaltime = 0;
			BattleStatus = _camera_set2;
		}
		if (pp->timer <= 12)
		if ((LocalTimer % 3) == 0) {
			get_parts_ws_val(&pp->mod->objpos[8], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[12], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[17], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[21], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[25], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[29], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
		}
	}
}


void attack()
{
	int i;

	(cursol+3+(command_no*2))->status = 11;
	if (cam.mode == 0) {
		if (pp->mot->num != *pp->seq) motion_init( pp->motd, pp->mot, *pp->seq, 1 );
		if (pp->hyper) {
			gcb.ClearMode = 1;
			bg_col[R] = bg_col[G] = HYPER_RG;
			bg_col[B] = HYPER_B;
		}
		pos[0].vx = 0;
		pos[0].vy = (-200 << 12);
		pos[0].vz = -ep->length;
		at_field(&pos[0]);
		zp = *(((Z_POS **) zpos) + pp->chrno);
//		if (battleturn) {
//			cvec.r = 0;
//			cvec.g = 1;
//			cvec.b = 1;
//		} else {
			cvec.r = 1;
			cvec.g = 1;
			cvec.b = 0;
//		}
		for (i = 0; i < pp->hitpos; i++, zp++) {
			if (((*(pp->seq + 4) >> i) & 1) == 0) {
				get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs0, NULL, &pos[i]);
				get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs1, NULL, &trans);
				zanzo_entry( i, &pos[i], &trans, &cvec);
			}
		}
		if (pp->mot->count == *(pp->seq + 3)) {
			result = hit_check();
			if (result == -1) {
				if (ep->dp == 0) motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
			}
		}
		if (pp->mot->count == (*(pp->seq + 3) + 1)) {
			if (result == -1) {
				damage_set(-1);
			} else {
				damage_set(0);
				hit_effect(*(pp->seq + 4));
				if ((ep->dp == 0) && (ep->mot->num !=  *(pp->seq + 2))) motion_init( ep->motd, ep->mot, *(pp->seq + 2), 1 );
#if AT_UKE
				else if (result != -1) {
					motion_init( ep->motd, ep->mot, 34, 1 );	// Ａ２受けモーション
				}
#endif
			}
		}
		if ((pp->mot->count >= *(pp->seq + 3)) && (pp->mot->count <= (*(pp->seq + 3) + 2))) {
			if (result != -1) {
				hibana(*(pp->seq + 4));
			}
		}
		if (pp->mot->frame == 0) {
			command_next();
			pp->totaltime = 0;
			if (*(pp->seq + 1)) motion_init( pp->motd, pp->mot, *(pp->seq + 1), 1 );
			pp->seq += 5;
			BattleStatus = *pp->seq++;
		}
	} else {
		zanzo_first[0] =
		zanzo_first[1] =
		zanzo_first[2] =
		zanzo_first[3] = 0;
	}
}


void ranbu()
{
	int i,j;

	(cursol+3+(command_no*2))->status = 11;
	if (cam.mode == 0) {
		if (pp->mot->num != *pp->seq) {
			result = hit_check();
			if (result == -1) {
				damage_set(-1);
				motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
				command_next();
				pp->totaltime = 0;
				*pp->seq = _motion_wait2;	// 次のタスク
				*(pp->seq+1) = _returnset;		// 次のタスク
				*(pp->seq+2) = 29;	// バックステップモーション
				*(pp->seq+3) = _command_analyze;
				BattleStatus = *pp->seq++;
				return;
			} else {
				model_init( (long *) (pp->buf + 1)->tmd,  pp->mod );		// 飛びモデル
				coord_init( (KAISOU *) ((pp->buf + 1)->cls + 8), pp->mod );
				motion_init( pp->motd, pp->mot, *pp->seq, 1 );
			}
		}
//		pos[0].vx = 0;
//		pos[0].vy = (-200 << 12);
//		pos[0].vz = -ep->length;
//		at_field(&pos[0]);
		zp = *(((Z_POS **) zpos) + pp->chrno);
		for (j = 0; j < pp->hitpos; j++, zp++) {
			get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs0, NULL, &pos[j]);
		}
		if (pp->mot->count <= (*(pp->seq + 6 + 3) + 1)) {
			cvec.r = 1;
			cvec.g = 1;
			cvec.b = 0;
			zp = *(((Z_POS **) zpos) + pp->chrno);
			for (j = 0; j < pp->hitpos; j++, zp++) {
				if (((*(pp->seq + 4) >> j) & 1) == 0) {
					get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs1, NULL, &trans);
					zanzo_entry( j, &pos[j], &trans, &cvec);
				}
			}
		}
		for (i = 0; i < 9; i += 3) {
			if ((pp->mot->count >= *(pp->seq + i + 3)) && (pp->mot->count <= (*(pp->seq + i + 3) + 2))) {
				if (pp->mot->count == (*(pp->seq + i + 3) + 1)) {
					hit_effect(*(pp->seq + i + 4));
				}
				hibana(*(pp->seq + i + 4));
				if ((ep->mot->num !=  *(pp->seq + i + 2))) motion_init( ep->motd, ep->mot, *(pp->seq + i + 2), 1 );
			}
		}
		if (pp->mot->count == (*(pp->seq + 6 + 3) + 2)) {
			eq_timer = 16;		// 地震セット
			damage_set(1);
		}
		if (pp->mot->frame == 0) {
			command_next();
			pp->totaltime = 0;
			model_init( (long *) pp->buf->tmd,  pp->mod );
			coord_init( (KAISOU *) (pp->buf->cls + 8), pp->mod );
			if (*(pp->seq + 1)) motion_init( pp->motd, pp->mot, *(pp->seq + 1), 1 );
			pp->seq += (2 + 9);
			BattleStatus = *pp->seq++;
		}
	} else {
		zanzo_first[0] =
		zanzo_first[1] =
		zanzo_first[2] =
		zanzo_first[3] = 0;
	}
}


void tackle()
{
	int i;

	if (cam.mode == 0) {
		if (pp->mot->num != *pp->seq) {
			if ((pp->chrno != MODEL_TN) &&
				(pp->chrno != MODEL_HM) &&
				(pp->chrno != MODEL_OS) &&
				(pp->chrno != MODEL_OT)) {
				model_init( (long *) (pp->buf + 1)->tmd,  pp->mod );		// 飛びモデル
				coord_init( (KAISOU *) ((pp->buf + 1)->cls + 8), pp->mod );
			}
			motion_init( pp->motd, pp->mot, *pp->seq, 1 );
		}
		if (pp->hyper) {
			gcb.ClearMode = 1;
			bg_col[R] = bg_col[G] = HYPER_RG;
			bg_col[B] = HYPER_B;
		}
		zp = *(((Z_POS **) zpos) + pp->chrno);
		for (i = 0; i < pp->hitpos; i++, zp++) {
			get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs1, NULL, &pos[i]);
		}
		if (pp->mot->count == *(pp->seq + 3)) {
			result = hit_check();
			if (result == -1) {
				damage_set(-1);
				motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
			} else {
				damage_set(1);
				hit_effect(0);
				if (ep->mot->num !=  *(pp->seq + 2)) motion_init( ep->motd, ep->mot, *(pp->seq + 2), 1 );
				SE_ENT(SE_ATTACK4);
				ep->model_col[R] = ep->model_col[G] = ep->model_col[B] = 0xd0;
				ep->render = jt_colorset;								// モデルフラッシュ
			}
		} else {
			pd = (P_DATA *) player_data + ep->chrno;
			ep->render = pd->render;
		}
		if ((pp->mot->count >= *(pp->seq + 3)) && (pp->mot->count <= (*(pp->seq + 3) + 2))) {
			if (result != -1) {
				hibana(0);
			}
		}
		if (pp->mot->frame == 0) {
			command_next();
			pp->totaltime = 0;
			if (*(pp->seq + 1)) motion_init( pp->motd, pp->mot, *(pp->seq + 1), 1 );
			pp->seq += 4;
			model_init( (long *) pp->buf->tmd,  pp->mod );		// 飛びモデル
			coord_init( (KAISOU *) (pp->buf->cls + 8), pp->mod );
			BattleStatus = *pp->seq++;
		}
	}
}


void kumi()
{
	(cursol+3+(command_no*2))->status = 11;
	if (pp->mot->frame == 0) {
		motion_init( pp->motd, pp->mot, *pp->seq++, 1 );
		BattleStatus = *pp->seq++;
		result = hit_check();
		if (result == -1) {
			command_next();
			damage_set(-1);
			motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
			*pp->seq = _motion_wait2;	// 次のタスク
			*(pp->seq+1) = _returnset;		// 次のタスク
			*(pp->seq+2) = 29;	// バックステップモーション
			*(pp->seq+3) = _command_analyze;
		}
	}
}


void nage()
{
	int i;
	PATH2 *path;

//	if (cam.mode == 0) {
		if (pp->mot->num != *pp->seq) {
			motion_init( pp->motd, pp->mot, *pp->seq, 1 );
			motion_init( ep->motd, ep->mot, *(pp->seq + 2), 1 );
		}

		if (pp->mot->count == (*(pp->seq + 3) - 7)) {
			path = (PATH2 *) path2tbl + *(pp->seq + 1);
			cam.mode = 2;
			cam.timer = 0;
			cam.totaltime = path->time;
			cam.start.vx = cam.view.vpx;
			cam.start.vy = cam.view.vpy;
			cam.start.vz = cam.view.vpz;
			cam.relay.vx = path->p0.vx;
			cam.relay.vy = path->p0.vy;
			cam.relay.vz = path->p0.vz;
			cam.terminal.vx = path->p1.vx;
			cam.terminal.vy = path->p1.vy;
			cam.terminal.vz = path->p1.vz;
			if (battleturn) {
				cam.relay.vx *= -1;
				cam.terminal.vx *= -1;
			}
		}
		if (pp->mot->count == *(pp->seq + 3)) {
			SE_ENT(SE_DOWN1);
			eq_timer = 16;		// 地震セット
			get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
			pos[0].vy = 0;
			cvec.r = 0;
			cvec.g = 0;
			cvec.b = 0;
			EffectEntry(28, &pos[0], NULL, &cvec);					// 円形エフェクト
			get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
			for (i = 0; i < 80; i++) {
				avec.vx = ((rand() << 20) >> 21) - 1024;
				avec.vy = ((rand() << 20) >> 20);
				avec.vz = 2048;
				EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
			}
			Sprite3dEntry( 5, (480 << 6) | (288 >> 4), gol_ofs, &pos[0]); // ヒットマーク
			LightPos[X] = pos[0].vx >> 12;
			LightPos[Y] = pos[0].vy >> 12;
			LightPos[Z] = pos[0].vz >> 12;
			eflt[R] = 0x7000; eflt[G] = 0x7000; eflt[B] = 0x7000;	// 反射光
			get_parts_ws_val(&ep->mod->objpos[8], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[12], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[17], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[21], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[25], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[29], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[7], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[11], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[16], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[20], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[24], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&ep->mod->objpos[28], NULL, NULL, &pos[0]);
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			ep->model_col[R] = ep->model_col[G] = ep->model_col[B] = 0xd0;
			ep->render = jt_colorset;								// モデルフラッシュ
			damage_set(1);
		} else {
			pd = (P_DATA *) player_data + ep->chrno;
			ep->render = pd->render;
		}
		if (pp->mot->count == (*(pp->seq + 3) + 31)) {
			SE_ENT(SE_DOWN2);
			eq_timer = 4;		// 地震セット
			get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
			pos[0].vy = 0;
			cvec.r = 1;
			cvec.g = 1;
			cvec.b = 1;
			EffectEntry(25, &pos[0], NULL, &cvec);					// 円形エフェクト
			for (i = 0; i < 8; i++) {
				get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
				pos[0].vy = 0;
				pos[0].vx += ((rand() % 400) - 200) << 12;
				pos[0].vz += ((rand() % 400) - 200) << 12;
				Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			}
		}
		if (pp->mot->count == (*(pp->seq + 3) + 53)) {
			SE_ENT(SE_DOWN2);
			get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
			pos[0].vy = 0;
			cvec.r = 2;
			cvec.g = 2;
			cvec.b = 2;
			EffectEntry(25, &pos[0], NULL, &cvec);					// 円形エフェクト
			for (i = 0; i < 4; i++) {
				get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
				pos[0].vy = 0;
				pos[0].vx += ((rand() % 400) - 200) << 12;
				pos[0].vz += ((rand() % 400) - 200) << 12;
				Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			}
		}
		if (pp->mot->frame == 0) {
			command_next();
			pp->totaltime = 0;
			pp->seq += 4;
			BattleStatus = *pp->seq++;
		}
//	}
}


void motion_wait()
{
	if (pp->mot->frame == 0) {
		zanzo_first[0] =
		zanzo_first[1] =
		zanzo_first[2] =
		zanzo_first[3] = 0;
		BattleStatus = *pp->seq++;
	}
}


void motion_wait2()
{
	if (ep->mot->frame == 0) {
		BattleStatus = *pp->seq++;
	}
}


void returnset()
{
	int rr;

		if (pp->hyper) {
			gcb.ClearMode = 0;
			bg_col[R] = bg_col[G] = bg_col[B] = 0x00;
		}
		if (pp->mot->num != *pp->seq) {
			model_init( (long *) (pp->buf + 1)->tmd,  pp->mod );		// 飛びモデル
			coord_init( (KAISOU *) ((pp->buf + 1)->cls + 8), pp->mod );
			motion_init( pp->motd, pp->mot, *pp->seq, 1 );
		}
		if ((pp->mot->count == 4) && (pp->totaltime == 0)) {
			pp->timer = 0;
			pp->totaltime = 36;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn == 0) pp->terminal.vx = toFIXED(1300);
			else pp->terminal.vx = toFIXED(-1300);
			pp->terminal.vy = 0;
			pp->terminal.vz = pp->mod->pos[Z];

			cam.mode = 2;
			cam.timer = 0;
			cam.totaltime = 36;
			cam.start.vx = cam.view.vpx;
			cam.start.vy = cam.view.vpy;
			cam.start.vz = cam.view.vpz;
			if (battleturn) cam.terminal.vx = -2100;
			else cam.terminal.vx = 2100;
			cam.terminal.vy = -300;
			cam.terminal.vz = 200;
			cam.relay.vx = cam.terminal.vx;
			cam.relay.vy = -300;
			cam.relay.vz = 200;
		}

		if (pp->totaltime) {
			rr = rsin((++pp->timer * 1024) / pp->totaltime);
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->totaltime == pp->timer) {
				model_init( (long *) pp->buf->tmd,  pp->mod );
				coord_init( (KAISOU *) (pp->buf->cls + 8), pp->mod );
				motion_init( pp->motd, pp->mot, 0, -1 );
				pp->totaltime = 0;
				pp->seq++;
				BattleStatus = *pp->seq++;
			}
		}
}


void floting()
{
	int rr;

	(cursol+3+(command_no*2))->status = 11;
	if (pp->hyper) {
		gcb.ClearMode = 1;
		bg_col[R] = bg_col[G] = HYPER_RG;
		bg_col[B] = HYPER_B;
	}

	if (cam.mode == 0) {
		if (pp->mot->num == 0) {
			SE_ENT(SE_DASH2);
			model_init( (long *) (pp->buf + 1)->tmd,  pp->mod );		// 飛びモデル
			coord_init( (KAISOU *) ((pp->buf + 1)->cls + 8), pp->mod );
			motion_init( pp->motd, pp->mot, *pp->seq++, 1 );
			pp->timer = 0;
			pp->totaltime = 12;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn) pp->terminal.vx = pp->mod->pos[X] - (100 << 12);
			else pp->terminal.vx = pp->mod->pos[X] + (100 << 12);
			pp->terminal.vy = pp->mod->pos[Y] - toFIXED(100);
			pp->terminal.vz = pp->mod->pos[Z];
		}
		if ((pp->timer % 3) == 0) {
			pos[0].vx = pp->mod->pos[X];
			pos[0].vy = 0;
			pos[0].vz = pp->mod->pos[Z];
			cvec.r = 2;
			cvec.g = 2;
			cvec.b = 2;
			EffectEntry(28, &pos[0], NULL, &cvec);					// 円形エフェクト
		}
		if (pp->totaltime != 0) {
			rr = rsin((++pp->timer * 1024) / pp->totaltime);
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->timer == pp->totaltime) {
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
		}
	}
}


void rush()
{
	int rr;

//	if (cam.mode == 0) {
		if (pp->totaltime == 0) {
			SE_CLR(SE_DASH2);
			SE_ENT(SE_DASH3);
			pp->timer = 0;
			pp->totaltime = 10;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (ep->dp > 0) {
				if (battleturn) pp->terminal.vx = ep->mod->pos[X] - (ep->length + pp->length);
				else pp->terminal.vx = ep->mod->pos[X] + (ep->length + pp->length);
			} else {
				if (battleturn) pp->terminal.vx = ep->mod->pos[X] - pp->length;
				else pp->terminal.vx = ep->mod->pos[X] + pp->length;
			}
			pp->terminal.vy = 50;
			pp->terminal.vz = pp->mod->pos[Z];
		}
		if (pp->totaltime != 0) {
//			rr = (++pp->timer * 4096) / pp->totaltime;
			rr = ((++pp->timer * 64) / pp->totaltime);
			rr *= rr;
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->timer == pp->totaltime) {
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
//			if ((LocalTimer % 3) == 0) {
				get_parts_ws_val(&pp->mod->objpos[8], NULL, NULL, &pos[0]);
				pos[0].vy = 0;
				Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
				get_parts_ws_val(&pp->mod->objpos[12], NULL, NULL, &pos[0]);
				pos[0].vy = 0;
				Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
//			}
		}
//	}
}


void rush_hit()
{
	int i;

//	if (cam.mode == 0) {
		pos[0].vx = 0;
		pos[0].vy = (-200 << 12);
		pos[0].vz = -ep->length;
		at_field(&pos[0]);
		zp = *(((Z_POS **) zpos) + pp->chrno);
		for (i = 0; i < pp->hitpos; i++, zp++) {
			get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs0, NULL, &pos[i]);
		}
		result = hit_check();
		if (result == -1) {
			damage_set(-1);
			motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
		} else {
			damage_set(2);
			hit_effect(impact_pos[pp->chrno][3]);
			hibana(impact_pos[pp->chrno][3]);
			if ((ep->dp == 0) && (ep->mot->num != *pp->seq)) motion_init( ep->motd, ep->mot, *pp->seq, 1 );
		}
		cam.work = NULL;
		pp->seq++;
		BattleStatus = *pp->seq++;
//	}
}


void rush1()
{
	int rr;

	if (cam.mode == 0) {
		if (pp->totaltime == 0) {
			pp->timer = 0;
			pp->totaltime = 14;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn) pp->terminal.vx = ep->mod->pos[X] + (400 << 12);
			else pp->terminal.vx = ep->mod->pos[X] - (400 << 12);
			pp->terminal.vy = (-150 << 12);
			pp->terminal.vz = pp->mod->pos[Z];
			cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
			cam.work = NULL;
		}
		if (pp->totaltime != 0) {
//			rr = ((++pp->timer * 64) / pp->totaltime);
//			rr *= rr;
			rr = (++pp->timer * 4096) / pp->totaltime;
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			pp->mod->ang[X] -= 56;
			if (pp->timer == pp->totaltime) {
				command_next();
				pp->mod->ang[X] = -896;
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
		}
	}
}


void rush2()
{
	int rr;

	if (pp->command[command_no] != -1) (cursol+3+(command_no*2))->status = 11;
	if (cam.mode == 0) {
		if (pp->totaltime == 0) {
			SE_ENT(SE_DASH1);
			pp->timer = 0;
			pp->totaltime = 70;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn) pp->terminal.vx = ep->mod->pos[X] + (800 << 12);
			else pp->terminal.vx = ep->mod->pos[X] - (800 << 12);
			pp->terminal.vy = (-4000 << 12);
			pp->terminal.vz = pp->mod->pos[Z];
//			if ((pp->timer & 1) == 0) {
				pos[0].vx = pp->mod->pos[X];
				pos[0].vy = pp->mod->pos[Y];
				pos[0].vz = pp->mod->pos[Z];
				cvec.r = 1;
				cvec.g = 1;
				cvec.b = 1;
				EffectEntry(25, &pos[0], NULL, &cvec);					// 円形エフェクト
				pos[0].vx = pp->mod->pos[X];
				pos[0].vy = 0;
				pos[0].vz = pp->mod->pos[Z];
				cvec.r = 0;
				cvec.g = 0;
				cvec.b = 0;
				EffectEntry(28, &pos[0], NULL, &cvec);					// 円形エフェクト
//			}
			zanzo_first[0] =
			zanzo_first[1] =
			zanzo_first[2] =
			zanzo_first[3] = 0;
		}
		if (pp->totaltime != 0) {
//			rr = (++pp->timer * 4096) / pp->totaltime;
			rr = rsin((++pp->timer * 1024) / pp->totaltime);
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
//			pp->mod->ang[Y] += (pp->timer << 4);
			if (pp->timer == pp->totaltime) {
				motion_init( pp->motd, pp->mot, *pp->seq++, -1 );
				pp->timer = 0;
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
				pp->mod->ang[X] = 0;
				if (battleturn) pp->mod->ang[Y] = 1024;
				else pp->mod->ang[Y] = -1024;
			}
			if (pp->chrno != MODEL_TC) {
				/* ベイパー */
				cvec.r = 1;
				cvec.g = 1;
				cvec.b = 1;
				trans.vy = -100;
				trans.vz = -150;
				trans.vx = -300;
				get_parts_ws_val(&pp->mod->objpos[1], &trans, NULL, &pos[0]);
				trans.vx = -260;
				get_parts_ws_val(&pp->mod->objpos[1], &trans, NULL, &pos[1]);
				zanzo_entry( 0, &pos[0], &pos[1], &cvec);
				trans.vx = 300;
				get_parts_ws_val(&pp->mod->objpos[1], &trans, NULL, &pos[0]);
				trans.vx = 260;
				get_parts_ws_val(&pp->mod->objpos[1], &trans, NULL, &pos[1]);
				zanzo_entry( 1, &pos[0], &pos[1], &cvec);
			}
		}
	}
}


void rush3()
{
	int rr;

//	if (cam.mode == 0) {
		if (pp->mod->ang[X] != 896) {
			rr = rsin((++pp->timer * 1024) / 16);
			pp->mod->ang[X] = rr / 16 + 640;
		} else if (pp->totaltime == 0) {
			pp->timer = 0;
			pp->totaltime = 30;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			pp->terminal.vx = ep->mod->pos[X];
			pp->terminal.vy = ep->mod->pos[Y] - (50 << 12);
			pp->terminal.vz = ep->mod->pos[Z];
			trans.vx = 0;
			trans.vy = -50;
			trans.vz = 100;
			get_parts_ws_val(&ep->mod->objpos[1], &trans, NULL, &pp->terminal);
		}
		if (pp->totaltime != 0) {
			rr = ((++pp->timer * 64) / pp->totaltime);
			rr *= rr;
//			rr = rsin((++pp->timer * 1024) / pp->totaltime);
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->timer == pp->totaltime) {
				result = hit_check();
				if (result == -1) {
					motion_init( ep->motd, ep->mot, _motion_sake, 1 );	// 避けモーション
					damage_set(-1);
					pp->seq++;
				} else {
					eq_timer = 16;		// 地震セット
					motion_init( ep->motd, ep->mot, *pp->seq++, 1 );
					hit_effect(0);
					hibana(0);
					hibana(0);
					hibana(0);
					damage_set(2);
				}
				get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
				PolyefeEntry( 1, 0, &pos[0], NULL);	// 爆風
				PolyefeEntry( 2, 1, &pos[0], NULL);	// 爆風
				SE_ENT(SE_DOWN1);
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
		}
//	}
}


void rush4()
{
	int rr;

	if (cam.mode == 0) {
		if (pp->totaltime == 0) {
			if (pp->chrno == MODEL_TC) motion_init( pp->motd, pp->mot, 2, -1 );
			pp->timer = 0;
			pp->totaltime = 30;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn == 0) pp->terminal.vx = toFIXED(3000);
			else pp->terminal.vx = toFIXED(-3000);
			pp->terminal.vy = (-100 << 12);
			pp->terminal.vz = pp->mod->pos[Z];
			pp->mod->ang[X] = 0;
			if (battleturn == 0) cam.view.vpx = 1800;
			else cam.view.vpx = -1800;
			cam.view.vpy = -100;
			cam.view.vpz = 200;
			cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー

			pos[0].vx = ep->mod->pos[X];
			pos[0].vy = ep->mod->pos[Y] - (100 << 12);
			pos[0].vz = ep->mod->pos[Z];
		}
		if (pp->totaltime != 0) {
			rr = ((++pp->timer * 64) / pp->totaltime);
			rr *= rr;
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->timer == pp->totaltime) {
				command_next();
				pp->mod->ang[Y] += 2048;
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
		}
#if 0
		if ((LocalTimer & 1) == 0) {
			get_parts_ws_val(&pp->mod->objpos[8], NULL, NULL, &pos[0]);
			pos[0].vy = 0;
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			get_parts_ws_val(&pp->mod->objpos[12], NULL, NULL, &pos[0]);
			pos[0].vy = 0;
			Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
		}
#endif
	}
}


void zoom()
{
	SE_ENT(SE_BARIA1);
#if AT_UKE
	motion_init( ep->motd, ep->mot, 34, 1 );	// Ａ２受けモーション
#endif
	eq_timer = 60;		// 地震セット
	cam.mode = 2;
	cam.timer = 0;
	cam.totaltime = 60;
	cam.start.vx = cam.view.vpx;
	cam.start.vy = cam.view.vpy;
	cam.start.vz = cam.view.vpz;
	if (battleturn) cam.terminal.vx = 100;
	else cam.terminal.vx = -100;
	cam.terminal.vy = -400;
	cam.terminal.vz = 2000;
	cam.relay.vx = cam.terminal.vx * -10;
	cam.relay.vy = cam.terminal.vy * 2;
	cam.relay.vz = cam.terminal.vz * 2;
	cam.work = NULL;
	avec.vx =  40 - 160;
	avec.vy = 144 - 120;
	avec.vz = 1;
	button[0] = SpriteEntry((0x120 << 5) + 482, renda_ofs + 1, &avec, NULL, 3, 0xff);
	avec.vx =  32 - 160;
	avec.vy = 112 - 120;
	button[1] = SpriteEntry((0x120 << 5) + 481, renda_ofs + 0, &avec, NULL, 3, 0xff);
	avec.vy = 184 - 120;
	button[2] = SpriteEntry((0x120 << 5) + 483, renda_ofs + 4, &avec, NULL, 3, 0xff);
	pp->timer = pp->totaltime = 0;
	pp->power = 0;
	BattleStatus = *pp->seq++;
}


void renda()
{
	int i, j, flag;
	long ll;
	POL4 pol4;

	sindo_set( 0, 0x01);
	sindo_set( 1, 0x01);
	pos[0].vx = 0;
	pos[0].vy = (-200 << 12);
	pos[0].vz = -ep->length;
	at_field(&pos[0]);
	zp = *(((Z_POS **) zpos) + pp->chrno);
	for (i = 0; i < pp->hitpos; i++, zp++) {
		get_parts_ws_val(&pp->mod->objpos[zp->no], &zp->ofs0, NULL, &pos[i]);
	}
	cvec.r = 2;
	cvec.g = 1;
	cvec.b = 0;
	if (LocalTimer & 1) {
		for (i = 0; i < 7;) {
			for (j = 0; j < pp->hitpos; j++) {
				if (((impact_pos[pp->chrno][3] >> j) & 1) == 0) {
					avec.vx = ((rand() << 20) >> 21) + ep->mod->ang[X];
					avec.vy = ep->mod->ang[Y] - 1024;
					avec.vz = ((rand() << 20) >> 21) + 1024 + ep->mod->ang[Z];
					EffectEntry( 7, &pos[j], &avec, &cvec);					// 火花
				}
				i++;
			}
		}
	}

	/* ＣＰＵ */
	if ((gcb.TitleSelect == 2) || ((gcb.TitleSelect) && (battleturn))) {
		PadDat[battleturn].rpt =
		PadDat[battleturn].trg = 0;
		if ((rand() % 3) == 0) {
			PadDat[battleturn].trg ^= PADRR;
		}
	}

	flag = pp->lv - ep->lv;		// レベル差
	if (flag > 5) flag = 5;		// ダメージ計算
	else if (flag < -5) flag = -5;
	if (ep->dp <= ep->dpmax) ep->dp -= ((8 * (10 + flag)) / 10);	// 一定量ケズリ
	if (ep->dp > ep->dpmax) ep->dp = 0;
	if (button[0]->spd[X] == 0) {
		if (pp->power > ep->lv) pp->power -= ep->lv;
		else pp->power = 0;
		if (((PadDat[battleturn].trg & PADRright)>0) || ((PadDat[battleturn].trg & PADRleft)>0)) {
			if (ep->dp <= ep->dpmax) ep->dp -= (((pp->attack / 50) * (10 + flag)) / 10);	// 連打ケズリ
			if (ep->dp > ep->dpmax) ep->dp = 0;
			pp->power += (pp->lv * 4);
			if (pp->power > ep->dp) pp->power = ep->dp;
		}
		if (ep->dp) {
			pol4.code = 0x38;
			ll = ((pp->power % (ep->dp + 1)) * 79) / ep->dp;
			ll = (((ep->dpmax - ep->dp) % (ep->dpmax + 1)) * 79) / ep->dpmax;
			pol4.sxy[0][X] =
			pol4.sxy[2][X] = 32 - 160;
			pol4.sxy[1][X] =
			pol4.sxy[3][X] = 32 - 160 + ll;
			pol4.sxy[0][Y] =
			pol4.sxy[1][Y] = 185 - 120;
			pol4.sxy[2][Y] =
			pol4.sxy[3][Y] = 199 - 120;
			pol4.sz[0][0] = (1 << SPRITEOT_LENGTH) - 1;
			pol4.rgb[0][R] =
			pol4.rgb[1][R] =
			pol4.rgb[0][G] =
			pol4.rgb[1][G] = 0xf0;
			pol4.rgb[2][R] =
			pol4.rgb[3][R] =
			pol4.rgb[2][G] =
			pol4.rgb[3][G] = 0x40;
			pol4.rgb[0][B] =
			pol4.rgb[1][B] =
			pol4.rgb[2][B] =
			pol4.rgb[3][B] = 0x00;
			Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &spriteot[ PSDIDX ]);
		}
	}

//	if (pp->power == ep->dp) {
	if (ep->dp == 0) {
		*pp->seq = _rush_hit;			// 次のタスク
		*(pp->seq+1) = 7;				// ダメージモーション
		*(pp->seq+2) = _rush1;			// 次のタスク
		*(pp->seq+3) = _rush2;			// 次のタスク
		*(pp->seq+4) = 28;				// 飛行モーション
		if ((command_no < 3) &&
			(pp->command[command_no + 1] == 1)) {
			*(pp->seq+5) = _camera_set2;	// 次のタスク
			*(pp->seq+6) = 3 + camera_ofs;	// カメラのパス
			*(pp->seq+7) = _camera_set2;	// 次のタスク
			*(pp->seq+8) = 4 + camera_ofs;	// カメラのパス
			*(pp->seq+9) = _rush3;			// 次のタスク
			*(pp->seq+10) = 7;				// ダメージモーション
			*(pp->seq+11) = _rush4;			// 次のタスク
			*(pp->seq+12) = _returnset2;	// 次のタスク
			*(pp->seq+13) = _command_analyze;
		} else {
			*(pp->seq+5) = _returnset2;	// 次のタスク
			*(pp->seq+6) = _command_analyze;
		}
		eq_timer = 0;
		button[0]->spd[X] =
		button[1]->spd[X] =
		button[2]->spd[X] = 0;
		button[0]->acc[X] =
		button[1]->acc[X] =
		button[2]->acc[X] = -acceleration * 4;
		pp->timer = pp->totaltime = 0;
		cam.mode = 0;
		BattleStatus = *pp->seq++;
	} else {
		ll = ((LocalTimer >> 1) & 3);
		if (ll == 3) ll = 1;
		button[0]->chr = (renda_ofs + 1) + ll;	// 連打アニメ
		if (++pp->timer > 60) {
			button[0]->spd[X] =
			button[1]->spd[X] =
			button[2]->spd[X] = 0;
			button[0]->acc[X] =
			button[1]->acc[X] =
			button[2]->acc[X] = -acceleration * 4;
			BattleStatus = *pp->seq++;
		}
	}
}


void rush_pass()
{
	int rr;

	if (cam.mode == 0) {
		if (pp->totaltime == 0) {
			pp->timer = 0;
			pp->totaltime = 24;
			pp->start.vx = pp->mod->pos[X];
			pp->start.vy = pp->mod->pos[Y];
			pp->start.vz = pp->mod->pos[Z];
			if (battleturn) pp->terminal.vx = ep->mod->pos[X] + (2500 << 12);
			else pp->terminal.vx = ep->mod->pos[X] - (2500 << 12);
			pp->terminal.vy = (-200 << 12);
			pp->terminal.vz = pp->mod->pos[Z];
			cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
		}
		if (pp->totaltime != 0) {
			rr = (++pp->timer * 4096) / pp->totaltime;
			pp->mod->pos[X] = pp->start.vx + (((pp->terminal.vx - pp->start.vx) / 4096) * rr);
			pp->mod->pos[Y] = pp->start.vy + (((pp->terminal.vy - pp->start.vy) / 4096) * rr);
			pp->mod->pos[Z] = pp->start.vz + (((pp->terminal.vz - pp->start.vz) / 4096) * rr);
			if (pp->timer == pp->totaltime) {
				command_next();
				if ((command_no <= 3) && (pp->command[command_no] == 1)) {
					if (battleturn == 1) {
						(cursol+2+(command_no*2))->acc[X] =
						(cursol+3+(command_no*2))->acc[X] = acceleration * 4;
					} else {
						(cursol+2+(command_no*2))->acc[X] =
						(cursol+3+(command_no*2))->acc[X] = -acceleration * 4;
					}
					command_no++;
				}
				pp->totaltime = 0;
				BattleStatus = *pp->seq++;
			}
		}
	}
}


void returnset2()
{
	if (pp->hyper) {
		gcb.ClearMode = 0;
		bg_col[R] = bg_col[G] = bg_col[B] = 0x00;
	}
	if (battleturn == 0) {
		pp->mod->pos[X] = toFIXED(1300);
		pp->mod->ang[Y] = 1024;
	} else {
		pp->mod->pos[X] = toFIXED(-1300);
		pp->mod->ang[Y] = -1024;
	}
	pp->mod->pos[Y] = 0;
	pp->mod->pos[Z] = pp->mod->pos[Z];
	pp->mod->ang[X] = 0;

	cam.mode = 2;
	cam.timer = 0;
	cam.totaltime = 1;
	cam.start.vx = cam.view.vpx;
	cam.start.vy = cam.view.vpy;
	cam.start.vz = cam.view.vpz;
	if (battleturn) cam.terminal.vx = -2100;
	else cam.terminal.vx = 2100;
	cam.terminal.vy = -300;
	cam.terminal.vz = 200;
	cam.relay.vx = cam.terminal.vx;
	cam.relay.vy = cam.terminal.vy;
	cam.relay.vz = cam.terminal.vz;
	cam.work = NULL;
	Projection = 700;

	model_init( (long *) pp->buf->tmd,  pp->mod );
	coord_init( (KAISOU *) (pp->buf->cls + 8), pp->mod );
	motion_init( pp->motd, pp->mot, 0, -1 );
	pp->totaltime = 0;
	BattleStatus = *pp->seq++;
}


void beam_pos()
{
	if ((BattleStatus >= _missile0) && (BattleStatus <= _missile1)) {
		pos[0].vx = pp->mod->pos[X];
		pos[0].vy = pp->mod->pos[Y] - (300 << 12);
		pos[0].vz = pp->mod->pos[Z];
	} else if (BattleStatus >= _missile2) {
		pos[0].vx = beam->pos[X];
		pos[0].vy = beam->pos[Y];
		pos[0].vz = beam->pos[Z];
	} else {
		PushMatrix();
		GsInitCoordinate2(WORLD,&coord);
		avec.vx = pp->mod->ang[X];
		avec.vy = pp->mod->ang[Y];
		avec.vz = pp->mod->ang[Z];
		RotMatrixYXZ_gte(&avec, &coord.coord);
		SetRotMatrix(&coord.coord);
		pos[0].vx = 0;
		pos[0].vy = 0;
		pos[0].vz = -(2600 * beam->objscl.vz);
		ApplyRotMatrixLV(&pos[0], &trans);
		pos[0].vx = beam->pos[X] + trans.vx;
		pos[0].vy = beam->pos[Y] + trans.vy;
		pos[0].vz = beam->pos[Z] + trans.vz;
		PopMatrix();
		LightPos[X] = pos[0].vx >> 12;
		LightPos[Y] = pos[0].vy >> 12;
		LightPos[Z] = pos[0].vz >> 12;
		eflt[R] = 0x6000; eflt[G] = 0x4000; eflt[B] = 0x7000;	// 反射光
	}
}


void laser0()
{
	(cursol+3+(command_no*2))->status = 11;
	if (pp->hyper) {
		gcb.ClearMode = 1;
		bg_col[R] = bg_col[G] = HYPER_RG;
		bg_col[B] = HYPER_B;
	}

	PushMatrix();
	GsInitCoordinate2(WORLD,&coord);
	avec.vx = pp->mod->ang[X];
	avec.vy = pp->mod->ang[Y];
	avec.vz = pp->mod->ang[Z];
	RotMatrixYXZ_gte(&avec, &coord.coord);
	SetRotMatrix(&coord.coord);
	pos[0].vx = 0;
	pos[0].vy = (-100 << 12);
	pos[0].vz = -pp->length;
	ApplyRotMatrixLV(&pos[0], &trans);
	pos[0].vx = pp->mod->pos[X] + trans.vx;
	pos[0].vy = pp->mod->pos[Y] + trans.vy;
	pos[0].vz = pp->mod->pos[Z] + trans.vz;
	PopMatrix();
	if (pp->arank >= 2 ) PolyefeEntry( 7, 2, &pos[0], NULL);
	else PolyefeEntry( 5, 2, &pos[0], NULL);

	SE_ENT(SE_CHARGE1);
//	motion_init( pp->motd, pp->mot, 40, -1);	// ためモーション

	cam.work = &pp->mod->pos[X];	// 注視点－＞プレイヤー
	Projection = 500;
	LocalTimer = 0;
	BattleStatus = *pp->seq++;
}


void laser1()
{
	int i;

	PushMatrix();
	GsInitCoordinate2(WORLD,&coord);
	avec.vx = pp->mod->ang[X];
	avec.vy = pp->mod->ang[Y];
	avec.vz = pp->mod->ang[Z];
	RotMatrixYXZ_gte(&avec, &coord.coord);
	SetRotMatrix(&coord.coord);
	pos[0].vx = 0;
	pos[0].vy = (-100 << 12);
	pos[0].vz = -pp->length;
	ApplyRotMatrixLV(&pos[0], &trans);
	pos[0].vx = pp->mod->pos[X] + trans.vx;
	pos[0].vy = pp->mod->pos[Y] + trans.vy;
	pos[0].vz = pp->mod->pos[Z] + trans.vz;
	PopMatrix();
	LightPos[X] = pos[0].vx >> 12;
	LightPos[Y] = pos[0].vy >> 12;
	LightPos[Z] = pos[0].vz >> 12;
	eflt[R] = 0x6000; eflt[G] = 0x4000; eflt[B] = 0x7000;	// 反射光
	if (LocalTimer >= 20) {
		cvec.r = 1;
		cvec.g = 2;
		cvec.b = 0;
		EffectEntry(10, &pos[0], NULL, &cvec );		// サンダー
	}
	if (LocalTimer < (60 - 16)) {
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 4; i++) {
			EffectEntry(4, &pos[0], NULL, &cvec );		// 集中線
		}
	}
	if (LocalTimer >= 60) {
		pp_distance = ((2600 << 12) - (pp->length + ep->length)) / 2600;
		avec.vx  = -1024;
		avec.vy = 0;
		avec.vz = -pp->mod->ang[Y];
		if (pp->arank >= 2 ) beam = PolyefeEntry( 6, 8 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		else if (pp->arank >= 1 ) beam = PolyefeEntry( 6, 6 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		else beam = PolyefeEntry( 6, 4 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		beam->objscl.vz = 0;
		avec.vx =
		avec.vy = 0;
		avec.vz = 1024;
		cvec.r = 1;
		cvec.g = 2;
		cvec.b = 0;
		EffectEntry(25, &pos[0], &avec, &cvec);					// 円形エフェクト
		BattleStatus = *pp->seq++;
		SE_ENT(SE_BEAM1);
	}
}


void laser2()
{
	int i;

	beam->objscl.vz = (++beam->counter << 8);
	beam_pos();
	if (beam->objscl.vz >= pp_distance) {
		beam->objscl.vz = pp_distance;
		LocalTimer = 0;
		pp->timer = pp->totaltime = 0;
		pp->power = 0;
		if (ep->dp == 0) {
			cam.mode = 0;
			cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
		}
		BattleStatus = *pp->seq++;
	} else {
		for (i = 0; i < 4; i++) {
			Sprite3dEntry( 2, ((490 + (pp->mod->status * 3)) << 6) | (304 >> 4), beem3_ofs + 1, &pos[0]);	// ビーム粉
		}
		cam.work = NULL;
		cam.mode = 4;
	}
}


void laser3()
{
	int i, flag;
	long ll;
	POL4 pol4;

	sindo_set( 0, 0x01);
	sindo_set( 1, 0x01);
	pp->timer++;
	if (LocalTimer == 2) {
#if AT_UKE
		motion_init( ep->motd, ep->mot, 34, 1 );	// Ａ２受けモーション
#endif
		beam_pos();
		avec.vx = -1024;
		avec.vy = 0;
		avec.vz = -pp->mod->ang[Y];
		if (pp->arank >= 2 ) beam2 = PolyefeEntry( 4, 9 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		else if (pp->arank >= 1 ) beam2 = PolyefeEntry( 4, 7 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		else beam2 = PolyefeEntry( 4, 5 + (pp->mod->status * 7), &pos[0], &avec);	// レーザー
		SE_ENT(SE_BARIA1);
		avec.vx =  40 - 160;
		avec.vy = 144 - 120;
		avec.vz = 1;
		button[0] = SpriteEntry((0x120 << 5) + 482, renda_ofs + 1, &avec, NULL, 3, 0xff);
		avec.vx =  32 - 160;
		avec.vy = 112 - 120;
		button[1] = SpriteEntry((0x120 << 5) + 481, renda_ofs + 0, &avec, NULL, 3, 0xff);
		avec.vy = 184 - 120;
		button[2] = SpriteEntry((0x120 << 5) + 483, renda_ofs + 4, &avec, NULL, 3, 0xff);
		eq_timer = 60;
	}
	pos[0].vx = 0;
	pos[0].vy = (-100 << 12);
	pos[0].vz = -ep->length;
	at_field(&pos[0]);
	beam_pos();
	cvec.r = 0;
	cvec.g = 2;
	cvec.b = 1;
	if (LocalTimer & 1) {
		for (i = 0; i < 4; i++) {
//			Sprite3dEntry( 2, (490 << 6) | (304 >> 4), beem3_ofs + 1, &pos[0]);	// ビーム粉
			avec.vx = ((rand() << 20) >> 21) + ep->mod->ang[X];
			avec.vy = ep->mod->ang[Y] - 1024;
			avec.vz = ((rand() << 20) >> 21) + 1024 + ep->mod->ang[Z];
			EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
		}
	}
	if ((LocalTimer & 0x07) == 2) {
		avec.vx =
		avec.vy = 0;
		avec.vz = -pp->mod->ang[Y];
		if (pp->arank >= 2 ) PolyefeEntry( 10, 10 + (pp->mod->status * 7), &pos[0], &avec);	// 輪っか
		else if (pp->arank >= 1 ) PolyefeEntry( 9, 10 + (pp->mod->status * 7), &pos[0], &avec);	// 輪っか
		else PolyefeEntry( 8, 10 + (pp->mod->status * 7), &pos[0], &avec);	// 輪っか
	}
	/* ＣＰＵ */
	if ((gcb.TitleSelect == 2) || ((gcb.TitleSelect) && (battleturn))) {
		PadDat[battleturn].rpt =
		PadDat[battleturn].trg = 0;
		if ((rand() % 3) == 0) {
			PadDat[battleturn].trg ^= PADRR;
		}
	}

	flag = pp->lv - ep->lv;		// レベル差
	if (flag > 5) flag = 5;		// ダメージ計算
	else if (flag < -5) flag = -5;
	if (ep->dp <= ep->dpmax) ep->dp -= (((8 * (10 + flag)) / 10) * (2 + pp->aura));	// 一定量ケズリ
	if (ep->dp > ep->dpmax) ep->dp = 0;
	if (button[0]->spd[X] == 0) {
		if (pp->power > ep->lv) pp->power -= ep->lv;
		else pp->power = 0;
		if (((PadDat[battleturn].trg & PADRright)>0) || ((PadDat[battleturn].trg & PADRleft)>0)) {
			if (ep->dp <= ep->dpmax) ep->dp -= ((((pp->attack / 50) * (10 + flag)) / 10) * (2 + pp->aura));	// 連打ケズリ
			if (ep->dp > ep->dpmax) ep->dp = 0;
			pp->power += (pp->lv * 4);
			if (pp->power > ep->dp) pp->power = ep->dp;
		}
		if (ep->dp) {
			pol4.code = 0x38;
			ll = ((pp->power % (ep->dp + 1)) * 79) / ep->dp;
			ll = (((ep->dpmax - ep->dp) % (ep->dpmax + 1)) * 79) / ep->dpmax;
			pol4.sxy[0][X] =
			pol4.sxy[2][X] = 32 - 160;
			pol4.sxy[1][X] =
			pol4.sxy[3][X] = 32 - 160 + ll;
			pol4.sxy[0][Y] =
			pol4.sxy[1][Y] = 185 - 120;
			pol4.sxy[2][Y] =
			pol4.sxy[3][Y] = 199 - 120;
			pol4.sz[0][0] = (1 << SPRITEOT_LENGTH) - 1;
			pol4.rgb[0][R] =
			pol4.rgb[1][R] =
			pol4.rgb[0][G] =
			pol4.rgb[1][G] = 0xf0;
			pol4.rgb[2][R] =
			pol4.rgb[3][R] =
			pol4.rgb[2][G] =
			pol4.rgb[3][G] = 0x40;
			pol4.rgb[0][B] =
			pol4.rgb[1][B] =
			pol4.rgb[2][B] =
			pol4.rgb[3][B] = 0x00;
			Poly4Set( ((1 << 9) | (0 << 5)), 0, &pol4, &spriteot[ PSDIDX ]);
		}
	}

//	if (pp->power == ep->dp) {
	if (ep->dp == 0) {
		*pp->seq = _camera_set2;		// 次のタスク
		*(pp->seq+1) = 3 + camera_ofs;	// カメラのパス
		*(pp->seq+2) = _laser4;			// 次のタスク
		*(pp->seq+3) = _motion_wait2;	// 次のタスク
		*(pp->seq+4) = _returnset2;		// 次のタスク
		*(pp->seq+5) = _command_analyze;
		eq_timer = 16;
		LocalTimer = 0;
		beam2->status = 0;
		PolyefeCounter--;
		button[0]->spd[X] =
		button[1]->spd[X] =
		button[2]->spd[X] = 0;
		button[0]->acc[X] =
		button[1]->acc[X] =
		button[2]->acc[X] = -acceleration * 4;
		cam.mode = 0;
		cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
		BattleStatus = *pp->seq++;
	} else {
		ll = ((LocalTimer >> 1) & 3);
		if (ll == 3) ll = 1;
		button[0]->chr = (renda_ofs + 1) + ll;	// 連打アニメ
		if (LocalTimer >= 60) {
			command_next();
			LocalTimer = 0;
			button[0]->spd[X] =
			button[1]->spd[X] =
			button[2]->spd[X] = 0;
			button[0]->acc[X] =
			button[1]->acc[X] =
			button[2]->acc[X] = -acceleration * 4;
			pp->timer = pp->totaltime = 0;
			beam2->status = 11;
			BattleStatus = *pp->seq++;
		}
	}
}


void laser4()
{
	int i;

	if (LocalTimer == 2) {
		command_next();
		result = hit_check();
		result = 0;
		if (result == -1) {
			damage_set(-1);
			motion_init( ep->motd, ep->mot, _motion_sake, 1);	// 避けモーション
			*pp->seq = _returnset2;		// 次のタスク
			*(pp->seq+1) = _command_analyze;
		} else {
			SE_ENT(SE_ATTACK3);
			damage_set((4 - (pp->timer / 20)) * (1 + pp->arank));
			if (ep->chrno == MODEL_SP) {
				motion_init( ep->motd, ep->mot, 31, 1);	// ダメージモーション
				*pp->seq = _returnset2;		// 次のタスク
				*(pp->seq+1) = _command_analyze;
			} else if (pp->arank) {
				motion_init( ep->motd, ep->mot, 35, 1);	// ダメージモーション
			} else {
				motion_init( ep->motd, ep->mot, 7, 1);	// ダメージモーション
				*pp->seq = _returnset2;		// 次のタスク
				*(pp->seq+1) = _command_analyze;
			}
		}
		cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
	}
	if (beam->objscl.vz < 6144) {
		beam->objscl.vz = (++beam->counter << 8);
		for (i = 0; i < 4; i++) {
			Sprite3dEntry( 2, ((490 + (pp->mod->status * 3)) << 6) | (304 >> 4), beem3_ofs + 1, &pos[0]);	// ビーム粉
		}
	} else {
		beam->objscl.vx -= 128;
		beam->objscl.vy -= 128;
	}
	if (beam->objscl.vx <= 0) {
		beam->status = 0;
		PolyefeCounter--;
		pp->timer = pp->totaltime = 0;
		pp->power = 0;
		BattleStatus = *pp->seq++;
	} else {
		if (result != -1) {
			beam_pos();
			if ((pos[0].vx >= (ep->mod->pos[X] - (250 << 12))) && (pos[0].vx <= (ep->mod->pos[X] + (250 << 12)))) {
//			if (beam->objscl.vz <= 4224) {
				SE_ENT(SE_ATTACK2);
				avec.vx =
				avec.vy = 0;
				avec.vz = 1024;
				cvec.r = 0;
				cvec.g = 1;
				cvec.b = 1;
				EffectEntry(25, &pos[0], &avec, &cvec);					// 円形エフェクト
				cvec.r = 0;
				cvec.g = 1;
				cvec.b = 2;
				for (i = 0; i < 12; i++) {
					avec.vx = ((rand() << 20) >> 21) - 1024;
					avec.vy = ((rand() << 20) >> 20);
					avec.vz = 2048;
					EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
				}
				Sprite3dEntry( 5, (480 << 6) | (288 >> 4), gol_ofs, &pos[0]); // ヒットマーク
				Sprite3dEntry( 4, (480 << 6) | (272 >> 4), efe1_ofs, &pos[0]);		// 煙
			} else if (beam->objscl.vz < 6144) {
				cvec.r = 0;
				cvec.g = 1;
				cvec.b = 2;
				get_parts_ws_val(&ep->mod->objpos[1], NULL, NULL, &pos[0]);
				for (i = 0; i < 8; i++) {
					avec.vx = ((rand() << 20) >> 21) - 1024;
					avec.vy = ((rand() << 20) >> 20);
					avec.vz = 2048;
					EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
				}
			}
		}
	}
}


void laser5()
{
	int i;

	pos[0].vx = 0;
	pos[0].vy = (-100 << 12);
	pos[0].vz = -ep->length;
	at_field(&pos[0]);
	beam->objscl.vx -= 128;
	beam->objscl.vy -= 128;
	if (beam->objscl.vx <= 0) {
		beam->status = 0;
		PolyefeCounter--;
		pp->timer = pp->totaltime = 0;
		pp->power = 0;
		BattleStatus = *pp->seq++;
	} else {
		beam_pos();
		if (LocalTimer & 1) {
			cvec.r = 0;
			cvec.g = 2;
			cvec.b = 1;
			for (i = 0; i < 2; i++) {
				avec.vx = ((rand() << 20) >> 21) + ep->mod->ang[X];
				avec.vy = ep->mod->ang[Y] - 1024;
				avec.vz = ((rand() << 20) >> 21) + 1024 + ep->mod->ang[Z];
				EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
			}
		}
	}
}


void missile0()
{
	(cursol+3+(command_no*2))->status = 11;
	if (pp->hyper) {
		gcb.ClearMode = 1;
		bg_col[R] = bg_col[G] = HYPER_RG;
		bg_col[B] = HYPER_B;
	}

	PushMatrix();
	GsInitCoordinate2(WORLD,&coord);
	avec.vx = pp->mod->ang[X];
	avec.vy = pp->mod->ang[Y];
	avec.vz = pp->mod->ang[Z];
	RotMatrixYXZ_gte(&avec, &coord.coord);
	SetRotMatrix(&coord.coord);
	pos[0].vx = 0;
	pos[0].vy = (-300 << 12);
	pos[0].vz = 0;
	ApplyRotMatrixLV(&pos[0], &trans);
	pos[0].vx = pp->mod->pos[X] + trans.vx;
	pos[0].vy = pp->mod->pos[Y] + trans.vy;
	pos[0].vz = pp->mod->pos[Z] + trans.vz;
	PopMatrix();
	beam = PolyefeEntry( 5, 2, &pos[0], NULL);

	SE_ENT(SE_CHARGE1);
	cam.work = &pp->mod->pos[X];	// 注視点－＞プレイヤー
	Projection = 500;
	LocalTimer = 0;
	BattleStatus = *pp->seq++;
}


void missile1()
{
	int i;

	PushMatrix();
	GsInitCoordinate2(WORLD,&coord);
	avec.vx = pp->mod->ang[X];
	avec.vy = pp->mod->ang[Y];
	avec.vz = pp->mod->ang[Z];
	RotMatrixYXZ_gte(&avec, &coord.coord);
	SetRotMatrix(&coord.coord);
	pos[0].vx = 0;
	pos[0].vy = (-300 << 12);
	pos[0].vz = 0;
	ApplyRotMatrixLV(&pos[0], &trans);
	pos[0].vx = pp->mod->pos[X] + trans.vx;
	pos[0].vy = pp->mod->pos[Y] + trans.vy;
	pos[0].vz = pp->mod->pos[Z] + trans.vz;
	PopMatrix();
	if (LocalTimer < (64 - 16)) {
		LightPos[X] = pos[0].vx >> 12;
		LightPos[Y] = pos[0].vy >> 12;
		LightPos[Z] = pos[0].vz >> 12;
		eflt[R] = 0x6000; eflt[G] = 0x4000; eflt[B] = 0x7000;	// 反射光
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 4; i++) {
			EffectEntry(4, &pos[0], NULL, &cvec );		// 集中線
		}
	}
	if (LocalTimer == 62) {
		beam->status = 1;
		beam->timer = 0;
		avec.vx = -1024;
		avec.vy = 0;
		avec.vz = -pp->mod->ang[Y];
		beam = PolyefeEntry( 12, 3, &pos[0], &avec);	// 槍
	}
	if ((LocalTimer > 62) && (LocalTimer < 96)) {
		cvec.r = 1;
		cvec.g = 2;
		cvec.b = 0;
		EffectEntry(10, &pos[0], NULL, &cvec );		// サンダー
	}
	if (LocalTimer >= 126) {
		beam_pos();
		avec.vx =
		avec.vy = 0;
		avec.vz = 1024;
		PolyefeEntry( 8, 10 + (pp->mod->status * 7), &pos[0], &avec);	// 輪っか
		pp->power = pp->arank;
		pp->timer = 0;
		LocalTimer = 0;
		BattleStatus = *pp->seq++;
	}
}


void missile2()
{
	int i;

	if ((beam->status == 13) && (beam->timer == 17) && (ep->dp > 0)) {
		pos[0].vx = 0;
		pos[0].vy = (-150 << 12);
		pos[0].vz = (-380 << 12);
		i = LocalTimer;
		LocalTimer = 0;
		at_field(&pos[0]);
		LocalTimer = i;
		cvec.r = 2;
		cvec.g = 1;
		cvec.b = 0;
		for (i = 0; i < 32; i++) {
			avec.vx = ((rand() << 20) >> 21) + ep->mod->ang[X];
			avec.vy = ep->mod->ang[Y] - 1024;
			avec.vz = ((rand() << 20) >> 21) + 1024 + ep->mod->ang[Z];
			EffectEntry( 7, &pos[0], &avec, &cvec);					// 火花
		}
		ep->dp -= pp->lv * 5;
		damage_set(-1);
		beam->timer = 0;
		beam->status++;
		cam.mode = 0;
		cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
		if (pp->power > pp->timer) beam = needle[pp->timer++];	// 引継ぎ
		else command_next();
	} else if ((beam->status == 13) && (beam->timer >= 20)) {
		if (beam->timer == 20) {
			result = hit_check();
			result = 0;
			if (result == -1) {
				motion_init( ep->motd, ep->mot, _motion_sake, 1);	// 避けモーション
				damage_set(-1);
			} else {
				damage_set(1 + pp->arank);
				avec.vx =
				avec.vy = 0;
				avec.vz = 1024;
				cvec.r = 1;
				cvec.g = 3;
				cvec.b = 3;
				EffectEntry(25, &beam->pos, &beam->objang, &cvec);					// 円形エフェクト
				cam.mode = 0;
				cam.work = &ep->mod->pos[X];	// 注視点－＞プレイヤー
				motion_init( ep->motd, ep->mot, 5, 1);
			}
		}
		if (result == 0) {
			cvec.r = 0;
			cvec.g = 1;
			cvec.b = 2;
			for (i = 0; i < 7; i++) {
				avec.vx = ((rand() << 20) >> 21) - 1024;
				avec.vy = ((rand() << 20) >> 20);
				avec.vz = 2048;
				EffectEntry( 7, &beam->pos[X], &avec, &cvec);					// 火花
			}
		}
	 	if (beam->timer == 27) {
	 		if (pp->power > pp->timer) beam = needle[pp->timer++];	// 引継ぎ
			else command_next();
		}
	}
	if (beam->status == 0) {
		BattleStatus = *pp->seq++;
	}
	if ((LocalTimer & 0x0f) == 0x0f) {
		if ((LocalTimer >> 4) < pp->power) {
			pos[0].vx = pp->mod->pos[X];
			pos[0].vy = pp->mod->pos[Y] - (300 << 12);
			pos[0].vz = pp->mod->pos[Z];
			avec.vx = -1024;
			avec.vy = 0;
			avec.vz = -pp->mod->ang[Y];
			needle[LocalTimer >> 4] = PolyefeEntry( 13, 3, &pos[0], &avec);	// 槍
		}
	}
}


void aura_tame0()
{
	(cursol+3+(command_no*2))->status = 11;

	if (pp->mot->num != 40) {
#if TAME
		motion_init( pp->motd, pp->mot, 40, -1);	// ためモーション
#endif
//		eq_timer = 70;
	}
	SE_ENT(SE_CHARGE1);
	LocalTimer = 0;
	BattleStatus = *pp->seq++;
}

void aura_tame1()
{
	int i;

	if ((LocalTimer & 3) == 0) {
		pp->model_col[R] = pp->model_col[G] = pp->model_col[B] = 0xd0;
		pp->render = jt_colorset;								// モデルフラッシュ
	} else {
		pd = (P_DATA *) player_data + pp->chrno;
		pp->render = pd->render;
	}
	if (LocalTimer < 40) {
		cvec.r = 0;
		cvec.g = 0;
		cvec.b = 2;
		get_parts_ws_val(&pp->mod->objpos[1], NULL, NULL, &pos[0]);
		for (i = 0; i < 5; i++) {
			EffectEntry(4, &pos[0], NULL, &cvec );		// 集中線
		}
	}
	if (LocalTimer > 60) {
		if (pp->aura >= 100) {
			SE_ENT(SE_CRASH);
			SE_ENT(SE_ATTACK3);
			pp->hyper = 1;
			LocalTimer = 0;
			*pp->seq = _aura_tame2;
			*(pp->seq+1) = _returnset2;
			*(pp->seq+2) = _command_analyze;
		}
		command_next();
		BattleStatus = *pp->seq++;
	}
}


void aura_tame2()
{
	if (((LocalTimer & 0x01) == 1) && (LocalTimer < 16)) {
		pos[0].vx = pp->mod->pos[X];
		pos[0].vy = 0;
		pos[0].vz = pp->mod->pos[Z];
		cvec.r = 0;
		cvec.g = 0;
		cvec.b = 1;
		avec.vx = rand() % 4096;
		avec.vy = rand() % 4096;
		avec.vz = rand() % 4096;
		EffectEntry(28, &pos[0], &avec, &cvec);					// 円形エフェクト
		get_parts_ws_val(&pp->mod->objpos[0], NULL, NULL, &pos[0]);
	}

	if (LocalTimer > 30) {
		BattleStatus = *pp->seq++;
	}
}



