/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : MENU TEST                                                */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : MENU.C                                                   */
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
#include "../lib/fade.h"
#include "../lib/akmcrd.h"
#include "../lib/czarpad.h"
#include "../lib/istatic.h"
#include "../lib/polygon.h"
#include "../lib/menu.h"
#include "../p01/bg.h"
#include "../p02/anmdata.h"
#include "../sprite/sprite.h"
#include "../redlib/sound.h"
#include "../redlib/sndno.h"
#include "../p00/ldaddr.ext"

//#define SONY 1

/*----- User Local      Works -----*/
long		MenuLocalTimer = 0;
u_char		MenuSubStatus = 0;
int			MenuCursolPos, MenuCursolMax;
int			MenuCursolPos2, MenuCursolMax2;
SPRWORK		*MenuStatus, *MenuStatus2;
short		mode;
int			GetNumber;
LPISTATIC	istatic2 = (ISTATIC_ADDR);

int MenuInit();
int MenuMain();
int MenuSub1();
int TestMenu();
void Mn_texture_init(addr);

PRCS_TBL menu_tbl[] =
{
	{ MenuInit },
	{ MenuMain },
	{ MenuSub1 },
	{ TestMenu },
};

#include "menu.tbl"

#define CLEAR_FLAG 0x801ef9f1

