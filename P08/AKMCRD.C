/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : AUTO LOAD                                                */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : AKMCRD.C                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <kernel.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>
#include <libmcrd.h>
#include <memory.h>
//#include <libmcrd.h>
/*----- User Header     Files -----*/
#include "../lib/libctl.h"
#include "../lib/libfio.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/mainsys.h"
#include "ak_mem.h"/* GO.hより抜粋したアドレスあり変更されたら泣きそう */
//#include "mcapi.h"
#include	"oh_tools.h"
#include "../lib/iSTATIC.h"
#include "../redlib/sound.h"
#include "../redlib/sndno.h"


#define SOUND	1			// loadがいる時は１にする事

/*----------prottype function-------*/
void Tim2Vram(u_long);// イメージの取り込み
void InitSpr(int);// 表示メッセージの初期化
void Init_Yes_No(void);// はいいいえのしょきか
void Init_New_Or_Replay(void);// ロードするか新しく始めるかチェック
void AK_Auto_Load(void);// 起動時のメモリカードチェック
void AK_Mess_Sort(void);// メッセージの表示
void AK_Mess_Sort2(void);// メッセージの表示その２
void AK_Yes_No_Sort(void);// はいいいえの表示
void AK_New_Or_Load_Sort(void);// 新しく始めるかロードするかのソート
void AK_Pnl_Sort(void);// 選択パネルのソート
int _calc_total_blocks( int , struct DIRENTRY* dir );

void AK_Save_StoryMode(void);// 立山さんのところからきた時シナリオセーブ
void AK_Save_Mode_Init_Tim(void);// てきとーしょきか
void AK_Save_Mode_Init_2(void);// カード抜かないでね
void AK_Save_Mode_Init_3(void);// セーブ完了

void AK_MEM_DATA_INIT(int no);// データ初期化 23 or 24

short AK_Select_Load_Or_New(void);// カーソルセレクト ０で上選択１で下選択


/*----------Initialize-------------*/


//static struct DIRENTRY fileList[2][BLOCK_MAX];

// 赤沢構造体
typedef struct{
	unsigned long *pixel;// pixel data
	unsigned long *clut;// clut data
	unsigned long *pix2;
	unsigned long *clt2;
} RED;

static RED AKTEMP;


/* ファイルヘッダ構造体*/
typedef struct {
	char	Magic[2];
	char	Type;
	char	BlockEntry;
	char	Title[64];
	char	reserve[28];
	char	Clut[32];
	char	Icon[3][128];
} _CARD;

static _CARD HEAD;




/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SAVE LOAD                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int AKMCRD()
{
	static short redswitch;
//	FntPrint("SAVE LOAD");
	switch(redswitch){
		case 0:
			if ( *( (unsigned char *)RED_INIT_FLG_ADDR ) == 1 ){// 初期化フラグをみる
				pcb.srst = 0x01;// ソフトリセットが利かなくなる
				redswitch = 1;
			}
			else if ( *( (unsigned char *)RED_INIT_FLG_ADDR ) == 0 ){
				AK_MEM_DATA_INIT(23);// データ初期化
				pcb.srst = 0x01;// ソフトリセットが利かなくなる
				redswitch = 1;
			}
		break;
		case 1:
			if ( pcb.pno == 0x05){// タイトルから来た時対戦モード
				// 対戦用ロード関数(未完成)
				Red_2P_Unit_Load();
			}
			else if ( pcb.pno == 0x04 ) {// 立山さんのところからくる場合。セーブするよ
				AK_Save_StoryMode();
			}
			else{// それ以外は最初のオートロード
				AK_Auto_Load();
				// AK_Save_StoryMode();// チェックの為とりあえず置いてみる
			}
		memcpy( (unsigned char * ) 0x801e0000,( unsigned char *)EVT_FLAG_ADDR,4096);// ソフトリセット対策
		*( (unsigned char *)RED_INIT_FLG_ADDR ) = 1;// 初期化フラグセット

			
		break;
	}
	return ( 0 );
}// オートロードか対戦かチェック


/********************************************************************************
*																				*
*					対戦モードの２Ｐロード関数									*
*					port2固定パッドも２コンで操作します							*
********************************************************************************/
void Red_2P_Unit_Load(){
	static int aiload = AI_INIT;// ロード関数の流れ、初期化
	static int aitime;// 表示用タイマー
	static int ailoop = 0;
	long chan = 0x10;// 2P port
	long rslt,cmds;
	
	switch ( aiload ){
		case AI_INIT:// tim読み込み等

			while (ailoop < TIM_MAX_NUM){
				FioDivReadFile("DT\\AK.T",(unsigned char *)TIM_LOAD_ADDR,TIM_TBL[ailoop].ST,TIM_TBL[ailoop].SI);
				Tim2Vram(TIM_LOAD_ADDR);
				ailoop++;
			}// while last

			aiload = AI_START_PRN;

		break;
		case AI_START_PRN:// 準備ができたら○を押す

			// スプライトの初期化
			InitSpr(AI_START_PRN);// どうせ○押すだけだから、ここに戻せば楽だし

			if( PadDat[0].trg & PADRR ){// ○を押した
				SE_ENT(SE_OK1);
				aiload = AI_CARD_CHECK;
			}

		break;
		case AI_CARD_CHECK:// カードチェック

			switch ( MemCardSync(1,&cmds,&rslt) ){
				case -1:// 登録処理無し
					/* カードの接続テスト*/
					MemCardExist(chan);
				break;
				case 0:// 登録処理実行中
				break;
				case 1:// 登録処理終了
					switch (cmds){
						case McFuncExist:// の関数が終了
							switch(rslt) {
								case McErrNone:// 問題なし
									aiload = AI_FILE_OPEN;// file open してチェック
								break;
								case McErrNewCard:	/* 新規カード検出*/
									MemCardAccept( chan );	/* さらに詳細な情報を取得*/
								break;
								/* カードなし他*/
								case McErrCardNotExist:// カード無し
									aitime = 0;// タイマー初期化
									InitSpr(AI_CARD_NO);// 刺さってないよめっせーじ
									aiload = AI_CARD_NO;// カード無いよ表示
								break;
								case McErrCardInvalid:// カード壊れ
									aitime = 0;// タイマー初期化
									InitSpr(AI_NO_DATA);
									// 壊れでもデータありませんでしたを出す
									aiload = AI_NO_DATA;
								break;
							}
						break;
						case McFuncAccept:// の関数が終了
							switch(rslt){
								case McErrNone:// 接続されている
									aiload = AI_FILE_OPEN;// file open してチェック
								break;
								case McErrCardNotExist:// 接続されていない
									aitime = 0;// タイマー初期化
									InitSpr(AI_CARD_NO);// 刺さってないよめっせーじ
									aiload = AI_CARD_NO;// カード無いよ表示
								break;
								case McErrCardInvalid:// 不良カード
									aitime = 0;// タイマー初期化
									InitSpr(AI_NO_DATA);
									// 壊れてるとは表示できないソニーのやろう！
									aiload = AI_NO_DATA;
								break;
								case McErrNewCard:// 新規カード（カードが交換された）
									MemCardAccept( chan );	/* リトライ*/
								break;
								case McErrNotFormat:// フォーマットされていない
									aitime = 0;// タイマー初期化
									InitSpr(AI_NO_DATA);
									aiload = AI_NO_DATA;
								break;
							}// switch last
						break;
					}// switch last
				break;
			}// switch last




		break;
// AI_CARD_CHECH ここまで
		case AI_FILE_OPEN:// データあるかチェック

			switch ( MemCardOpen(chan,"BISLPS-01779",O_RDONLY) ){
				case McErrNone:// 正常終了
				// ファイルがある
					aiload = AI_DATA_LOAD;// 実際にデータロード
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 不良カード
				case McErrNotFormat:// フォーマットされていない
				case McErrFileNotExist:// ファイルが見つからない
				case -1:// 既に他のファイルがオープンされいるか、非同期関数がバックグラウンドで動作中である。
					// データが無いと表示
					aitime = 0;
					InitSpr(AI_NO_DATA);
					aiload = AI_NO_DATA;
				break;
			}// switch last
			

		break;
		case AI_DATA_LOAD:// データロード

		switch ( MemCardSync(1,&cmds,&rslt) ){
			case -1:// 登録処理無し
				/* カードの接続テスト*/
				MemCardReadData((unsigned long * )MEMCARD_LOAD_ADDR_2P,4096,4096);
			break;
			case 0:// 登録処理実行中
				aitime = 0;// 表示用カウンター初期化してみるー
			break;
			case 1:// 登録処理終了
				switch (cmds){
					case McFuncReadData:// の関数が終了
						switch(rslt) {
							case McErrNone:// 正常終了
								aiload = AI_UNIT_SELECT;// 終了処理して戻す
							break;
							case McErrCardNotExist:// カードが接続されていない
							case McErrCardInvalid:// 通信エラー発生
							case McErrNewCard:// 新規カード（カードが交換された）
							case McErrFileNotExist:// ファイルが見つからない
								// ロードに失敗しましたメッセージ表示
								aitime = 0;
								InitSpr(AI_LOAD_MISS);// メッセージ初期化
								aiload = AI_LOAD_MISS;
							break;
						}
				}
		}

		break;
		case AI_LOAD_MISS:// ロードミス

			aitime ++;
			if (aitime > PRINTTIME){// 時間がきたら元に戻る
				MemCardClose();// 一応閉じておく
				aiload = AI_START_PRN;
			}

		break;
		case AI_NO_DATA:// データが無い

			aitime ++;
			if (aitime > PRINTTIME){// 時間がきたら元に戻る
				MemCardClose();// 一応閉じておく
				aiload = AI_START_PRN;
			}

		break;
		case AI_CARD_NO:// カード刺さってない

			aitime ++;
			if (aitime > PRINTTIME){// 時間がきたら元に戻る
				MemCardClose();// 一応閉じておく
				aiload = AI_START_PRN;
			}

		break;
		case AI_CARD_NUKI:// カード抜かれた

			aitime ++;
			if (aitime > PRINTTIME){// 時間がきたら元に戻る
				MemCardClose();// 一応閉じておく
				aiload = AI_START_PRN;
			}

		break;
		case AI_UNIT_SELECT:// ロード成功したら終了処理して抜ける

			aitime = 0;// とりあえず初期化しておく
			MemCardClose();// きちんと閉じておく

			// 戻し場所判らず･･･


		break;
	}// switch last

AK_Mess_Sort();// メッセージの表示

}// 対戦モードロード関数おしまい


