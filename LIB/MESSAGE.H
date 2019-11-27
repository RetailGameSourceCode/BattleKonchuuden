/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫げー"                                       */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : message 表示                                           */
/*  File Name     : MESSAGE.H                                              */
/*                                                           by H.TATEYAMA */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*  MES WINDOW は FONT.C 内部で LOAD 済み                                  */
/*                                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _MESSAGE_H_
#define _MESSAGE_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#if 0
#define  MSG_ADDR  0x80156800     //メッセージバッファ(0xb000)
#endif

enum {
    CLOSE,
    OPENING,
    OPEN,
    CLOSING,
};

enum {
    MOVE,
    STOP,
};

enum {
    WMSG_OFF,
    WMSG_JUDGE,
    WMSG_WAIT,
    WMSG_END,
    WMSG_SCROOL,
    WMSG_CLOSE,
};

typedef struct {
    unsigned int   id;
    unsigned int   size;
    unsigned int   tnb_msg;
    unsigned int   index[1];
} MESSAGECHUNK, MSG;

typedef struct {
    unsigned short imoji;
    unsigned short ix;
    unsigned short  iy;
    unsigned       col_bit   :4;
    unsigned       size_bit  :2;
    unsigned       rot_bit   :2;
    unsigned       speed_bit :1;
    unsigned       dummy     :7;
} mesdata, MESDATA;

extern char        cMsgSelOk;
extern char        cMesWinSta;
extern char        cMsgOn;
extern char        cMsgSend;
extern short       iMsgSendCount, iMsgSendCountBak;
extern short       iMsgSta, iMsgOn, irot, iMsgNo;
extern short       iWinXdef, iWinYdef, iReqPerm;
extern MESDATA     mes_screen[3][18];


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void msg_init(void);
extern void msg_window_ctrl(void);               // メッセージウィンド管理 
extern void msg_ctrl(void);                      // メッセージ管理 
extern void data_judge(void);                    // データ判断 
extern void request_msg(unsigned short msg);     // 指定メッセージ要求 
extern void msgdata_set(short iNo);              // メッセージデータセット 
extern void screen_init(void);                   // 描画スクリーン初期化 
extern void screen_disp(void);                   // 描画 
extern void msg_close(void);                     // メッセージ強制終了 


#endif


