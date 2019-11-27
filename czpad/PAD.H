#ifndef _PAD1_H_
#define _PAD1_H_

extern	void setPad(int port, Uint8 *rxbuf);
extern	void	pad_work_clear(Uint16 num);
extern	void	sindo_set(Uint16 num,Sint16 time);
extern	void	sindo_set2(Uint16 num, Sint16 level, Sint16 time);
extern	void	set_control_mode(Uint8 port, Uint8 mode);
extern	void	checkPad(int port, Uint8 *rxbuf);


//	しんどーに対応するための構造体
typedef struct {
	unsigned char Lock;	// コントローラの切り替えスイッチロック状態
	unsigned char Motor0;
	unsigned char Motor1;	//	アクチュエータ(振動子)にセットする値
	unsigned char Send;	//アクチュエータ(振動子)制御データ送信位置設定関数コール済みフラグ
	Sint16	act_timer0;		//モーター０の振動用
	Sint16	act_flag0;		//モーター０の振動用
	Sint16	act_timer1;		//モーター１の振動用
	Sint16	act_flag1;		//モーター１の振動用
} PAD_BUF;



void	sindo_set(Uint16 num,Sint16 time);
void	sindo_set2(Uint16 num, Sint16 level, Sint16 time);

extern	PAD_BUF	padbuf[2];
extern	Uint8 padbuff[2][34];


#endif