/********************************************************************************
*																				*
*					ストーリーモードのセーブ関数								*
*																				*
********************************************************************************/

void AK_Save_StoryMode(){
	static int gosave = SYSINIT;// セーブプロセス 初期化する
	static int gotime;// 表示用タイマー
	static int akloop = 0;
	long chan = 0x00;// 1P port
	long rslt;
	long cmds;
	switch(gosave){
		case SYSINIT:
#if (SOUND)// 多分要らないであろう。
//			SOUND_I();
//			SE_LOAD(0);
#endif
			*( (unsigned char *)RED_INIT_FLG_ADDR ) = 1;// 初期化フラグセット

			while (akloop < TIM_MAX_NUM){
				FioDivReadFile("DT\\AK.T",(unsigned char *)TIM_LOAD_ADDR,TIM_TBL[akloop].ST,TIM_TBL[akloop].SI);
				Tim2Vram(TIM_LOAD_ADDR);
				akloop++;
			}// while last

			// AK_Save_Mode_Init_Tim();
			InitSpr(SAVEFILE);
			Init_Yes_No();// はいいいえのしょきか
			gosave = SAVEFILE;
		break;
		case SAVEFILE:
			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				pcb.req = 0x04;// 清算画面へ戻ると思う。
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
				gosave = MCCHECK;
			}

//			AK_Mess_Sort();// メッセージの表示
			AK_Yes_No_Sort();// はいいいえの表示
			AK_Pnl_Sort();// 選択パネルのソート
			
		break;
		case MCCHECK:// カードチェック


			switch ( MemCardSync(1,&cmds,&rslt) ){
				case -1:// 登録処理無し
					/* カードの接続テスト*/
					MemCardExist(chan);
				break;
				case 0:// 登録処理実行中
				break;
				case 1:// 登録処理終了
					switch (cmds){
						case McFuncExist:// の関数が終了
							switch(rslt) {
								case McErrNone:// 問題なし
									gosave = SAVE_FILE_CHECK;// file open してチェック
								break;
								case McErrNewCard:	/* 新規カード検出*/
									MemCardAccept( chan );	/* さらに詳細な情報を取得*/
								break;
								/* カードなし他*/
								case McErrCardNotExist:// カード無し
									gotime = 0;
									InitSpr(CARD_NO);// 刺さってないよめっせーじ
									gosave = CARD_NOTHING;// カード無いよ表示
								break;
								case McErrCardInvalid:// カード壊れ
									gotime = 0;// タイマー初期化
									InitSpr(SAVEMISS);
									gosave = SAVEMISS;// 壊れでもセーブできませんでしたを出す。
								break;
							}
						break;
						case McFuncAccept:// の関数が終了
							switch(rslt){
								case McErrNone:// 接続されている
									gosave = SAVE_FILE_CHECK;// file open してチェック
								break;
								case McErrCardNotExist:// 接続されていない
									gotime = 0;
									InitSpr(CARD_NO);// 刺さってないよめっせーじ
									gosave = CARD_NOTHING;// カード無いよ表示
								break;
								case McErrCardInvalid:// 不良カード
									gotime = 0;
									InitSpr(SAVEMISS);
									gosave = SAVEMISS;// 壊れてるとは表示できないソニーのやろう！
								break;
								case McErrNewCard:// 新規カード（カードが交換された）
									MemCardAccept( chan );	/* リトライ*/
								break;
								case McErrNotFormat:// フォーマットされていない
									// メッセージ初期化
									InitSpr(FORMATOK);
									Init_Yes_No();// はいいいえのしょきか
									gosave = FORMATOK;// フォーマット確認
								break;
							}// switch last
						break;
					}// switch last
				break;
			}// switch last
		
		
		
			// AK_Save_Mode_Init_2();// カード抜かないでね
		break;
		case FORMATOK:// フォーマット確認
		// フォーマットするかしないかチェックする
			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
				gosave = RUNFORMAT;// 実際にフォーマット
			}

		AK_Yes_No_Sort();// はいいいえの表示
		AK_Pnl_Sort();// 選択パネルのソート
			
		break;
		case RUNFORMAT:// 実際にフォーマット
			switch ( MemCardFormat( chan ) ){
				case McErrNone:// 正常終了
					InitSpr(CREATE_FILE);
					gosave = CREATE_FILE;// 実際にセーブ
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 通信エラー発生
				case -1:// 非同期関数が動作中
					// オートロードの時の表示を使いまわし
					gotime = 0;// タイマー初期化
					InitSpr(UNFORMAT);
					Init_Yes_No();// はいいいえのしょきか
					gosave = FORMATMISS;
				break;
			}// switch last
		break;
		case FORMATMISS:// フォーマットエラー
			gotime ++;
			if ( gotime > PRINTTIME ){// 元に戻る
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
		break;
		case SAVE_FILE_CHECK:// データあるかチェック
		// 実際にファイルオープンする
			switch ( MemCardOpen(chan,"BISLPS-01779",O_WRONLY) ){
				case McErrNone:// 正常終了
				// ファイルがある
				// 上書き確認
					InitSpr(OVER_WRITE_CHECK);
					Init_Yes_No();// はいいいえのしょきか
					gosave = OVER_WRITE_CHECK;
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 不良カード
				case McErrNotFormat:// フォーマットされていない
				case -1:// 既に他のファイルがオープンされいるか、非同期関数がバックグラウンドで動作中である。
					// セーブ失敗を表示
					gotime = 0;
					InitSpr(SAVEMISS);
					gosave = SAVEMISS;
				break;
				case McErrFileNotExist:// ファイルが見つからない
					// 空き容量チェック
					gosave = CARD_SPACE_CHECK;
				break;
			}// switch last
		break;
		case OVER_WRITE_CHECK:// 上書き確認
		// カーソル選択
			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
				InitSpr(CREATE_FILE);
				gosave = CREATE_FILE;// 実際に作成
			}

		AK_Yes_No_Sort();// はいいいえの表示
		AK_Pnl_Sort();// 選択パネルのソート
			
		break;
		case CARD_SPACE_CHECK:// 空き容量チェック
			// FileCreate使用
			switch ( MemCardCreateFile(chan,"BISLPS-01779",MEM_BLOCK) ){
				case McErrNone:// 正常終了
					InitSpr(CREATE_FILE);
					gosave = CREATE_FILE;
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 通信エラー発生
				case McErrNotFormat:// フォーマットされていない
				case -1:// 非同期関数が動作中
					// セーブ失敗を表示
					gotime = 0;
					InitSpr(SAVEMISS);
					gosave = SAVEMISS;
				break;
				case McErrAlreadyExist:// 既にファイルが存在する
				// 上書き確認
					InitSpr(OVER_WRITE_CHECK);
					Init_Yes_No();// はいいいえのしょきか
					gosave = OVER_WRITE_CHECK;
				break;
				case McErrBlockFull:// 空きブロックが足りない
					gotime = 0;// タイマー初期化
					InitSpr(SPACECHECK);
					gosave = NO_SPACE;
				break;
			}// switch last
		break;
		case NO_SPACE:// 空き容量無し
			gotime ++;
			if ( gotime > PRINTTIME ){
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
		break;
		case CREATE_FILE:// 実際にセーブ
		// どうせメモリー上から直接取るので一回削除する
			switch ( MemCardDeleteFile(chan, "BISLPS-01779") ){// 既存ファイルを削除
				case McErrNone:// 正常終了
					// 消した後、新規作成する。
					switch ( MemCardCreateFile( chan, "BISLPS-01779" , MEM_BLOCK) ){
						case McErrNone:// 正常終了
							gosave = HEADCREATE;// 先ずヘッダ作成
						break;
						case McErrCardNotExist:// カードが接続されていない
						case McErrCardInvalid:// 通信エラー発生
						case McErrNotFormat:// フォーマットされていない
						case McErrAlreadyExist:// 既にファイルが存在する
						case McErrBlockFull:// 空きブロックが足りない
						case -1:// 非同期関数が動作中
							gotime = 0;
							InitSpr(SAVEMISS);
							gosave = SAVEMISS;
						break;
					}// 新規作成のスイッチ文
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 通信エラー発生
				case McErrNotFormat:// フォーマットされていない
				case McErrFileNotExist:// ファイルが見つからない
				case -1:// 非同期関数が動作中
					gotime = 0;
					InitSpr(SAVEMISS);
					gosave = SAVEMISS;// 多分こうするべきだと思う
				break;
			}// switch last
			
		break;
		case HEADCREATE:// 先ずヘッダ作成
			// ヘッダ書き込み
			/* ファイルヘッダの準備*/
			HEAD.Magic[0] = 'S';
			HEAD.Magic[1] = 'C';
			HEAD.Type = 0x12;
			HEAD.BlockEntry = 1;
			strcpy( HEAD.Title, "バトル昆虫伝" );
			memcpy( HEAD.Clut, AKTEMP.clut, 32 );
		//	memcpy( HEAD.Icon[0], AKTEMP.pix2, 128);
			memcpy( HEAD.Icon[0], AKTEMP.pixel, 128);
			memcpy( HEAD.Icon[1], AKTEMP.pixel, 128);

			/* ファイル作成*/
			MemCardWriteFile( chan, "BISLPS-01779", (long*)&HEAD, 0, sizeof(HEAD) );
			/* 終了待ち*/
			MemCardSync(0,0,&rslt);
// ここまででヘッダが出来ました。
			MemCardClose();
			gosave = FILEOPEN;
		break;
		case FILEOPEN:

			/* ファイルオープン*/
			switch ( MemCardOpen( chan, "BISLPS-01779" , O_WRONLY) ){
				case McErrNone:// 正常終了
					gosave = NOWSAVING;// 実際にセーブ
				break;
				case McErrCardNotExist:// カードが接続されていない
				case McErrCardInvalid:// 不良カード
				case McErrNotFormat:// フォーマットされていない
				case McErrFileNotExist:// ファイルが見つからない
				case -1:// 他の関数実行中
					gotime = 0;
					InitSpr(SAVEMISS);
					gosave = SAVEMISS;
				break;
			}// switch last
			
		break;
		case NOWSAVING:// 実際にセーブ
		switch ( MemCardSync(1,&cmds,&rslt) ){
			case -1:// 登録処理無し
				/* ファイル作成*/
				MemCardWriteData( (long*)EVT_FLAG_ADDR, SAVEOFFSET, SAVEBYTES );
			break;
			case 0:// 登録処理実行中
			break;
			case 1:// 登録処理終了
				switch (cmds){
					case McFuncWriteData:// の関数が終了
						switch(rslt) {
							case McErrNone:// 正常終了
								gotime = 0;// タイマー初期化
								InitSpr(GO_SEISAN);
								gosave = GO_SEISAN;// 成功したので清算画面へ
							break;
							case McErrCardNotExist:// カードが接続されていない
							case McErrCardInvalid:// 通信エラー発生
							case McErrNewCard:// 新規カード（カードが交換された)
								gotime = 0;
								InitSpr(SAVEMISS);
								gosave = SAVEMISS;// エラーメッセージ
							break;
						}
					break;
					default:// その他
					break;
				}
		}
		
		
		
		break;
		case SAVEMISS:// セーブ失敗
		// カード壊れとか失敗とかで表示します
			gotime ++;
			if ( gotime > PRINTTIME ){
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
		break;
		case GO_SEISAN:// 清算画面へ戻る
			MemCardClose();
			gotime ++;
			if( gotime > PRINTTIME ){
				memcpy( (unsigned char * ) 0x801e0000,( unsigned char *)EVT_FLAG_ADDR,4096);// ソフトリセット対策
				*( (unsigned char *)RED_INIT_FLG_ADDR ) = 1;// 初期化フラグセット
				pcb.srst = 0x00;// ソフトリセット利く
				pcb.req = 0x04;// 清算画面へ戻る
			}
		break;
		case CARD_NOTHING:// カード無いよ表示
			InitSpr(CARD_NO);// メッセージは２種類あります。
			AK_Mess_Sort2();// スロット１にメモカ刺してください。
			// 刺さっていませんは自動的に出ます
			gotime ++;
			if ( gotime > PRINTTIME ){
				InitSpr(SAVEFILE);
				Init_Yes_No();// はいいいえのしょきか
				MemCardClose();
				gosave = SAVEFILE;
			}
		break;
	}// switch last


AK_Mess_Sort();// 何かは必ず表示しておく

// 今後は背景もくるらしい

}// AK_Save_StoryMode last


