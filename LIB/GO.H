/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫ゲー（仮）"                                 */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : test                                                   */
/*  File Name     : GO.H                                                   */
/*                                                           by H.TATEYAMA */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _GO_H_
#define _GO_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  Include File(s)                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#include <libcd.h>
#include <libpad.h>


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  マクロ & 置換 & 変数他                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
//#define  CD_VER              1
#define  BLOCKTURN           0 // 赤沢氏 XA 対応までは１にする事 
#define  PACK_INF_ADDR       0x80100000     // (2048 = 0x800)
#define  TC_INF_ADDR         0x80100800     // (2048 = 0x800)
#define  CH_TIM_ADDR         0x80101000     // (203360 = 0x31a60)
#define  CH_CLT_ADDR         CH_TIM_ADDR
#define  CH_PIX_ADDR         (CH_TIM_ADDR+5852) // 532*11 <- 532 * 11chara 
#define  EVENT_DATA          0x80140000
#define  EVENT_ADDRESS       EVENT_DATA               // 0x80140000 ↓ inf file が 0x2000(8192)以下 
#define  EVT_DATA_ADDRESS    (EVENT_DATA+0x00002000)  // 0x80142000 ↓ dat file が 0xE000(57344)以下 
#define  EVT_BUFF_ADDRESS    (EVENT_DATA+0x00009000)  // 0x80150000 ↓ 1event   が 0x2000 以下 
#define  HITPOS_ADDR         0x8015e000     // 0x640(1600) 
#define  MSG_ADDR            0x80160000     // メッセージバッファ(0x1f380)('98 11/9 最大14336 = 0x3800) 
#define  TALK_CHARA_ADDR     0x8017f380     // 0x640(1600) 
#define  TALK_CHARA_ADDR2    0x8017f9c0     // 0x640(1600) 
#define  TIM_ADDR            0x80180000
//#define  STATIC_ADDR         0x801E0000     // static mem 
// 固定↓ 
#define  RESULT_ADDR         0x801EF000     // result (32byte) 
#define  MAP_SHOP_ADDR       0x801EF9EA     // shop (虫ゼリー他) 
#define  EVT_FLAG_ADDR       0x801EF800     // event flag addr 
#define  CARD_ADDR           0x801EF9F8     // card 
#define  MONTH_ADDR          0x801EF9FD     // month 
#define  DAY_ADDR            0x801EF9FE     // day 
#define  WEEK_ADDR           0x801EF9FF     // 総日数 
#define  ISONO_ADDR          0x801EFA00     // 磯野氏 
#define  SOUNND_ADDR         0x801F0000     // sound 

#define toFIXED(a)      ((FIXED)(4096.0 * (a)))
#define toFIXED16(a)    ((FIXED)(65536.0 * (a)))
#define DEGtoANG(d)     ((ANGLE)((4096.0 * (d)) / 360.0))
#define DEGtoANG2(d)    ((long)((1474560.0 * (d)) / 360.0))
#define DEGtoANG3(d)    (long)((65536.0 * (d) / 360))
#define PAD_U           PADLup
#define PAD_D           PADLdown
#define PAD_L           PADLleft
#define PAD_R           PADLright
#define PAD_SANKAKU     PADRup
#define PAD_BATU        PADRdown
#define PAD_SIKAKU      PADRleft
#define PAD_MARU        PADRright
#define PAD_L1          PADL1
#define PAD_L2          PADL2
#define PAD_R1          PADR1
#define PAD_R2          PADR2
#define PAD_ST          PADstart
#define PAD_SEL         PADselect
#define PAD_CROSS       (PAD_U|PAD_D|PAD_L|PAD_R)
#define BIT1            1<<1
#define BIT2            1<<2
#define BIT3            1<<3
#define BIT4            1<<4
#define BIT5            1<<5
#define BIT6            1<<6
#define BIT7            1<<7
#define BIT8            1<<8
#define BIT9            1<<9
#define BIT11           1<<11
#define BIT12           1<<12
#define BIT13           1<<13
#define BIT14           1<<14
#define BIT15           1<<15
#define BIT16           1<<16
#define BIT17           1<<17
#define BIT18           1<<18
#define BIT19           1<<19
#define BIT20           1<<20
#define BIT21           1<<21
#define BIT22           1<<22
#define BIT23           1<<23
#define BIT24           1<<24
#define BIT25           1<<25
#define BIT26           1<<26
#define BIT27           1<<27
#define BIT28           1<<28
#define BIT29           1<<29
#define BIT30           1<<30
#define BIT31           1<<31

