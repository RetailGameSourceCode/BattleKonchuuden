/****************************************************************************************
*						赤沢サウンドツール												*
*														1998/7/6 written by red			*
*														とりあえずＸＡ後回し(;_;)		*
*														SOUND_CLOSE()も後回し			*
****************************************************************************************/
#include <sys/types.h>
#include <libetc.h>
//#include <libgte.h>/*graphic system?*/
//#include <libgpu.h>
#include <libcd.h>	/*use cd-rom */
#include <libds.h>	/*cd-xa vol*/
#include <libsnd.h>/*sound system*/
#include <libsn.h> 
#include <stdio.h>/*for printf???*/

#include "ak_sound.h"/*赤沢ヘッダファイル*/
#include "../lib/libfio.h"/*山内さんスーパーライブラリ*/
#include "../lib/libdbg.h"/*同じくデバッグ用(未使用かも？)*/
#include "../lib/libsxa.h"// スーチーXA

#define TEST 0			/*0:リリースバージョン 1:デバッグバージョン*/

#define SPEED 0			/*0:normal speed 1:double speed */

/****************************************************************************************
*						関数プロトタイプ宣言											*
*																						*
****************************************************************************************/
void 	cbsync( u_char , u_char* );
int 	AK_READ(void);			/*タイトルコールデータロード関数*/
int 	SE_LOAD(short);			/*SE データロード関数*/
void DATA_CLOSE(short);
void BGM_VOL_0(void);

void red_xa_ready_callback( u_char intr, u_char *result );
int XA_CNT(void);

/****************************************************************************************
*						変数定義														*
*																						*
****************************************************************************************/
/*ak_sound.hにてextern*/

/*psx libds*/
// DslATV	CD_VOL;		/*オーディオアッテネータ*/
/*	サウンドツール用 */
// short vab[4];			/* vab data id */
// short seq[4];			/* seq data id */

static char seq_table [SS_SEQ_TABSIZ * SEQ_NO * SEP_NO];  /* seq table size */

int CurPos = 0;
int EndPos = 0;
int StartPos = 0;
static int Loop_F = 1;
static int XA_END = 0;
static int AK_Chan = 0;
static int VOLFLAG = 0;
static int	var_err = 0;
/* XA */
static int Flame_cnt = 0;

static char *redsecter_buffer =  ( char * )( 0x801fff00 - 2336 );// セクタ情報バッファ
static int  red_xa_error;// XA error カウント用



//static int RepTime;					// XAリピート回数カウント
// char	VAB_STATUS[4];			// 内臓音源管理ワーク 
// char	SEQ_STATUS[4];
//int	 	SN_ENT_W[4][2];




/****************************************************************************************
*					構造体とテーブル実体												*
*																						*
****************************************************************************************/
SND_DATA snd_data = { 0, 127, 127, 0 };/*実際に使う構造体の実体*/
unsigned char param[4] = {0,0,0,0};

CATSND BGM_TBL_ALL[]={/*内臓音全て固めたデータのテーブル*/
#include "BGM.REP"
};


/****************************************************************************************
*					関数スタート														*
*																						*
****************************************************************************************/

/*初期化関数はこれで大丈夫なはずだ！！！*/
/*データロード前に初期化してみるとりあえず*/
void 	SOUND_I(void){/*サウンド関係初期化*/
int	i;/*roop counter*/

	SsInit();/*libsnd*/

//CdSetDebug(2);


	SsSetTableSize (seq_table, SEQ_NO, NO_SEP);/*とりあえずSEP未使用*/
//	SsSetTickMode(30|SS_NOTICK);	/* set tick mode = NOTICK */
	SsSetTickMode(SS_TICK60);		/*分解能1/60 callback自動呼出し*/
//	SsSetTickMode(SS_NOTICK);		/* set tick mode = NOTICK */


	SsStart2();						/* start sound */
	/*SS_TICK60なのでSsStart()ではなく、こちらを呼ぶ*/


	SsSetMVol(127,127);				/*メインボリューム(データロード後のほうが良い？)*/

	snd_data.FLAG	= 0;			/*未来予約*/
	snd_data.BGM_VOL= 127;			/*ボリューム初期値(最大に設定)*/
	snd_data.SE_VOL	= 127;			/*同上*/
	snd_data.MODE	= 0;			/*0:stereo 1:monoral*/



	// サウンド管理ワーク初期化 
	for(i=0;i<4;i++)
		VAB_STATUS[i] = 0;
	for(i=0;i<4;i++)
		SEQ_STATUS[i] = 0;
	for(i=0;i<4;i++){
		SN_ENT_W[i][0]	= -1;
		SN_ENT_W[i][1]	= -1;
	}

/*リバーブタイプ設定*/
	SsUtSetReverbType(SS_REV_TYPE_HALL);		// サウンドリバーブタイプ設定 
	SsSetRVol(127,127);
	SsUtReverbOn();								// リバーブをＯＮ 
	SsUtSetReverbDepth(127*0.3,127*0.3);


	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);	// SsInit()(SndInit()の内部で呼ばれる)でＣＤの属性が初期化されてしまうので再設定 
	SsSetSerialVol(SS_SERIAL_A, 127, 127);