/********************************************************************************
*																				*
*					起動時のオートロード関数									*
*																				*
********************************************************************************/


void AK_Auto_Load(){
	static unsigned long aktime;
	static int sltest = INITSYS;// 一応０だけどきちんと初期化しておく
	static short	akloop;
//	int Redselect;// はいいいえとか選択用
	long rslt = 0;// メモカチェック用
	long chan = 0;
	long cmds = 0;
//	long files[2];
	chan = 0x00;
	
	aktime ++;
	FntPrint("\nTIME : %d\n",aktime);

switch (sltest){
	case INITSYS:
#if (SOUND)
			SOUND_I();
			SE_LOAD(0);
#endif


		while (akloop < TIM_MAX_NUM){// 今は９個
			FioDivReadFile("DT\\AK.T",(unsigned char *)TIM_LOAD_ADDR,TIM_TBL[akloop].ST,TIM_TBL[akloop].SI);
			Tim2Vram(TIM_LOAD_ADDR);
			akloop++;
		}// while last
		if(akloop >= TIM_MAX_NUM){// tim全部読み込んだら次へ
			/* メモリーカードシステム初期化 */
			// 秋山さんのところでやってある
			sltest = CARDCHECK;
		}// if last
#if 0
		if(akloop == 8){// richard.tim
			AKTEMP.pix2 = AKTEMP.pixel;
			AKTEMP.clt2 = AKTEMP.clut;
		}
#endif
		
	break;
	case CARDCHECK:// 刺さってるかチェック
			FntPrint("\nCHECK START\n");

	switch ( MemCardSync(1,&cmds,&rslt) ){
		case -1:// 登録処理無し
			/* カードの接続テスト*/
			MemCardExist(chan);
		break;
		case 0:// 登録処理実行中
		break;
		case 1:// 登録処理終了
			switch (cmds){
				case McFuncExist:// の関数が終了
					switch(rslt) {
						case McErrNone:// 問題なし
							sltest = DATACHECK;
						break;
						case McErrNewCard:	/* 新規カード検出*/
							MemCardAccept( chan );	/* さらに詳細な情報を取得*/
		//					MemCardExist(chan);// Acceptはどうせ新規制作時にやるから良い
							// と思ったら、Existのままだと新規カードが毎回通知されて抜けられない。
						break;
						/* カードなし他*/
						case McErrCardNotExist:// カード無し
							Init_New_Or_Replay();// ロードするか新しく始めるかチェック
							InitSpr(NOCARD);
							sltest = NOCARD;
					//		FntPrint("\nNO CARD\n");
						break;
						case McErrCardInvalid:// カード壊れ
							InitSpr(BREAK_DATA);
							sltest = BREAK_DATA;
						break;
					}
				break;
				case McFuncAccept:// の関数が終了
					switch(rslt){
						case McErrNone:// 接続されている
							sltest = DATACHECK;
						break;
						case McErrCardNotExist:// 接続されていない
							Init_New_Or_Replay();// ロードするか新しく始めるかチェック
							InitSpr(NOCARD);
							sltest = NOCARD;
						break;
						case McErrCardInvalid:// 不良カード
							aktime = 0;// 画面表示タイマー初期化
							InitSpr(BREAK_DATA);
							sltest = BREAK_DATA;
						break;
						case McErrNewCard:// 新規カード（カードが交換された）
							MemCardAccept( chan );	/* リトライ*/
						break;
						case McErrNotFormat:// フォーマットされていない
							Init_New_Or_Replay();// ロードするか新しく始めるかチェック
							InitSpr(NOCARD);
							sltest = NOCARD;
						break;
					}// switch last
				break;
				default:
				break;
			}// switch last
		
		
		
		
		
		break;
	}// switch last




	
	break;
	case NOCARD:// カード無い時
		// ロードするか新規ゲームか選ぶ

			if ( PadDat[0].trg & PADLU ){// 上 ロードを選択
				SE_ENT(SE_CUR1);
				AK_LOAD_OK.cy = 511;// 選択カラー
				AK_NEW_GAME.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 新しく始めるを選択
				SE_ENT(SE_CUR1);
				AK_LOAD_OK.cy = 510;
				AK_NEW_GAME.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_LOAD_OK.cy == 511)&&(PadDat[0].trg & PADRR) ){// ロードするで決定
				SE_ENT(SE_OK1);
				sltest = CARDCHECK;// カードチェックへ戻る
			}
			else if( (AK_NEW_GAME.cy == 511)&&(PadDat[0].trg & PADRR) ){// 新規開始で決定
				SE_ENT(SE_OK1);
				InitSpr(NODATA);// ソートの前に初期化
				Init_Yes_No();// はいいいえのしょきか
				sltest = NODATA;// 新規ファイル作成するかを選ぶ
			}

//			AK_Mess_Sort();
			AK_Pnl_Sort();// 選択パネルのソート
			AK_New_Or_Load_Sort();// 新しく始めるかロードするかのソート
			
	break;
	case DATACHECK:// データがあるかチェック
	//	MemCardGetDirentry( chan, "*", fileList, &files, 0, BLOCK_MAX );
	//	sltest = GOTITLE;

		switch ( MemCardOpen( chan , "BISLPS-01779" , O_RDONLY ) ){
			case McErrNone:// 正常終了
				// ファイルがあるよ
				aktime = 0;// 初期化してみる
				sltest = DATALOAD;
			break;
			case McErrCardNotExist:// カードが接続されていない
				// 表示初期化
				Init_New_Or_Replay();// ロードするか新しく始めるかチェック
				InitSpr(NOCARD);
				sltest = NOCARD;// カード刺してねメッセージ表示
			break;
			case McErrCardInvalid:// 不良カード
				aktime = 0;// 画面表示タイマー初期化
				InitSpr(BREAK_DATA);
				sltest = BREAK_DATA;
			break;
			case McErrNotFormat:// フォーマットされていない
								// データが無いとみなす
			case McErrFileNotExist:// ファイルが見つからない
				InitSpr(NODATA);// ソートの前に初期化
				Init_Yes_No();// はいいいえのしょきか
				sltest = NODATA;// 新規ファイル作成するかを選ぶ
			break;
			case -1:
				Init_New_Or_Replay();// ロードするか新しく始めるかチェック
				InitSpr(NOCARD);
				sltest = NOCARD;// カード刺してねメッセージ表示
			break;
		}// switch last

//			FntPrint("\nCARD OK\n");
//			printf("CARD OK\n");
	break;
	case NODATA:// データ無い時
		// セーブファイルを作るかどうかを選択させる
			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				sltest = GOTITLE;// タイトルへ
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
				sltest = NEWGAME;// 新規ファイル作成へ
			}

