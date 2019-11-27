/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON SUBROUTINE                                       */
/*  File Attribute: HEADER                                                   */
/*  File Name     : POLY_SUB.H                                               */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _POLY_SUB_H_
#define _POLY_SUB_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  POLYGON EFFECT                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define	EFFECTMAX		(256)

typedef struct {
	u_short			status;
	u_short			counter;
	u_short			timer;
	u_short			chr;
	long			pos[XYZ];
	long			spd[XYZ];
	short			ang[XYZ];
	u_short			col[RGB];
	SVECTOR			wv[4];
	GsCOORDINATE2	coord;
} EFEWORK;	//total 82bytes

#define	POLYEFEMAX		(16)

typedef struct {
	u_short			status;
	u_short			counter;
	u_short			timer;
	u_short			chr;
	long			pos[XYZ];
	GsDOBJ2			object;					/* オブジェクトハンドラ オブジェクトの数だけ必要 */
	GsCOORDINATE2	objpos;					/* オブジェクトごとの座標系 */
	SVECTOR			objang;					/* 座標系を作るためのローテーションベクター */
	VECTOR			objscl;					/* オブジェクトのスケール */
} POLYEFE;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern short EffectCounter;
extern EFEWORK efe[EFFECTMAX];
extern short PolyefeCounter;
extern POLYEFE pefe[POLYEFEMAX];
extern short zanzo_first[4];
extern SVECTOR zvec[4][4];

extern void get_parts_ws_val(GsCOORDINATE2 *coord, VECTOR *trans, SVECTOR *ang, VECTOR *vec);
extern void kage_set(MODEL *mod, GsOT *ot);
extern EFEWORK* EffectEntry(u_short status, VECTOR *pv, SVECTOR *av, CVECTOR *cv);
extern EFEWORK* EffectEntry_R(u_short status, VECTOR *pv, SVECTOR *av, CVECTOR *cv, EFEWORK *spp);
extern void EffectControll();
extern POLYEFE* PolyefeEntry(u_short status, u_short chrno, VECTOR *pv, SVECTOR *av);
extern void PolyefeControll();
extern void zanzo_entry(short bank, VECTOR *vec0, VECTOR *vec1, CVECTOR *cvec);
extern void Poly4Set(u_long tpage, short clut, POL4 *pol4, GsOT *ot);
extern void lensflare(VECTOR *sunpos);
extern void lensflare_y(SVECTOR *sunpos);
extern void LineSet(SVECTOR *p0, SVECTOR *p1);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _POLY_SUB_H_ */
