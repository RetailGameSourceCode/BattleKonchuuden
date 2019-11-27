/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON SUBROUTINE                                       */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : POLY_SUB.C                                               */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>
#include <inline_c.h>
#include <gtemac.h>

/*----- User Header     Files -----*/
#include "../lib/libctl.h"
#include "../lib/aki_def.h"
#include "../lib/address.h"
#include "../lib/lz.h"
#include "../lib/grpara.h"
#include "../lib/polygon.h"
#include "../model/spadstk.h"	/* for Scratch Pad Stack */
#include "../p01/poly_sub.h"
#include "../p01/battle.h"
#include "../p01/anmdata.h"
#include "../p01/bg.h"
#include "../redlib/sndno.h"
#include "../sprite/sprite.h"

short EffectCounter;
EFEWORK efe[EFFECTMAX];
short PolyefeCounter;
POLYEFE pefe[POLYEFEMAX];
short zanzo_first[4];
SVECTOR zvec[4][4];

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	パーツの種類からワールド座標をもとめる
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void get_parts_ws_val(GsCOORDINATE2 *coord, VECTOR *trans, SVECTOR *ang, VECTOR *vec)
{
	struct {
		MATRIX	tmpmat;
		GsCOORDINATE2	coord2;
		SVECTOR	svec;
		long	flag;
		VECTOR	vec0;
	} *sc = (void *)getScratchAddr(0);

	PushMatrix();

	memcpy(&sc->coord2,coord,sizeof(GsCOORDINATE2));

	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	if(ang != NULL)	{
		RotMatrixYXZ(ang, &(sc->coord2.coord));
	}
	sc->coord2.flg = 0;
	GsGetLw(&sc->coord2,&sc->tmpmat);
	
	if(trans != NULL)	{
		gte_SetTransMatrix(&sc->tmpmat);
		gte_SetRotMatrix(&sc->tmpmat);
		
		sc->svec.vx = (Sint16)(trans->vx);
		sc->svec.vy = (Sint16)(trans->vy);
		sc->svec.vz = (Sint16)(trans->vz);
	
		gte_RotTrans(&sc->svec, &sc->vec0, &sc->flag);
	
		vec->vx = (FIXED)(sc->vec0.vx << 12);
		vec->vy = (FIXED)(sc->vec0.vy << 12);
		vec->vz = (FIXED)(sc->vec0.vz << 12);
	}
	else	{
		vec->vx = (FIXED)(sc->tmpmat.t[X] << 12);
		vec->vy = (FIXED)(sc->tmpmat.t[Y] << 12);
		vec->vz = (FIXED)(sc->tmpmat.t[Z] << 12);
	}
	PopMatrix();
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  KAGE SET                                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
// 40x128 -> 300x960
const SVECTOR kage[] = {
	{  300,    0, -550},
	{    0,    0, -550},
	{  300,    0,  -70},
	{    0,    0,  -70},

	{  300,    0,  -70},
	{    0,    0,  -70},
	{  300,    0,  409},
	{    0,    0,  409},

	{    0,    0, -550},
	{ -299,    0, -550},
	{    0,    0,  -70},
	{ -299,    0,  -70},

	{    0,    0,  -70},
	{ -299,    0,  -70},
	{    0,    0,  409},
	{ -299,    0,  409},
};

#define KAGE_CLUTX	0
#define KAGE_CLUTY	482

const u_long kage_tpage[] = {
	(( ((KAGE_CLUTY << 6) | (KAGE_CLUTX >> 4)) << 16) | ( 0 << 8) | 176),	// CLUT  v0 u0
	(( ((2 << 5) | (492 >> 6)) << 16) | ( 0 << 8) | 215),	// TPAGE v1 u1
	(( 63 << 8) | 176),	// v2 u2
	(( 63 << 8) | 215),	// v3 u3

	(( ((KAGE_CLUTY << 6) | (KAGE_CLUTX >> 4)) << 16) | (64 << 8) | 176),	// CLUT  v0 u0
	(( ((2 << 5) | (492 >> 6)) << 16) | (64 << 8) | 215),	// TPAGE v1 u1
	((127 << 8) | 176),	// v2 u2
	((127 << 8) | 215),	// v3 u3

	(( ((KAGE_CLUTY << 6) | (KAGE_CLUTX >> 4)) << 16) | ( 0 << 8) | 215),	// CLUT  v0 u0
	(( ((2 << 5) | (492 >> 6)) << 16) | ( 0 << 8) | 176),	// TPAGE v1 u1
	(( 63 << 8) | 215),	// v2 u2
	(( 63 << 8) | 176),	// v3 u3

	(( ((KAGE_CLUTY << 6) | (KAGE_CLUTX >> 4)) << 16) | (64 << 8) | 215),	// CLUT  v0 u0
	(( ((2 << 5) | (492 >> 6)) << 16) | (64 << 8) | 176),	// TPAGE v1 u1
	((127 << 8) | 215),	// v2 u2
	((127 << 8) | 176),	// v3 u3
};

void kage_set(MODEL *mod, GsOT *ot)
{
	struct {
		SVECTOR	Rotx;
		MATRIX  tmpmatls;
		VECTOR	Trnsx;
		GsCOORDINATE2 coord;
	} *sc = (void *)getScratchAddr(0);

	register long *tag;
	register u_long *si_env  = (u_long *) GsOUT_PACKET_P;
	int i;
	long flg, otz;

	/* プレイヤーのマトリックスをセット */

	GsInitCoordinate2(WORLD, &sc->coord);
	sc->Trnsx.vx = (mod->pos[X] >> 12);
	sc->Trnsx.vy = 0;
	sc->Trnsx.vz = (mod->pos[Z] >> 12);
	get_parts_ws_val(&mod->objpos[1], NULL, NULL, &sc->Trnsx);
	sc->Trnsx.vx >>= 12;
	sc->Trnsx.vz >>= 12;
	sc->Trnsx.vy = 0;
	TransMatrix(&(sc->coord.coord), &sc->Trnsx);	// Ｙ軸を０に固定
	sc->Rotx.vz = 0;
	sc->Rotx.vy = mod->ang[Y];
	sc->Rotx.vx = 0;
	RotMatrixYXZ_gte(&sc->Rotx, &(sc->coord.coord));	// 常に水平
	sc->coord.flg = 0;
	GsGetLs(&sc->coord, &sc->tmpmatls);
	GsSetLsMatrix(&sc->tmpmatls);

	/* ポリゴンの登録(POLY_FT4) */

	for (i = 0; i < 16; i += 4) {
		gte_ldv3(&kage[i+0], &kage[i+1], &kage[i+2]);
		gte_rtpt();			/* RotTransPers3 */

		si_env[1] = (u_long)((0x2e << 24) | (0xc0 << 16) | (0xc0 << 8) | 0xc0);	// 影の濃さ
		si_env[3] = kage_tpage[i+0] + ((mod->status * 8) << 22);
		si_env[5] = kage_tpage[i+1] + ((mod->status * 4) << 16);
		si_env[7] = kage_tpage[i+2];
		si_env[9] = kage_tpage[i+3];

		gte_stflg(&flg);
		if (flg & 0x80000000) continue;
		gte_nclip();		/* NormalClip */
		gte_stopz(&otz);	/* back clip */
		if (otz <= 0) continue;

		gte_stsxy3_ft4((u_long *) si_env);	// si_env[2,4,6]

		gte_ldv0(&kage[i+3]);
		gte_rtps();			/* RotTransPers4 */
		gte_stsxy((u_long *) &si_env[8]);

		tag = (u_long *) (ot->org);
		si_env[0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
		*tag = ((u_long) si_env << 8) >> 8;

		si_env += 10;
	}
	GsOUT_PACKET_P = (PACKET *) si_env;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ポリゴンエフェクトエントリー                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
EFEWORK* EffectEntry(u_short status, VECTOR *pv, SVECTOR *av, CVECTOR *cv)
{
	register	EFEWORK	*spp = efe;

	if (EffectCounter >= EFFECTMAX) return (-1);
	while (spp->status) spp++;

	spp->status = status;
	spp->counter = 0;
	spp->timer = 0;
	spp->chr = 0;
	spp->spd[X] = 0;
	spp->spd[Y] = 0;
	spp->spd[Z] = 0;
	if (pv != NULL) {
		spp->pos[X] = pv->vx;
		spp->pos[Y] = pv->vy;
		spp->pos[Z] = pv->vz;
	} else {
		spp->pos[X] = 0;
		spp->pos[Y] = 0;
		spp->pos[Z] = 0;
	}
	if (av != NULL) {
		spp->ang[X] = av->vx;
		spp->ang[Y] = av->vy;
		spp->ang[Z] = av->vz;
	} else {
		spp->ang[X] = 0;
		spp->ang[Y] = 0;
		spp->ang[Z] = 0;
	}
	if (cv != NULL) {
		spp->col[R] = cv->r;
		spp->col[G] = cv->g;
		spp->col[B] = cv->b;
	} else {
		spp->col[R] = 0;
		spp->col[G] = 0;
		spp->col[B] = 0;
	}
	GsInitCoordinate2(WORLD, &spp->coord);

	EffectCounter++;
	return (EFEWORK *) spp;
}


EFEWORK* EffectEntry_R(u_short status, VECTOR *pv, SVECTOR *av, CVECTOR *cv, EFEWORK *spp)
{
	while (spp->status) {
		spp--;
		if (spp < (EFEWORK *) &efe) return (-1);
	}
	spp->status = status;
	spp->counter = 0;
	spp->timer = 0;
	spp->chr = 0;
	spp->spd[X] = 0;
	spp->spd[Y] = 0;
	spp->spd[Z] = 0;
	if (pv != NULL) {
		spp->pos[X] = pv->vx;
		spp->pos[Y] = pv->vy;
		spp->pos[Z] = pv->vz;
	} else {
		spp->pos[X] = 0;
		spp->pos[Y] = 0;
		spp->pos[Z] = 0;
	}
	if (av != NULL) {
		spp->ang[X] = av->vx;
		spp->ang[Y] = av->vy;
		spp->ang[Z] = av->vz;
	} else {
		spp->ang[X] = 0;
		spp->ang[Y] = 0;
		spp->ang[Z] = 0;
	}
	if (cv != NULL) {
		spp->col[R] = cv->r;
		spp->col[G] = cv->g;
		spp->col[B] = cv->b;
	} else {
		spp->col[R] = 0;
		spp->col[G] = 0;
		spp->col[B] = 0;
	}
	GsInitCoordinate2(WORLD, &spp->coord);

	EffectCounter++;
	return (EFEWORK *) spp;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	ポリゴンエフェクトシステム
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
const SVECTOR qu[] = {
	{   40,    0,  -40},
	{  -40,    0,  -40},
	{   40,    0,   40},
	{  -40,    0,   40},
	{    0, 4096,    0},
	{  160, -160,    0},
	{ -160, -160,    0},
	{  160,  160,    0},
	{ -160,  160,    0},
	{    0, 4096,    0},
	{    0,    0,-4096},
	{    0,    0, 4096},
};

void EffectControll()
{
	struct {
		MATRIX  tmpmatls,tmpmatws;
		MATRIX m;
		VECTOR h, r;
		VECTOR	Trnsx;
		VECTOR	Scalx;
		SVECTOR	Rotx;
		SVECTOR wv;
		CVECTOR cv;
	} *sc = (void *)getScratchAddr(0);
	register	long *tag;
	register	EFEWORK *spp = efe;
	register	u_long *packet  = (u_long *) GsOUT_PACKET_P;
	int d0, counter = EffectCounter, i;
	long flg, otz, ll;
	short r,g,b;

	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	for (d0 = 0; d0 < counter; spp++) {
		if (spp->status) d0++;
		switch (spp->status) {
			case 1:		// 残像(POLY_G4)
				ll = 0xf8 - (spp->timer * 12);
				if (++spp->timer == 0x14) {
					spp->status = 0;
					EffectCounter--;
				}
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);
				gte_ldv3c( &spp->wv[0]);
				gte_rtpt();			/* RotTransPers3 */
				packet[7] =
				packet[3] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
				ll -= 0x10;
				packet[5] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
				packet[1] = ((0x3a << 24) | packet[5]);
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_stsxy3_g4((u_long *) packet);
				gte_ldv0(&spp->wv[3]);
				gte_rtps();		/* RotTransPers4 */
				gte_stsxy((u_long *) &packet[8]);
				gte_stszotz(&otz);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[9] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[10] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x08000000);
				*tag = ((u_long) &packet[9] << 8) >> 8;
				packet += 11;
				break;
			case 2:		// さくらの花びら(POLY_FT4)
				if (spp->counter == 0) {
					spp->ang[Y] = (rand() % 4096);
					spp->spd[Y] = 8 << 12;
					spp->counter++;
				}
				if (spp->pos[Y] > 0) {
					if (++spp->timer == 0x20) {
						spp->status = 0;
						EffectCounter--;
					}
				} else {
					spp->pos[Y] += spp->spd[Y];
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					sc->m = GsIDMATRIX;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					spp->ang[X] += (sc->r.vx / 64) + (rand() % 8);
					spp->ang[Y] += (sc->r.vy / 32) + (rand() % 8);
					spp->ang[Z] += (sc->r.vz / 64) + (rand() % 8);
					spp->pos[X] += (spp->spd[Y] * sc->r.vx) / 2048;
					spp->pos[Y] -= abs(spp->spd[Y] * sc->r.vy) / 6144;
					spp->pos[Z] += (spp->spd[Y] * sc->r.vz) / 2048;
				}
				sc->Trnsx.vx = (spp->pos[X] >> 12);
				sc->Trnsx.vy = (spp->pos[Y] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				gte_ldv3c(&qu[0]);
				gte_rtpt();			/* RotTransPers3 */
				packet[3] = (long)((510 << 22) | (0 << 8) | 0);
				packet[5] = (long)((((1 << 5) + 30) << 16) | (0 << 8) | 15);
				packet[7] = (long)((15 << 8) | 0);
				packet[9] = (long)((15 << 8) | 15);
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_avsz3();
				gte_stszotz(&otz);
				ll = 0xff - (otz>>4) - (spp->timer<<2);
				if (ll < 0) break;
				packet[1] = ((0x2e << 24) | (ll << 16) | (ll << 8) | ll);
				gte_stotz(&otz);
				gte_stsxy3_ft4((u_long *) packet);
				gte_ldv0(&qu[3]);
				gte_rtps();		/* RotTransPers4 */
				gte_stsxy((u_long *) &packet[8]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				*packet = (u_long)(((*tag << 8) >> 8) | 0x09000000);
				*tag = ((u_long) packet << 8) >> 8;
				packet += 10;
				break;
			case 26:		// さくらの花びら(POLY_FT4)
				if (spp->counter == 0) {
					spp->ang[Y] = (rand() % 4096);
					spp->spd[Y] = 32 << 12;
					spp->counter++;
				}
				if (spp->pos[Y] > toFIXED(10300)) {
					if (++spp->timer == 0x20) {
						spp->status = 0;
						EffectCounter--;
					}
				} else {
					spp->pos[Y] += spp->spd[Y];
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					sc->m = GsIDMATRIX;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					spp->ang[X] += (sc->r.vx / 64) + (rand() % 8);
					spp->ang[Y] += (sc->r.vy / 32) + (rand() % 8);
					spp->ang[Z] += (sc->r.vz / 64) + (rand() % 8);
					spp->pos[X] += (spp->spd[Y] * sc->r.vx) / 8192;
					if (spp->pos[X] <= 50) {
						spp->pos[X] = 50;
						spp->ang[X] += 4096;
					}
					spp->pos[Y] -= abs(spp->spd[Y] * sc->r.vy) / 8192;
					spp->pos[Z] += (spp->spd[Y] * sc->r.vz) / 8192;
				}
				sc->Trnsx.vx = (spp->pos[Y] >> 12);
				sc->Trnsx.vy = -(spp->pos[X] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z] + 1024;
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				gte_ldv3c(&qu[0]);
				gte_rtpt();			/* RotTransPers3 */
				packet[3] = (long)((495 << 22) | ((288 >> 4) << 16) | (0 << 8) | 80);
				packet[5] = (long)((((1 << 5) + 29) << 16) | (0 << 8) | 111);
				packet[7] = (long)((31 << 8) | 80);
				packet[9] = (long)((31 << 8) | 111);
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_avsz3();
				gte_stszotz(&otz);
				ll = 0xff - (otz>>4) - (spp->timer<<2);
				if (ll < 0) break;
				packet[1] = ((0x2e << 24) | (ll << 16) | (ll << 8) | ll);
				gte_stotz(&otz);
				gte_stsxy3_ft4((u_long *) packet);
				gte_ldv0(&qu[3]);
				gte_rtps();		/* RotTransPers4 */
				gte_stsxy((u_long *) &packet[8]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				*packet = (u_long)(((*tag << 8) >> 8) | 0x09000000);
				*tag = ((u_long) packet << 8) >> 8;
				packet += 10;
				break;
			case 3:		// 拡散線(LINE_G2)
				if (spp->counter == 0) {
					spp->ang[X] = 0;
					spp->ang[Y] = ((rand() << 20) >> 20);
					spp->ang[Z] = (rand() & 0x1ff) + 1024;

					spp->ang[X] = ((rand() << 20) >> 20);
					spp->ang[Y] = 0;
					spp->ang[Z] = ((rand() << 20) >> 20);

					spp->spd[Y] = 0;
					spp->spd[Z] = 0;
					spp->counter++;
				}
				if (++spp->timer == 0x10) {
					spp->status = 0;
					EffectCounter--;
				}
				spp->ang[X] += 4;
				spp->ang[Z] += 4;
//				spp->ang[Y] += 16;
				spp->spd[Y] += 0;
				spp->spd[Z] += 50;

				sc->Trnsx.vx = (spp->pos[X] >> 12);
				sc->Trnsx.vy = (spp->pos[Y] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				sc->wv.vx = 0;
				sc->wv.vy = spp->spd[Y];
				sc->wv.vz = 0;
				gte_ldv0(&sc->wv);
				gte_rtps();
				packet[3] = 0;
				gte_stsxy((u_long *) &packet[2]);
				gte_stszotz(&otz);
				ll = 0xff - (otz>>5) - (spp->timer<<4);
				if (ll < 0) break;
				packet[1] = ((0x52 << 24) | ((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
				sc->wv.vy = spp->spd[Z];
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[4]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[5] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[6] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x04000000);
				*tag = ((u_long) &packet[5] << 8) >> 8;
				packet += 7;
				break;
			case 4:		// 集中線(LINE_G2)
				if (spp->counter == 0) {
					spp->ang[X] = ((rand() << 20) >> 20);
					spp->ang[Y] = ((rand() << 20) >> 20);
					spp->ang[Z] = ((rand() << 20) >> 20);
					spp->spd[Y] = 640;
					spp->spd[Z] = 640;
					spp->counter++;
				}
				if (++spp->timer == 0x10) {
					spp->status = 0;
					EffectCounter--;
				}
				spp->spd[Y] -= 10;
				spp->spd[Z] -= 40;
				spp->ang[X] += 8;
				spp->ang[Y] += 8;

				sc->Trnsx.vx = (spp->pos[X] >> 12);
				sc->Trnsx.vy = (spp->pos[Y] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				sc->wv.vx = 0;
				sc->wv.vy = spp->spd[Y];
				sc->wv.vz = 0;
				gte_ldv0(&sc->wv);
				gte_rtps();
#if 0
				packet[1] = ((0x52 << 24) | (0 << 16) | (0 << 8) | 0);
				ll = ((spp->timer<<4) - 1) - (otz>>5);
				if (ll < 0) break;
				packet[3] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
#else
				r = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[R]));
				g = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[G]));
				b = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[B]));
				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;
				packet[3] = ((b << 16) | (g << 8) | r);
				packet[1] = ((0x52 << 24) | (0 << 16) | (0 << 8) | 0);
#endif
				gte_stsxy((u_long *) &packet[2]);
				gte_stszotz(&otz);

				sc->wv.vy = spp->spd[Z];
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[4]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[5] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[6] = (u_long)((0xe1 << 24) | (1 << 9) | ((1 << 5) + 30));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x04000000);
				*tag = ((u_long) &packet[5] << 8) >> 8;
				packet += 7;
				break;
			case 5:		// 画面飛び散り(POLY_FT4)
				spp->counter++;
				ll = (((d0 - 1) / 10) << 3) + 1;
//				ll = 1;
				if (spp->counter == ll) {
					SE_CLR(SE_BREAK);
					SE_ENT(SE_BREAK);
					spp->spd[Y] = -((rand() % 64) + 24) << 12;
					spp->spd[X] = ((rand() % 48) - 24) << 12;
					spp->spd[Z] = ((rand() % 16) + 96) << 12;
				}
				if (spp->counter >= ll) {
					spp->spd[Y] += 2 << 12;
					spp->pos[Y] += spp->spd[Y];
					spp->pos[X] += spp->spd[X];
					spp->spd[Z] -= 1 << 11;
					spp->pos[Z] += spp->spd[Z];
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					sc->m = GsIDMATRIX;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[9], &sc->r);
					spp->ang[X] += (sc->r.vx / 24) + (rand() % 32);
					spp->ang[Y] += (sc->r.vy / 24) + (rand() % 32);
					spp->ang[Z] += (sc->r.vz / 24) + (rand() % 32);
					if (spp->pos[Y] >= (80 << 12)) {
						spp->status = 0;
						EffectCounter--;
					}
				}
				sc->Trnsx.vx = (spp->pos[X] >> 12);
				sc->Trnsx.vy = (spp->pos[Y] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				gte_ldv3c(&qu[5]);
				gte_rtpt();			/* RotTransPers3 */
				ll = d0 - 1;
				packet[1] = ((0x2c << 24) | (0x80 << 16) | (0x80 << 8) | 0x80);
				packet[3] = (long)((510 << 22) | (((ll / 10) * 32) << 8) | (((ll % 10) & 3)* 32));
				packet[5] = (long)((((2 << 7) + (3 << 5) + 5 + (((ll % 10) >> 2) << 1)) << 16) | (((ll / 10) * 32) << 8) | ((((ll % 10) & 3) * 32) + 32));
				packet[7] = (long)(((((ll / 10) * 32) + 32) << 8) | (((ll % 10) & 3) * 32));
				packet[9] = (long)(((((ll / 10) * 32) + 32) << 8) | ((((ll % 10) & 3) * 32) + 32));
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_avsz3();
				gte_stotz(&otz);
				gte_stsxy3_ft4((u_long *) packet);
				gte_ldv0(&qu[8]);
				gte_rtps();		/* RotTransPers4 */
				gte_stsxy((u_long *) &packet[8]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				*packet = (u_long)(((*tag << 8) >> 8) | 0x09000000);
				*tag = ((u_long) packet << 8) >> 8;
				packet += 10;
				break;
#if 0
			case 6:		// 変なグラデ(POLY_G4)
				spp->counter += 4;
				r = (spp->counter + 0x000) & 0x1ff;
				if (r & 0x100) r ^= 0x1ff;
				g = (spp->counter + 0x080) & 0x1ff;
				if (g & 0x100) g ^= 0x1ff;
				b = (spp->counter + 0x100) & 0x1ff;
				if (b & 0x100) b ^= 0x1ff;
				packet[1] = ((0x38 << 24) | (b << 16) | (g << 8) | r);
				r = (spp->counter + 0x180) & 0x1ff;
				if (r & 0x100) r ^= 0x1ff;
				packet[3] = ((r << 16) | (b << 8) | g);
				g = (spp->counter + 0x000) & 0x1ff;
				if (g & 0x100) g ^= 0x1ff;
				packet[7] = ((g << 16) | (r << 8) | b);
				b = (spp->counter + 0x080) & 0x1ff;
				if (b & 0x100) b ^= 0x1ff;
				packet[5] = ((b << 16) | (g << 8) | r);
				packet[2] = ((-120 << 16) | 0xff60);
				packet[4] = ((-120 << 16) | 0x00a0);
				packet[6] = (( 120 << 16) | 0xff60);
				packet[8] = (( 120 << 16) | 0x00a0);

				tag = (u_long *) (ot[ PSDIDX ].org + (spp->pos[Z] >> (14 - OT_LENGTH)));
				*packet = (u_long)(((*tag << 8) >> 8) | 0x08000000);
				*tag = ((u_long) packet << 8) >> 8;
				packet += 9;
				break;
#endif
			case 7:		// 飛び散り線(LINE_G2)
				if (spp->counter == 0) {
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					sc->m = GsIDMATRIX;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					ll = 48 + (rand() % 32);
					spp->spd[X] = (sc->r.vx * ll);
					spp->spd[Y] = (sc->r.vy * ll);
					spp->spd[Z] = (sc->r.vz * ll);
					sc->wv.vx = (spp->pos[X] >> 12);
					sc->wv.vy = (spp->pos[Y] >> 12);
					sc->wv.vz = (spp->pos[Z] >> 12);
					spp->counter++;
				} else {
					spp->spd[X] -= (spp->spd[X] / 24);
					spp->spd[Z] -= (spp->spd[Z] / 24);
					spp->spd[Y] += (5 << 12);
//					if ((spp->pos[Z] < (300 << 12)) && (spp->pos[Z] > (-300 << 12)) && ((spp->pos[Y] + spp->spd[Y]) > 0)) spp->spd[Y] /= -2;
					if ((spp->pos[Y] + spp->spd[Y]) > 0) spp->spd[Y] /= -2;
					sc->wv.vx = ((spp->pos[X] - spp->spd[X]) >> 12);
					sc->wv.vy = ((spp->pos[Y] - spp->spd[Y]) >> 12);
					sc->wv.vz = ((spp->pos[Z] - spp->spd[Z]) >> 12);
				}
				gte_SetTransMatrix(&GsWSMATRIX);
				gte_SetRotMatrix(&GsWSMATRIX);
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[2]);
				gte_stszotz(&otz);
				spp->pos[X] += spp->spd[X];
				spp->pos[Y] += spp->spd[Y];
				spp->pos[Z] += spp->spd[Z];
				sc->wv.vx = (spp->pos[X] >> 12);
				sc->wv.vy = (spp->pos[Y] >> 12);
				sc->wv.vz = (spp->pos[Z] >> 12);
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[4]);
				r = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[R]));
				g = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[G]));
				b = 0xff - (otz>>4) - (spp->timer<<(2 + spp->col[B]));
				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;
				packet[3] = ((b << 16) | (g << 8) | r);
				r >>= 3;
				g >>= 3;
				b >>= 3;
				packet[1] = ((0x52 << 24) | (b << 16) | (g << 8) | r);
				if (++spp->timer == 0x40) {
					spp->status = 0;
					EffectCounter--;
				}

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[5] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[6] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x04000000);
				*tag = ((u_long) &packet[5] << 8) >> 8;
				packet += 7;
				break;
			case 8:		// ＡＴフィールド(POLY_FT4)
				if (++spp->timer == 0x06) {
					spp->status = 0;
					EffectCounter--;
				}
				ll = 0xa0 - ((spp->timer - 1) << 5);
				if (ll <= 0) break;
				packet[1] = ((0x2e << 24) | (ll << 16) | (ll << 8) | ll);

				spp->pos[X] += spp->spd[X];
				spp->pos[Y] += spp->spd[Y];
				spp->pos[Z] += spp->spd[Z];
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				sc->Trnsx.vx = spp->pos[X] >> 12;
				sc->Trnsx.vy = spp->pos[Y] >> 12;
				sc->Trnsx.vz = spp->pos[Z] >> 12;
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Scalx.vx =
				sc->Scalx.vy =
				sc->Scalx.vz = (spp->timer << 10);
				ScaleMatrix( &(spp->coord.coord), &sc->Scalx);
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				gte_ldv3c(&qu[5]);
				gte_rtpt();			/* RotTransPers3 */
				packet[3] = (long)(((((490 + spp->col[R]) << 6) | (256 >> 4)) << 16) | (0 << 8) | 0);
				packet[5] = (long)((((1 << 5) + 13) << 16) | (0 << 8) | 63);
				packet[7] = (long)((63 << 8) | 0);
				packet[9] = (long)((63 << 8) | 63);
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_stsxy3_ft4((u_long *) packet);
				gte_avsz3();
				gte_stotz(&otz);
				gte_ldv0(&qu[8]);
				gte_rtps();		/* RotTransPers4 */
				gte_stsxy((u_long *) &packet[8]);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				*packet = (u_long)(((*tag << 8) >> 8) | 0x09000000);
				*tag = ((u_long) packet << 8) >> 8;
				packet += 10;
				break;
			case 9:		// 木漏れ日(POLY_G4)
				if (++spp->timer == 0x80) {
					spp->status = 0;
					EffectCounter--;
				}
				sc->m = GsWSMATRIX;
				sc->Scalx.vy = (1 << 12);
				sc->Scalx.vx =
				sc->Scalx.vz = (-1 << 12);
				ScaleMatrix(&sc->m ,&sc->Scalx);
				gte_SetRotMatrix(&sc->m);
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);
				sc->Rotx.vx = (spp->pos[X] >> 12) + 200;
				sc->Rotx.vy = (spp->pos[Y] >> 12);
				sc->Rotx.vz = (spp->pos[Z] >> 12);
				gte_ApplyMatrixSV(&GsIDMATRIX, &sc->Rotx, &sc->wv)
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[6]);
				sc->Rotx.vx = (spp->pos[X] >> 12);
				gte_ApplyMatrixSV(&GsIDMATRIX, &sc->Rotx, &sc->wv)
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[8]);
				sc->Rotx.vx = (spp->pos[X] >> 12) - 400;
				sc->Rotx.vy = (spp->pos[Y] >> 12) - 1000 + (cam.view.vpy / 10);
				gte_ApplyMatrixSV(&GsIDMATRIX, &sc->Rotx, &sc->wv)
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[2]);
				sc->Rotx.vx = (spp->pos[X] >> 12) - 600;
				gte_ApplyMatrixSV(&GsIDMATRIX, &sc->Rotx, &sc->wv)
				gte_ldv0(&sc->wv);
				gte_rtps();
				gte_stsxy((u_long *) &packet[4]);
				gte_stszotz(&otz);
				ll = spp->timer << 2;
				if (ll >= 0xff) ll = 0xff - (ll - 0xff);
				ll += (cam.view.vpy / 16) - (otz>>4);
				if (ll <= 0) break;
				packet[1] = ((0x3a << 24) | (ll << 16) | (ll << 8) | ll);
				ll >>= 1;
				packet[3] = ((ll << 16) | (ll << 8) | ll);
				packet[5] = ((0 << 16) | (0 << 8) | 0);
				packet[7] = ((0 << 16) | (0 << 8) | 0);
				gte_avsz4();
				gte_stotz(&otz);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[9] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[10] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x08000000);
				*tag = ((u_long) &packet[9] << 8) >> 8;
				packet += 11;
				break;
			case 10:	// サンダー(LINE_F4)
			case 11:	// サンダー(LINE_F4)
			case 12:	// サンダー(LINE_F4)
			case 13:	// サンダー(LINE_F4)