#if 0
// うまく行くと見た目がちょっと良い
Redselect = AK_Select_YorN();

if( (Redselect == 1)&&(PadDat[0].trg & PADRR) ){// ok
	sltest = GOTITLE;// タイトルへ
}
else if( (Redselect == 2)&&(PadDat[0].trg & PADRR) ){// no
	sltest = NEWGAME;// 新規ファイル作成
}
#endif

			
//			AK_Mess_Sort();
			AK_Yes_No_Sort();// はいいいえの表示
			AK_Pnl_Sort();// 選択パネルのソート
			
	break;
	case DATABREAKCHECK:// データ壊れてるかチェック
	break;
	case BREAK_DATA:// データ壊れちゃってる
//			AK_Mess_Sort();
	// この後タイトルへ移動
		aktime ++;
		if (aktime > PRINTTIME ){// 1秒表示後タイトルへ
			sltest = GOTITLE;
		}
	break;
	case DATALOAD:// データロード
	//sltest = GOTITLE;// タイトルへ
		// ロードしましょう
		switch ( MemCardSync(1,&cmds,&rslt) ){
			case -1:// 登録処理無し
				/* カードの接続テスト*/
				MemCardReadData((unsigned long * )EVT_FLAG_ADDR,4096,4096);
			break;
			case 0:// 登録処理実行中
				aktime = 0;// 表示用カウンター初期化してみるー
			break;
			case 1:// 登録処理終了
				switch (cmds){
					case McFuncReadData:// の関数が終了
						switch(rslt) {
							case McErrNone:// 正常終了
// ロードした場合のみ初期化フラグセット
								*( (unsigned char *)RED_INIT_FLG_ADDR ) = 1;// 初期化フラグセット
								sltest = GOTITLE;// タイトルへゴー
							break;
							case McErrCardNotExist:// カードが接続されていない
							case McErrCardInvalid:// 通信エラー発生
							case McErrNewCard:// 新規カード（カードが交換された）
							case McErrFileNotExist:// ファイルが見つからない
								// ロードに失敗しましたメッセージ表示
								InitSpr(LOADMISS);
//								AK_Mess_Sort();
								aktime ++;
								if (aktime > PRINTTIME-60 ){
									Init_New_Or_Replay();// カード無いから刺してねメッセージ
									InitSpr(NOCARD);
									sltest = NOCARD;
								}
							break;
							default:// 突貫工事
								// 何やらせんだよまったくよ。もうやってられないっすよ。
							break;
						}
				}
		}
		
	break;
	case LOADCHECK:// ロード成功したかな？
	break;
	case LOADMISS:// ロード失敗
		aktime ++;
		if ( aktime > PRINTTIME ){
			
		}
	break;
	case GOTITLE:// ロード成功したらタイトルへ
		MemCardClose();// ファイルクローズ
