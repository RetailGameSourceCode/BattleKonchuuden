/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON TEST [ DEV CODE: 97026 ]                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : POLYGON.H                                                */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "../lib/model.h"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ADDRESS INFOMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define TENKAI_ADDR	 (0x80100000)	/* 28展開バッファ */
#define LOAD_ADDR	 (0x80128000)	/* 18ファイルロードバッファ */
#define PLAYER1_ADDR (0x80140000)	/* 28モーションデータ（MTNフォーマット）がおかれるアドレス */
#define MODEL1_ADDR	 (0x80168000)	/* 14モデリングデータ（TMDフォーマット）がおかれるアドレス */
#define PLAYER2_ADDR (0x8017c000)	/* 28モーションデータ（MTNフォーマット）がおかれるアドレス */
#define MODEL2_ADDR	 (0x801a4000)	/* 14モデリングデータ（TMDフォーマット）がおかれるアドレス */
#define BGMODEL_ADDR (0x801b8000)	/* 08モデリングデータ（TMDフォーマット）がおかれるアドレス */
#define EFMODEL_ADDR (0x801c0000)	/* 10モデリングデータ（TMDフォーマット）がおかれるアドレス */
#define STATIC_ADDR	 (0x801d0000)	/* 常駐データ */

//#define TENKAI_ADDR	 (0x80100000)	/* 展開バッファ */
//#define LOAD_ADDR	 (0x80128000)	/* ファイルロードバッファ */
//#define PLAYER1_ADDR (0x80140000)	/* モーションデータ（MTNフォーマット）がおかれるアドレス */
//#define MODEL1_ADDR	 (0x80168000)	/* モデリングデータ（TMDフォーマット）がおかれるアドレス */
//#define PLAYER2_ADDR (0x80188000)	/* モーションデータ（MTNフォーマット）がおかれるアドレス */
//#define MODEL2_ADDR	 (0x801b0000)	/* モデリングデータ（TMDフォーマット）がおかれるアドレス */
//#define BGMODEL_ADDR (0x801d8000)	/* モデリングデータ（TMDフォーマット）がおかれるアドレス */
//#define EFMODEL_ADDR (0x801e0000)	/* モデリングデータ（TMDフォーマット）がおかれるアドレス */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CHARACTER NUMBER                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
enum {
	MODEL_JP,	/* ニホンカブトムシ                 */
	MODEL_HR,	/* ヘルクレスオオカブト             */
	MODEL_NP,	/* ネプチューンカブト               */
	MODEL_ST,	/* サタンオオカブト                 */
	MODEL_AT,	/* アトラスオオカブト               */
	MODEL_CO,	/* コーカサスオオカブト             */
	MODEL_BL,	/* ボルネオオオカブト               */
	MODEL_ZO,	/* ゾウカブト                       */
	MODEL_YA,	/* ヤヌスゾウカブト                 */
	MODEL_MA,	/* マルスゾウカブト                 */
	MODEL_AZ,	/* アクテオンゾウカブト             */
	MODEL_AF,	/* アフリカオオカブト               */
	MODEL_GO,	/* ゴホンヅノカブト                 */
	MODEL_SN,	/* サンボンヅノカブト               */
	MODEL_HK,	/* ヒメカブト                       */
	MODEL_NT,	/* ノコギリタテヅノカブト           */
	MODEL_PT,	/* ピサロタテヅノカブト             */
	MODEL_PN,	/* パンカブト(インフンディブルム型) */
	MODEL_P2,	/* パンカブト(ティピカ型)           */
	MODEL_OM,	/* オオツノメンガタカブト           */
	MODEL_HO,	/* オオヒロヅノカブト               */
	MODEL_YM,	/* ユリアヌスミツノカブト           */
	MODEL_AR,	/* アラメヘラヅノカブト             */
	MODEL_TN,	/* テナガコガネ                     */
	MODEL_OT,	/* セラムドウナガテナガコガネ       */
	MODEL_HM,	/* オオゴライアスツノコガネ         */
	MODEL_OS,	/* オオサマゴライアスツノコガネ     */
	MODEL_EM,	/* ヨーロッパミヤマクワガタ         */
	MODEL_MY,	/* ミヤマクワガタ                   */
	MODEL_AO,	/* アッサムオオツノクワガタ         */
	MODEL_AK,	/* アカミトゲシカクワガタ           */
	MODEL_TH, 	/* テイオウホソアカクワガタ         */
	MODEL_O2,	/* オニツヤクワガタ                 */
	MODEL_FA,	/* フチドリアカクワガタ             */
	MODEL_AA,	/* アフリカアカクワガタ             */
	MODEL_KN,	/* オオキバナガクワガタ             */
	MODEL_DH,	/* ダイオウヒラタクワガタ           */
	MODEL_HT,	/* ヒラタクワガタ                   */
	MODEL_OK,	/* オオクワガタ                     */
	MODEL_ON,	/* オオゴンオニクワガタ             */
	MODEL_GR,	/* グラディアトールメンガタクワガタ */
	MODEL_KK,	/* クロツヤクビボソクワガタ         */
	MODEL_NJ,	/* ニジイロクワガタ                 */
	MODEL_TK,	/* チリークワガタ                   */
	MODEL_KR,	/* クロツヤオオツノクワガタ         */
	MODEL_NK,	/* ノコギリクワガタ                 */
	MODEL_KM,	/* オオカマキリ                     */
	MODEL_K2,	/* ハナカマキリ                     */
	MODEL_BE,	/* スズメバチ                       */
	MODEL_KB,	/* スズメバチ                       */
	MODEL_SK,	/* シロスジカミキリ                 */
	MODEL_RB,	/* シロスジカミキリ                 */
	MODEL_TC,	/* タランチュラ                     */
	MODEL_SP,	/* 霊虫                             */
	MODEL_MK,	/* カブト戦車                       */
	MODEL_ME,	/* メカブトン                       */
	MODEL_PC,	/* ワイヤークワガタ                 */
	MODEL_CK,	/* スケルトンカブト                 */
	MODEL_SO,	/* スケルトンオオクワ               */
	MODEL_MAX
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER DATA                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	long	length;
	u_char	reflect;
	task_a	render;
	short	size;
	short	hitpos;
} P_DATA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern long		LocalTimer;

extern int Polygon();
extern void texture_init(u_long addr);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _POLYGON_H_ */
