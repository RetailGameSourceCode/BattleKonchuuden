
/*----------------------------------------------------------------------------+
|                                                                             |
|     Name   :                                                                |
| Description:                                                                |
|                                                                             |
|   Parameter:                                                                |
|                                                                             |
|Return Value:                                                                |
|                                                                             |
|     Version:                                                                |
|                                                                             |
|  Search Key:                                                                |
|                                                                             |
|                                   1996-07-29 (Mon) 16:04:33        Ver 0.05 |
|                                              Copyright (C) 1996 Indick-Czar |
+----------------------------------------------------------------------------*/

#if !defined _CZARSPRT_H_
#define _CZARSPRT_H_
/*----------------------------------------------------------------------------+
|    Include File                                                             |
+----------------------------------------------------------------------------*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*----------------------------------------------------------------------------+
|    Constant Declaration                                                     |
+----------------------------------------------------------------------------*/
enum {
	CZS_EOD = 0x80,
	CZS_TP = 0x40,
	CZS_HF = 0x20,
	CZS_VF = 0x10,
};

enum {
	CZA_EOD = 0x80,
	CZA_LOOP = 0x40,
};

/*----------------------------------------------------------------------------+
|    Data Type Declaration                                                    |
+----------------------------------------------------------------------------*/
typedef struct {
	unsigned long code[4];
} CZCODE;

typedef struct {
	  signed short  x0, y0;

	unsigned char u0, v0;
	unsigned short clut;

	unsigned short w, h;

	unsigned short tpage;
	unsigned char flg;
	unsigned char code;
} CZSPRT;

typedef struct {
	  signed short x0, y0;
	unsigned short w, h;
	unsigned long rfu0;

	unsigned char rfu1;
	unsigned char rfu2;
	unsigned char flg;
	unsigned char code;
} CZTILE;					/* free size Tile */

typedef struct {
	short   x, y;

	unsigned char w, h;
	unsigned char u, v;

	short   cx, cy;

	unsigned char tp;
	unsigned char rfu;
	unsigned char flg;
	unsigned char code;
} CZSPRITE;

typedef union {
	CZCODE c;
	CZSPRITE p;
	CZSPRT s;
	CZTILE t;
} CzAnimData;

typedef struct {
	unsigned short n;						/* キャラクターナンバー */
	unsigned char fc;						/* フレーム数 */
	unsigned char flg;						/* 終了判定などのフラグ */
} CzAnimNo;

typedef struct {
	CzAnimData *add;						/* Character Sequence Data Table */
	CzAnimNo *p;							/* Character Number */
	unsigned char fc;						/* Frame Counter */
	unsigned char ac;						/* Animation Counter */
	unsigned char pri;						/* Priority */
	unsigned char flag;						/* Animaition Flag */
} CzANIM;

struct CZAR_LCOORDINATE {								  /* Czar Coordinate */
	signed int x;												/* x (16:16) */
	signed int y;												/* y (16:16) */
	signed int z;												/* z (16:16) */
};

struct CZAR_SCOORDINATE {						/* Czar Short Coordinate */
	unsigned short xl;										/* decimal */
	signed short xh;							/* integer */
	unsigned short yl;										/* decimal */
	signed short yh;							/* integer */
	unsigned short zl;										/* decimal */
	signed short zh;							/* integer */
};

typedef union {
	struct CZAR_LCOORDINATE l;
	struct CZAR_SCOORDINATE s;
} CzXYZ;

typedef struct {
	unsigned long atr;						/* Attribute */
	CzXYZ pos;								/* 3Dimention Coordinate x, y, z */

	signed short sx, sy;					/* Scale Value */

	unsigned char r, g, b, a;				/* rgb Value and Flag */
	long rot;								/* Rotation Value */
	CzANIM anim;							/* Animation Structure */
} CzSPRITE;

/*----------------------------------------------------------------------------+
|    Prototype Declaration                                                    |
+----------------------------------------------------------------------------*/
void CzSortSpriteInit(void);
void CzSortSprite(CzSPRITE *p, GsOT *otp);
signed int CzAnimation(CzANIM *p);
void CzSpriteSetPriority(unsigned short n);

/*----------------------------------------------------------------------------+
|    Global Variable Declaration                                              |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Macro Declaration                                                        |
+----------------------------------------------------------------------------*/
// 各マクロパラメータの説明 
//  x : Offset x
//  y : Offset y
//  u : U
//  v : V
//  w : Width 
//  h : Hight
//  cx: CLUT x pos
//  cy: CLUT y pos
//  tp: Texture Page
// dfe: 
// dtd: 
// abr: Ambient Rate
//  tm: Texture Mode(0:4bit 1:8bit 2:16bit)
//   f: Flag 
 




#define CzSPRITE_SET(x, y, u, v, w, h, cx, cy, tp, f) \
	((((-(y)) << 16) & 0xffff0000) | ((-(x)) & 0x0000ffff)), \
	((((v)   << 24) & 0xff000000) | (((u) << 16) & 0x00ff0000) | \
	(((h) << 8) & 0x0000ff00) | ((w) & 0x000000ff)), \
	((((cy) << 16) & 0xffff0000) | ((cx) & 0x0000ffff)), \
	(((0)   << 24) | (((f) << 16) & 0x00ff0000) | ((0) << 8) | ((tp) & 0x000000ff))


#define CzSPRT_SET(x, y, u, v, w, h, cx, cy, tp, dfe, dtd, abr, tm, f) \
	((y) << 16) | ((x) & 0xffff), \
	((( cy << 6) | ((cx >> 4) & 0x3f)) << 16) | ((v) << 8) | (u), \
	((h) << 16) | (w), \
	((1) << 24) | ((f) << 16) | \
	((dfe & 1) << 10) | ((dtd & 1) << 9) | ((tm & 3) << 7) | ((abr & 3) << 5) | (tp & 0x1f)

#define CzSPRT8_SET(x, y, u, v, cx, cy, tp, dfe, dtd, abr, tm, f) \
	((y) << 16) | ((x) & 0xffff), \
	((( cy << 6) | ((cx >> 4) & 0x3f)) << 16) | ((v) << 8) | (u), \
	(0), \
	((2) << 24) | ((f) << 16) | \
	((dfe & 1) << 10) | ((dtd & 1) << 9) | ((tm & 3) << 7) | ((abr & 3) << 5) | (tp & 0x1f)

#define CzSPRT16_SET(x, y, u, v, cx, cy, tp, dfe, dtd, abr, tm, f) \
	((y) << 16) | ((x) & 0xffff), \
	(((cy << 6) | ((cx >> 4) & 0x3f)) << 16) | ((v) << 8) | (u), \
	(0), \
	((3) << 24) | ((f) << 16) | \
	((dfe & 1) << 10) | ((dtd & 1) << 9) | ((tm & 3) << 7) | ((abr & 3) << 5) | (tp & 0x1f)

#define CzTILE_SET(x, y, w, h, dfe, dtd, abr, f) \
	((y) << 16) | ((x) & 0xffff), \
	((h) << 16) | (w), \
	(0), \
	((4) << 24) | ((f) << 16) | \
	((dfe & 1) << 10) | ((dtd & 1) << 9) | ((abr & 3) << 5)

#endif
