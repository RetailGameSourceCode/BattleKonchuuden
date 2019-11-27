/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SAVE LOAD  [ DEV CODE: 98025 ]                           */
/*  File Attribute: HEADER                                                   */
/*  File Name     : MCRD.H                                                   */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _MCRD_H_
#define _MCRD_H_

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern int AKMCRD();
extern void AK_MEM_DATA_INIT(int no);// データ初期化 23 or 24 入力でスタート日変更
// オートロード後に呼んでください
extern int RED_GAME_DAY_FLG(void);// 初日かどうかみます。返りが０だと初日、１だとそれ以外です
extern char RED_GAME_CLR_NO(void);// ゲームクリア回数を返します。クリア回数はcharでカウントしてください
extern int Red_2P_Unit_Load(void);// 2Pロード関数。０処理中 １で終了２はキャンセル 

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _MCRD_H_ */