//	AK_READ();
// タイトルコールのSEが追加された為、SE_LOAD関数を別に用意しました
}
/****************************************************************************************************
	SE(VAB)のエントリです。
	サウンドのデータテーブル（SE_TBL）の何番目を鳴らすかを登録する
	注）サンプルを参照した結果。音を消してから鳴らすらしい・・・
	1998/10/27追加事項
	複数回エントリしたときに連続して鳴るようにする為、KeyOffはコメント
****************************************************************************************************/
void 	SE_ENT(int snd_no){
u_short	SE_Vol;
	SE_Vol = (u_short)(snd_data.SE_VOL*SE_VOL_D/127);
//	SsVoKeyOff(SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch);
	SsVoKeyOn( SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch,SE_Vol,SE_Vol);
}
/****************************************************************************************************
	SE(VAB)のクリアです。
	サウンドのデータテーブル（SE_TBL）の何番目を消すかを登録する
****************************************************************************************************/
void 	SE_CLR(int snd_no){
	SsVoKeyOff(SE_TBL[snd_no].prog,SE_TBL[snd_no].pitch);
}
/****************************************************************************************************
	SE(VAB)のオールクリアです。
	注）SsUtAllKeyOff だと SEQも一瞬消えてしまうのが少し気になる。
****************************************************************************************************/
void 	SE_ALLCLR(void){
	SsUtAllKeyOff(0);
}
/****************************************************************************************************
	BGM（SEQ）のエントリです。
****************************************************************************************************/
int 	BGM_ENT(short bgm_no){
	SsSeqPlay(bgm_no,SSPLAY_PLAY,SSPLAY_INFINITY);
	return ( SN_ENT_W[3][1] );
}
/****************************************************************************************************
	BGM（SEQ）のクリアです。
****************************************************************************************************/
void 	BGM_CLR(short bgm_no){
	SsSeqPause(seq[3]);
}
/****************************************************************************************************
	BGM（SEQ)一時停止 赤沢テスト
****************************************************************************************************/
void BGM_PAUSE(void){
	SsSeqPause(seq[3]);
}
/****************************************************************************************************
	BGM（SEQ）リプレイ。
****************************************************************************************************/
void 	BGM_RENT(short bgm_no){
u_short	BG_Vol;
	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);
	SsSeqReplay(bgm_no);
}

/****************************************************************************************************
	BGM（SEQ）のサウンドフェード
	注）現在のボリューム値からの変化
		時間がボリュームの倍数がベスト
		SsUtAoutVolでやる？
****************************************************************************************************/
//void 	BGM_FADE(int fade_flag,short seq_no,short seq_vol,long seq_time){
void 	BGM_FADE(int fade_flag,short seq_vol,long seq_time){
u_short	BG_Vol;
	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	if(fade_flag == BGM_DOWN   )
//		SsSeqSetDecrescendo(seq_no,BG_Vol,seq_time);
		SsSeqSetDecrescendo(0,BG_Vol,seq_time);
	if(fade_flag == BGM_UP   )
//		SsSeqSetCrescendo(seq_no,BG_Vol,seq_time);
		SsSeqSetCrescendo(0,BG_Vol,seq_time);
}
/****************************************************************************************************/
/****************************************************************************************************/
void	BGM_VOL_SET(void){
u_short	BG_Vol;

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);

	/* ＸＡボリューム設定 */
	CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
	CD_VOL.val1 = 0;
	CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
	CD_VOL.val3 = 0;
