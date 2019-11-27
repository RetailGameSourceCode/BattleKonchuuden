#ifndef _YUMA_H_
#define _YUMA_H_

//	ＰＳライブラリーをＳＧＬライクに使うためのマクロ
typedef unsigned char	Uint8 ;		/* 符号なし１バイト整数 */
typedef signed   char	Sint8 ;		/* 符号つき１バイト整数 */
typedef unsigned short	Uint16 ;	/* 符号なし２バイト整数 */
typedef signed   short	Sint16 ;	/* 符号つき２バイト整数 */
typedef unsigned long	Uint32 ;	/* 符号なし４バイト整数 */
typedef signed   long	Sint32 ;	/* 符号つき４バイト整数 */
typedef float		Float32 ;	/* ４バイト実数 */
typedef double		Float64 ;	/* ８バイト実数 */
typedef Sint32	FIXED ;		/* 上位１６ビットで整数部、下位１６ビットで小数部を表す固定小数点型 */

typedef int		Int ;		/* INT型（ツール用）		*/

typedef int		Bool ;		/* 論理型（論理定数を値にとる）	*/
typedef short	ANGLE;

typedef	void(*task_a)();	// task_aは関数型と定義

#define	    toFIXED(a)		((FIXED)(4096.0 * (a)))
#define	    toFIXED16(a)	((FIXED)(65536.0 * (a)))
#define	    DEGtoANG(d)		((ANGLE)((4096.0 * (d)) / 360.0))
#define	    DEGtoANG2(d)	((long)((1474560.0 * (d)) / 360.0))
#define		DEGtoANG3(d)	(long)((65536.0 * (d) / 360))


enum {
	OFF,
	ON,
};

//	コントローラの定義
//	LIBETC.H
#define PAD_U	PADLup
#define PAD_D	PADLdown
#define PAD_L	PADLleft
#define PAD_R	PADLright
#define PAD_SANKAKU	PADRup
#define PAD_BATU	PADRdown
#define PAD_SIKAKU	PADRleft
#define PAD_MARU	PADRright
#define PAD_L1	PADL1
#define PAD_L2	PADL2
#define PAD_R1	PADR1
#define PAD_R2	PADR2
#define PAD_ST	PADstart
#define PAD_SEL	PADselect

enum {
	X,
	Y,
	Z,
	XYZ,
	XY = 2,
	XYZD = 4,
	D = 3,
};

enum {
	R,
	G,
	B,
	RGB,
};

#define	    SETRGB(r,g,b)		((b)<<10)|((g)<<5)|(r)



//	スプライト定義
#define	COL16	0			//１６色モード
#define	COL256	1<<24		//２５６色モード
#define	COL32K	1<<25		//３２Ｋ色モード
#define	SPRITE_OFF	1<<31	//表示
#define	SPRITE_ON	0<<31	//非表示
#define	CL_Trans	1<<30			//半透明on

#define TRANSLATION(x,y,z)	{toFIXED(x),toFIXED(y),toFIXED(z)}
#define ROTATION(x,y,z)		{DEGtoANG(x),DEGtoANG(y),DEGtoANG(z)}
#define SCALING(x,y,z)		{toFIXED(x),toFIXED(y),toFIXED(z)}

typedef struct obj{
	GsDOBJ2	*pat;			/* ポリゴンモデルデータテーブル */
    FIXED	 pos[XYZ] ;		/* 相対位置データ */
    ANGLE	 ang[XYZ] ;		/* 回転角データ */
    FIXED	 scl[XYZ] ;		/* スケーリングデータ */
    struct obj	*child ;		/* 子オブジェクトデータ */
    struct obj	*sibling ;		/* 兄弟オブジェクトデータ */
} OBJECT ;

//ポリゴンアトリビュート
#define	    UseLight		(0<<6)		//光源の影響を受けるポリゴン 
#define	    NotUseLight		(1<<6)		//光源の影響を受けないポリゴン 
#if 0
enum {
	FALSE,
	TRUE,
};
#endif

#define	SHADOW_OFF	0
#define	SHADOW_ON	1




//	数値演算マクロ
//掛け算
//#define slMulFX(v0,v1)	(((v0) * (v1)) >> 12)
//絶対値
#define ABS(x)	((x) < 0 ? -(x) : (x))
//正接
#define rtan(x)	(((rsin(x)<<12) / rcos(x)))
//割り算
//#define slDivFX(v0,v1)	(((v1) / (v0)) << 12)

typedef struct  {
	u_long *vertop;		/* vertex top address of TMD format */
	u_long  vern;		/* the number of vertex of TMD format */
	u_long *nortop;		/* normal top address of TMD format */
	u_long  norn;		/* the number of normal of TMD format */
	u_long *primtop;	/* primitive top address of TMD format */
	u_long  primn;		/* the number of primitives of TMD format */
	u_long  scale;		/* the scale factor of TMD format */
} TMD_STRUCT2;

typedef struct {
	Sint16	x;
	Sint16	y;
	Sint16	z;
} STRUCT_XYZ;


typedef struct {
	Sint16	x;
	Sint16	y;
} STRUCT_XY;

typedef struct {
	Sint16	x;
	Sint16	y;
	Sint16	w;
	Sint16	h;
} STRUCT_XYWH;

typedef struct {
	Sint16	x1;
	Sint16	y1;
	Sint16	x2;
	Sint16	y2;
} STRUCT_LINE;



#endif


