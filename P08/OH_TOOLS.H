/****************************************************************************************************
*																									*
*										      定数定義												*
*																									*
****************************************************************************************************/
// メモリカードツール用
#define		BLOCK_MAX 15
// ０１２３ ４５６７ ８９ＡＢ ＣＤＥＦ

/****************************************************************************************************
*																									*
*											    型定義												*
*																									*
****************************************************************************************************/
typedef struct {
//	long	attribute;
	long	info;			// 接続				結果
	long	load;			// 状態				
	long	read;			// 読み込み			
	long	write;			// 書き込み			
	long	init;			// ホーマット   	
	long	open;			// ファイルオープン	
	long	file;			// ファイル数
	long	func;			// 実行命令
	long	flag[10];		// 実行命令に対するエンドフラグ
} MCARD;



/* メモリカード検査用構造体 */
typedef struct {
	int		mc_port;			// 1P = 0 / 2P = 1
	char	mc_file[28];		// セーブ/ロード用ファイルネーム
	long	*mc_addr;			// セーブ/ロード用データ先頭アドレス（ポインタ）
	long	mc_start;			// セーブ/ロード用スタートアドレス（１２８＊ｎ）
	long	mc_size;			// セーブ/ロード用データサイズ    （１２８＊ｎ）
} CARD_ACCESS;
/* ファイルヘッダ構造体 */
typedef struct {
	char	Space0[4];
	char	name0[16];
	char	name1[16];
	char	name2[16];
	char	name3[16];
	char	Space1[60];
} MESS;
/* バックアップ用 128*1 バイト用*/
typedef struct {
	char	Space[128*1];
} BACK_DATA;

/* バックアップ用 128*28 バイト用*/
typedef struct {
	char	Space[128*28];
} BACK_DATA28;

typedef struct {
	int	M_NO;
	int	M_CNT;
	int	M_MAX;
} MT_DT;

//	TIM 情報 
typedef struct{
	short	mode,ix, iy, cx, cy;
	} Tim_Info;

typedef struct {
	int	Jump;
	int	Cnt;
	int E_Flag;
} YN2_DATA;


typedef struct {
	short	Dr[3][4];		/* ドラゴン番号,ＡＴＴＡＣＫ,ＡＶＯＩＤ,ＴＭＰ */
	char	Bt;				/* 戦っているドラゴンの番号 */
} CVS_DT;

typedef struct {
	int	Mode;
	int	Sel[2];
} MENU_ST;

// ストーリーモード管理ワーク 
typedef struct {
	char	TMP[64];
	int		s_flag;				// スタートフラグ 0=ロード/1=ニュー 
	int		code[2];			// ファイル識別コードセット用 
	char	f_name[28];			// メモリカードファイル名 
} LSMODE_DATA;


typedef struct {
	short   	Name[8];				// 名前			（8文字）（ゲーム中表示用データ） 
	short		Level;					// プレーヤレベル 1: 完竜まで育てた 2: WDCちゃんぷ 
	int			Money;					// お金			Max 99999 
	int			Day[4];					// 年月日時		Max 9999,12,31,24 
	char		tmp[72+16];
} PLAY_LD;




extern	PLAY_LD			Load_Data[2][15];		// ゲーム情報データロード（１２８バイト） 
extern	CARD_ACCESS		MC_DATA;
extern	MCARD			mcard_data[2];
extern	int				File_No[2][15];
extern	struct DIRENTRY file_data[2][15];



/****************************************************************************************************
*																									*
*										関数プロトタイプ宣言										*
*																									*
****************************************************************************************************/
void 		CARD_SYNC_I(void);
int 		CARD_SYNC(CARD_ACCESS);
int 		CARD_SYNC_WAIT();
int 		_calc_total_blocks( int , struct DIRENTRY* );

void		CARD_DRAGON_I(void);
int			CARD_DRAGON(int);