//		MemCardStop();// メモリーカードシステムの停止
//		MemCardEnd();// メモリーカードシステムの終了
//		多分ストップとエンドはゲームを完全に抜ける時だけで良さそう

		*( (unsigned char *)RED_INIT_FLG_ADDR ) = 1;// 初期化フラグセット


		// 日付チェックします


		pcb.req = 0x05;// タイトルへゴー
		pcb.srst = 0x00;// ソフトリセット利く
		
	break;
// 以後新規作成手順
	case NEWGAME:// NODATAから分岐。初めてゲームをします
		sltest = CHECK_CARD;// めもかー刺さりチェックへ
	break;
	case CREATEFILE:// ファイル作るよ
	break;
	case CHECK_CARD:// 作成開始してからのメモカ刺さってるかチェック
		// やり方を考えないと、また失敗するーーーーーーーー
		// いきなりファイルクリエイトに行った方が楽
		// はいいいえはここで初期化

		switch ( MemCardCreateFile( chan,"BISLPS-01779",MEM_BLOCK) ){
			case McErrNone:// 正常終了
				// この後実際にファイル書き込み
				aktime = 0;// 表示用タイマー初期化
				sltest = FILE_CREATE;
			break;
			case McErrCardNotExist:// カードが接続されていない
				aktime = 0;// 表示用タイマー初期化
				sltest = CARD_NO;
			break;
			case McErrCardInvalid:// 通信エラー発生
				sltest = CREATEERROR;
			break;
			case McErrNotFormat:// フォーマットされていない
				InitSpr(UNFORMAT);
				Init_Yes_No();// はいいいえのしょきか
				sltest = UNFORMAT;
			break;
			case McErrAlreadyExist:// 既にファイルが存在する( 上書き ）
				InitSpr(OVERWRITE);
				Init_Yes_No();// はいいいえのしょきか
				sltest = OVERWRITE;
			break;
			case McErrBlockFull:// 空きブロックが足りない
				aktime = 0;// 表示タイマー初期化
				InitSpr(SPACECHECK);
				sltest = SPACECHECK;
			break;
		}// switch last


	break;
	case CARD_NO:// 刺さっていません
		InitSpr(CARD_NO);// メッセージは２種類あります。
		
		AK_Mess_Sort2();// スロット１にメモカ刺してください。
		// 刺さっていませんはデフォで出ます。
//		AK_Mess_Sort();
		
		if(aktime>PRINTTIME){// この前の部分でタイマーはクリアされています
			InitSpr(NODATA);// ソートの前に初期化
			Init_Yes_No();// はいいいえのしょきか
			sltest = NODATA;
		}
	break;
	case FORMATCHECK:// フォーマットされてるかチェック
	// MemCardCreateFile();で可能なので未使用
	break;
	case UNFORMAT:// フォーマットされていないよ！フォーマットする？？？

			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				InitSpr(NODATA);
				Init_Yes_No();// はいいいえ初期化
				sltest = NODATA;
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
				sltest = CHECK_FORMAT;// フォーマット実行
			}

//		AK_Mess_Sort();
		AK_Pnl_Sort();// 選択パネルのソート
		// はいいいえが必要
		// いいえでNODATAまで戻る
		AK_Yes_No_Sort();// はいいいえの表示
		
	break;
	case CHECK_FORMAT:// フォーマットは成功したかな？
		// 失敗ならミスメッセージを表示してUNFORMATへ戻る
		// 実際のフォーマット処理
		switch ( MemCardFormat(chan) ){
			case McErrNone:// 正常終了
				sltest = FILE_CREATE;// ファイル作成へ
			break;
			case McErrCardNotExist:// カードが接続されていない
			case McErrCardInvalid:// 通信エラー発生
			case -1:// 非同期関数が動作中
			// フォーマット失敗を表示
				InitSpr(UNFORMAT);
				Init_Yes_No();// はいいいえのしょきか
				sltest = UNFORMAT;
			break;
		}// switch last
	break;
	case SPACECHECK:// 空き容量チェック
		aktime ++;
		// タイマーで表示後ファイル作成まで戻す
		if(aktime > PRINTTIME){
		InitSpr(NODATA);// ソートの前に初期化
		Init_Yes_No();// はいいいえのしょきか
		sltest = NODATA;// 新規ファイル作成するかを選ぶ
		}
	break;
	case CHECK_DATA:// 虫のデータがあるかな？
		// 未使用
	break;
	case OVERWRITE:// データがあった時は上書き確認

			if ( PadDat[0].trg & PADLU ){// 上 はいを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 511;// 選択カラー
				AK_NO.cy = 510;
			}
			else if ( PadDat[0].trg & PADLD ){// 下 いいえを選択
				SE_ENT(SE_CUR1);
				AK_YES.cy = 510;
				AK_NO.cy = 511;// 選択カラー
			}// else if last

			else if( (AK_NO.cy == 511)&&(PadDat[0].trg & PADRR) ){// いいえで決定
				SE_ENT(SE_OK1);
				InitSpr(NOCARD);
				Init_Yes_No();// はいいいえ初期化
				sltest = NOCARD;
			}
			else if( (AK_YES.cy == 511)&&(PadDat[0].trg & PADRR) ){// はいで決定
				SE_ENT(SE_OK1);
//				MemCardDeleteFile(chan, "BISLPS-01779");// 既存ファイルを削除
				aktime = 0;
				sltest = FILE_CREATE;
			}
		


//		AK_Mess_Sort();
		AK_Pnl_Sort();// 選択パネルのソート
		AK_Yes_No_Sort();// はいいいえの表示
	break;
	case FILE_CREATE:// 作成中メッセージと実際の作成
	// ヘッダ書き込み
	/* ファイルヘッダの準備*/
	HEAD.Magic[0] = 'S';
	HEAD.Magic[1] = 'C';
	HEAD.Type = 0x12;
	HEAD.BlockEntry = 1;
	strcpy( HEAD.Title, "バトル昆虫伝" );
	memcpy( HEAD.Clut, AKTEMP.clut, 32 );
//	memcpy( HEAD.Icon[0], AKTEMP.pix2, 128);
	memcpy( HEAD.Icon[0], AKTEMP.pixel, 128);
	memcpy( HEAD.Icon[1], AKTEMP.pixel, 128);



	/* ファイル作成*/
	MemCardWriteFile( chan, "BISLPS-01779", (long*)&HEAD, 0, sizeof(HEAD) );
	/* 終了待ち*/
	MemCardSync(0,0,&rslt);



	AK_MEM_DATA_INIT(23);// データ初期化。新規ファイルなので


	/* ファイルオープン*/
	switch ( MemCardOpen( chan, "BISLPS-01779" , O_WRONLY) ){
		case McErrNone:// 正常終了
			sltest = CREATE_CHECK;
		break;
		case McErrCardNotExist:// カードが接続されていない
		case McErrCardInvalid:// 不良カード
		case McErrNotFormat:// フォーマットされていない
		case McErrFileNotExist:// ファイルが見つからない
		case -1:// 他の関数実行中
			aktime = 0;// 表示タイマー初期化
			sltest = CREATEERROR;// 作成ミスメッセージ表示へ
		break;
	}// switch last


		InitSpr(FILE_CREATE);
