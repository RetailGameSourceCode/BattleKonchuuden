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
#include "../p01/battle.h"
#include "../p01/anmdata.h"
#include "../p01/pinit.h"

void player_init(char p_no, P_MODEL *ppp);
void player_init_NB(char p_no, P_MODEL *ppp);

const u_short model_sector[] = {
#include "../p01/model/model.rep"
};

const u_short beem_pal[] = {
#include "sprite/beempal.c"
};

#include "../p01/player.tbl"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER INIT                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void player_init(char p_no, P_MODEL *ppp)
{
	P_DATA *pd;
	long i, j, cmp, len, num;
	short sector;
	RECT rect;

#ifndef PREPRE
	printf("player%dinit = %d\n", p_no, ppp->chrno);
#endif
	pd = (P_DATA *) player_data + ppp->chrno;
	ppp->mod->status = p_no;
	ppp->length = pd->length;
	ppp->reflect = pd->reflect;
	ppp->render = pd->render;
	ppp->size = pd->size;
	ppp->hitpos = pd->hitpos;

	/* モーションデータ */
	sector = (ppp->chrno * 10);
	FioDivReadFile( "DT\\MODEL.DAT", ppp->motd, model_sector[sector], model_sector[sector + 1] );

	sector += (p_no * 2);
	FioDivReadFile( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, model_sector[sector + 2], model_sector[sector + 3] );
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
	FioDivReadFile( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, model_sector[sector + 6], model_sector[sector + 7] );
	num = *(u_long *) LOAD_ADDR;
	for (i = 0; i < num; i++) {
		cmp = NumToAddrMcr( i, LOAD_ADDR );
		LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
		LzDecB();
		texture_init( TENKAI_ADDR );
		DrawSync(0);
	}

	// ビームカラーバリエーション
	rect.x = 304;
	rect.y = 488 + (p_no * 3);
	rect.w = 16;
	rect.h = 3;
	/* VRAMにクラットをロードする */
	LoadImage(&rect, &beem_pal[(ppp->chrno % 4) * 48]);

	model_init( (long *) ppp->buf->tmd,  ppp->mod );
	coord_init( (KAISOU *) (ppp->buf->cls + 8), ppp->mod );
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER INIT(NON BLOCK)                                                   */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void player_init_NB(char p_no, P_MODEL *ppp)
{
	P_DATA *pd;
	long cmp, len, num;
	short sector;

	switch (ppp->status) {
		case 1:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
#ifndef PREPRE
				printf("player%dinit = %d\n", p_no, ppp->chrno);
#endif
				pd = (P_DATA *) player_data + ppp->chrno;
				ppp->length = pd->length;
				ppp->reflect = pd->reflect;
				ppp->render = pd->render;
				ppp->size = pd->size;
				ppp->hitpos = pd->hitpos;

				/* モーションデータ */
				sector = (ppp->chrno * 10);
				FioDivReadFile2( "DT\\MODEL.DAT", ppp->motd, model_sector[sector], model_sector[sector + 1] );
				ppp->status++;
			}
			break;
		case 2:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				/* モデルデータ */
				sector = (ppp->chrno * 10) + (p_no * 2);
				FioDivReadFile2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, model_sector[sector + 2], model_sector[sector + 3] );
				ppp->power = 0;
				ppp->status++;
			}
			break;
		case 3:
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
		case 4:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				sector = (ppp->chrno * 10) + (p_no * 2);
				/* テクスチャ */
				FioDivReadFile2( "DT\\MODEL.DAT", (u_char *) LOAD_ADDR, model_sector[sector + 6], model_sector[sector + 7] );
				ppp->power = 0;
				ppp->status++;
			}
			break;
		case 5:
			if (FioReadStatus(FIO_NON_BLOCK) == FIO_CD_READY) {
				num = *((u_long *) LOAD_ADDR);
				cmp = NumToAddrMcr( ppp->power, LOAD_ADDR );
				LzDecInit( (u_char *) cmp, (u_char *) TENKAI_ADDR, 0);
				LzDecB();
				texture_init( TENKAI_ADDR );
				if (++ppp->power == num) ppp->status++;
			}
			break;
		case 6:
			model_init( (long *) ppp->buf->tmd,  ppp->mod );
			coord_init( (KAISOU *) (ppp->buf->cls + 8), ppp->mod );
			motion_init( ppp->motd, ppp->mot, 0, -1 );
			ppp->status = 0;
			break;
	}
}




