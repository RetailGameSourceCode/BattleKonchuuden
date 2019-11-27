//
//
//	PS XA Driver Ver 1.0
//
//


#if !defined _PK_XA_H_
#define		_PK_XA_H_

#include	<kernel.h>
#include	<sys/types.h>
#include	<libsnd.h>
#include	<libcd.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct {
	char				sfno;						// XA file No
	char				ch;							// XA Ch No
	char				offset;						// start sector offset
	char				vol;						// Play Volume
	unsigned short		time;						// Play time
	char				pad0,pad1;
} XA_DATA;

#define	s_char	signed char

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

enum {
	 XA_WM_READY= 0
	,XA_WM_PLAY
};

#define		SCTSIZE	2336
#define		RNGSIZE	1

/* ---  XA size → フレーム数変換定数  括弧は付けてはダメです ---------- */

#define		XATIME	8 * 60 / 75 / 2336
// 下記のマクロはczarmac.h S2F()とバッティングするのでコメントアウト（基本的に直値なので問題なし） 
//#define		S2F		8*60/75/SCTSIZE
#define		s2f(x)	((x)*8*60/75/SCTSIZE)

/* -------------------------------------------------------------------- */

extern volatile s_char	xa_working_mode;

void	XaInit(CdlLOC xa_loc[], XA_DATA xa_data[], char *buff);
void	XaVSyncJob(void );
int		XaSeekS(int xa_no);
void	xa_seek(int	xa_no);
void	xa_stop(void );
void	set_xa_mode(void );

// 1997/10/01 append by Czar 
extern volatile int	xa_vsync_f;
extern volatile s_char	xa_working_mode;
extern volatile int	xa_error;
extern volatile int	xa_flame;
extern volatile int	xa_time_work;

#define CDDATA_READ_CLOSE() \
{\
	SsSetSerialVol(SS_SERIAL_A, 0,0);\
	xa_vsync_f= 0;\
	CdReadyCallback(NULL);\
	CdSyncCallback(NULL);\
	CdControl(CdlPause, NULL,NULL);\
	xa_flame= -1;\
	xa_working_mode= XA_WM_READY;\
	xa_error= 0;\
}

// end of append by Czar

#define	XaPlay(xa_no)		xa_seek(xa_no)
#define	XaStop()			xa_stop()
#define	XaModeSet()			set_xa_mode()
#define	XaSeek(xa_no)		XaSeekS(xa_no)

#endif








#if 0

XaInit		XAシステム初期化(ファイル設定)
			XAシステムを使用するにあたり始めに呼んでおく。

	形式	void		XaInit(CdlLOC xa_loc[], XA_DATA xa_data[], char *buff)

	引数	xa_loc[]	ファイルポジション配列先頭アドレス
						全 xa_loc[]はデータが設定されている必要があります。
yy
			xa_data[]	XA 属性データ
						全 xa_data[] はデータが設定されている必要があります。

			buff		SCTSIZE*RNGSIZE byte分の読みだしバッファ

XaVSyncJob	再生時間管理
			XaInit()後 1/60sec の割り込みを使用して 呼び続ける。

	形式	void		XaVSyncJob(void )



XaModeSet	CDシステムをXA 再生モードに設定する。
			 始めて、あるいは CDからのデータリード,DA再生後 に XAを再生するとき
			にあらかじめ呼んでおく (ブロックされます)

	形式	void		XaModeSet(void )






XaPlay		XA再生

	形式	void		XaPlay(int xa_no)

	引数	xa_no		XA No





XaSeek		XA Noによるシークリクエストを発行する。
		(CdControlF()使用,後始末(エラー処理,シーク終了確認等)はユーザがする。)

	形式	void		XaSeek(int xa_no)

	引数	xa_no		XA No





XaStop		XA強制終了

	形式	void		XaStop(void )


#endif