//	DsMix(&CD_VOL);
CdMix(&CD_VOL);

}

void	BGM_VOL_0(void){
u_short	BG_Vol;

	BG_Vol = 0;
	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);

	/* ＸＡボリューム設定 */
	CD_VOL.val0 = 0;
	CD_VOL.val1 = 0;
	CD_VOL.val2 = 0;
	CD_VOL.val3 = 0;
//	DsMix(&CD_VOL);
CdMix(&CD_VOL);

	SsSetRVol(0,0);
	SsUtReverbOff();								// リバーブをOFF 
	SsUtSetReverbDepth(0,0);

}



void	SND_MODE_SET(void){/*構造体中で定義されたモードをセットする*/
	if(snd_data.MODE == 0){
	/* ステレオセット */
		SsSetStereo();
	}
	else{
	/* モノラルセット */
		SsSetMono();
	}
}
/****************************************************************************************************/
/****************************************************************************************************/
void 	SOUND_E(){

	BGM_VOL_0();
	SsSeqStop(seq[3]);	/* stop seq data */
	SsSeqClose(seq[3]);	/* close seq data */
	SsVabClose(vab[3]);	/* close vab data */
	SsEnd();		/* sound system end */
	SsQuit();
}
/****************************************************************************************************
	データロード(test)
****************************************************************************************************/
int AK_READ(void){/*とりあえずのデータロード用関数*/

u_short	BG_Vol;

//	printf("MCCHK : %d\n", FioGetMachine() );
#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

#if 0
		FioReadFile(SE_LTBL[1][0], (void *)VAB_HADDR0);
		FioReadFile(SE_LTBL[1][1], (void *)VAB_BADDR0);
#endif

//		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[0].ST,BGM_TBL_ALL[0].SI);
//		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[1].ST,BGM_TBL_ALL[1].SI);

		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[65].ST,BGM_TBL_ALL[65].SI);
		FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[66].ST,BGM_TBL_ALL[66].SI);


	vab[2] = SsVabOpenHead ((void *)VAB_HADDR0, OPENVABID0);
	if (vab[2] < 0) {
		var_err = 1;
		printf("BGM ERROR 0\n");
		return(0);
	}

	if (SsVabTransBody ((void *)VAB_BADDR0, vab[2]) != vab[2]) {
		var_err = 2;
		printf("BGM ERROR 1\n");
		return(0);
	}
	SsVabTransCompleted (SS_WAIT_COMPLETED);
//	seq[3] = SsSeqOpen((void *)SEQ_ADDR0, vab[3]);	/* open seq data */

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
//	SsSeqSetVol(seq[3], BG_Vol,BG_Vol);	/* set seq data volume (0-127)*/

	printf("se_set\n");
	return(1);
}


int SE_LOAD(short dtno){/*SEデータロード用関数*/

u_short	BG_Vol;

//DATA_CLOSE(2);// タイトルコールSEは閉じておく必要あり

//	printf("MCCHK : %d\n", FioGetMachine() );
#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

	switch(dtno){
		case 0:// 本編用

			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[0].ST,BGM_TBL_ALL[0].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[1].ST,BGM_TBL_ALL[1].SI);
		break;
		case 1:// タイトル用
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[65].ST,BGM_TBL_ALL[65].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[66].ST,BGM_TBL_ALL[66].SI);
		break;
		case 2:// PDA用追加
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR0,BGM_TBL_ALL[70].ST,BGM_TBL_ALL[70].SI);
			FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR0,BGM_TBL_ALL[71].ST,BGM_TBL_ALL[71].SI);
		break;
	}// switch last
	
	vab[2] = SsVabOpenHead ((void *)VAB_HADDR0, OPENVABID0);
	if (vab[2] < 0) {
		var_err = 1;
		printf("BGM ERROR 0\n");
		return(0);
	}

	if (SsVabTransBody ((void *)VAB_BADDR0, vab[2]) != vab[2]) {
		var_err = 2;
		printf("BGM ERROR 1\n");
		return(0);
	}
	SsVabTransCompleted (SS_WAIT_COMPLETED);

	BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);

	printf("se_set\n");
	return(1);
}