//		AK_Mess_Sort();
		// カウンターで表示をきるか、ずっと表示させとく。
		aktime ++;
		if (aktime > TIM_PRINT * 2){// タイマーで表示時間決定
		sltest = GOTITLE;
		}
	break;
	case CREATEERROR:// セーブファイル作成ミス
		InitSpr(CREATEERROR);
		
		aktime ++;
		if( ( aktime > PRINTTIME )&&( PadDat[0].trg & PADRR ) ){
			InitSpr(NODATA);// ソートの前に初期化
			Init_Yes_No();// はいいいえのしょきか
			sltest = NODATA;// 新規ファイル作成するかを選ぶ
		}

	break;
	case CREATE_CHECK:// 作成チェックの分岐OKならタイトルへnoならNEWGAMEへ
		switch ( MemCardSync(1,&cmds,&rslt) ){
			case -1:// 登録処理無し
				/* ファイル作成*/
				MemCardWriteData( (long*)EVT_FLAG_ADDR, SAVEOFFSET, SAVEBYTES );
			break;
			case 0:// 登録処理実行中
			break;
			case 1:// 登録処理終了
				switch (cmds){
					case McFuncWriteData:// の関数が終了
						switch(rslt) {
							case McErrNone:// 正常終了
								sltest = GOTITLE;// タイトルへ
							break;
							case McErrCardNotExist:// カードが接続されていない
							case McErrCardInvalid:// 通信エラー発生
							case McErrNewCard:// 新規カード（カードが交換された)
								sltest = CREATEERROR;// エラーメッセージ
							break;
						}
					break;
					default:// その他
					break;
				}
		}
	break;
}// switch last


AK_Mess_Sort();// 何かは必ず表示しておく
// 今後は背景もはいる予定

//   return( 0 );
}



/************************************************************************************
*																					*
*				スプライト初期化とかデータ初期化とか								*
*																					*
*																					*
************************************************************************************/





/*--------------------------------
テクスチャを貼る
--------------------------------*/
void Tim2Vram(u_long addr){
  RECT rect1;
  GsIMAGE tim1;
  
  GsGetTimInfo((u_long *)(addr+4),&tim1);
  rect1.x=tim1.px;
  rect1.y=tim1.py;
  rect1.w=tim1.pw;
  rect1.h=tim1.ph;
  LoadImage(&rect1,tim1.pixel);
  if((tim1.pmode>>3)&0x01)	/* if clut exist */
    {
      rect1.x=tim1.cx;
      rect1.y=tim1.cy;
      rect1.w=tim1.cw;
      rect1.h=tim1.ch;
      LoadImage(&rect1,tim1.clut);
    }
    AKTEMP.pixel = tim1.pixel;
    AKTEMP.clut = tim1.clut;
}// Tim2Vram last

void AK_Mess_Sort(void){// メッセージの表示
		GsSortFastSprite(&AK_Font[0],&ot[ PSDIDX ],0);// メッセージのみ表示
}// function last
void AK_Mess_Sort2(void){// メッセージの表示その２
		GsSortFastSprite(&AK_Font[1],&ot[ PSDIDX ],0);// メッセージのみ表示
}

void AK_Yes_No_Sort(void){// はいいいえの表示
		GsSortFastSprite(&AK_YES,&ot[ PSDIDX ],0);// はい
		GsSortFastSprite(&AK_NO,&ot[ PSDIDX ],0);// いいえ
}// function last

void AK_New_Or_Load_Sort(void){// 新しく始めるかロードするかのソート
		GsSortFastSprite(&AK_LOAD_OK,&ot[ PSDIDX ],0);// ロードします
		GsSortFastSprite(&AK_NEW_GAME,&ot[ PSDIDX ],0);// 新しく始める
}// function last


void AK_Pnl_Sort(void){// 選択パネルのソート

			// 選ぶ
			AK_SELECT.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_SELECT.attribute |= (0x00<<24);/*16*/
			AK_SELECT.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_SELECT.tpage = 21;/*21page*/
			AK_SELECT.cx = 960;
			AK_SELECT.cy = 496;
			AK_SELECT.u = AK_Pnl_Size[0][U];
			AK_SELECT.v = AK_Pnl_Size[0][V];
			AK_SELECT.w = AK_Pnl_Size[0][W];
			AK_SELECT.h = AK_Pnl_Size[0][H];
			AK_SELECT.x = 40;// 表示位置は薫と共通に。元はマイナス１６
			AK_SELECT.y = 80;
			// 次へ
			AK_NEXT.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_NEXT.attribute |= (0x00<<24);/*16*/
			AK_NEXT.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_NEXT.tpage = 21;/*21page*/
			AK_NEXT.cx = 960;
			AK_NEXT.cy = 497;
			AK_NEXT.u = AK_Pnl_Size[1][U];
			AK_NEXT.v = AK_Pnl_Size[1][V];
			AK_NEXT.w = AK_Pnl_Size[1][W];
			AK_NEXT.h = AK_Pnl_Size[1][H];
			AK_NEXT.x = 96;// 表示位置は薫と共通に。
			AK_NEXT.y = 80;
			// 決定
			AK_OK.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_OK.attribute |= (0x00<<24);/*16*/
			AK_OK.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_OK.tpage = 21;/*21page*/
			AK_OK.cx = 960;
			AK_OK.cy = 497;
			AK_OK.u = AK_Pnl_Size[2][U];
			AK_OK.v = AK_Pnl_Size[2][V];
			AK_OK.w = AK_Pnl_Size[2][W];
			AK_OK.h = AK_Pnl_Size[2][H];
			AK_OK.x = 96;// 表示位置は薫と共通に。元は40
			AK_OK.y = 80;

		GsSortFastSprite(&AK_SELECT,&ot[ PSDIDX ],0);// 選択パネル
//		GsSortFastSprite(&AK_NEXT,&ot[ PSDIDX ],0);// 次へ
		GsSortFastSprite(&AK_OK,&ot[ PSDIDX ],0);// 決定
}// function last


short AK_Select_Load_Or_New(void){// カーソルセレクト ０で上選択１で下選択
			if ( PadDat[0].trg & PADLU ){// 上 ロードを選択
				SE_ENT(SE_CUR1);
				AK_LOAD_OK.cy = 511;// 選択カラー
				AK_NEW_GAME.cy = 510;
				return ( 1 );// 1を返す
			}
			else if ( PadDat[0].trg & PADLD ){// 下 新しく始めるを選択
				SE_ENT(SE_CUR1);
				AK_LOAD_OK.cy = 510;
				AK_NEW_GAME.cy = 511;// 選択カラー
				return ( 2 );// 2を返す
			}// else if last
	return ( 0 );// 普段は０を返す
}// function last




/* ブロック数算出*/
int _calc_total_blocks( int files, struct DIRENTRY* dir )
{
	int i;
	int n;

	for( i=0, n=0; i<files; i++ )
		n += dir[i].size/8192 + (dir[i].size%8192 ? 1:0);
	return(n);
}

