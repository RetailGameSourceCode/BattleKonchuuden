/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON MODEL/MOTION ENGINE                              */
/*  File Attribute: HEADER                                                   */
/*  File Name     : MODEL.H                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _MODEL_H_
#define _MODEL_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  OBJECT MAX                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define OBJECTMAX	(43)					/* １モデルに対する最大オブジェクト数 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL DATA INFORMATION                                                   */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short			status;					/* モデルのステータス */
	u_long			attribute;				/* モデル全体のアトリビュート */
	short			Objnum;					/* モデリングデータのオブジェクトの数を保持する */
	long			pos[XYZ];				/* モデルの座標系 */
	short			ang[XYZ];				/* 座標系を作るためのローテーションベクター */
//	long			scl[XYZ];				/* モデルのスケール */
	long			trans[XYZ];				/* モーションのトランス */
	GsDOBJ2			object[OBJECTMAX];		/* オブジェクトハンドラ オブジェクトの数だけ必要 */
	GsCOORDINATE2	objpos[OBJECTMAX];		/* オブジェクトごとの座標系 */
	SVECTOR			objang[OBJECTMAX];		/* 座標系を作るためのローテーションベクター */
//	VECTOR			objscl[OBJECTMAX];		/* オブジェクトのスケール */
} MODEL ;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL ATTRIBUTE INFORMATION                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define OBJ_NBLEND	(GsALON | GsAZERO)		/* 半透明 */
#define OBJ_ABLEND	(GsALON | GsAONE)		/* 加算 */
#define OBJ_HBLEND	(GsALON | GsATWO)		/* 減算 */
#define OBJ_SBLEND	(GsALON | GsATHREE)		/* 半加算 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  KAISOU DATA ( CLS FILE ) INFORMATION                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short			exist;					/* オブジェクトが存在するか？（１する、０しない） */
	short			parts_no;				/* オブジェクトのパーツナンバー */
	short			super;					/* 親オブジェクトの番号(PARENTでWORLD) */
	short			ang[XYZ];				/* アングル */
	long			pos[XYZ];				/* トランスデータ */
	long			scl[XYZ];				/* スケール */
} KAISOU;

#define EXIST		(1)
#define NOT_EXIST	(0)
#define PARENT		(-1)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION MAX                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define FRAMEMAX	(144)					/* モーションの最大フレーム数 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION DATA INFORMATION                                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	long			pos[XYZ];				/* ルートオブジェクトのトランス */
	short			ang[OBJECTMAX][XYZ];	/* オブジェクトごとのアングル */
} MOTION_DATA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION INFORMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	u_short			num;					/* モーションナンバー */
	u_short			frame;					/* モーションの総フレーム数 */
	u_short			parts;					/* モデルのパーツ数 */
	u_short			count;					/* モーションのフレーム数 */
	short			loop;					/* ループカウンタ */
	int				*otbl;					/* オブジェクトナンバーテーブル */
	MOTION_DATA		*bufp;					/* モーションデータバッファ */
} MOTION;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CAMERA INFORMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	GsRVIEW2		view;					/* 視点を設定するための構造体 */
	GsCOORDINATE2	DView;					/* 視点をぶら下げる座標系 */
	int				mode;					/* モード */
	short			angle;					/* アングル */
	SVECTOR			svec;					/* ベクトル */
	long			*work;					/* ターゲットのワーク */
	long			timer;					/* タイマー */
	long			totaltime;				/* 総時間 */
	VECTOR			start;					/* 始点 */
	VECTOR			relay;					/* 中継点 */
	VECTOR			terminal;				/* 終点 */
} CAMERA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GsF_LIGHT	pslt[3];				/* 平行光源を設定するための構造体 */
extern GsRVIEW2		view;					/* 視点を設定するための構造体 */
extern u_short		Projection;				/* プロジェクション */
extern u_char		reflect;				/* 反射率 */
extern CAMERA		cam;					/* カメラ */
extern u_char		model_col[RGB];			/* カラーポリゴン色指定 */
extern u_short		tpage;					/* テクスチャページ指定 */

extern void model_sort(MODEL *mod, u_char rfl);
extern void motion_init(u_char *adr, MOTION *mot, u_short num, short loop);
extern void motion_test(MODEL *mod, MOTION *mot);
extern void camera_init();
extern void camera_move();
extern void light_init();
extern void fog_init();
extern void model_init(long *tmd, MODEL *mod);
extern void coord_init(KAISOU *cls, MODEL *mod);
extern void jt_init4();						/* 描画環境の初期化 */
extern void jt_smnlset();					/* 環境マッピング( LIGHT OFF )の登録 */
extern void jt_smlset();					/* 環境マッピング( LIGHT ON  )の登録 */
extern void jt_smsplset();					/* 環境マッピング( 虹色 )の登録 */
extern void jt_smsp3lset();					/* 環境マッピング( クロツヤ )の登録 */
extern void jt_smsp4lset();					/* 環境マッピング( チリー )の登録 */
extern void jt_wireset();					/* ワイヤーフレームの登録 */
extern void jt_colorset();					/* カラーポリゴン( LIGHT OFF )の登録 */
extern void jt_colorcset();					/* カラーポリゴン( LIGHT ON  )の登録 */
extern void jt_tpageset();					/* TPAGE付きポリゴンの登録 */
extern void jt_opticsset();					/* 光学迷彩の登録 */
extern void jt_wire2set();					/* ワイヤーフレーム（加算） */
extern void jt_glassset();					/* ガラスの登録 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _MODEL_H_ */