/****************************************************************************************************
	ＢＧＭロード
****************************************************************************************************/
void 	BGM_LOAD(int no){
//int		i,j;
//char	*BGM_DATA;/*固めたら使わなくなった*/
int		BGM_no;
u_short	BG_Vol;
//u_long	*addr1;

		BGM_no = no;
//			/* ＢＧＭ登録 */

#if (TEST)
	fio.dbg_flg = FIO_MC_DEV;
#endif

			BGM_no = no;
VSync(0);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_HADDR3,BGM_TBL_ALL[BGM_no].ST,BGM_TBL_ALL[BGM_no].SI);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)VAB_BADDR3,BGM_TBL_ALL[BGM_no + 1].ST,BGM_TBL_ALL[BGM_no + 1].SI);
	FioDivReadFile("DT\\BGM.DAT",(unsigned char *)SEQ_ADDR3,BGM_TBL_ALL[BGM_no + 2].ST,BGM_TBL_ALL[BGM_no + 2].SI);

#if 0
			BGM_DATA  =  BGM_LTBL[BGM_no][0]; /*全部固めたら使えなくなった*/

			BGM_DATA  =  BGM_LTBL[BGM_no][0];
			FioReadFile(BGM_DATA,(void *)VAB_HADDR3);
			
			BGM_DATA  =  BGM_LTBL[BGM_no][1];
			FioReadFile(BGM_DATA,(void *)VAB_BADDR3);
			
			BGM_DATA  =  BGM_LTBL[BGM_no][2];
			FioReadFile(BGM_DATA,(void *)SEQ_ADDR3);
#endif
VSync(0);
			vab[3] = SsVabOpenHead ((u_char *)VAB_HADDR3, OPENVABID3);
			if (vab[3] < 0) {
				var_err = 1;
				printf("BGM ERROR 2\n");
				return;
			}
VSync(0);
			if (SsVabTransBody ((u_char*)VAB_BADDR3, vab[3]) != vab[3]) {
				var_err = 2;
				printf("BGM ERROR 3\n");
				return;
			}
			SsVabTransCompleted (SS_WAIT_COMPLETED);
			seq[3] = SsSeqOpen((u_long *)SEQ_ADDR3, vab[3]);	/* open seq data */

			BG_Vol = (u_short)(snd_data.BGM_VOL*BGM_VOL_D/127);
			SsSeqSetVol(seq[3], BG_Vol,BG_Vol);	/* set seq data volume (0-127)*/

			VAB_STATUS[3] = 1;		// 登録中 
			SEQ_STATUS[3] = 1;		// 登録中 


			SN_ENT_W[3][0]	= 1;	/* BGM */
			SN_ENT_W[3][1]	= no;	/* BGM NO */

			printf("DATA SET\n");
//		}// else last
}
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/

/*test*/
void DATA_CLOSE(short no){
	switch (no){
		case 1:// すべてクローズ
			SsSeqStop(seq[3]);/*不必要？？？*/
			SsSeqClose(seq[3]);
			SsVabClose(vab[3]);
			SsVabClose(vab[2]);/*常駐ＳＥ*/
			printf("DATA CLOSE ALL\n");
		break;
		case 2:// ＳＥクローズ
			SsVabClose(vab[2]);/*常駐ＳＥ*/
			printf("DATA CLOSE SE\n");
		break;
		case 3:// ＢＧＭクローズ
			SsSeqStop(seq[3]);/*不必要？？？*/
			SsSeqClose(seq[3]);
			SsVabClose(vab[3]);
			printf("DATA CLOSE BGM\n");
		break;
		default:
			printf("error!!\n");
		break;
	}
}
/****************************************************************************************************/
/****************************************************************************************************/
/*以下ＸＡ*/

/*実際にみんなに呼んでもらう関数はここから・・・
--------------------------------------------------------------------------------*/


void 	XA_CLR(void){



		CdSyncCallback(NULL);
		CdReadyCallback(NULL);
		red_xa_error = 0;





		// XA
		/* ボリューム設定 */
		CD_VOL.val0 = 0;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = 0;
		CD_VOL.val3 = 0;
//		DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//		param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//		param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
CdControl( CdlPause , param , NULL );
CdFlush();
}

