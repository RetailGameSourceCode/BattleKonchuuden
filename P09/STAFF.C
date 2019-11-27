/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : STAFF ROLL                                               */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : STAFF.C                                                  */
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
#include "../lib/polygon.h"
#include "../sprite/sprite.h"
#include "../redlib/sndno.h"
#include "../redlib/xano.h"
#include "../p09/anmdata.h"

/*----- Local Works           -----*/
u_char		StSubStatus = 0;
u_char		StBgStatus = 0;
u_char		StBgNumber = 0;
long		StLocalTimer = 0;

/*----- Local Difinitions     -----*/
int StaffInit();
int StaffMain();
int StFadeWait();
void StNextBgSet();
void St_texture_init(addr);
void St_SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize);

PRCS_TBL staff_tbl[] =
{
	{ StaffInit },
	{ StaffMain },
	{ StFadeWait },
};


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STAFF ROLL                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int Staff()
{
	StLocalTimer++;

	staff_tbl[ StSubStatus ].func();

	XA_SYNC();
	GsClearOt( 0, 0, &spriteot[ PSDIDX ] );
	GsSortOt( &spriteot[ PSDIDX ], &ot[ PSDIDX ]);

	if (BGFadeOffset) St_SpriteBgSet( 26, 481, -160, -120, CLUT8, 160, 240);
	SpriteControll();

   return( 0 );
};


int StaffInit()
{
	int i, j;
	SVECTOR avec;
	u_short pal,chr,mode,wait;
	RECT            rect;

	DATA_CLOSE(1);
	SOUND_I();
	SE_LOAD(0);

	SpriteInit((CzAnimData *) St_SequenceTbl);

	{
		long i, cmp;

		FioReadFile((Uint8 *) "DT\\ROLL.TEX", (Uint8 *) LOAD_ADDR);
		StBgNumber = 32;
		for (i = 0; i < StBgNumber; i++) {
			cmp = NumToAddrMcr( i, LOAD_ADDR );
			LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
			LzDecB();
			St_texture_init( TENKAI_ADDR );
			DrawSync(0);
		}
	}

	avec.vz = 1;
	avec.vx = 160 - 160;
	avec.vy = 240 - 120;
	SpriteEntry((0x000 << 5) + 480, roll_ofs + 0, &avec, NULL, 18, 0);
	avec.vy = 240 - 120 + 128;
	SpriteEntry((0x000 << 5) + 480, roll_ofs + 1, &avec, NULL, 18, 0);
	avec.vy = 240 - 120 + 256;
	SpriteEntry((0x000 << 5) + 480, roll_ofs + 2, &avec, NULL, 18, 0);
	avec.vy = 240 - 120 + 384;
	SpriteEntry((0x000 << 5) + 480, roll_ofs + 3, &avec, NULL, 18, 0);

	XA_LOAD( XA_ED );

	FadeInit( FADE_IN, 0x08);

	BGFadeOffset = 0;
	StBgStatus = 2;
	StSubStatus++;
	return (0);
}


int StaffMain()
{
	if (StLocalTimer >= (60 * 32 + 20)) {
		StLocalTimer = 0;
		if (StBgNumber == 38) {
			XA_CLR();
			FadeInit( FADE_OUT, 0x08);
			pcb.req = PRCS_04;
			StSubStatus++;
		} else {
			StBgStatus = 1;
		}
	}
	StNextBgSet();
	return (0);
}


int StFadeWait()
{
	if (fade.status == 0) {
		SpriteInit((CzAnimData *) St_SequenceTbl);
		pcb.req = pcb.pno;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TEXTURE INIT                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/* テクスチャデータをVRAMにロードする */
void St_texture_init(addr)
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


void StNextBgSet()
{
	long cmp;

	switch (StBgStatus) {
		case 0:
			break;
		case 1:
			if (BGFadeOffset == 0) {
				StBgStatus++;
			} else {
				BGFadeOffset -= 2;
				if (BGFadeOffset < 0) BGFadeOffset = 0;
			}
			break;
		case 2:
			cmp = NumToAddrMcr( StBgNumber++, LOAD_ADDR );
			St_texture_init( cmp );
			StBgStatus++;
			break;
		case 3:
			if (BGFadeOffset == 0x80) {
				StBgStatus = 0;
			} else {
				BGFadeOffset += 2;
				if (BGFadeOffset > 0x80) BGFadeOffset = 0x80;
			}
			break;
	}
}


#define	max_width	64
void St_SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize)
{
	Uint32	pri;
	GsSPRITE	sp,sprite;

		pri = (1 << OT_LENGTH) - 1;
		sprite.attribute = attr | ZOOM_OFF;
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


