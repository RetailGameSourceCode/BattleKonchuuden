//---------------------------------------------------------------
//	ファンタステップ２
//		パッドの制御プログラム
//---------------------------------------------------------------
#include	<sys/types.h>
#include	<sys/file.h>
#include	<libetc.h>
#include	<libgte.h>
#include	<libgpu.h>
#include	<libsnd.h>
#include	<libcd.h>
#include	<libpad.h>
#include	<memory.h>
#include	"CZARDBUG.h"
#include	"CZARPAD.h"
#include	"main.h"
#include	"pad.h"
#include	"../lib/comara.h"

CZARPAD Pad[CZPAD_MAX];
Uint8 padbuff[2][34];

PAD_BUF	padbuf[2];

//OPTION	option;

void setPad(int port, Uint8 *rxbuf);

unsigned long PadManagerInit(void)
{
	int i;

	bzero((Uint8 *)padbuff, sizeof(padbuff));
	PadInitDirect(padbuff[0],padbuff[1]);		//コントローラ環境の初期化

	PadStartCom();
	
	for (i = 0; i < CZPAD_MAX; i++) {
		pad_work_clear(i);
//		padbuf[i].Lock = 0;			//2 unlock 3 lock
//		padbuf[i].Send = 0;
//		padbuf[i].act_timer0 = 0;
//		padbuf[i].act_flag0 = 0;
//		padbuf[i].act_timer1 = 0;
//		padbuf[i].act_flag1 = 0;
	}
}

//-----------------------------------------------------------------------------
//	パッドの値を入手
//-----------------------------------------------------------------------------
void PadGet(void)
{
	setPad(0,padbuff[0]);
	setPad(0x10,padbuff[1]);
	checkPad(0,padbuff[0]);
	checkPad(0x10,padbuff[1]);
}

//送信パケット内の振動子制御データ位置指定
//	 （本来はアクチュエータ情報の取得が完了してから内容を決定すべきで
//	   あるが簡単のため固定データとしている）
unsigned char align[6]={0,1,0xFF,0xFF,0xFF,0xFF};