extern CzAnimData *SequenceTbl_Menu[];

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MAIN MENU                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int MainMenu()
{
	MenuLocalTimer++;
	GsClearOt( 0, 0, &spriteot[ PSDIDX ] );
	GsSortOt( &spriteot[ PSDIDX ], &ot[ PSDIDX ]);
	if (MenuSubStatus) {
		GsClearOt( 0, (1<<OT_LENGTH) - (1<<BGOT_LENGTH), &bgot[ PSDIDX ] );
		GsSortOt( &bgot[ PSDIDX ], &ot[ PSDIDX ] );
		SpriteBgSet( 21, 0, -160, -120, DIRECT15, 320, 256);
	}
	menu_tbl[ MenuSubStatus ].func();
	SpriteControll();
	FntPrint("\nspr=%d\n", SpriteCounter);

   return( 0 );
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MENU INIT                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int MenuInit()
{
	int i, j, cmp, num;
	SVECTOR svec;
	u_short pal,chr,mode,wait;
	RECT            rect;

	GsInitGraph2( 320, 240, GsNONINTER | GsOFSGPU, 1, 0 ); /* Initialize Graphic System     */
	GsDefDispBuff2( 0, 0, 0, 240 );           /* Double Buffer Setting         */
	setRECT( &rect, 0, 8, 320, 224 );
	GsSetClip2D( &rect );                    /* Display Masking               */
	POSITION.offx = 160;
	POSITION.offy = 120;

	XA_CLR();
	DATA_CLOSE(1);
	SOUND_I();
	SE_LOAD(0);
	BGM_LOAD(BGM_HOME);
	BGM_ENT(0);

	bgot[0].length = BGOT_LENGTH;
	bgot[0].org    = bgot_tag[0];
	bgot[1].length = BGOT_LENGTH;
	bgot[1].org    = bgot_tag[1];

	SpriteInit((CzAnimData *) SequenceTbl_Menu);

	FioDivReadFile( "DT\\SIR.BIN", (u_char *)LoadAddress8, gcb.ovs[ PRCS_08 ].ss, gcb.ovs[ PRCS_08 ].ns );

	FioReadFile((Uint8 *) "DT\\MENU.TEX", (Uint8 *) LOAD_ADDR);
	num = *(u_long *) LOAD_ADDR;
	for (i = 0; i < num; i++) {
		cmp = NumToAddrMcr( i, LOAD_ADDR );
		LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
		LzDecB();
		Mn_texture_init( TENKAI_ADDR );
		DrawSync(0);
	}

	GetNumber = 0;
	for (i = 0; i < 59; i++) {
		if ((i != MODEL_KB) &&
			(i != MODEL_RB) &&
			(i != MODEL_BE) &&
			((*(char *) CLEAR_FLAG != 0) ||
			((istatic2+i)->lv != 0) ||
			((istatic2+i)->pad != 0))) GetNumber++;
	}

	svec.vz = 1;
	for (i = 0, j = 0; i < 13; i++) {
		pal = menuobject_tbl[j++];
		chr = menuobject_tbl[j++];
		svec.vx = menuobject_tbl[j++];
		svec.vy = menuobject_tbl[j++];
		mode = menuobject_tbl[j++];
		wait = menuobject_tbl[j++];
		MenuStatus = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
		if (i == 0) MenuStatus->pmode = CLUT8 | NBLEND;
		else MenuStatus->pmode = CLUT4 | NBLEND;
	}
#ifdef SONY	// とりあえず提出版
	(MenuStatus-4)->status = 17;
#endif
	(MenuStatus-11)->chr = fix2_ofs + (GetNumber / 10);
	(MenuStatus-10)->chr = fix2_ofs + (GetNumber % 10);

	MenuCursolPos = RED_GAME_DAY_FLG();
	MenuCursolMax = 4;

	FadeInit( FADE_IN, 0x10);
	MenuSubStatus++;

   return( 0 );
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MENU MAIN                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int MenuMain()
{
	int i, j, sp;
	SVECTOR svec;
	u_short pal,chr,mode,wait;

	if ((MenuStatus-2)->vzoomac == 0) {
#if 0
		if (((PadDat[1].dat & PADL1)>0) &&
			((PadDat[1].dat & PADL2)>0) &&
			((PadDat[1].dat & PADR1)>0) &&
			((PadDat[1].dat & PADR2)>0) &&
			((PadDat[1].dat & PADLL)>0) &&
			((PadDat[1].trg & PADST)>0) &&
			(*(char *) CLEAR_FLAG == 0)) {	// 裏ワザ：クリアーフラグＯＮ
			SE_ENT(SE_LV_UP);
			*(char *) CLEAR_FLAG = 1;
		}
#endif
		(MenuStatus - 6 + MenuCursolPos)->pal = (0x000 << 5) + 480 + MenuCursolPos;
		if((PadDat[0].rpt & PADLU)>0) {
			SE_ENT(SE_CUR1);
			MenuCursolPos--;
#ifdef SONY	// とりあえず提出版
			if (MenuCursolPos == 2) MenuCursolPos--;
#endif
			if (MenuCursolPos < 0) MenuCursolPos = MenuCursolMax;
		} else if((PadDat[0].rpt & PADLD)>0) {
			SE_ENT(SE_CUR1);
			MenuCursolPos++;
#ifdef SONY	// とりあえず提出版
			if (MenuCursolPos == 2) MenuCursolPos++;
#endif
			if (MenuCursolPos > MenuCursolMax) MenuCursolPos = 0;
		} else if (((PadDat[0].trg & PADRL)>0) || ((PadDat[0].trg & PADRR)>0)) {
			SE_ENT(SE_OK1);
			(MenuStatus - 11)->vzoomac =
			(MenuStatus - 10)->vzoomac =
			(MenuStatus - 9)->vzoomac =
			(MenuStatus - 8)->vzoomac =
			(MenuStatus - 7)->vzoomac =
			(MenuStatus - 6)->vzoomac =
			(MenuStatus - 5)->vzoomac =
			(MenuStatus - 4)->vzoomac =
			(MenuStatus - 3)->vzoomac =
			(MenuStatus - 2)->vzoomac = acceleration;
			switch (MenuCursolPos) {
				case 0:	// はじめから
					gcb.TitleSelect = 1;
					for (i = 0; i <= 1; i++) {
						sp = (MenuStatus-i)->pos[Y];
						(MenuStatus-i)->pos[Y] -= (24 << 16);
						(MenuStatus-i)->acc[Y] = acceleration;
						while ((MenuStatus-i)->pos[Y] < sp) {
							(MenuStatus-i)->pos[Y] -= (MenuStatus-i)->spd[Y];
							(MenuStatus-i)->spd[Y] -= (MenuStatus-i)->acc[Y];
						}
					}
					svec.vx = 256 - 160;
					svec.vy = 200 - 120;
					svec.vz = 1;
					MenuStatus2 = SpriteEntry((0x100 << 5) + 485, fix_ofs + 28, &svec, NULL, 4, 8);
					for (i = 0, j = 14 * 6; i < 2; i++) {
						pal = menuobject_tbl[j++];
						chr = menuobject_tbl[j++];
						svec.vx = menuobject_tbl[j++];
						svec.vy = menuobject_tbl[j++];
						mode = menuobject_tbl[j++];
						wait = menuobject_tbl[j++];
						MenuStatus2 = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
						MenuStatus2->pmode = CLUT4 | NBLEND;
					}
					MenuCursolPos2 = 0;
					MenuCursolMax2 = 1;
					MenuSubStatus++;
					break;
				case 1:	// つづきから
					BGM_CLR(BGM_HOME);
					(MenuStatus - 1)->acc[Y] =
					(MenuStatus - 0)->acc[Y] = acceleration;
					FadeInit( FADE_OUT, 0x10);
					BGM_FADE( BGM_DOWN, 0,5);
					gcb.TitleSelect = 1;
					pcb.req = PRCS_04;
					break;
				case 2:	// 対戦する
					gcb.TitleSelect = 0;
					for (i = 0; i <= 1; i++) {
						sp = (MenuStatus-i)->pos[Y];
						(MenuStatus-i)->pos[Y] -= (24 << 16);
						(MenuStatus-i)->acc[Y] = acceleration;
						while ((MenuStatus-i)->pos[Y] < sp) {
							(MenuStatus-i)->pos[Y] -= (MenuStatus-i)->spd[Y];
							(MenuStatus-i)->spd[Y] -= (MenuStatus-i)->acc[Y];
						}
					}
					svec.vx = 256 - 160;
					svec.vy = 200 - 120;
					svec.vz = 1;
					MenuStatus2 = SpriteEntry((0x100 << 5) + 485, fix_ofs + 28, &svec, NULL, 4, 8);
					for (i = 0, j = 16 * 6; i < 2; i++) {
						pal = menuobject_tbl[j++];
						chr = menuobject_tbl[j++];
						svec.vx = menuobject_tbl[j++];
						svec.vy = menuobject_tbl[j++];
						mode = menuobject_tbl[j++];
						wait = menuobject_tbl[j++];
						MenuStatus2 = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
						MenuStatus2->pmode = CLUT4 | NBLEND;
					}
					MenuCursolPos2 = 0;
					MenuCursolMax2 = 1;
					MenuSubStatus++;
					break;
				case 3:	// 図鑑モード
					BGM_CLR(BGM_HOME);
					(MenuStatus - 1)->acc[Y] =
					(MenuStatus - 0)->acc[Y] = acceleration;
					FadeInit( FADE_OUT, 0x10);
					BGM_FADE( BGM_DOWN, 0,5);
					pcb.req = PRCS_06;
					break;
				case 4:	// ポケットステーション
					BGM_CLR(BGM_HOME);
					(MenuStatus - 1)->acc[Y] =
					(MenuStatus - 0)->acc[Y] = acceleration;
					FadeInit( FADE_OUT, 0x10);
					BGM_FADE( BGM_DOWN, 0,5);
					pcb.req = PRCS_07;
					break;
			}
		}
		if (MenuSubStatus == 1) (MenuStatus - 6 + MenuCursolPos)->pal = (0x000 << 5) + 485 + MenuCursolPos;
	}

#ifndef PREPRE
	if((PadDat[0].trg & PADSL)>0) MenuSubStatus = 3;
#endif

   return( 0 );
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MENU SUB1                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int MenuSub1()
{
	int i, j, sp;
	SVECTOR svec;
	u_short pal,chr,mode,wait;

	if (((MenuStatus2-2)->acc[X] == 0) && ((MenuStatus2-2)->acc[Y] == 0)) {
		(MenuStatus2 - 1 + MenuCursolPos2)->pal = (0x010 << 5) + 480 + MenuCursolPos;
		if((PadDat[0].rpt & PADLU)>0) {
			SE_ENT(SE_CUR1);
			MenuCursolPos2--;
			if (MenuCursolPos2 < 0) MenuCursolPos2 = MenuCursolMax2;
		} else if((PadDat[0].rpt & PADLD)>0) {
			SE_ENT(SE_CUR1);
			MenuCursolPos2++;
			if (MenuCursolPos2 > MenuCursolMax2) MenuCursolPos2 = 0;
		} else if (((PadDat[0].trg & PADRL)>0) || ((PadDat[0].trg & PADRR)>0)) {
			if ((MenuCursolPos == 2) && (MenuCursolPos2 == 1) && (Pad[1].id != 0x02) && (Pad[1].id != 0x04)) {
				SE_ENT(SE_PAUSE);
			} else {
				SE_ENT(SE_OK1);
				switch (MenuCursolPos) {
					case 0:	// はじめから
						BGM_CLR(BGM_HOME);
						AK_MEM_DATA_INIT(23 + MenuCursolPos2);			// メモリー初期化
						(MenuStatus - 1)->acc[Y] =
						(MenuStatus - 0)->acc[Y] =
						(MenuStatus2 - 2)->acc[Y] =
						(MenuStatus2 - 1)->vzoomac =
						(MenuStatus2 - 0)->vzoomac = acceleration;
						FadeInit( FADE_OUT, 0x10);
						BGM_FADE( BGM_DOWN, 0,5);
						pcb.req = PRCS_04;
						break;
					case 2:	// 対戦する
						BGM_CLR(BGM_HOME);
						gcb.TitleSelect = MenuCursolPos2 ^ 1;
						(MenuStatus - 1)->acc[Y] =
						(MenuStatus - 0)->acc[Y] =
						(MenuStatus2 - 2)->acc[Y] =
						(MenuStatus2 - 1)->vzoomac =
						(MenuStatus2 - 0)->vzoomac = acceleration;
						FadeInit( FADE_OUT, 0x10);
						BGM_FADE( BGM_DOWN, 0,5);
						pcb.req = PRCS_03;
						break;
				}
			}
		} else if ((PadDat[0].trg & PADRD)>0) {
			SE_ENT(SE_CANCEL);
			switch (MenuCursolPos) {
				case 0:	// はじめから
				case 2:	// 対戦する
					(MenuStatus2 - 2)->acc[Y] =
					(MenuStatus2 - 1)->vzoomac =
					(MenuStatus2 - 0)->vzoomac = acceleration;
					for (i = 0; i <= 1; i++) {
						sp = (MenuStatus-i)->pos[Y];
						(MenuStatus-i)->pos[Y] += (24 << 16);
						(MenuStatus-i)->acc[Y] = -acceleration;
						while ((MenuStatus-i)->pos[Y] > sp) {
							(MenuStatus-i)->pos[Y] -= (MenuStatus-i)->spd[Y];
							(MenuStatus-i)->spd[Y] -= (MenuStatus-i)->acc[Y];
						}
					}
					for (i = 1, j = 6; i < 11; i++) {
						pal = menuobject_tbl[j++];
						chr = menuobject_tbl[j++];
						svec.vx = menuobject_tbl[j++];
						svec.vy = menuobject_tbl[j++];
						mode = menuobject_tbl[j++];
						wait = menuobject_tbl[j++];
						MenuStatus2 = SpriteEntry(pal, chr, &svec, NULL, mode, wait);
						MenuStatus2->pmode = CLUT4 | NBLEND;
					}
#ifdef SONY	// とりあえず提出版
					(MenuStatus2 - 2)->status = 17;
#endif
					(MenuStatus2-9)->chr = fix2_ofs + (GetNumber / 10);
					(MenuStatus2-8)->chr = fix2_ofs + (GetNumber % 10);
					MenuSubStatus--;
					break;
			}
		}
		if (MenuSubStatus == 2) (MenuStatus2 - 1 + MenuCursolPos2)->pal = (0x010 << 5) + 485 + MenuCursolPos;
	}

   return( 0 );
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TEST MENU                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
const char *task_name[] = {
	"%d<POLYGON TEST>",
	"%d<MAIN MENU>",
	"%d<STRATEGY MAP>",
	"%d<STREET MAP>",
	"%d<TITLE>",
	"%d<ZUKAN>",
	"%d<POKESTE>",
	"%d<MEMOCAR>",
	"%d<STAFF>",
};

int TestMenu()
{
	pcb.dbg = 1;
	POSITION.offx = 160;
	POSITION.offy = 120;
	if ((PadDat[0].trg & PADLleft)>0) mode -= 1;
	if ((PadDat[0].trg & PADLright)>0) mode += 1;
	if (mode >= (PRCS_TBL_MAX - 1)) mode = 0;
	if (mode < 0) mode = (PRCS_TBL_MAX - 2);
	if ((PadDat[0].trg & PADstart)>0) {
		pcb.req = mode + 1;
		pcb.dbg = 0;
	}
	FntPrint(task_name[mode],mode + 1);

   return( 0 );
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TEXTURE INIT                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/* テクスチャデータをVRAMにロードする */
void Mn_texture_init(addr)
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