#if 0
			case 14:	// サンダー(LINE_F4)
			case 15:	// サンダー(LINE_F4)
			case 16:	// サンダー(LINE_F4)
			case 17:	// サンダー(LINE_F4)
			case 18:	// サンダー(LINE_F4)
			case 19:	// サンダー(LINE_F4)
			case 20:	// サンダー(LINE_F4)
			case 21:	// サンダー(LINE_F4)
			case 22:	// サンダー(LINE_F4)
			case 23:	// サンダー(LINE_F4)
			case 24:	// サンダー(LINE_F4)
#endif
				if (spp->counter == 0) {
					if ((spp->ang[X] == 0) && (spp->ang[Y] == 0) && (spp->ang[Z] == 0)) {
						sc->Rotx.vx = (rand() << 20) >> 20;
						sc->Rotx.vy = (rand() << 20) >> 20;
						sc->Rotx.vz = (rand() << 20) >> 20;
					} else {
						sc->Rotx.vx = spp->ang[X];
						sc->Rotx.vy = spp->ang[Y];
						sc->Rotx.vz = spp->ang[Z];
					}
					spp->wv[0].vx = (spp->pos[X] >> 12);
					spp->wv[0].vy = (spp->pos[Y] >> 12);
					spp->wv[0].vz = (spp->pos[Z] >> 12);
					sc->m = GsIDMATRIX;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					ll = 80 + (rand() % 32);
					spp->spd[X] = (sc->r.vx * ll);
					spp->spd[Y] = (sc->r.vy * ll);
					spp->spd[Z] = (sc->r.vz * ll);
					spp->wv[3].vx = ((spp->pos[X] + spp->spd[X]) >> 12);
					spp->wv[3].vy = ((spp->pos[Y] + spp->spd[Y]) >> 12);
					spp->wv[3].vz = ((spp->pos[Z] + spp->spd[Z]) >> 12);
					sc->Rotx.vx = (rand() << 20) >> 20;
					sc->Rotx.vy = (rand() << 20) >> 20;
					sc->Rotx.vz = (rand() << 20) >> 20;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					ll = 8 + (rand() % 64);
					spp->wv[1].vx = spp->wv[0].vx + ((sc->r.vx * ll) >> 12);
					spp->wv[1].vy = spp->wv[0].vy + ((sc->r.vy * ll) >> 12);
					spp->wv[1].vz = spp->wv[0].vz + ((sc->r.vz * ll) >> 12);
					sc->Rotx.vx = (rand() << 20) >> 20;
					sc->Rotx.vy = (rand() << 20) >> 20;
					sc->Rotx.vz = (rand() << 20) >> 20;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &qu[4], &sc->r);
					ll = 8 + (rand() % 64);
					spp->wv[2].vx = spp->wv[3].vx + ((sc->r.vx * ll) >> 12);
					spp->wv[2].vy = spp->wv[3].vy + ((sc->r.vy * ll) >> 12);
					spp->wv[2].vz = spp->wv[3].vz + ((sc->r.vz * ll) >> 12);
					if (spp->status < 13) {
						sc->Trnsx.vx = (spp->pos[X] + spp->spd[X]);
						sc->Trnsx.vy = (spp->pos[Y] + spp->spd[Y]);
						sc->Trnsx.vz = (spp->pos[Z] + spp->spd[Z]);
						sc->cv.r = spp->col[R];
						sc->cv.g = spp->col[G];
						sc->cv.b = spp->col[B];
						EffectEntry_R( spp->status + 1, &sc->Trnsx, &spp->ang, &sc->cv, spp);	//	自己増殖
					}
					spp->counter++;
				}
				if (++spp->timer == 0x10) {
					spp->status = 0;
					EffectCounter--;
				}
				gte_SetTransMatrix(&GsWSMATRIX);
				gte_SetRotMatrix(&GsWSMATRIX);
				gte_ldv3c(&spp->wv[0]);
				gte_rtpt();
				packet[6] = 0x55555555;
				gte_stflg(&flg);
				if (flg & 0x80000000) break;
				gte_stsxy3c((u_long *) &packet[2]);
				gte_ldv0(&spp->wv[3]);
				gte_rtps();
				gte_stsxy((u_long *) &packet[5]);
				gte_avsz4();
				gte_stotz(&otz);
				r = 0x80 - (otz>>5) - ((spp->timer - 1)<<(4 + spp->col[R]));
				g = 0x80 - (otz>>5) - ((spp->timer - 1)<<(4 + spp->col[G]));
				b = 0x80 - (otz>>5) - ((spp->timer - 1)<<(4 + spp->col[B]));
				if (r < 0) r = 0;
				if (g < 0) g = 0;
				if (b < 0) b = 0;
				packet[1] = ((0x4a << 24) | (b << 16) | (g << 8) | r);

				tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
				packet[7] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
				packet[8] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
				*packet = (u_long)((( *tag << 8) >> 8) | 0x06000000);
				*tag = ((u_long) &packet[7] << 8) >> 8;
				packet += 9;
				break;
			case 25:	// 円形エフェクト(POLY_G3 * 28)
				ll = 0xff - (spp->timer << 4);
				if (++spp->timer == 0x10) {
					spp->status = 0;
					EffectCounter--;
				}
				gte_SetTransMatrix(&GsWSMATRIX);
				gte_SetRotMatrix(&GsWSMATRIX);
				sc->m = GsIDMATRIX;
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
				gte_ApplyMatrix(&sc->m, &qu[10], &sc->r);
				spp->wv[2].vx = spp->pos[X] >> 12;
				spp->wv[2].vy = spp->pos[Y] >> 12;
				spp->wv[2].vz = spp->pos[Z] >> 12;
				r = rsin(spp->timer << 6);
				spp->wv[1].vx = ((sc->r.vx * r) / 49152) + spp->wv[2].vx;
				spp->wv[1].vy = ((sc->r.vy * r) / 49152) + spp->wv[2].vy;
				spp->wv[1].vz = ((sc->r.vz * r) / 49152) + spp->wv[2].vz;
				for (i = 0; i <= 28; i++) {
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = 0;
					sc->Rotx.vy = ((4096 * i) / 28);
					sc->Rotx.vz = 0;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrixSV(&sc->m, &qu[10], &sc->wv);
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &sc->wv, &sc->r);
					spp->wv[0].vx = spp->wv[1].vx;
					spp->wv[0].vy = spp->wv[1].vy;
					spp->wv[0].vz = spp->wv[1].vz;
					spp->wv[1].vx = ((sc->r.vx * r) / 49152) + spp->wv[2].vx;
					spp->wv[1].vy = ((sc->r.vy * r) / 49152) + spp->wv[2].vy;
					spp->wv[1].vz = ((sc->r.vz * r) / 49152) + spp->wv[2].vz;
					gte_SetRotMatrix(&GsWSMATRIX);
					gte_ldv3c( &spp->wv[0]);
					gte_rtpt();			/* RotTransPers3 */
					packet[3] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
					packet[1] = ((0x32 << 24) | packet[3]);
					packet[5] = 0;
					gte_stflg(&flg);
					if ((flg & 0x80000000) == 0) {
						gte_stsxy3_g3((u_long *) packet);
						gte_avsz3();
						gte_stotz(&otz);

						tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
						packet[7] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
						packet[8] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
						*packet = (u_long)((( *tag << 8) >> 8) | 0x06000000);
						*tag = ((u_long) &packet[7] << 8) >> 8;
						packet += 9;
					}
				}
				break;
			case 27:	// 破片エフェクト(POLY_F3)
				ll = 0xff - (spp->timer << 3);
				if (++spp->timer == 0x20) {
					spp->status = 0;
					EffectCounter--;
				}
				if (spp->counter == 0) {
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = ((rand() << 20) >> 23);
					sc->Rotx.vy = ((rand() << 20) >> 23);
					sc->Rotx.vz = 0;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrixSV(&sc->m, &qu[11], &sc->wv);
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &sc->wv, &sc->r);
					r = 16 + (rand() % 32);
					spp->spd[X] = (sc->r.vx * r);
					spp->spd[Y] = (sc->r.vy * r);
					spp->spd[Z] = (sc->r.vz * r);

					spp->wv[0].pad = rand() % 1536;	// ベクトルの長さ
					spp->wv[1].pad = rand() % 1536;
					spp->wv[2].pad = rand() % 1536;
					spp->wv[3].pad = (rand() % 256) - 128;	// 回転速度
					spp->wv[3].vx = (rand() << 20) >> 20;	// ベクトルの向き
					spp->wv[3].vy = (rand() << 20) >> 20;
					spp->wv[3].vz = (rand() << 20) >> 20;
					spp->counter++;
				}
				gte_SetTransMatrix(&GsWSMATRIX);
				gte_SetRotMatrix(&GsWSMATRIX);
				for (i = 0; i < 3; i++) {
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = 0;
					sc->Rotx.vy = 0;
					switch (i) {
						case 0:
							sc->Rotx.vz = spp->wv[3].vx;
							break;
						case 1:
							sc->Rotx.vz = spp->wv[3].vy;
							break;
						case 2:
							sc->Rotx.vz = spp->wv[3].vz;
							break;
					}
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrixSV(&sc->m, &qu[9], &sc->wv);
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &sc->wv, &sc->r);
					spp->wv[i].vx = ((sc->r.vx * spp->wv[i].pad) >> 16) + (spp->pos[X] >> 12);
					spp->wv[i].vy = ((sc->r.vy * spp->wv[i].pad) >> 16) + (spp->pos[Y] >> 12);
					spp->wv[i].vz = ((sc->r.vz * spp->wv[i].pad) >> 16) + (spp->pos[Z] >> 12);
				}
				spp->ang[X] += spp->wv[3].pad;
				spp->ang[Y] += spp->wv[3].pad;
				spp->pos[X] += spp->spd[X];
				spp->pos[Y] += spp->spd[Y];
				spp->pos[Z] += spp->spd[Z];
				gte_SetRotMatrix(&GsWSMATRIX);
				gte_ldv3c( &spp->wv[0]);
				gte_rtpt();			/* RotTransPers3 */
				packet[1] = ((0x22 << 24) | ((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
				gte_stflg(&flg);
				if ((flg & 0x80000000) == 0) {
					gte_stsxy3_f3((u_long *) packet);
					gte_avsz3();
					gte_stotz(&otz);

					tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
					packet[5] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
					packet[6] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
					*packet = (u_long)((( *tag << 8) >> 8) | 0x04000000);
					*tag = ((u_long) &packet[5] << 8) >> 8;
					packet += 7;
				}
				break;
			case 28:	// 円形エフェクト(POLY_G3 * 28)
				ll = 0xff - (spp->timer << 4);
				if (++spp->timer == 0x10) {
					spp->status = 0;
					EffectCounter--;
				}
				gte_SetTransMatrix(&GsWSMATRIX);
				gte_SetRotMatrix(&GsWSMATRIX);
				sc->m = GsIDMATRIX;
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
				gte_ApplyMatrix(&sc->m, &qu[10], &sc->r);
				spp->wv[2].vx = spp->pos[X] >> 12;
				spp->wv[2].vy = spp->pos[Y] >> 12;
				spp->wv[2].vz = spp->pos[Z] >> 12;
				r = rsin(spp->timer << 6);
				spp->wv[1].vx = ((sc->r.vx * r) >> 15) + spp->wv[2].vx;
				spp->wv[1].vy = ((sc->r.vy * r) >> 15) + spp->wv[2].vy;
				spp->wv[1].vz = ((sc->r.vz * r) >> 15) + spp->wv[2].vz;
				for (i = 0; i <= 28; i++) {
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = 0;
					sc->Rotx.vy = ((4096 * i) / 28);
					sc->Rotx.vz = 0;
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrixSV(&sc->m, &qu[10], &sc->wv);
					sc->m = GsIDMATRIX;
					sc->Rotx.vx = spp->ang[X];
					sc->Rotx.vy = spp->ang[Y];
					sc->Rotx.vz = spp->ang[Z];
					RotMatrixYXZ_gte(&sc->Rotx, &sc->m);
					gte_ApplyMatrix(&sc->m, &sc->wv, &sc->r);
					spp->wv[0].vx = spp->wv[1].vx;
					spp->wv[0].vy = spp->wv[1].vy;
					spp->wv[0].vz = spp->wv[1].vz;
					spp->wv[1].vx = ((sc->r.vx * r) >> 15) + spp->wv[2].vx;
					spp->wv[1].vy = ((sc->r.vy * r) >> 15) + spp->wv[2].vy;
					spp->wv[1].vz = ((sc->r.vz * r) >> 15) + spp->wv[2].vz;
					gte_SetRotMatrix(&GsWSMATRIX);
					gte_ldv3c( &spp->wv[0]);
					gte_rtpt();			/* RotTransPers3 */
					packet[3] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));
					packet[1] = ((0x32 << 24) | packet[3]);
					packet[5] = 0;
					gte_stflg(&flg);
					if ((flg & 0x80000000) == 0) {
						gte_stsxy3_g3((u_long *) packet);
						gte_avsz3();
						gte_stotz(&otz);

						tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
						packet[7] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
						packet[8] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
						*packet = (u_long)((( *tag << 8) >> 8) | 0x06000000);
						*tag = ((u_long) &packet[7] << 8) >> 8;
						packet += 9;
					}
				}
				break;
			case 29:	// 拡散線(POLY_G3)
				if (spp->counter == 0) {
					spp->ang[X] = 0;
					spp->ang[Y] = (rand() & 0xfff);
					spp->ang[Z] = (rand() & 0x0ff) + 1088;

					spp->wv[1].vx =
					spp->wv[1].vy =
					spp->wv[1].vz =
					spp->wv[0].vx =
					spp->wv[0].vy =
					spp->wv[2].vx =
					spp->wv[2].vy = 0;
					spp->wv[0].vz = 50;
					spp->wv[2].vz = -50;
					spp->counter++;
				}
				if (++spp->timer == 0x20) {
					spp->status = 0;
					EffectCounter--;
				}
				spp->ang[Y] += 8;

				sc->Trnsx.vx = (spp->pos[X] >> 12);
				sc->Trnsx.vy = (spp->pos[Y] >> 12);
				sc->Trnsx.vz = (spp->pos[Z] >> 12);
				TransMatrix(&(spp->coord.coord), &sc->Trnsx);
				sc->Rotx.vx = spp->ang[X];
				sc->Rotx.vy = spp->ang[Y];
				sc->Rotx.vz = spp->ang[Z];
				RotMatrixYXZ_gte(&sc->Rotx, &(spp->coord.coord));
				spp->coord.flg = 0;
				GsGetLs(&spp->coord, &sc->tmpmatls);
				GsSetLsMatrix(&sc->tmpmatls);

				spp->wv[0].vy =
				spp->wv[2].vy += (56 - (spp->timer * 2));
				gte_ldv3c(&spp->wv[0]);
				gte_rtpt();
				packet[1] = (0x32 << 24);
				packet[5] = 0;
				gte_stflg(&flg);
				if ((flg & 0x80000000) == 0) {
					gte_stsxy3_g3((u_long *) packet);
					gte_stszotz(&otz);
					ll = 0xff - (otz>>5) - (spp->timer<<3);
					if (ll < 0) break;
					packet[3] = (((ll >> spp->col[B]) << 16) | ((ll >> spp->col[G]) << 8) | (ll >> spp->col[R]));

					tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
					packet[7] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
					packet[8] = (u_long)((0xe1 << 24) | (1 << 9) | (1 << 5));
					*packet = (u_long)((( *tag << 8) >> 8) | 0x06000000);
					*tag = ((u_long) &packet[7] << 8) >> 8;
					packet += 9;
				}
				break;
		}
	}
	GsOUT_PACKET_P = (PACKET *) packet;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	軌跡エフェクト
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void zanzo_entry(short bank, VECTOR *vec0, VECTOR *vec1, CVECTOR *cvec)
{
	register	EFEWORK *spp;
	int i;

	if (zanzo_first[bank] == 0) {
		zvec[bank][1].vx = vec0->vx >> 12;
		zvec[bank][1].vy = vec0->vy >> 12;
		zvec[bank][1].vz = vec0->vz >> 12;
		zvec[bank][3].vx = vec1->vx >> 12;
		zvec[bank][3].vy = vec1->vy >> 12;
		zvec[bank][3].vz = vec1->vz >> 12;
		zanzo_first[bank] = 1;
	}
	zvec[bank][0] = zvec[bank][1];
	zvec[bank][2] = zvec[bank][3];
	zvec[bank][1].vx = vec0->vx >> 12;
	zvec[bank][1].vy = vec0->vy >> 12;
	zvec[bank][1].vz = vec0->vz >> 12;
	zvec[bank][3].vx = vec1->vx >> 12;
	zvec[bank][3].vy = vec1->vy >> 12;
	zvec[bank][3].vz = vec1->vz >> 12;

	spp = EffectEntry(1, NULL, NULL, cvec);
	if (spp != -1) {
		for (i = 0; i < 4; i++) spp->wv[i] = zvec[bank][i];
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	ポリゴンセット
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void Poly4Set(u_long tpage, short clut, POL4 *pol4, GsOT *ot)
{
	register	long *tag;
	register	u_long *packet  = (u_long *) GsOUT_PACKET_P;
	int i = 1;

	packet[i++] = (u_long)((pol4->code << 24) | (pol4->rgb[0][B] << 16) | (pol4->rgb[0][G] << 8) | pol4->rgb[0][R]);
	tag = (u_long *) (ot->org + (pol4->sz[0][0] >> (14 - ot->length)));
	switch (pol4->code & 0x7c) {
		case 0x28:	// POLY_F4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[i] << 8) >> 8;
			packet[i++] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
			packet[i++] = (u_long)((0xe1 << 24) | tpage);
			break;
		case 0x38:	// POLY_G4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[1][B] << 16) | (pol4->rgb[1][G] << 8) | pol4->rgb[1][R]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[2][B] << 16) | (pol4->rgb[2][G] << 8) | pol4->rgb[2][R]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->rgb[3][B] << 16) | (pol4->rgb[3][G] << 8) | pol4->rgb[3][R]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[i] << 8) >> 8;
			packet[i++] = (u_long)((((u_long) &packet[0] << 8) >> 8) | 0x01000000);
			packet[i++] = (u_long)((0xe1 << 24) | tpage);
			break;
		case 0x2c:	// POLY_FT4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((clut << 16) | (pol4->uv[0][1] << 8) | pol4->uv[0][0]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((tpage << 16) | (pol4->uv[1][1] << 8) | pol4->uv[1][0]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[2][1] << 8) | pol4->uv[2][0]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[3][1] << 8) | pol4->uv[3][0]);
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[0] << 8) >> 8;
			break;
		case 0x3c:	// POLY_GT4
			packet[i++] = (u_long)((pol4->sxy[0][Y] << 16) | (pol4->sxy[0][X] & 0xffff));
			packet[i++] = (u_long)((clut << 16) | (pol4->uv[0][1] << 8) | pol4->uv[0][0]);
			packet[i++] = (u_long)((pol4->rgb[1][B] << 16) | (pol4->rgb[1][G] << 8) | pol4->rgb[1][R]);
			packet[i++] = (u_long)((pol4->sxy[1][Y] << 16) | (pol4->sxy[1][X] & 0xffff));
			packet[i++] = (u_long)((tpage << 16) | (pol4->uv[1][1] << 8) | pol4->uv[1][0]);
			packet[i++] = (u_long)((pol4->rgb[2][B] << 16) | (pol4->rgb[2][G] << 8) | pol4->rgb[2][R]);
			packet[i++] = (u_long)((pol4->sxy[2][Y] << 16) | (pol4->sxy[2][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[2][1] << 8) | pol4->uv[2][0]);
			packet[i++] = (u_long)((pol4->rgb[3][B] << 16) | (pol4->rgb[3][G] << 8) | pol4->rgb[3][R]);
			packet[i++] = (u_long)((pol4->sxy[3][Y] << 16) | (pol4->sxy[3][X] & 0xffff));
			packet[i++] = (u_long)((pol4->uv[3][1] << 8) | pol4->uv[3][0]);
			*packet = (u_long)((( *tag << 8) >> 8) | ((i - 1) << 24));
			*tag = ((u_long) &packet[0] << 8) >> 8;
			break;
	}
	GsOUT_PACKET_P = (PACKET *) &packet[i];
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ポリゴンエフェクトエントリー                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
POLYEFE* PolyefeEntry(u_short status, u_short chrno, VECTOR *pv, SVECTOR *av)
{
	long *tmd;
	register	POLYEFE	*spp = pefe;

	if (PolyefeCounter >= POLYEFEMAX) return (-1);
	while (spp->status) spp++;

	spp->status = status;
	spp->counter = 0;
	spp->timer = 0;
	spp->chr = chrno;

	tmd = NumToAddrMcr( chrno, EFMODEL_ADDR );
	tmd++;			/* hedder skip */
	GsMapModelingData(tmd);	/* モデリングデータ（TMDフォーマット）を実アドレスにマップする*/
	tmd++;
	tmd++;			/* GsLinkObject4でリンクするためにTMDのオブジェクトの先頭にもってくる */
	GsLinkObject4( (u_long)tmd, &spp->object, 0);
	spp->object.attribute = 0;
	GsInitCoordinate2(WORLD, &spp->objpos);
	if (pv != NULL) {
		spp->pos[X] = pv->vx;
		spp->pos[Y] = pv->vy;
		spp->pos[Z] = pv->vz;
		TransMatrix(&(spp->objpos.coord), (VECTOR *)(spp->objpos.coord.t));
	}
	if (av != NULL) {
		spp->objang.vx = av->vx;
		spp->objang.vy = av->vy;
		spp->objang.vz = av->vz;
	} else {
		spp->objang.vx =
		spp->objang.vy =
		spp->objang.vz = 0;
	}
	spp->objscl.vx =
	spp->objscl.vy =
	spp->objscl.vz = 4096;

	PolyefeCounter++;
	return (POLYEFE *) spp;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	ポリゴンエフェクトシステム
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void PolyefeControll()
{
	struct {
		SVECTOR	Rotx;
		MATRIX  tmpmatls,tmpmatws;
		MATRIX m;
		VECTOR	Trnsx;
		VECTOR	Scalx;
	} *sc = (void *)getScratchAddr(0);
	register	POLYEFE *spp = pefe;
	int d0, counter = PolyefeCounter;
	VECTOR vec,trans;
	GsCOORDINATE2 coord;

	jt_tpageset();
	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	for (d0 = 0; d0 < counter; spp++) {
		tpage = ((1 << 9) | (1 << 5));
		model_col[R] =
		model_col[G] =
		model_col[B] = 0;
		if (spp->status) {
			d0++;
			switch (spp->status) {
				case 1:	// 爆風
					spp->objscl.vx =
					spp->objscl.vy =
					spp->objscl.vz = rsin(spp->timer << 5) * 2;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 3);
					if (++spp->timer == 32) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 2:	// 輪っか
					spp->objscl.vx =
					spp->objscl.vz = rsin(spp->timer << 5) * 5;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 3);
					if (++spp->timer == 32) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 3:	// レーザー本体
					spp->objscl.vz = (++spp->counter << 8);
					if (spp->objscl.vz >= pp_distance) {
						spp->status = 0;
						PolyefeCounter--;
					}
				case 6:
					spp->objang.vy = (++spp->timer * 448);
					break;
				case 4:	// レーザー笠
					spp->objscl.vx =
					spp->objscl.vy =
					spp->objscl.vz = 3072 + ((++spp->timer % 3) << 10);
					spp->objang.vy = (++spp->timer << 9);
					break;
				case 5:	// だんだん膨らむ球体
					spp->objscl.vx =
					spp->objscl.vy =
					spp->objscl.vz = (spp->timer << 5) + ((spp->timer & 3) << 7);
					model_col[R] =
					model_col[G] =
					model_col[B] = 0xff - (spp->timer << 2);
					if (++spp->timer == 64) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 7:	// だんだん膨らむ球体
					spp->objscl.vx =
					spp->objscl.vy =
					spp->objscl.vz = (spp->timer << 6) + ((spp->timer & 3) << 8);
					model_col[R] =
					model_col[G] =
					model_col[B] = 0xff - (spp->timer << 2);
					if (++spp->timer == 64) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 8:	// 輪っか
					spp->objang.vy = (spp->timer << 9);
					spp->pos[X] -= spp->objang.vz << 5;
					spp->objscl.vy = 1024;
					spp->objscl.vx =
					spp->objscl.vz = rsin(spp->timer << 6) / 2;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 4);
					if (++spp->timer == 16) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 9:	// 輪っか
					spp->objang.vy = (spp->timer << 9);
					spp->pos[X] -= spp->objang.vz << 6;
					spp->objscl.vy = 1024;
					spp->objscl.vx =
					spp->objscl.vz = rsin(spp->timer << 6);
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 4);
					if (++spp->timer == 16) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 10:	// 輪っか
					spp->objang.vy = (spp->timer << 9);
					spp->pos[X] -= spp->objang.vz << 7;
					spp->objscl.vy = 1024;
					spp->objscl.vx =
					spp->objscl.vz = rsin(spp->timer << 6) * 3 / 2;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 4);
					if (++spp->timer == 16) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 11:	// レーザー笠消え
					spp->objscl.vx -= 128;
					spp->objscl.vy -= 128;
					spp->objscl.vz -= 64;
					spp->objang.vy = (++spp->timer << 9);
					if (spp->objscl.vx == 0) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 12:	// 槍槍
					if (spp->timer <= 64) {
						spp->objscl.vz = rsin(spp->timer << 4);
						spp->objang.vx = -1024 + 64 - (spp->timer);
					}
					spp->objang.vy = (++spp->timer << 8);
					if (spp->timer == 64) {
						spp->objang.vy = 0;
						spp->timer = 0;
						spp->status++;
					}
					break;
				case 13:	// 槍槍刺さり
					if (spp->timer < 20) {
						spp->pos[X] += (spp->objang.vz - (spp->objang.vz * spp->timer / 56)) << 9;
						spp->pos[Y] -= (spp->objang.vx * spp->timer) * 3;
						if (spp->objang.vz < 0) spp->objang.vz -= 12;
						else spp->objang.vz += 12;
					} else if (spp->timer < 28) {
						spp->pos[X] += ((spp->objang.vz - (spp->objang.vz * spp->timer / 56)) << 9) / 8;
						spp->pos[Y] -= ((spp->objang.vx * spp->timer) * 3) / 8;
					} else {
						spp->timer = 0;
						spp->status = 15;
					}
					spp->timer++;
					break;
				case 14:	// 槍槍跳ね返り
					spp->pos[X] -= (spp->objang.vz - (spp->objang.vz * spp->timer / 56)) << 7;
					spp->pos[Y] += spp->timer << 12;
					spp->objang.vx += 320;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer++ << 3);
					if (model_col[R] >= 0xf8) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 15:	// 槍槍消え
					spp->objscl.vx =
					spp->objscl.vy = 4096 + rsin(spp->timer << 5) * 4;
					model_col[R] =
					model_col[G] =
					model_col[B] = (spp->timer << 3);
					if (++spp->timer == 32) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
				case 16:	// 岩
					spp->pos[Y] -= 75 << 12;
					spp->objang.vx += (rand() % 256);
					spp->objang.vy += (rand() % 256);
					if (++spp->timer == 128) {
						spp->status = 0;
						PolyefeCounter--;
					}
					break;
			}
			sc->Trnsx.vx = spp->pos[X] / 4096;
			sc->Trnsx.vy = spp->pos[Y] / 4096;
			sc->Trnsx.vz = spp->pos[Z] / 4096;
			TransMatrix(&(spp->objpos.coord), &sc->Trnsx);
			sc->Rotx.vx = spp->objang.vx;
			sc->Rotx.vy = spp->objang.vy;
			sc->Rotx.vz = spp->objang.vz;
			RotMatrixZYX_gte(&sc->Rotx, &(spp->objpos.coord));
			sc->Scalx.vx = spp->objscl.vx;
			sc->Scalx.vy = spp->objscl.vy;
			sc->Scalx.vz = spp->objscl.vz;
			ScaleMatrix( &(spp->objpos.coord), &sc->Scalx);
			spp->objpos.flg = 0;
			GsGetLws(&spp->objpos, &sc->tmpmatws, &sc->tmpmatls);
			GsSetLightMatrix2(&sc->tmpmatws);
			GsSetLsMatrix(&sc->tmpmatls);
			SetSpadStack(SPAD_STACK_ADDR);
			if (spp->status == 16) GsSortObject4J(&spp->object, &bgot[ PSDIDX ], 14 - BGOT_LENGTH, getScratchAddr(0));
			else GsSortObject4J(&spp->object, &ot[ PSDIDX ], 14 - OT_LENGTH, getScratchAddr(0));
			ResetSpadStack();
		}
	}
}