#define McrGsSprSet( atr, xx, yy, ww, hh, tpa, uu, vv, clx, cly, rr, gg, bb, mix, miy, scx, scy, rot) \
    ((GsSPRITE *)(gsSpr))->attribute = (atr); \
    ((GsSPRITE *)(gsSpr))->x = (xx); \
    ((GsSPRITE *)(gsSpr))->y = (yy); \
    ((GsSPRITE *)(gsSpr))->w = (ww); \
    ((GsSPRITE *)(gsSpr))->h = (hh); \
    ((GsSPRITE *)(gsSpr))->tpage = (tpa); \
    ((GsSPRITE *)(gsSpr))->u = (uu); \
    ((GsSPRITE *)(gsSpr))->v = (vv); \
    ((GsSPRITE *)(gsSpr))->cx = (clx); \
    ((GsSPRITE *)(gsSpr))->cy = (cly); \
    ((GsSPRITE *)(gsSpr))->r = (rr); \
    ((GsSPRITE *)(gsSpr))->g = (gg); \
    ((GsSPRITE *)(gsSpr))->b = (bb); \
    ((GsSPRITE *)(gsSpr))->mx = (mix); \
    ((GsSPRITE *)(gsSpr))->my = (miy); \
    ((GsSPRITE *)(gsSpr))->scalex = (scx); \
    ((GsSPRITE *)(gsSpr))->scaley = (scy); \
    ((GsSPRITE *)(gsSpr))->rotate = (rot);

#define McrGsSprSet2( atr, ww, hh, uu, vv, rr, gg, bb ) \
    ((GsSPRITE *)(gsSpr))->attribute = (atr); \
    ((GsSPRITE *)(gsSpr))->w = (ww); \
    ((GsSPRITE *)(gsSpr))->h = (hh); \
    ((GsSPRITE *)(gsSpr))->u = (uu); \
    ((GsSPRITE *)(gsSpr))->v = (vv); \
    ((GsSPRITE *)(gsSpr))->r = (rr); \
    ((GsSPRITE *)(gsSpr))->g = (gg); \
    ((GsSPRITE *)(gsSpr))->b = (bb);

#define McrGsFastSprSet( atr, xx, yy, ww, hh, tpa, uu, vv, clx, cly, rr, gg, bb) \
    ((GsSPRITE *)(gsSpr))->attribute = (atr); \
    ((GsSPRITE *)(gsSpr))->x = (xx); \
    ((GsSPRITE *)(gsSpr))->y = (yy); \
    ((GsSPRITE *)(gsSpr))->w = (ww); \
    ((GsSPRITE *)(gsSpr))->h = (hh); \
    ((GsSPRITE *)(gsSpr))->tpage = (tpa); \
    ((GsSPRITE *)(gsSpr))->u = (uu); \
    ((GsSPRITE *)(gsSpr))->v = (vv); \
    ((GsSPRITE *)(gsSpr))->cx = (clx); \
    ((GsSPRITE *)(gsSpr))->cy = (cly); \
    ((GsSPRITE *)(gsSpr))->r = (rr); \
    ((GsSPRITE *)(gsSpr))->g = (gg); \
    ((GsSPRITE *)(gsSpr))->b = (bb);

#define McrGsLineSet( atr, x, y, xx, yy, rr, gg, bb ) \
    ((GsLINE *)(gsLine))->attribute = (atr); \
    ((GsLINE *)(gsLine))->x0 = (x); \
    ((GsLINE *)(gsLine))->y0 = (y); \
    ((GsLINE *)(gsLine))->x1 = (xx); \
    ((GsLINE *)(gsLine))->y1 = (yy); \
    ((GsLINE *)(gsLine))->r = (rr); \
    ((GsLINE *)(gsLine))->g = (gg); \
    ((GsLINE *)(gsLine))->b = (bb);

typedef  void(*task)();    // taskは関数型と定義


#ifndef _YUMA_H_
#define _YUMA_H_
//  ＰＳライブラリーをＳＧＬライクに使うためのマクロ
typedef unsigned char   Uint8 ;   /* 符号なし１バイト整数 */
typedef signed   char   Sint8 ;   /* 符号つき１バイト整数 */
typedef unsigned short  Uint16 ;  /* 符号なし２バイト整数 */
typedef signed   short  Sint16 ;  /* 符号つき２バイト整数 */
typedef unsigned long   Uint32 ;  /* 符号なし４バイト整数 */
typedef signed   long   Sint32 ;  /* 符号つき４バイト整数 */
typedef float           Float32 ; /* ４バイト実数 */
typedef double          Float64 ; /* ８バイト実数 */
typedef Sint32          FIXED ;   /* 上位１６ビットで整数部、下位１６ビットで小数部を表す固定小数点型 */
typedef short           ANGLE;

enum {
    X,
    Y,
    Z,
    XYZ,
    XY = 2,
    XYZD = 4,
};
#endif

enum {
    R,
    G,
    B,
    RGB,
};


#endif


