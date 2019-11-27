/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : STREET MAP [ DEV CODE: 97026 ]                           */
/*  File Attribute: HEADER                                                   */
/*  File Name     : STREET.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _STREET_H_
#define _STREET_H_

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#if 0
#define PACK_INF_ADDR        0x80100000     // (2048 = 0x800)
#define TIM_ADDR             0x80100800
#define HITPOS_ADDR          0x80105000
#endif

extern int                   activeBuff;    // アクティブなバッファへのポインタ 
extern short                 area, stage;
extern GsSPRITE              *gsSpr;
extern GsLINE                *gsLine;
extern RECT                  rect;
extern GsIMAGE               im;


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern int Street();
extern void street_init();
extern void street_ctrl();


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _STREET_H_ */