//----------------------------------------------------------------------------
//	パッド情報をゲット
//----------------------------------------------------------------------------
void setPad(int port, Uint8 *rxbuf)
{
	Uint16	i,j;
	Uint16	tmp;
	Uint16	padd;
	Uint16	bitcheck;
	Uint8	analog_d;
	Uint8	analog_d2;
	int	initlevel;

	if(*rxbuf) 	return;			//通信に失敗しているときはボタン情報を読まない

	if(port == 0)	{
		i = 0;
	}
	else	{
		i = 1;
	}

	if(padbuf[i].act_flag0 != 0)	{
//	振動時間チェック
		if(--padbuf[i].act_timer0 < 0)	{
			padbuf[i].act_flag0 = 0;
			if(PadInfoMode(port,InfoModeCurExID,0)) {
				padbuf[i].Motor0 = 0;
			}
			else	{
				padbuf[i].Motor1 += 1;
			}
		}
	}
	if(padbuf[i].act_flag1 != 0)	{
//	振動時間チェック
		if(--padbuf[i].act_timer1 < 0)	{
			padbuf[i].act_flag1 = 0;
			if(PadInfoMode(port,InfoModeCurExID,0)) {
				padbuf[i].Motor1 = 0;
			}
			else	{
				padbuf[i].Motor1 += 1;
			}
		}
	}


	Pad[i].analog1 = rxbuf[4];
	Pad[i].analog2 = rxbuf[5];
	Pad[i].analog3 = rxbuf[6];
	Pad[i].analog4 = rxbuf[7];
	
	analog_d = 0;
	analog_d2 = 0;
//	右アナログ
	if(Pad[i].analog1 <= 0x50)	{
		analog_d |= 8;				//left
	}
	if(Pad[i].analog1 >= 0xb0) {
		analog_d |= 2;				//right
	}
	if(Pad[i].analog2 <= 0x50)	{
		analog_d |= 1;				//up
	}
	if(Pad[i].analog2 >= 0xb0) {
		analog_d |= 4;				//down
	}
//	左アナログ
	if(Pad[i].analog3 <= 0x50)	{
		analog_d2 |= 8;				//left
	}
	if(Pad[i].analog3 >= 0xb0) {
		analog_d2 |= 2;				//right
	}
	if(Pad[i].analog4 <= 0x50)	{
		analog_d2 |= 1;				//up
	}
	if(Pad[i].analog4 >= 0xb0) {
		analog_d2 |= 4;				//down
	}
	analog_d = (analog_d | analog_d2 << 4);

	analog_d2 = Pad[i].analogdat & analog_d;
	Pad[i].analogtrg = analog_d2 ^ analog_d;		//トリガゲット
	Pad[i].analogdat = analog_d;

	padd = (Uint16)((Uint16)(rxbuf[2] << 8) | rxbuf[3]);
	padd ^= 0xffff;
	
	Pad[i].id = rxbuf[1]>>4;			//端末の種類を記録
	Pad[i].old = Pad[i].dat;		//前のデータをストア

	Pad[i].dat = padd;				//このフレームのデータをセット
	tmp = Pad[i].old & padd;
	Pad[i].trg = tmp ^ padd;		//トリガゲット
	
	Pad[i].rpt = 0;
	for(j = 0 ; j < 16 ; j++)	{
		bitcheck = 2<<j;
		if((Pad[i].dat & bitcheck) != 0)	{
//	このボタンが押されてる
			if(Pad[i].timer[j] < 14)	{
				Pad[i].timer[j]++;
				Pad[i].rpt |= (Pad[i].trg & bitcheck);
			}
			else	{
				Pad[i].timer[j] -= 6;
				Pad[i].rpt |= (Pad[i].dat & bitcheck);
			}
		}
		else	{
//	ボタンがはなされた
			Pad[i].timer[j] = 0;
			Pad[i].rpt |= (Pad[i].trg & bitcheck);
		}
	}
	Pad[i].rpt |= Pad[i].trg;		//


}




void	checkPad(int port, Uint8 *rxbuf)
{
	Uint16	i;
	int	initlevel;


	if(port == 0)	{
		i = 0;
	}
	else	{
		i = 1;
	}


	initlevel = PadGetState(port);

	if(initlevel==PadStateDiscon) {
//コントローラが接続されていないとき
		pad_work_clear(i);		//中身をクリアする
		return;
	}
//アクチュエータ情報取り込みが完了したらパケット内での
//アクチュエータの制御データを設定する位置を指定する
	if(!(padbuf[i].Send)) {
		PadSetAct(port,&(padbuf[i].Motor0),2);
//拡張コントローラ以外のとき
		if(initlevel == PadStateFindCTP1) {
			padbuf[i].Send = 1;
		}
//拡張コントローラのとき
//（アクチュエータ情報の取り込みが完了するまでは呼ばない
		else if(initlevel == PadStateStable) {
//受け付けられたらフラグを立てる
			if(PadSetActAlign(port,align)) {
				padbuf[i].Send = 1;
			}
		}
	}


//	PadSetMainMode(port,0,padbuf[i].Lock);
#if 0
	PadSetMainMode(port,
		PadInfoMode(port,InfoModeCurExOffs,0),
		padbuf[i].Lock);
#endif
//コントローラが差し替えられたり、端末種別が切り替えられ
//たりしてライブラリがコントローラ情報をアクセスしに行ったとき
//  アクチュエータの設定位置情報送信済みフラグをクリアする
	if(initlevel == PadStateFindPad) {
		padbuf[i].Send = 0;
	}
}
//----------------------------------------------------------------
//	パッドのワーククリア
//----------------------------------------------------------------
void	pad_work_clear(Uint16 num)
{
	Uint16 j;
	
	
	Pad[num].id = 0;
	Pad[num].dat =
	Pad[num].trg =
	Pad[num].rpt =
	Pad[num].old = 0;
	for(j = 0 ; j < 16 ; j++)	{
		Pad[num].timer[j] = 0;
	}
	Pad[num].analog1 =
	Pad[num].analog2 =
	Pad[num].analog3 =
	Pad[num].analog4 = 0x80;
	
	Pad[num].analogdat = 
	Pad[num].analogtrg = 0;

//	check
	padbuf[num].Lock = 0;			//2 unlock 3 lock
	padbuf[num].Send = 0;
	padbuf[num].act_timer0 = 0;
	padbuf[num].act_flag0 = 0;
	padbuf[num].act_timer1 = 0;
	padbuf[num].act_flag1 = 0;
	padbuf[num].Motor0 = 0x0;
	padbuf[num].Motor1 = 0x0;


}