// データ初期化、0クリアとか
void AK_MEM_DATA_INIT(int no)
{
	int i = 0;
	int REDDAY = 0;
	LPISTATIC curr=(LPISTATIC)ISTATIC_ADDR;

	REDDAY = no;// 23日スタートか２４日スタートか選ばせる


// イベントフラグからサウンド先頭までセーブする場所を先ず０クリアしておく
	memset (( unsigned long *)0x801ef800,0,0x200);
// その後初期データセット

	
	curr->hp = 3000;      /* 4: ヒットポイント            */
	curr->dp = 2500;      /* 4: ディフェンスポイント      */
	curr->hpmax = 3000;   /* 4: ヒットポイント            */
	curr->dpmax = 2500;   /* 4: ディフェンスポイント      */
	curr->exp = 100;        /* 2: 獲得経験値                */
	curr->at = 2000;      /* 2: 攻撃力                    */
	curr->lv = 1;         /* 1: レベル（持ってない虫は０）*/
	curr->crank = 2;      /* 1: コマンドランク            */
	curr->arank = 2;      /* 1: オーラランク              */
	curr->pad = 0;        /* 1:                           */
	// 以上カブト虫
	// 残りは0クリアしておく
	for (i=1;i<64;i++){
		(curr+i)->hp=0;
		(curr+i)->dp = 0;   
		(curr+i)->hpmax = 0;
		(curr+i)->dpmax = 0;
		(curr+i)->exp = 0;  
		(curr+i)->at = 0;   
		(curr+i)->lv = 0;   
		(curr+i)->crank = 0;
		(curr+i)->arank = 0;
		(curr+i)->pad = 0;  
		
	}// for last
	// マップのイベントフラグ初期化
	// 801EF800から801f0000迄0クリアする
	// 差を取って0x800ある、longなので4バイトだから4で割る。0x200が実際の距離
	//	memset (( unsigned long *)0x801ef800,0,0x200);// 上でやっている
	
	
	if ( REDDAY == 24 ){
		memset( (unsigned char *)MONTH_ADDR,7,1 );// 7月
		*( ( unsigned char *)DAY_ADDR ) = 24;// 24日
		memset( (unsigned char *)WEEK_ADDR,2,1 );// 2日目からにしてほしいとの要望あり
		*( (unsigned long *)0x801ef9f8 ) = 1000;// 所持金1000円
	}
	else if ( REDDAY == 23 ){
		memset( (unsigned char *)MONTH_ADDR,7,1 );// 7月
		*( ( unsigned char *)DAY_ADDR ) = 23;// 23日
		memset( (unsigned char *)WEEK_ADDR,1,1 );// 1日目
		*( (unsigned long *)0x801ef9f8 ) = 1000;// 所持金1000円
	}
}


/*-------------------------------
スプライト初期化
-------------------------------*/
void InitSpr(int no){
#if 0
	AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
	AK_Font[0].attribute |= (0x00<<24);/*16*/
	AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
	AK_Font[0].tpage = 5;/*5page*/
	AK_Font[0].cx = 960;
	AK_Font[0].cy = 510;
	AK_Font[0].u =
	AK_Font[0].v = 0;
	AK_Font[0].w = 16;
	AK_Font[0].h = 16;
	AK_Font[0].x =  
	AK_Font[0].y = 0;// 画面中央が原点
#endif
	
	switch (no){
		case NOCARD:// セーブファイルをロードします･･･
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 5;/*5page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load0_Size[0][U];
			AK_Font[0].v = AK_Load0_Size[0][V];
			AK_Font[0].w = AK_Load0_Size[0][W];
			AK_Font[0].h = AK_Load0_Size[0][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;
		case NODATA:// お買い上げありがとうございます。・・・
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 5;/*5page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load0_Size[1][U];
			AK_Font[0].v = AK_Load0_Size[1][V];
			AK_Font[0].w = AK_Load0_Size[1][W];
			AK_Font[0].h = AK_Load0_Size[1][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
			// はいいいえが必要
		break;

		case CARDCHECK:// 刺さってるかチェック
		break;
		case DATACHECK:// データがあるかチェック
		break;
		case DATABREAKCHECK:// データ壊れてるかチェック
		break;

		case BREAK_DATA:// データ壊れちゃってる
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 6;/*6page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load1_Size[0][U];
			AK_Font[0].v = AK_Load1_Size[0][V];
			AK_Font[0].w = AK_Load1_Size[0][W];
			AK_Font[0].h = AK_Load1_Size[0][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;

		case DATALOAD:// データロード
		break;
		case LOADCHECK:// ロード成功したかな？
		break;

		case LOADMISS:// ロード失敗
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 9;/*9page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load1_Size[0][U];
			AK_Font[0].v = AK_Load1_Size[0][V];
			AK_Font[0].w = AK_Load1_Size[0][W];
			AK_Font[0].h = AK_Load1_Size[0][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;
		case GOTITLE:// ロード成功したらタイトルへ
		break;
	// 以後新規作成手順
		case NEWGAME:// NODATAから分岐。初めてゲームをします
		break;
		case CREATEFILE:// ファイル作るよ
		break;
		case CHECK_CARD:// 作成開始してからのメモカ刺さってるかチェック
		break;
		case CARD_NO:// 刺さっていません
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 6;/*6page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load1_Size[2][U];
			AK_Font[0].v = AK_Load1_Size[2][V];
			AK_Font[0].w = AK_Load1_Size[2][W];
			AK_Font[0].h = AK_Load1_Size[2][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
			// スロット１にカードセットしてください
			AK_Font[1].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[1].attribute |= (0x00<<24);/*16*/
			AK_Font[1].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[1].tpage = 6;/*6page*/
			AK_Font[1].cx = 960;
			AK_Font[1].cy = 510;
			AK_Font[1].u = AK_Load1_Size[3][U];
			AK_Font[1].v = AK_Load1_Size[3][V];
			AK_Font[1].w = AK_Load1_Size[3][W];
			AK_Font[1].h = AK_Load1_Size[3][H];
			AK_Font[1].x = MESSPOSX;
			AK_Font[1].y = MESSPOSY+16;
		break;
		case FORMATCHECK:// フォーマットチされてるかチェック
		break;
		case UNFORMAT:// フォーマットされていないよ！フォーマットする？？？
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 6;/*5page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load1_Size[4][U];
			AK_Font[0].v = AK_Load1_Size[4][V];
			AK_Font[0].w = AK_Load1_Size[4][W];
			AK_Font[0].h = AK_Load1_Size[4][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
			// はい いいえが必要
			
		break;
		case CHECK_FORMAT:// フォーマットは成功したかな？

		// 表示はチェックの結果駄目だった場合にします。

			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 6;/*6page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load1_Size[5][U];
			AK_Font[0].v = AK_Load1_Size[5][V];
			AK_Font[0].w = AK_Load1_Size[5][W];
			AK_Font[0].h = AK_Load1_Size[5][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		
		break;
		case SPACECHECK:// 空き容量チェック
		// 表示はチェックしてだめだった場合にします
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 7;/*7page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load2_Size[0][U];
			AK_Font[0].v = AK_Load2_Size[0][V];
			AK_Font[0].w = AK_Load2_Size[0][W];
			AK_Font[0].h = AK_Load2_Size[0][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		
		break;
		case CHECK_DATA:// 虫のデータがあるかな？
		break;
		case OVERWRITE:// データがあった時は上書き確認
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 7;/*7page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load2_Size[1][U];
			AK_Font[0].v = AK_Load2_Size[1][V];
			AK_Font[0].w = AK_Load2_Size[1][W];
			AK_Font[0].h = AK_Load2_Size[1][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		// はいいいえが必要

		break;
		case FILE_CREATE:// 作成中メッセージと実際の作成
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 7;/*7page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load2_Size[2][U];
			AK_Font[0].v = AK_Load2_Size[2][V];
			AK_Font[0].w = AK_Load2_Size[2][W];
			AK_Font[0].h = AK_Load2_Size[2][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;
		case CREATEERROR:// 新規ファイル作成失敗

		// 表示はチェックして失敗した時に出します

			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 7;/*7page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load2_Size[3][U];
			AK_Font[0].v = AK_Load2_Size[3][V];
			AK_Font[0].w = AK_Load2_Size[3][W];
			AK_Font[0].h = AK_Load2_Size[3][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;
/********************************************************************************
*			 ここまでオートロード用、以降はセーブ画面用							*
*																				*
********************************************************************************/
		case SAVEFILE:// セーブするか聴く、キャンセルはタイトルへ
		// セーブしますよろしいですか？
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 10;/*10page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load8_Size[0][U];
			AK_Font[0].v = AK_Load8_Size[0][V];
			AK_Font[0].w = AK_Load8_Size[0][W];
			AK_Font[0].h = AK_Load8_Size[0][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case MCCHECK:// 刺さってるかチェック、フォーマットもチェックできる
		break;
		case FORMATOK:// フォーマットしますか？成功なら流れへ
		break;
		case FORMATMISS:// フォーマットミス
		break;
		case SAVE_FILE_CHECK:// セーブデータがあるかのチェック。openしてみる
		break;
		case OVER_WRITE_CHECK:// 上書き確認
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 10;/*10page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load8_Size[1][U];
			AK_Font[0].v = AK_Load8_Size[1][V];
			AK_Font[0].w = AK_Load8_Size[1][W];
			AK_Font[0].h = AK_Load8_Size[1][H];
			AK_Font[0].x = MESSPOSX;// 表示位置は薫と共通に。
			AK_Font[0].y = MESSPOSY;
		break;
		case CARD_SPACE_CHECK:// 空き容量確認
		break;
		case NO_SPACE:// 空き容量無し
		
		break;
		case CREATE_FILE:// 実際にセーブ
		// ただいまセーブ中です
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 10;/*10page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load8_Size[2][U];
			AK_Font[0].v = AK_Load8_Size[2][V];
			AK_Font[0].w = AK_Load8_Size[2][W];
			AK_Font[0].h = AK_Load8_Size[2][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case SAVEMISS:// セーブミス
		// セーブに失敗しました
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 10;/*10page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load8_Size[3][U];
			AK_Font[0].v = AK_Load8_Size[3][V];
			AK_Font[0].w = AK_Load8_Size[3][W];
			AK_Font[0].h = AK_Load8_Size[3][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case GO_SEISAN:// 清算画面へ
		// セーブ完了しました
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 10;/*10page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load8_Size[4][U];
			AK_Font[0].v = AK_Load8_Size[4][V];
			AK_Font[0].w = AK_Load8_Size[4][W];
			AK_Font[0].h = AK_Load8_Size[4][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
/***********************************************************************************
*					ここから下は対戦モードロード用
*
*
***********************************************************************************/
		case AI_START_PRN:// 準備が出来たら○を押してね
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 8;/*8page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load6_Size[0][U];
			AK_Font[0].v = AK_Load6_Size[0][V];
			AK_Font[0].w = AK_Load6_Size[0][W];
			AK_Font[0].h = AK_Load6_Size[0][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case AI_CARD_NO:// カード刺さってないよ
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 8;/*8page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load6_Size[1][U];
			AK_Font[0].v = AK_Load6_Size[1][V];
			AK_Font[0].w = AK_Load6_Size[1][W];
			AK_Font[0].h = AK_Load6_Size[1][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case AI_NO_DATA:// データ無いよ
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 8;/*8page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load6_Size[2][U];
			AK_Font[0].v = AK_Load6_Size[2][V];
			AK_Font[0].w = AK_Load6_Size[2][W];
			AK_Font[0].h = AK_Load6_Size[2][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;
		case AI_LOAD_MISS:// ロードに失敗しました
			AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_Font[0].attribute |= (0x00<<24);/*16*/
			AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_Font[0].tpage = 9;/*9page*/
			AK_Font[0].cx = 960;
			AK_Font[0].cy = 510;
			AK_Font[0].u = AK_Load7_Size[0][U];
			AK_Font[0].v = AK_Load7_Size[0][V];
			AK_Font[0].w = AK_Load7_Size[0][W];
			AK_Font[0].h = AK_Load7_Size[0][H];
			AK_Font[0].x = MESSPOSX;
			AK_Font[0].y = MESSPOSY;
		break;

		default:
		break;
}// switch last


}





