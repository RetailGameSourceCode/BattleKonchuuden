// 赤沢ヘッダファイルメモカー用
#ifndef __AK_MEM_H__
#define __AK_MEM_H__


// メモリカードツール用
#define		BLOCK_MAX 15									// 15ブロック
#define		MEM_BLOCK	1									// とりあえず１ブロック使用
#define		SAVEOFFSET	4096								// ファイルの先頭を０とした時のオフセットバイト数
#define		SAVEBYTES	4096								// 書き込むバイト数(１２８の倍数)

#define		RETRY_MAX	3									// とりあえず３回リトライ



// セーブするのはここから下、801f0000サウンド常駐エリアの手前まで。
// 変わらない事を祈る･･･
#define  EVT_FLAG_ADDR       0x801EF800     // event flag addr 
#define  MONTH_ADDR          0x801EF9FD     // month 
#define  DAY_ADDR            0x801EF9FE     // day 
#define  WEEK_ADDR           0x801EF9FF     // 総日数 
#define  ISONO_ADDR          0x801EFA00     // 磯野氏 
#define  RED_INIT_FLG_ADDR   0x801EF9F0     // 初期化フラグ。起動時に0クリアされます

#define  MEMCARD_LOAD_ADDR_2P 0x80120000    // 今は超てきとー


#define		TIM_LOAD_ADDR				0x80120000			// tim load addr
#define		TIM_MAX_NUM					9					// tim number

#define		TIM_PRINT					10					// カード抜いちゃイヤーん表示時間ブロック関数なので10でも結構長いよ
#define		PRINTTIME					60					// 60flames print mess

#define		U							0// 変換テーブル用
#define		V							1
#define		W							2
#define		H							3

#define		MESSPOSX					-112// メッセージスタート位置は薫と共通にしました
#define		MESSPOSY					-72

#define		AK_YES						AK_Font[1]
#define		AK_NO						AK_Font[2]
#define		AK_LOAD_OK					AK_Font[3]
#define		AK_NEW_GAME					AK_Font[4]
#define		AK_SELECT					AK_Font[5]
#define		AK_NEXT						AK_Font[6]
#define		AK_OK						AK_Font[7]




/*固めたtim読み込み用*/
typedef struct {
	int ST;// start point
	int SI;// size
} CATTIM;


/*-----------User Table ------------*/
static CATTIM TIM_TBL[]={/*固めたtimデータのテーブル*/
#include "/98025/P08/TIMLST.REP"
};



/*文字表示用スプライト(1文字)*/
extern GsSPRITE AK_Font[16];			// 1行16文字


extern short AK_Load0_Size[][4];// Load0.tim size table
extern short AK_Load1_Size[][4];// Load1.tim uvwh table
extern short AK_Load2_Size[][4];// Load2.tim table
extern short AK_Load6_Size[][4];// Load6.tim table
extern short AK_Load7_Size[][4];// Load7.tim table
extern short AK_Load8_Size[][4];// Load8.tim size
extern short AK_Pnl_Size[][4];// Loadpnl.tim size

/*セーブロード処理enum*/
// ちょっと具合が悪いのでdefine に変更
// オートロード用
#define	INITSYS			0	// いろんな初期化とフォントロード
#define	CARDCHECK		1	// メモカ刺さってるかチェック
#define	NOCARD			2	// カード無いよ
#define	DATACHECK		3	// データあるかチェック
#define	NODATA			4	// データ無いよ
#define	DATABREAKCHECK	5	// データ壊れチェック
#define	BREAK_DATA		6	// データ壊れてるよ！！
#define	DATALOAD		7	// データロード
#define	LOADCHECK		8	// ロード成功か？チェック
#define	LOADMISS		9	// ロード失敗
#define	GOTITLE			10	// 成功ならタイトルへ
#define	NEWGAME			11	// 初めてのゲーム
#define	CREATEFILE		12	// ファイル作成。いいえならGOTITLEへ移動
#define	CHECK_CARD		13	// ファイル作成時のメモカチェック
#define	CARD_NO			14	// 刺さっていない時メッセージ表示後、NEWGAMEへ移動
#define	FORMATCHECK		15	// フォーマットされてるかチェック
#define	UNFORMAT		16	// フォーマットされていないのでフォーマットするか聴く。キャンセルの場合はNEWGAMEへ移動
#define	CHECK_FORMAT	17	// 失敗の場合はメッセージ後NEWGAMEへ移動。成功の場合はCHECK_DATA
#define	SPACECHECK		18	// 空き容量チェック。無い場合はメッセージ後NEWGAMEへある時はCHECK_DATA
#define	CHECK_DATA		19	// データがあるかチェック。無い場合は作成手順へ、ある場合は上書き確認のメッセージ
#define	OVERWRITE		20	// データがある時、上書きして新規ファイル作成するかの確認メッセージ。キャンセルはNOCARDへ移動
#define	FILE_CREATE		21	// 新規作成
#define	HEAD_CREATE		211	// ヘッダ作成
#define	CREATE_CHECK	22	// 作成チェックOKならGOTITLE、NGならメッセージ後NEWGAME
#define CREATEERROR		23	// 作成ミス