//------------------------------------------------------------------
//	振動のセット
//	motor0の振動セット
//	num port No 0,1
//------------------------------------------------------------------
void	sindo_set(Uint16 num,Sint16 time)
{
	Uint16	port;

	if(gcb.actuator == 0)	return;
	if(num == 0)	{
		port = 0;
	}
	else	{
		port = 0x10;
	}
	if(padbuf[num].act_flag0 == 0)	{
		if(PadInfoMode(port,InfoModeCurExID,0)) {
			if(padbuf[num].Motor0 == 0)	{
				padbuf[num].Motor0 = 1;
			}
			padbuf[num].act_timer0 = time;
			padbuf[num].act_flag0 = 1;
		}
		else	{
//SCPH-1150のアクチュエータ(振動子)の値設定 */
			padbuf[num].Motor0 = 0x40;
			padbuf[num].Motor1 += 1;
			padbuf[num].act_timer0 = time;
			padbuf[num].act_flag0 = 1;
		}
	}
}


//------------------------------------------------------------------
//	振動のセット
//	motor1の振動セット
//	num port No 0,1
//------------------------------------------------------------------
void	sindo_set2(Uint16 num, Sint16 level, Sint16 time)
{
	Uint16	port;

	if(gcb.actuator == 0)	return;
	if(num == 0)	{
		port = 0;
	}
	else	{
		port = 0x10;
	}
	if(padbuf[num].act_flag1 == 0)	{
		if(PadInfoMode(port,InfoModeCurExID,0)) {
			padbuf[num].Motor1 = level;
			padbuf[num].act_timer1 = time;
			padbuf[num].act_flag1 = 1;
		}
		else	{
//SCPH-1150のアクチュエータ(振動子)の値設定 */
			padbuf[num].Motor0 = 0x40;
			padbuf[num].Motor1 += 1;
			padbuf[num].act_timer1 = time;
			padbuf[num].act_flag1 = 1;
		}
	}
}

//------------------------------------------------------------------------
//	コントローラのモードをセットする
//	port 0, 0x10
//	mode 0,1
//------------------------------------------------------------------------
void	set_control_mode(Uint8 port, Uint8 mode)
{
	Uint16	i;
	Sint16	kaisuu;

	kaisuu = 0;
	if(port == 0)	{
		i = 0;
	}
	else	{
		i = 1;
	}
	if(mode == 0) {
		while(1)	{
			PadGet();				//	コントローラの値の取り出し
			VSync(0);
			kaisuu++;
			if(kaisuu >= 10)	return;
			if(PadSetMainMode(port,0,padbuf[i].Lock) == 1)	{
				return;		//DEGITAL
			}
			else return;
		}
	}
	else  {
		while(1)	{
			PadGet();				//	コントローラの値の取り出し
			VSync(0);
			kaisuu++;
			if(kaisuu >= 10)	return;
			if(PadSetMainMode(port,1,padbuf[i].Lock) == 1)	{
				return;			//ANALOG
			}
		}
	}
}