char lens_narabi[] = {
	1,0,0,0,3,0,0,6,3,0,
	    7,0,3,1,6,4,0,5
};

void lensflare(VECTOR *sunpos)
{
	SVECTOR avec;
	CVECTOR cvec;
	long i, sxy, otz;
	short sx, sy, bright;

	avec.vx = sunpos->vx >> 12;
	avec.vy = sunpos->vy >> 12;
	avec.vz = sunpos->vz >> 12;
	gte_ldv0(&avec);
	gte_rtps();
	gte_stsxy(&sxy);
	sx = (short)sxy;
	sy = (short)(sxy >> 16);
	gte_stszotz(&otz);
	if ((otz > 0) && (sx > -180) && (sx < 180) && (sy > -140) && (sy < 140)) {
		avec.vz = (1 << SPRITEOT_LENGTH) - 1;
		avec.vx = sx;
		avec.vy = sy;
		SpriteEntry((0x130 << 5) + 480, flare_ofs, &avec, NULL, 15, 0); // 太陽
		bright = 0xff - (abs(sx) + abs(sy));
		if (bright < 0) bright = 0;
		cvec.r =
		cvec.g =
		cvec.b = bright;
		for (i = 0; i < 18; i++) {
			if (lens_narabi[i]) {
				avec.vx = sx + (((-sx * 2) * (i - 2)) / 16);
				avec.vy = sy + (((-sy * 2) * (i - 2)) / 16);
				SpriteEntry((0x130 << 5) + 480 + lens_narabi[i], flare_ofs + lens_narabi[i], &avec, &cvec, 15, 0);
			}
		}
		{
	          GsBOXF boxf;
	
	          boxf.attribute = ABLEND;
	          boxf.x = -160;
	          boxf.y = -120;
	          boxf.w = 320;
	          boxf.h = 240;
	          boxf.r =
	          boxf.g =
	          boxf.b = bright >> 1;
	          GsSortBoxFill( &boxf, &ot[ PSDIDX ], 0);
		}
	}
}


