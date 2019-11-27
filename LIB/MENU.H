/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : MENU TEST [ DEV CODE: 97026 ]                            */
/*  File Attribute: HEADER                                                   */
/*  File Name     : MENU.H                                                   */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _MENU_H_
#define _MENU_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ADDRESS INFOMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define TENKAI_ADDR	 (0x80100000)	/* 展開バッファ */
#define LOAD_ADDR	 (0x80128000)	/* ファイルロードバッファ */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern int MainMenu();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _MENU_H_ */