void Init_Yes_No(void){// はいいいえのしょきか
			AK_YES.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_YES.attribute |= (0x00<<24);/*16*/
			AK_YES.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_YES.tpage = 6;/*6page*/
			AK_YES.cx = 960;
			AK_YES.cy = 511;// 選択カラー
			AK_YES.u = AK_Load1_Size[6][U];
			AK_YES.v = AK_Load1_Size[6][V];
			AK_YES.w = AK_Load1_Size[6][W];
			AK_YES.h = AK_Load1_Size[6][H];
			AK_YES.x = -112;// 表示位置は薫と共通に。
			AK_YES.y = 24;
			
			AK_NO.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_NO.attribute |= (0x00<<24);/*16*/
			AK_NO.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_NO.tpage = 6;/*6page*/
			AK_NO.cx = 960;
			AK_NO.cy = 510;
			AK_NO.u = AK_Load1_Size[7][U];
			AK_NO.v = AK_Load1_Size[7][V];
			AK_NO.w = AK_Load1_Size[7][W];
			AK_NO.h = AK_Load1_Size[7][H];
			AK_NO.x = -112;// 表示位置は薫と共通に。
			AK_NO.y = 48;
}// function last



void Init_New_Or_Replay(void){// ロードするか新しく始めるかチェック
			AK_LOAD_OK.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_LOAD_OK.attribute |= (0x00<<24);/*16*/
			AK_LOAD_OK.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_LOAD_OK.tpage = 5;/*5page*/
			AK_LOAD_OK.cx = 960;
			AK_LOAD_OK.cy = 511;// 選択カラー
			AK_LOAD_OK.u = AK_Load0_Size[2][U];
			AK_LOAD_OK.v = AK_Load0_Size[2][V];
			AK_LOAD_OK.w = AK_Load0_Size[2][W];
			AK_LOAD_OK.h = AK_Load0_Size[2][H];
			AK_LOAD_OK.x = -112;// 表示位置は薫と共通に。
			AK_LOAD_OK.y = 24;
			
			AK_NEW_GAME.attribute |= (0x01<<6);/*輝度調整オフ*/
			AK_NEW_GAME.attribute |= (0x00<<24);/*16*/
			AK_NEW_GAME.attribute |= (0x01<<27);/*回転拡縮不許可*/
			AK_NEW_GAME.tpage = 5;/*5page*/
			AK_NEW_GAME.cx = 960;
			AK_NEW_GAME.cy = 510;
			AK_NEW_GAME.u = AK_Load0_Size[3][U];
			AK_NEW_GAME.v = AK_Load0_Size[3][V];
			AK_NEW_GAME.w = AK_Load0_Size[3][W];
			AK_NEW_GAME.h = AK_Load0_Size[3][H];
			AK_NEW_GAME.x = -112;// 表示位置は薫と共通に。
			AK_NEW_GAME.y = 48;
}// function last

void AK_Save_Mode_Init_Tim(){// セーブしますよろしいですか？
	AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
	AK_Font[0].attribute |= (0x00<<24);/*16*/
	AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
	AK_Font[0].tpage = 10;/*10page*/
	AK_Font[0].cx = 960;
	AK_Font[0].cy = 510;
	AK_Font[0].u = AK_Load8_Size[0][U];
	AK_Font[0].v = AK_Load8_Size[0][V];
	AK_Font[0].w = AK_Load8_Size[0][W];
	AK_Font[0].h = AK_Load8_Size[0][H];
	AK_Font[0].x = MESSPOSX;
	AK_Font[0].y = MESSPOSY;
}// Init_Tim last
void AK_Save_Mode_Init_2(){// カード抜かないでね
	AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
	AK_Font[0].attribute |= (0x00<<24);/*16*/
	AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
	AK_Font[0].tpage = 10;/*10page*/
	AK_Font[0].cx = 960;
	AK_Font[0].cy = 510;
	AK_Font[0].u = AK_Load8_Size[2][U];
	AK_Font[0].v = AK_Load8_Size[2][V];
	AK_Font[0].w = AK_Load8_Size[2][W];
	AK_Font[0].h = AK_Load8_Size[2][H];
	AK_Font[0].x = MESSPOSX;
	AK_Font[0].y = MESSPOSY;
}// Init_Tim last
void AK_Save_Mode_Init_3(){// セーブ完了
	AK_Font[0].attribute |= (0x01<<6);/*輝度調整オフ*/
	AK_Font[0].attribute |= (0x00<<24);/*16*/
	AK_Font[0].attribute |= (0x01<<27);/*回転拡縮不許可*/
	AK_Font[0].tpage = 10;/*10page*/
	AK_Font[0].cx = 960;
	AK_Font[0].cy = 510;
	AK_Font[0].u = AK_Load8_Size[4][U];
	AK_Font[0].v = AK_Load8_Size[4][V];
	AK_Font[0].w = AK_Load8_Size[4][W];
	AK_Font[0].h = AK_Load8_Size[4][H];
	AK_Font[0].x = MESSPOSX;
	AK_Font[0].y = MESSPOSY;
}// Init_Tim last