void lensflare_y(SVECTOR *sunpos)
{
	SVECTOR avec;
	CVECTOR cvec;
	long i, otz;
	short sx, sy, bright;

	sx = (short) sunpos->vx;
	sy = (short) sunpos->vy;
	otz = sunpos->vz;
	if ((otz > 0) && (sx > -180) && (sx < 180) && (sy > -140) && (sy < 140)) {
		avec.vz = (1 << SPRITEOT_LENGTH) - 1;
		bright = 0xff - (abs(sx) + abs(sy));
		if (bright < 0) bright = 0;
		cvec.r =
		cvec.g =
		cvec.b = bright;
		for (i = 0; i < 18; i++) {
			if (lens_narabi[i]) {
				avec.vx = sx + (((-sx * 2) * (i - 2)) / 16);
				avec.vy = sy + (((-sy * 2) * (i - 2)) / 16);
				SpriteEntry((0x130 << 5) + 480 + lens_narabi[i], flare_ofs + lens_narabi[i], &avec, &cvec, 15, 0);
			}
		}
		{
	          GsBOXF boxf;
	
	          boxf.attribute = ABLEND;
	          boxf.x = -160;
	          boxf.y = -120;
	          boxf.w = 320;
	          boxf.h = 240;
	          boxf.r =
	          boxf.g =
	          boxf.b = bright >> 1;
	          GsSortBoxFill( &boxf, &ot[ PSDIDX ], 0);
		}
	}
}


