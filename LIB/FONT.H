/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫げー"                                       */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : font 表示                                              */
/*  File Name     : FONT.H                                                 */
/*                                                           by H.TATEYAMA */
/*                                                                         */
/*  void font_tim_set(void);                                               */
/*  void font_init(void);                                                  */
/*  void goprintf(int iX, int iY, char *str,...);                          */
/*  void goprintf2(int iX, int iY, char *str,...);                         */
/*                                                                         */
/*  >    goprintf goprintf2 は C関数 printf みたいな物です (DEBUG 用)      */
/*  >    goprintf  は画面座標で Ｘ・Ｙ を指定します                        */
/*  >    goprintf2 は Ｘ・Ｙ の １ が １文字分の 単位です                  */
/*                                                                         */
/*  >    usage:                                                            */
/*  >         goprintf(16, 16, "画面左上 16 X 16 から表示");               */
/*  >         goprintf2(10,10, "画面左上 10 X 10 文字分から表示");         */
/*                                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _FONT_H_
#define _FONT_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern char   cCol;
extern short  iFontPri;

#define  MOJIKANX            14 
#define  MOJIKANY            16 
#define  HIRAGANAKANKAKU     2    // ひらがなの間隔 
#define  SANO                144  // small 'a' font no 
#define  LANO                118  // large 'A' font no 
#define  ZERONO              108  // '0' font no 
#define  BARNO               60   // '-' or 'ー' font no 
#define  HIRAGANANO          171  // 'あ' font no 
#define  KATAKANANO          254  // 'ア' font no 
#define  McrFontPriSet(x) iFontPri = x;     // goprintf(2) 用 OT での位置指定 


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void font_tim_set(void);
extern void font_init(void);
extern void fontput(short iNo, short iX, short iY);
extern void puts_str(unsigned char *str, short iX, short iY);   // 文字列表示（画面座標版） 
extern void puts_str2(unsigned char *str, short iX, short iY);  // 文字列表示 
extern void puts_dec(int iN, int iX, int iY, int iZ);           // 整数 10 進数表示（画面座標版） 
extern void puts_dec2(int iN, int iX, int iY, int iZ);          // 整数 10 進数表示 
extern void puts_hex(int iN, int iX, int iY, int iZ);           // 整数 16 進数表示（画面座標版） 
extern void puts_hex2(int iN, int iX, int iY, int iZ);          // 整数 16 進数表示 
extern void goprintf(int iX, int iY, char *str,...);            // 書式指定文字列表示（画面座標版） 
extern void goprintf2(int iX, int iY, char *str,...);           // 書式指定文字列表示 
extern void font_col_set(char cColNo);


#endif


