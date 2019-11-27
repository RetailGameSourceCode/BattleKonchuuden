/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : INIT SPR                                                 */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : AKINIT.C                                                 */
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
		// 上と共用出来る
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