int 	XA_FADE(void){

// 0 :up 1:down

// XA VOL DOWN
		/* ボリューム設定 */
			if(CD_VOL.val0 > 0)CD_VOL.val0 -=3;
				CD_VOL.val1 = 0;
			if(CD_VOL.val2 > 0)CD_VOL.val2 -=3;
				CD_VOL.val3 = 0;

//			DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//			param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//			param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
			if((CD_VOL.val0 <= 0)&&(CD_VOL.val2 <= 0)){

				CD_VOL.val0 = CD_VOL.val2 = 0;/*とりあえず０クリアしておく*/

//				DsCommand( DslPause, param, 0 ,-1);
CdControl( CdlPause , param , 0 );
//				DsFlush();		/* 登録処理の解除 */
CdFlush();
				VOLFLAG = 1;
			}
			return(VOLFLAG);
}// function last




/*from oh_tools.c*/
/*----------------------------------------------------------------------------
*
-----------------------------------------------------------------------------*/

CdlLOC		r_pos;// 外に出してみる





int 	XA_LOAD(int no){
CdlFILE			file;
CdlFILTER filter;



int			ans;
int		NO;
char	*XA_DATA;

unsigned short err_flag = 0;

Flame_cnt = 0;// カウンタクリア

		ans		= 0;
		NO		= no & 0x0000ffff;			/* ファイル番号ゲット */
		AK_Chan	= (no >> 16) & 0xf;			/* チャンネルゲット   */
		Loop_F	= (no >> 20) & 1;			/* ループフラグゲット */
		XA_END  = 0;						/* エンドフラグクリア */

#if(SPEED)
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
param[0] = CdlModeRT | CdlModeSF | CdlModeSize1;
#endif

CdSyncCallback(NULL);
printf("CDCD\n");
CdControlB( CdlSetmode , param , 0 );
CdSync(0,NULL);
//VSync(0);
//VSync(0);
//VSync(0);

		/* ファイル位置の獲得 */
		XA_DATA  =  XA_LTBL[NO];

		do{
//			if( DsSearchFile( &file, XA_DATA ) == 0 ) {
//			if( PkSearchFile( &file, XA_DATA ) == 0 ) {
//			if( CdSearchFile( &file, XA_DATA ) == 0 ) {
if (FioCdSearchFile( &file, XA_DATA ) == 0 ) {
				err_flag ++;/*リトライフラグインクリメント*/
				ans  = 1;		// 検索エラー 
//				goto abort;
printf("LOAD ERR!\n");
			}// if last
			else{
				err_flag = XA_ERR_MAX;/*リトライ処理を抜ける*/
				ans = 0;		// エラーフラグクリア

//CdControl( CdlSeekL, (u_char * )&filter, 0 );

printf("LOAD OK!!\n");
			}// else last
		}// do last
		while( (err_flag < XA_ERR_MAX) );


		/* ADPCM 再生チャネル設定 */
		filter.file = 1;
		filter.chan = (u_char)AK_Chan;
		
		CdControlB( CdlSetfilter, (u_char * )&filter, 0 );

		/* ループ用セクタ番号 */
		StartPos = CdPosToInt( &file.pos );
//		EndPos   = StartPos + file.size / 2048;
		EndPos   = StartPos+XA_LONG[NO][AK_Chan];	// テーブル使用
		CurPos   = StartPos;
		
		CdIntToPos(StartPos,&r_pos);
		
		/* ボリューム設定 */
		CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val3 = 0;

//CdSync(0,NULL);
CdControlB( CdlSeekL, (u_char *)&( r_pos ), NULL);
//CdSync(0,NULL);

		CdMix(&CD_VOL);

		/* 再生 */
#if(SPEED)
//		DsPacket( DslModeSpeed | DslModeRT | DslModeSF, &file.pos, DslReadS, 0, -1 );
#else
//		DsPacket( DslModeRT | DslModeSF, &file.pos, DslReadN, 0, -1 );
CdControl(CdlReadN,(u_char *)&r_pos,0);// 付け足し
return ( 1 );
#endif

//abort:
if(ans == 1){
	printf("XAMISS\n");
}

	return(ans);

}

