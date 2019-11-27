/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫げー"                                       */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : decoration 表示                                        */
/*  File Name     : MAPDEC.H                                               */
/*                                                           by H.TATEYAMA */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _MAPDEC_H_
#define _MAPDEC_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#define  DAYDISPX      -160+24
#define  DAYDISPY      -120+24
#define  PLACEDISPX    -40
#define  PLACEDISPY    -100
#define  SAVEPLATEX    -160+40
#define  SAVEPLATEY     72
#define  CROSSPLATEX    8
#define  CROSSPLATEY    72+8 // '98 11/16 下に1キャラずらすた↓ 
#define  BATUPLATEX     72
#define  BATUPLATEY     72+8
#define  SIKAKUPLATEX   72
#define  SIKAKUPLATEY   72+8
#define  CDPLATEX       -160+40
#define  CDPLATEY       72+8
/*- Color Image File Def ----3----+----4----+----5----+----6----+----7----+*/
#define  TATEX          80
#define  TATEY          511
/*- Color Image Def ----+----3----+----4----+----5----+----6----+----7----+*/
#define  MESWINX        80   // messsage window & name window
#define  MESWINY        511
#define  PUSHCOLX       96   // push any key 
#define  PUSHCOLY       511
#define  KEYCOLX        112  // 十字 key 
#define  KEYCOLY        511
#define  MARUCOLX       128  // ◎ key 
#define  MARUCOLY       511
#define  BATUCOLX       144  // × key 
#define  BATUCOLY       511
#define  SANKAKUCOLX    160  // △ key 
#define  SANKAKUCOLY    511
#define  SIKAKUCOLX     176  // □ key 
#define  SIKAKUCOLY     511

extern char   cPanelMove;
//extern char   cCdPanelUp;
extern char   cMapdecSta;
extern char   cCdSta;
extern char   cDayDispSta;
extern char   cSaveKeySta;
extern char   cCrossKeySta;
extern char   cBatuKeySta;
extern char   cSikakuKeySta;
extern char   cCdPlateSta;
extern short  iHit;
extern short  iHitBak;
extern short  iXCROSS;
extern short  iXBATU;


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void mapdec_tim_set(void);      // map decoration tim set 
extern void mapdec_disp(void);         // map decoration disp 
extern void day_disp(char cSta);       // day disp 
extern void place_disp(char cSta);     // place disp 
extern void save_key_disp(char cSta);  // savee key plate disp 
extern void cross_key_disp(char cSta); // cross key plate disp 
extern void batu_key_disp(char cSta);  // batu key plate disp 
extern void sikaku_key_disp(char cSta);// sikaku key plate disp 
extern void cd_sta_disp(char cSta);    // cd-rom status disp 
extern void enter_disp(void);          // enter plate disp 


#endif


