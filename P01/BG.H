/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : BG ENGINE                                                */
/*  File Attribute: HEADER                                                   */
/*  File Name     : BG.H                                                     */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _BG_H_
#define _BG_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ORDERING TABLE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define BGOT_LENGTH	8		/* オーダリングテーブルの解像度 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  BGMODEL DATA INFORMATION                                                   */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short			status;					/* モデルのステータス */
	u_long			attribute;				/* モデル全体のアトリビュート */
	short			Objnum;					/* モデリングデータのオブジェクトの数を保持する */
	long			pos[XYZ];				/* モデルの座標系 */
	short			ang[XYZ];				/* 座標系を作るためのローテーションベクター */
	long			trans[XYZ];				/* モーションのトランス */
	GsDOBJ2			object[1];				/* オブジェクトハンドラ オブジェクトの数だけ必要 */
	GsCOORDINATE2	objpos[1];				/* オブジェクトごとの座標系 */
	SVECTOR			objang[1];				/* 座標系を作るためのローテーションベクター */
} BGMODEL ;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GsOT        bgot[2];						/* Ordering Table                  */
extern GsOT_TAG    bgot_tag[2][1<<BGOT_LENGTH];	/* オーダリングテーブル実体        */

extern void bg_main();
extern void bg_init();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _BG_H_ */