/****************************************************************************************************/
/****************************************************************************************************/
int 	XA_SYNC(void){

int		ANS;
//unsigned char result[8];


	if(XA_END == 0){
	if( Flame_cnt % XA_FREQ == 0){
		if( (CurPos > EndPos) || (CurPos < (StartPos - SP_MARGIN)) ){
			//if(Loop_F){/*ループ時にミスる時があるのでループは一切なしに変更12/4*/
				CD_VOL.val0 = 0;
				CD_VOL.val1 = 0;
				CD_VOL.val2 = 0;
				CD_VOL.val3 = 0;
				CdMix(&CD_VOL);
				/* 再生 （リピート）*/
				CurPos   = StartPos;
				//セクタ番号からポジションゲット 
				//CdIntToPos( StartPos, &r_pos );
				/* ボリューム設定 */
				CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
				CD_VOL.val1 = 0;
				CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
				CD_VOL.val3 = 0;
				CdMix(&CD_VOL);
#if(SPEED)
#else
param[0] = CdlModeRT | CdlModeSF | CdlModeSize1;// 完全な付け足し
CdControlB(CdlSetmode , param, 0 );// 11/17付け足し

CdControl(CdlReadN,(u_char *)&r_pos,0);// これも付け足し

CdReadyCallback( red_xa_ready_callback );

CdSyncCallback(NULL);// 11/18
CdReadyCallback(NULL);
#endif
			//}// Loop_F last
			//else{/*ここもループ時の部分なのでコメント*/
				/* 停止 */
				XA_CLR();
				XA_END = 1;
				printf("STOP\n");
			//}// else last
		}// Cur_Pos last
		else{
// 現在セクタ番号ゲット 

				ANS = CdControl(CdlGetlocP , 0 , 0 );
				CdSyncCallback(NULL);
				CdSyncCallback(cbsync);

//printf("ANS:%d\n",ANS);
//			if(ANS == 0){
			if ( CdSync(0,(void *)NULL) == CdlDiskError ){// 11/19サンプルのままだとワークを潰してしまっていた。
				/* エラーによる停止 */
				XA_CLR();
				XA_END = 1;/*元のソースでは１*/
				printf("ERROR\n");
			}// ANS == 0 last
		}// else last
	}// Flame_cnt last
	}// XA_END last
#if (TEST)
FntPrint("\nS:%d\n",StartPos);
FntPrint("C:%d\n",CurPos);
FntPrint("E:%d\n",EndPos);
FntPrint("F:%d\n",XA_END);
#endif
	return(XA_END);
}

void cbsync( u_char intr, u_char* result ){
int cnt;
	if( intr == CdlComplete ) {
		CdSyncCallback(NULL);// 磯野さんの追加
		
		CdReadyCallback( red_xa_ready_callback );
		CdReadyCallback(NULL);
		
		cnt = CdPosToInt( (CdlLOC* )&result[5] );
		if( cnt > 0 ){
			CurPos = cnt;
		}
			CdControlB(CdlGetlocP, 0, 0 );// 11/17追加
	}
	else{
		CdSyncCallback(NULL);
		CdReadyCallback(NULL);
		CdControl(CdlPause, 0, 0 );// 11/17追加
	}
}


void red_xa_ready_callback( u_char intr, u_char *result ){
   if ( intr == CdlDataReady ){
       CdGetSector( redsecter_buffer, 2336 / sizeof( long ) );
   }
   else{
        red_xa_error++;
        if( red_xa_error > XA_ERR_MAX ){
          XA_CLR();
          XA_END = 1;// 追加してみた11/22
          printf("XA ERROR MAX!!\n");
        }
   }
	
}


int XA_CNT(void){
	Flame_cnt++;
	if(Flame_cnt >  (127922-126194) ){
		XA_CLR();
		return ( 1 );
	}
	return ( 0 );
}


void 	XA_START(void){

		/* ボリューム設定 */
		CD_VOL.val0 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val1 = 0;
		CD_VOL.val2 = snd_data.BGM_VOL*XA_VOL_D/127;
		CD_VOL.val3 = 0;
//		DsMix(&CD_VOL);
CdMix(&CD_VOL);
#if (SPEED)
//		param[0] = DslModeSpeed | DslModeRT | DslModeSF;
param[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
#else
//		param[0] = DslModeRT | DslModeSF;
param[0] = CdlModeRT | CdlModeSF;
#endif
//		DsCommand( DslReadS, param, 0 ,-1);
CdControl( CdlReadS, param, 0 );
}