// ストーリーモードセーブ用
#define 			SYSINIT				100		// いろいろ初期化
#define 			SAVEFILE			101		// セーブするか聴く、キャンセルはタイトルへ
#define 			MCCHECK				102		// 刺さってるかチェック、フォーマットもチェックできる
#define 			FORMATOK			103		// フォーマットしますか？成功なら流れへ
#define 			FORMATMISS			104		// フォーマットミス
#define 			SAVE_FILE_CHECK		105		// セーブデータがあるかのチェック。openしてみる
#define 			OVER_WRITE_CHECK	106		// 上書き確認
#define 			CARD_SPACE_CHECK	107		// 空き容量確認
#define 			NO_SPACE			108		// 空き容量無し
#define 			CREATE_FILE			109		// 実際にセーブ
#define 			SAVEMISS			110		// セーブミス。カード壊れでも使用
#define 			GO_SEISAN			111		// 清算画面へ
// 追加
#define				CARD_NOTHING		112		// カード無いよ
#define				RUNFORMAT			113		// 実際にフォーマット
#define				NOWSAVING			114		// 実際にセーブ
#define				HEADCREATE			115		// ヘッダ作成
#define				FILEOPEN			116		// ファイルオープン

// 2P対戦モードロード用
#define				AI_INIT				1000	// tim読みとか初期化
#define				AI_CARD_CHECK		1001	// カードチェック
#define				AI_FILE_OPEN		1002	// ファイルオープンしてデータあるかチェック
#define				AI_DATA_LOAD		1003	// データロード
#define				AI_LOAD_MISS		1004	// ロード失敗
#define				AI_NO_DATA			1005	// データが無いよ
#define				AI_CARD_NO			1006	// カードが無いよ
#define				AI_CARD_NUKI		1007	// カード抜かれちゃったよ
#define				AI_START_PRN		1008	// セットしたら○を押してね
#define				AI_UNIT_SELECT		1009	// ２Ｐユニットセレクトへゴー！！




// 使ってる関数
extern void Tim2Vram(u_long);// イメージの取り込み
extern void InitSpr(int);// 表示メッセージの初期化
extern void Init_Yes_No(void);// はいいいえのしょきか
extern void Init_New_Or_Replay(void);// ロードするか新しく始めるかチェック
extern void AK_Auto_Load(void);// 起動時のメモリカードチェック
extern void AK_Mess_Sort(void);// メッセージの表示
extern void AK_Yes_No_Sort(void);// はいいいえの表示
extern void AK_New_Or_Load_Sort(void);// 新しく始めるかロードするかのソート
extern void AK_Pnl_Sort(void);// 選択パネルのソート
extern int _calc_total_blocks( int , struct DIRENTRY* dir );

extern void AK_Save_StoryMode(void);// 立山さんのところからきた時シナリオセーブ
extern void AK_Save_Mode_Init_Tim(void);// てきとーしょきか
extern void AK_Save_Mode_Init_2(void);// カード抜かないでね
extern void AK_Save_Mode_Init_3(void);// セーブ完了

//extern void AK_MEM_DATA_INIT(int no);// データ初期化 23 or 24 入力でスタート日変更

extern short AK_Select_Load_Or_New(void);// カーソルセレクト ０で上選択１で下選択

extern void Red_2P_Unit_Load(void);// 2P対戦モード用のロード関数





#endif