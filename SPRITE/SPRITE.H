/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SPRITE LIBRARY                                           */
/*  File Attribute: HEADER                                                   */
/*  File Name     : SPRITE.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _SPRITE_H_
#define _SPRITE_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*----- User Header     Files -----*/
#include "../lib/czarsprt.h"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ORDERING TABLE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define SPRITEOT_LENGTH	3		/* オーダリングテーブルの解像度 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SPRITE CONTROLL INFORMATION                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define	SPRITEMAX		(64)
#define	SPRITE3DMAX		(64)
#define	acceleration	(0xc000)			//	移動加減速
#define	zoom_min		(0x000bffff)		//	拡縮収束点
#define	zoom_acc		(0x2000)			//	拡縮加減速
#define	_ZmLT			(0x05 << 8)			/* Zoom base Left Top */
#define	_ZmLC			(0x09 << 8)			/* Zoom base Left Center */
#define	_ZmLB			(0x0d << 8)			/* Zoom base Left Bottom */
#define	_ZmCT			(0x06 << 8)			/* Zoom base Center Top */
#define	_ZmCC			(0x0a << 8)			/* Zoom base Center Center */
#define	_ZmCB			(0x0e << 8)			/* Zoom base Center Bottom */
#define	_ZmRT			(0x07 << 8)			/* Zoom base Right Top */
#define	_ZmRC			(0x0b << 8)			/* Zoom base Right Center */
#define	_ZmRB			(0x0f << 8)			/* Zoom base Right Bottom */
#define	sprNoflip		(0)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SPRITE WORK                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	u_short			status;
	u_short			counter;
	u_short			timer;
	u_short			chr;
	u_short			pal;
	short			angle;
	u_long			pmode;
	u_long			flip;
	long			pos[XYZ];
	long			spd[XYZ];
	long			acc[XYZ];
	long			hzoom;
	long			vzoom;
	long			hzoomsp;
	long			vzoomsp;
	long			hzoomac;
	long			vzoomac;
	short			col[RGB];
} SPRWORK;	//total 78bytes

typedef struct {
	u_short			status;
	u_short			counter;
	u_short			timer;
	u_short			chr;
	short			angle;
	long			pos[XYZ];
	long			spd[XYZ];
	long			acc[XYZ];
	u_long			ft4[2][10];
} SPRITE3D;	//total 86bytes

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GsOT         spriteot[2];							/* Ordering Table                  */
extern GsOT_TAG     spriteot_tag[2][1<<SPRITEOT_LENGTH];	/* オーダリングテーブル実体        */
extern int			SpriteCounter;
extern int			Sprite3dCounter;
extern SPRWORK		sprite[SPRITEMAX];
extern SPRITE3D		spr3d[SPRITE3DMAX];
extern u_char		BGFadeOffset;

extern void SpriteInit(CzAnimData *tbl);
extern SPRWORK* SpriteEntry(u_short pal, u_short chr, SVECTOR *pv, CVECTOR *cp, u_short dir, u_short wait);
extern void SpriteControll();
extern SPRITE3D* Sprite3dEntry(u_short status, u_short pal, u_short chr,  VECTOR *pv);
extern void Sprite3dControll();
extern void SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize);
extern void DispSpriteGs(SPRWORK *spp);
extern void DispSpriteGs3D(SPRWORK *spp);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _SPRITE_H_ */
