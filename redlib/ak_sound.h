/*赤沢ヘッダファイル*/
#ifndef __AKAZAWA_H__
#define __AKAZAWA_H__
// define

#define SEQ_NO	1	/*同時オープンＳＥＱファイル(最大３２)*/
#define NO_SEP	1	/*ＳＥＰ未使用時*/
#define SEP_NO	16	/*ＳＥＰ内のＳＥＱ最大数  max=16*/

#define BGM_UP  		0			/* main volume */
#define BGM_DOWN		1			/* main volume */

#define MVOL			127			/* main volume */
#define SVOL			95			/* seq data volume 元は100*/ 
#define VOL				127			/* vab data volume */

#define	XA_VOL_D		90			/*default volume (xa)*/
#define	BGM_VOL_D		95			/*default volume (seq)*/
#define	SE_VOL_D		36			/*default volume (se)*/

#define SP_MARGIN	( 4 * 75 )	/* 4sec アンダーフローした時の保険*/
//#define SP_MARGIN	( 16 * 75 )	/* 1sec アンダーフローした時の保険*/
#define	XA_FREQ		32

#define XA_ERR_MAX	0x100		/*リトライ回数256回*/

#define		LZDATA_ADDR0		0x80160000		/* 圧縮データの先頭番地 */
#define		LZDATA_ADDR1		0x80120000		/* 圧縮データの解凍先頭番地 */
#define		LOAD_ADDR0  		0x80120000		/* とりあえず転送用先頭番地 */
//#define		secter_buffer		0x80120000		/* セクタ情報バッファ先頭番地 */
//サウンドツール用

/*  VB はサウンドバッファに転送される*/
//（常駐）
#define VAB_HADDR0      0x801f0000L             /* 常駐SE (0xc20）   Header Address */
#define VAB_BADDR0      0x80120000L             /* 常駐SE            Data   Address */
#define SEQ_ADDR0       0x801fC000L      		/* 常駐BGM（未使用） Data   Address */
//（ＳＥ）
#define VAB_HADDR1      0x801f2000L             /*     SE            Header Address */
#define VAB_BADDR1      0x80120000L             /*     SE            Data   Address */
#define SEQ_ADDR1       0x801fC000L      		/*     BGM（未使用） Data   Address */
//（ＳＥ）
#define VAB_HADDR2      0x801f4000L             /*     SE            Header Address */
#define VAB_BADDR2      0x80120000L             /*     SE            Data   Address */
#define SEQ_ADDR2       0x801fC000L      		/*     BGM（未使用） Data   Address */
//（ＢＧＭ）
//#define VAB_HADDR3      0x801f8000L             /*     SE            Header Address */
#define VAB_HADDR3      0x801f2000L             /*     SE            Header Address */
#define VAB_BADDR3      0x80180000L             /*     SE            Data   Address */
//#define SEQ_ADDR3       0x801fB000L      		/*     BGM           Data   Address */
#define SEQ_ADDR3       0x801f5000L      		/*     BGM           Data   Address */

// サウンドナンバ－       0x80114000L			/*     BGM           Data   Address */
#define OPENVABID0      0x00000000				/* VAB OPEN ID */
#define OPENVABID1      0x00000001				/* VAB OPEN ID */
#define OPENVABID2      0x00000002				/* VAB OPEN ID */
#define OPENVABID3      0x00000003				/* VAB OPEN ID */
#define OPENVABID4      0x00000004				/* VAB OPEN ID */
#define OPENVABID5      0x00000005				/* VAB OPEN ID */
#define OPENVABID6      0x00000006				/* VAB OPEN ID */
#define OPENVABID7      0x00000007				/* VAB OPEN ID */
#define OPENVABID8      0x00000008				/* VAB OPEN ID */
#define OPENVABID9      0x00000009				/* VAB OPEN ID */
#define OPENVABIDa      0x0000000a				/* VAB OPEN ID */
#define OPENVABIDb      0x0000000b				/* VAB OPEN ID */
#define OPENVABIDc      0x0000000c				/* VAB OPEN ID */
#define OPENVABIDd      0x0000000d				/* VAB OPEN ID */
#define OPENVABIDe      0x0000000e				/* VAB OPEN ID */
#define OPENVABIDf      0x0000000f				/* VAB OPEN ID */


// enum

// 変数
/*	サウンドツール用 */
extern short vab[4];			/* vab data id */
extern short seq[4];			/* seq data id */

/*ak_sound.c のみでしか使用しないのでここでは止めておく*/
//extern char seq_table [SS_SEQ_TABSIZ * SEQ_NO * SEP_NO];  /* seq table size */
//extern int	var_err;


/* XA */
/*from psx libds*/
//extern DslATV	CD_VOL;		/*オーディオアッテネータ(cd-cd,xaのボリューム指定に使用)*/
/*CD_VOL はwork.cにて定義すべき？*/
// libcd へ変更
extern CdlATV CD_VOL;// オーディオアッテネータ


extern int CurPos,EndPos,StartPos,Loop_F,XA_END,Chan;



extern unsigned char		param[4];
extern unsigned char		result[8];



//extern int 		CurPos,EndPos,StartPos,Loop_F,XA_END,Chan;
extern char		VAB_STATUS[4];			// 内臓音源管理ワーク 
extern char		SEQ_STATUS[4];
extern int	 	SN_ENT_W[4][2];


// 構造体
typedef struct {/*サウンド関係構造体*/
	u_char  FLAG;			/* サイズ的にあまったので付けてみただけ */
	u_char	BGM_VOL;		/* ＢＧＭ（ＸＡ込み） ボリューム値（０～１２７）*/
	u_char	SE_VOL;			/* ＳＥ  			  ボリューム  （０～１２７）*/
	u_char  MODE;			/* ０：ステレオ／１：モノラル */
} SND_DATA;

extern SND_DATA snd_data;


/*program no & pitch*/
typedef struct {/*ＳＥナンバー構造体*/
	long prog;	/* program no */
	long pitch;	/* pitch */
} KON;

/*サウンド固めた奴読み込み用*/
typedef struct {
	int ST;// start point
	int SI;// size
} CATSND;




extern KON SE_TBL[];/*ak_sntbl.cにてテーブル指定します*/
//extern SE_TBL[];/*実体は関数の外側に記述*/


// table
// extern short test_sound_table[];// exsample
/*KON は構造体、この宣言は構造体の後の方が良い？？*/
//extern SE_TBL[];//どうやら構造体の宣言だけでテーブルのほうは要らないらしい

extern int	VAB_HADDR[];
extern int	VAB_BADDR[];
extern int	OPENVABID[];

// 以下のテーブルはXA以外は未使用状態(データ固めちゃったから)
extern char *BGM_LTBL[][3];/*文字列配列への参照(教本１２３Ｐ)*/
extern char *SE_LTBL[][2];
extern char *XA_LTBL[];/*XAの場所*/
extern int XA_LONG[][8];/*こちらは変更の可能性あり*/
// これも確か未使用
extern char *REP_TBL[];/*REP文字列テーブル*/

// たまに使う汎用テスト変数
extern int bgm;		/*BGM ループテスト用*/


#endif