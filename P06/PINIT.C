/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : PLAYER INIT                                              */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : PINIT.C                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <sys/file.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>
#include <libcd.h>
#include <libds.h>

/*----- User Header     Files -----*/
#include "../lib/libctl.h"
#include "../lib/libfio.h"
#include "../lib/aki_def.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/mainsys.h"
#include "../lib/lz.h"
#include "../lib/model.h"
#include "../lib/polygon.h"
#include "../p06/pinit.h"

void Zu_player_init(char p_no, P_MODEL *ppp);
void Zu_player_init_NB(char p_no, P_MODEL *ppp);

const u_short Zu_model_sector[] = {
#include "../p01/model/model.rep"
};

const u_short Zu_panel_sector[] = {
#include "../p06/sprite/panel.rep"
};

const P_DATA Zu_player_data[] = {
#include "../p01/pdata.tbl"
};

u_char   cdlmodespeed2[ 4 ] = { CdlModeSpeed                        , 0, 0, 0 };

//#define CD 1

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER INIT                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void Zu_player_init(char p_no, P_MODEL *ppp)
{
	P_DATA *pd;
	long i, j, cmp, len, num;
	short sector;

#ifndef PREPRE
	printf("player%dinit = %d\n", p_no, ppp->chrno);
#endif
	pd = (P_DATA *) Zu_player_data + ppp->chrno;
	ppp->mod->status = p_no;
	ppp->length = pd->length;
	ppp->reflect = pd->reflect;
	ppp->render = pd->render;
	ppp->size = pd->size;
	ppp->hitpos = pd->hitpos;

	/* モーションデータ */
	sector = (ppp->chrno * 10);
	FioDivReadFile( "DT\\MODEL.DAT", ppp->motd, Zu_model_sector[sector], Zu_model_sector[sector + 1] );

	sector += (p_no * 2);
	FioDivReadFile( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 2], Zu_model_sector[sector + 3] );
	num = *(u_long *) LOAD_ADDR;
	for (i = 0, j = 0; i < num; j++) {
		/* 階層データ */
		cmp = NumToAddrMcr( i++, LOAD_ADDR );
		len = (NumToAddrMcr( i, LOAD_ADDR )) - cmp;
		memcpy((ppp->buf + j)->cls, (u_char *) cmp, len);
		/* モデルデータ */
		cmp = NumToAddrMcr( i++, LOAD_ADDR );
		LzDecInit( (u_char *) cmp, (ppp->buf + j)->tmd, 0);
		LzDecB();
	}

	/* テクスチャ */
	FioDivReadFile( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 6], Zu_model_sector[sector + 7] );
	num = *(u_long *) LOAD_ADDR;
	for (i = 0; i < num; i++) {
		cmp = NumToAddrMcr( i, LOAD_ADDR );
		LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
		LzDecB();
		Zu_texture_init( TENKAI_ADDR );
		DrawSync(0);
	}
	FioDivReadFile( "DT\\PANEL.TEX", (u_char *) LOAD_ADDR, Zu_panel_sector[ppp->chrno * 2], Zu_panel_sector[ppp->chrno * 2 + 1] );
	LzDecInit( (u_char *) LOAD_ADDR, (u_char *) TENKAI_ADDR, 0);
	LzDecB();
	Zu_texture_init( TENKAI_ADDR );

	model_init( (long *) ppp->buf->tmd,  ppp->mod );
	coord_init( (KAISOU *) (ppp->buf->cls + 8), ppp->mod );
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER INIT(NON BLOCK)                                                   */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void Zu_player_init_NB(char p_no, P_MODEL *ppp)
{
	P_DATA *pd;
	long cmp, len, num, rtn;
	short sector;
static int id;

#ifndef PREPRE
	printf("player%dinit = %d\n", p_no, ppp->chrno);
#endif
	switch (ppp->status) {
		case 1:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				id = CdControlF( CdlSetmode, cdlmodespeed2 );
				if ( id == 0 )
				{
					printf( "Can't CD Setmode\n");
					return( -1 );
				} else ppp->status++;
				break;
			}
		case 2:
			if (CdSync( 1, NULL) == CdlComplete) {
				pd = (P_DATA *) Zu_player_data + ppp->chrno;
				ppp->length = pd->length;
				ppp->reflect = pd->reflect;
				ppp->render = pd->render;
				ppp->size = pd->size;
				ppp->hitpos = pd->hitpos;

				/* モーションデータ */
				sector = (ppp->chrno * 10);
#if CD
				rtn = FioDivReadCD2( "DT\\MODEL.DAT", ppp->motd, Zu_model_sector[sector], Zu_model_sector[sector + 1] );
#else
				rtn = FioDivReadFile2( "DT\\MODEL.DAT", ppp->motd, Zu_model_sector[sector], Zu_model_sector[sector + 1] );
#endif
				if ( rtn != -1 ) ppp->status++;
			}
			break;
		case 3:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				/* モデルデータ */
				sector = (ppp->chrno * 10) + (p_no * 2);
#if CD
				rtn = FioDivReadCD2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 2], Zu_model_sector[sector + 3] );