void LineSet(SVECTOR *p0, SVECTOR *p1)
{
	struct {
		MATRIX  tmpmatls;
		GsCOORDINATE2 coord;
	} *sc = (void *)getScratchAddr(0);
	register	long *tag;
	register	u_long *packet  = (u_long *) GsOUT_PACKET_P;
	long otz;

	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	GsInitCoordinate2(WORLD, &sc->coord);
	sc->coord.flg = 0;
	GsGetLs(&sc->coord, &sc->tmpmatls);
	GsSetLsMatrix(&sc->tmpmatls);
	packet[1] = ((0x40 << 24) | (0x00 << 16) | (0xf0 << 8) | 0x00);
	gte_ldv0((SVECTOR *) p0);
	gte_rtps();
	gte_stsxy((u_long *) &packet[2]);
	gte_ldv0((SVECTOR *) p1);
	gte_rtps();
	gte_stsxy((u_long *) &packet[3]);
	gte_stszotz(&otz);

	tag = (u_long *) (ot[ PSDIDX ].org + (otz >> (14 - OT_LENGTH)));
	*packet = (u_long)((( *tag << 8) >> 8) | 0x03000000);
	*tag = ((u_long) &packet[0] << 8) >> 8;
	packet += 4;
	GsOUT_PACKET_P = (PACKET *) packet;
}

