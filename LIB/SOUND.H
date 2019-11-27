/*ak_sound tools
*----------------------------------------------------------------------------
*/

#ifndef __SOUND_H__
#define __SOUND_H__

#define BGM_UP  		0			/* volume up*/
#define BGM_DOWN		1			/* volume down*/



extern void AK_TEST(void);
extern void AK_BGM(void);
extern void AK_CLOSE(short);
extern void	BGM_VOL_SET(void);
extern void BGM_VOL_0(void);
extern void XA_START(void);/*ポーズしたＸＡを再開する*/
extern int XA_FADE(void);/*XA FADEOUT*/
extern int XA_CNT(void);

/*以上赤沢テスト関数*/

extern void SOUND_I(void);/*サウンド初期化(とSEデータロード)*/

extern void SE_LOAD(short);/*本編用SEデータロード関数*/
/*０で本編用データ、１はタイトルコールデータ*/

extern void SE_ENT(int);
extern void SE_CLR(int);
extern void SE_ALLCLR(void);

extern void BGM_LOAD(int);
extern int BGM_ENT(short);// 返り血は現在の演奏中ＢＧＭNOを返します。
extern void BGM_CLR(short);
extern void BGM_PAUSE(void);
extern void BGM_RENT(short);/*BGMリプレイ*/
extern void BGM_FADE(int,short,long);

extern void DATA_CLOSE(short);/*終了時データクローズ関数*/
/*1で全部クローズ 2でＳＥ 3でＳＥＱをクローズ*/

extern void XA_CLR(void);/*XAクリア*/
extern int XA_LOAD(int);/*ＸＡ再生*/

extern int XA_SYNC(void);/*この関数は毎フレーム呼ぶ*/
// 返り値０：処理中 １：終了

// サウンドデータクローズ後システムを終了します
extern void SOUND_E(void);/*サウンドシステム終了*/
#endif