#else
				rtn = FioDivReadFile2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 2], Zu_model_sector[sector + 3] );
#endif
				if ( rtn != -1 ) {
					ppp->power = 0;
					ppp->status++;
				}
			}
			break;
		case 4:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				num = *(u_long *) LOAD_ADDR;
				/* 階層データ */
				cmp = NumToAddrMcr( ppp->power, LOAD_ADDR );
				len = (NumToAddrMcr( ppp->power + 1, LOAD_ADDR )) - cmp;
				memcpy((ppp->buf + (ppp->power >> 1))->cls, (u_char *) cmp, len);
				/* モデルデータ */
				cmp = NumToAddrMcr( ppp->power + 1, LOAD_ADDR );
				LzDecInit( (u_char *) cmp, (ppp->buf + (ppp->power >> 1))->tmd, 0);
				LzDecB();
				if ((ppp->power += 2) == num) ppp->status++;
			}
			break;
		case 5:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				sector = (ppp->chrno * 10) + (p_no * 2);
				/* テクスチャ */
#if CD
				rtn = FioDivReadCD2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 6], Zu_model_sector[sector + 7] );
#else
				rtn = FioDivReadFile2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, Zu_model_sector[sector + 6], Zu_model_sector[sector + 7] );
#endif
				if ( rtn != -1 ) {
					ppp->power = 0;
					ppp->status++;
				}
			}
			break;
		case 6:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				num = *((u_long *) LOAD_ADDR);
				cmp = NumToAddrMcr( ppp->power, LOAD_ADDR );
				LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
				LzDecB();
				Zu_texture_init( TENKAI_ADDR );
				if (++ppp->power == num) {
#if CD
					rtn = FioDivReadCD2( "DT\\PANEL.TEX", (u_char *) LOAD_ADDR, Zu_panel_sector[ppp->chrno * 2], Zu_panel_sector[ppp->chrno * 2 + 1] );
#else
					rtn = FioDivReadFile2( "DT\\PANEL.TEX", (u_char *) LOAD_ADDR, Zu_panel_sector[ppp->chrno * 2], Zu_panel_sector[ppp->chrno * 2 + 1] );
#endif
					ppp->status++;
				}
			}
			break;
		case 7:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				LzDecInit( (u_char *) LOAD_ADDR, (u_char *) TENKAI_ADDR, 0);
				LzDecB();
				Zu_texture_init( TENKAI_ADDR );
				model_init( (long *) ppp->buf->tmd,  ppp->mod );
				coord_init( (KAISOU *) (ppp->buf->cls + 8), ppp->mod );
				motion_init( ppp->motd, ppp->mot, 0, -1 );
				ppp->status = 0;
			}
			break;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TEXTURE INIT                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/* テクスチャデータをVRAMにロードする */
void Zu_texture_init(addr)
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