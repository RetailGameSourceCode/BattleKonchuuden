#if !defined(__ISTATIC_H__)
#define	__ISTATIC_H__

/* ---- メモリ確保の数 ---- */
/* ---- バトル <=> ＳＬＧのみワーク ---- */
//#define ISTATIC2_ADDR     (0x801e5200) /* （２Ｐ向きワーク） 32 *  64 = 0x600 Byte(s) */
#define ISTATIC2_ADDR     (0x801e4a00) /* （２Ｐ向きワーク） 32 *  64 = 0x600 Byte(s) */
#define IUNITFT_DATA_ADDR (0x801e5800) /* 虫    テンプレート 34 *  64 = 0x800 Byte(s) */
#define ILEVEL_DATA_ADDR  (0x801e6000) /* LEVEL テンプレート  2 * 100 = 0x100 Byte(s) */
#define IUNITT_DATA_ADDR  (0x801e6100) /* 虫    テンプレート 34 *  64 = 0x800 Byte(s) */
#define IPUB_DATA_ADDR    (0x801e6900) /* IPUB  ワーク                  0x100 Bype(s) */
#define IMAP_ADDR         (0x801e6a00) /* IMAP マップデータ先頭        0x1500 Byte(s) */
//#define                 (0x801e7f00) /* 残り 256                      0x100 Byte(s) */

/* ---- ゲーム中常駐データ ---- */
#define IRESULT_ADDR (0x801e8000)     /* 清算データ受渡ワーク (2+1+1)*8 = 32 Byte */
#define ISTATIC_ADDR (0x801efa00)     /* ゲットした虫のデータ */

/* ---- 生産画面への受渡ワーク ---- */
typedef struct __tagIRESULT{
	long nSum;                    /* 4: 合計           */
	char nID;                     /* 1: キャラナンバー */
	char nTime;                   /* 1: 個数           */
	char pad[2];                  /* 2: 個数           */
} IRESULT, *LPIRESULT;

/* ---- ゲットした虫ワーク ---- */
typedef struct __tagISTATIC{
	long hp;                      /* 4: ヒットポイント            */
	long dp;                      /* 4: ディフェンスポイント      */
	long hpmax;                   /* 4: ヒットポイント            */
	long dpmax;                   /* 4: ディフェンスポイント      */
	short exp;                    /* 2: 獲得経験値                */
	short at;                     /* 2: 攻撃力                    */
	char lv;                      /* 1: レベル（持ってない虫は０）*/
	char crank;                   /* 1: コマンドランク            */
	char arank;                   /* 1: オーラランク              */
	char pad;                     /* 1:                           */
} ISTATIC, *LPISTATIC;

#endif
