/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫げー"                                       */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : map 表示                                               */
/*  File Name     : MAP.H                                                  */
/*                                                           by H.TATEYAMA */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _MAP_H_
#define _MAP_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  Include File(s)                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*----- User Header     Files -----*/
#include "../lib/go.h"


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
//extern char             cMapLimit;
extern char             cResOn;
extern char             cShopOn;
extern char             cFadeFlag, cFadeSyurui;
extern char             cGodebugstatus;
extern char             cResWinFlag;
extern int              intMapXaNo;
extern FIXED            worldpos[XY];  // world pos
extern unsigned char    *cMonth, *cDay, *cWeek;
extern unsigned long    map_frame;
extern short            iMapStatusMain;
extern short            iResRtn;
extern short            iShopRtn;
extern short            iFadeSpeed;
extern short            iRr, iGg, iBb;
extern short            fadergb[RGB];
extern short            iMapScale;
extern short            iNextPrs;
extern short            iNextArea;
extern short            iMapPanelX, iMapPanelY;  // 面のパネル数 

#define                 MPX            128
#define                 MPY            128
#define                 MAP_BUFX_MAX   1600/MPX+1
#define                 MAP_BUFY_MAX   1600/MPY+1

extern char             map_buf[MAP_BUFY_MAX][MAP_BUFX_MAX];


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void map_main(void);
extern void map_init(void);
extern void map_set(void);
extern void map_ctrl(void);
extern void map_pad_ctrl(void);
extern void map_disp_judge(void);
extern void map_load_image(short iNorB);
extern void map_disp(void);
extern void map_gray(char cSta, short iX, short iY, short iColor, short iXt, short iYt);
// cSta 0:change or 1:return      iColor 16 or 256 
extern void map_semitrans(short iA, short iX, short iY, short iColor, short iXt, short iYt);
extern void map_charmask(char cSta, short iX, short iY, short iColor, short iXt, short iYt);
extern void map_fade(void);
extern void map_obj_disp(void);
extern void map_hit_data_set(void);
extern void map_next_prcs(void);
extern void map_result(void);
extern void map_shop(void);
extern int  MapFioDivReadFile2( char *filename, u_char *addr, int ss, int ns );
extern int  MapFioDivReadCD( char *filename, u_char *addr, int ss, int ns );
extern int  MapFioReadStatus( int mode );


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  いいずか氏作                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#define RESOK SE_ENT(SE_OK1);
#define RESMV SE_ENT(SE_CUR1);

extern int ResultWindowDraw(int);
extern void LoadResultTim(void);
extern void FSNext(int,int);
extern void FSNakama(void);
extern void FSAjax(int,int,int,int);
extern void FSNumber(int,int,int);
extern void FSmushi(int,int);
extern void FSGoukei(int);
extern void SSWnd(int);
extern void FSCard(int,int,int);
//extern void LoadResultTim(void);
extern void FSErabu(int,int);
extern void SSSavePsSleep(int y);

//#define RESULT_ADDR 0x80100000

typedef struct {
	short	goukei_sum;		//その虫の合計ポイント.
	char	type;			//虫のタイプ（１＝カブトムシ）.
	char	kosuu;			//その虫を何匹ゲットしたか.
} *LPRESULT;

//LPRESULT result;   //=(LPRESULT)(RESULT_ADDR);



// warning warning warning warning warning warning warning warning
//  
//  以前のものよりも若干の変更があります！！.
//
//  ・「次へ」「決定」等の表示が半透明になりました.
//  ・ボスゲット時にもポイントが加算される仕様だそうですので、そうしました.
//    result[0].goukei_sum にボスのポイント数を渡して下さい.
//
// warning warning warning warning warning warning warning warning



//
// カード数を渡すには、以下のようにしてください.
//    result[0].card = 68000;
//
//  戦いでゲットした昆虫の種類数の識別は以下の例を参考にしてください.
//
//  result[0].type = 1;   //ボスのタイプ.
//  result[1].type = 23;  //ゲットした雑魚のタイプ.
//  result[2].type = 13;  //ゲットした雑魚のタイプ.
//  result[3].type = 0;   //終了識別のゼロ.
//  result[0].kosuu = ??; //void です.
//  result[1].kosuu = 8;
//  result[2].kosuu = 12;
//  result[0].goukei_sum = 500;
//  result[1].goukei_sum = 6800;
//  result[2].goukei_sum = 6500;
//
//  これで、ボス１番（カブトムシ）５００ポイントと.
//  ２３番（アラメヘラヅノカブト）を８匹で６８００ポイント. 
//  １３番（ゴホンヅノカブト）を１２匹で６５００ポイント.
//
//  入手したという引数になります.
//
//  ご注意！
//    この関数は算出結果を表示するだけです。内部パラメータの更新は致しませんので. 
//    ご注意下さい.
//
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern int  MapShopping(int);
extern void FSZabutonS(int,int,int);
extern void FSMochisuu(int,int);
extern void FSCommandS(int);
extern void FSZaikoS(void);
extern void SSWndS(int);
extern void FSNumberS(int,int,int);
extern void FS8x16S(int,int,int,int);
extern void FSCardS(int,int,int);
extern void LoadShoppingTim(void);
extern void FSKatta(int);
extern void FSTarimasen(void);
extern void FSKaisugideath(void);
extern void IchiBye(int);
extern void IchiTarinai(int);
extern void IchiMaido(int);

//int	*shoppar;		
//↑アイテム情報引き渡しのためのポインタです.
//
// 引数 Format :
//    shoppar[0] == むしむしゼリー   の所有数.
//    shoppar[1] == むしむしゼリーＡ の所有数.
//    shoppar[2] == むしむしゼリーＸ の所有数.
//    shoppar[3] == むしむしゼリーＺ の所有数.
//    shoppar[4] == むしむしパワードリンク の所有数.
//    shoppar[5] == むしエリクシール の所有数.
//    shoppar[6] == カード（お金？）の所有数.
//
// 戻り値 :
//   MapShopping(int); 終了後、上記メモリロケーション上にショッピングした
//   結果が戻ってきます。
//
// ご注意 :
//   各パラメータ受け取り直後の「丸め」は内部では行っていません.
//   蛇足ですが各アイテムの個数に９９を超える値を渡さないで下さい.
//   同様にカード（お金？）の値に 9999999 を超える値を渡さないで下さい.
//



/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/


#endif


