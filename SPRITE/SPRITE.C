/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SPRITE LIBRARY [ DEV CODE: 98025 ]                       */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : SPRITE.C                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <inline_c.h>
#include <gtemac.h>

/*----- User Header     Files -----*/
#include "../lib/aki_def.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/grpara.h"
#include "../lib/czarsprt.h"
#include "../lib/model.h"
#include "../sprite/sprite.h"
#include "../p01/poly_sub.h"
#include "../p01/bg.h"
#include "../p01/anmdata.h"

/*----- User External   Files -----*/
/* Non */

/*----- User Table      Files -----*/
/* Non */

GsOT        spriteot[2];							/* Ordering Table                  */
GsOT_TAG    spriteot_tag[2][1<<SPRITEOT_LENGTH];	/* オーダリングテーブル実体        */
int			SpriteCounter;
int			Sprite3dCounter;
SPRWORK		sprite[SPRITEMAX];
SPRITE3D	spr3d[SPRITE3DMAX];
u_char		BGFadeOffset;
CzAnimData	*anm;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ワーク初期化                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void SpriteInit(CzAnimData *tbl)
{
	int i;

	spriteot[0].length = SPRITEOT_LENGTH;
	spriteot[0].org    = spriteot_tag[0];
	spriteot[1].length = SPRITEOT_LENGTH;
	spriteot[1].org    = spriteot_tag[1];

	for (i = 0; i < SPRITEMAX; i++) {
		sprite[i].status = 0;
	}
	for (i = 0; i < SPRITE3DMAX; i++) {
		spr3d[i].status = 0;
	}
	for (i = 0; i < EFFECTMAX; i++) {
		efe[i].status = 0;
	}
	SpriteCounter = 0;
	Sprite3dCounter = 0;
	EffectCounter = 0;
	anm = tbl;
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//  スプライトエントリー
//	dir		1:上IN 2:下IN 3:左IN 4:右IN 5:拡大IN 6:縦拡大IN 7:２倍拡大IN 8:一定時間点滅
//	wait	待ち時間
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

SPRWORK* SpriteEntry(u_short pal, u_short chr, SVECTOR *pv, CVECTOR *cp, u_short dir, u_short wait)
{
	FIXED	sp;
	CZCODE	*cap;
	SPRWORK	*spp = sprite;

	if (SpriteCounter >= SPRITEMAX) return (-1);
	if (wait == 0xff) {
		wait = 0;
		spp += (SPRITEMAX - 1);
		while (spp->status) spp--;
	} else {
		while (spp->status) spp++;
	}

	spp->status = (chr & 0xf000) + dir;
	spp->flip = sprNoflip | _ZmCC;
	spp->pal = pal;
	spp->chr = chr & 0x0fff;
	cap = *(((CZCODE **) anm) + spp->chr);
	spp->pos[X] = (pv->vx + ((cap->code[1] & 0xff) / 2)) * 0x10000;
	spp->pos[Y] = (pv->vy + (((cap->code[1] >> 8) & 0xff) / 2)) * 0x10000;
	spp->pos[Z] = pv->vz;
	spp->spd[X] =
	spp->spd[Y] =
	spp->spd[Z] =
	spp->acc[X] =
	spp->acc[Y] =
	spp->acc[Z] = 0;
	if (cp != NULL) {
		spp->pmode = CLUT4 | ABLEND;
		spp->col[R] = cp->r;
		spp->col[G] = cp->g;
		spp->col[B] = cp->b;
	} else {
		spp->pmode = CLUT4 | LIGHT_OFF;
		if (((spp->pal >> 5) >= 256) && ((spp->pal & 0x1ff) <= 496)) spp->pmode |= NBLEND;
		spp->col[R] =
		spp->col[G] =
		spp->col[B] = 0x80;
	}
	spp->hzoom =
	spp->vzoom = 0xffff;
	spp->hzoomsp =
	spp->vzoomsp =
	spp->hzoomac =
	spp->vzoomac = 0;
	spp->angle = 0;
	spp->counter = 0;
	switch (dir) {
		case 0:
			spp->pmode = CLUT4 | LIGHT_OFF;
			spp->status += 9;
			break;
		case 1:
			sp = -((cap->code[1] & 0xff) / 2) * 0x10000 - 0x780000;
			spp->acc[Y] = -acceleration;
			while (spp->pos[Y] > sp) {
				spp->pos[Y] -= spp->spd[Y];
				spp->spd[Y] -= spp->acc[Y];
			}
			break;
		case 2:
			sp = (((cap->code[1] & 0xff) / 2) * 0x10000) + 0x780000;
			spp->acc[Y] = acceleration;
			while (spp->pos[Y] < sp) {
				spp->pos[Y] -= spp->spd[Y];
				spp->spd[Y] -= spp->acc[Y];
			}
			break;
		case 3:
			sp = -(((cap->code[1] >> 8) & 0xff) / 2) * 0x10000 - 0xa00000;
			spp->acc[X] = -acceleration;
			while (spp->pos[X] > sp) {
				spp->pos[X] -= spp->spd[X];
				spp->spd[X] -= spp->acc[X];
			}
			break;
		case 4:
			sp = ((((cap->code[1] >> 8) & 0xff) / 2) * 0x10000) + 0xa00000;
			spp->acc[X] = acceleration;
			while (spp->pos[X] < sp) {
				spp->pos[X] -= spp->spd[X];
				spp->spd[X] -= spp->acc[X];
			}
			break;
		case 5:
			spp->hzoomac =
			spp->vzoomac = zoom_acc;
			while (spp->hzoom < zoom_min) {
				spp->hzoom -= spp->hzoomsp;
				spp->hzoomsp -= spp->hzoomac;
			}
			spp->vzoom = spp->hzoom;
			spp->vzoomsp = spp->hzoomsp;
			break;
		case 6:
			spp->vzoomac = zoom_acc;
			while (spp->vzoom < zoom_min) {
				spp->vzoom -= spp->vzoomsp;
				spp->vzoomsp -= spp->vzoomac;
			}
			break;
		case 7:
			spp->hzoom =
			spp->vzoom = 0x8000;
			spp->hzoomac =
			spp->vzoomac = zoom_acc * 3;
			while (spp->hzoom < zoom_min) {
				spp->hzoom -= spp->hzoomsp;
				spp->hzoomsp -= spp->hzoomac;
			}
			spp->vzoom = spp->hzoom;
			spp->vzoomsp = spp->hzoomsp;
			break;
		case 8:
			spp->status |= 0x8000;
			spp->counter = 60;
			break;
		case 9:
			break;
		case 12:
			spp->hzoom =
			spp->vzoom = 0x6000;
			spp->hzoomac =
			spp->vzoomac = zoom_acc;
			while (spp->hzoom < 0xffff) {
				spp->hzoom -= spp->hzoomsp;
				spp->hzoomsp -= spp->hzoomac;
			}
			spp->vzoom = spp->hzoom;
			spp->vzoomsp = spp->hzoomsp;
			break;
		case 13:
			spp->hzoom =
			spp->vzoom = 0x8000;
			spp->hzoomac =
			spp->vzoomac = zoom_acc;
			while (spp->hzoom < 0xffff) {
				spp->hzoom -= spp->hzoomsp;
				spp->hzoomsp -= spp->hzoomac;
			}
			spp->vzoom = spp->hzoom;
			spp->vzoomsp = spp->hzoomsp;
			break;
		case 15:
			spp->pos[X] = pv->vx << 16;
			spp->pos[Y] = pv->vy << 16;
			break;
	}
	spp->timer = wait;
	SpriteCounter++;

	return (SPRWORK *) spp;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	スプライトシステム（高橋仕様対応版）
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void SpriteControll()
{
	register	SPRWORK *spp = sprite;
	int d0, d1, counter = SpriteCounter;

	for (d0 = 0; d0 < counter;) {
		if (spp->status) {
			if (spp->timer) {
				spp->timer--;
			} else {
				for (d1 = 0; d1 < RGB; d1++) {
					if (spp->col[d1] > 0x81) spp->col[d1] -= 2;
					else if (spp->col[d1] < 0x80) spp->col[d1] += 2;
				}
//				if ((spp->col[R] == 0x80) && (spp->col[G] == 0x80) && (spp->col[B] == 0x80)) spp->pmode = CLUT4 | LIGHT_OFF;
				spp->spd[X] += spp->acc[X];
				spp->spd[Y] += spp->acc[Y];
				if (spp->spd[X] == 0) spp->acc[X] = 0;
				if (spp->spd[Y] == 0) spp->acc[Y] = 0;
				spp->pos[X] += spp->spd[X];
				spp->pos[Y] += spp->spd[Y];
				spp->hzoomsp += spp->hzoomac;
				spp->vzoomsp += spp->vzoomac;
				spp->hzoom   += spp->hzoomsp;
				spp->vzoom   += spp->vzoomsp;
				switch (spp->status & 0xfff) {
					case 8:
						if (spp->counter) {
							if (--spp->counter == 0) spp->status &= 0x7fff;
						}
						break;
					case 7:
						if ((spp->hzoom >= 0xffff) && (spp->hzoomsp > 0)) {
							spp->hzoom =
							spp->vzoom = 0xffff;
							spp->hzoomsp =
							spp->vzoomsp =
							spp->hzoomac =
							spp->vzoomac = 0;
						}
						spp->pmode = CLUT4 | LIGHT_OFF;
						if (++spp->counter >= 22) {
							spp->pmode = CLUT4 | ABLEND;
							spp->col[R] =
							spp->col[G] =
							spp->col[B] = 0x80 - ((spp->counter - 22) << 4);
							if (spp->counter == 29) {
								spp->status = 0;
								SpriteCounter--;
							}
						}
						break;
					case 10:
						if (spp->vzoom > zoom_min) {
							spp->vzoom = zoom_min;
							spp->vzoomsp = 0;
							spp->vzoomac = -zoom_acc * 5;
						} else if (spp->vzoom <= 0xffff) {
							spp->vzoom = 0xffff;
							spp->vzoomsp =
							spp->vzoomac = 0;
							spp->status = 9;
						}
						break;
					case 11:
						spp->pal = (0x120 << 5) + 486 + ((gcb.GlobalTimer ) & 2);
						break;
					case 12:
					case 13:
						if (spp->hzoom == 0x6000) {
							spp->hzoomsp =
							spp->vzoomsp = zoom_acc / 3;
							spp->hzoomac =
							spp->vzoomac = 0;
						}
						spp->pmode = CLUT4 | ABLEND;
						spp->col[R] =
						spp->col[G] =
						spp->col[B] = (0x80 - (spp->counter << 3));
						if (++spp->counter == 16) {
							spp->status = 0;
							SpriteCounter--;
						}
						break;
					case 14:
							spp->pmode = CLUT4 | ABLEND;
							spp->col[R] =
							spp->col[G] =
							spp->col[B] = 0x80 - (spp->counter << 3);
							if (++spp->counter == 16) {
								spp->status = 0;
								SpriteCounter--;
							}
						break;
					case 15:
						spp->pmode = CLUT4 | ABLEND;
						spp->status = 0;
						SpriteCounter--;
						break;
					case 16:
						spp->pmode = CLUT4 | NBLEND;
						spp->status = 0;
						SpriteCounter--;
						break;
					case 17:
						spp->hzoomsp =
						spp->hzoomac =
						spp->vzoomsp =
						spp->vzoomac = 0;
						spp->hzoom =
						spp->vzoom = zoom_min;
						break;
					case 18:
						spp->pos[Y] -= 0x5ca0;
						if (spp->pos[Y] < -0xf80000) {
							spp->chr += 4;
							spp->pos[Y] += 0x2000000;
							if (spp->chr >= 32) {
								spp->status = 0;
								SpriteCounter--;
							}
						}
						break;
				}
				if (spp->hzoom == 0xffff) {
					spp->hzoomsp =
					spp->hzoomac = 0;
				}
				if (spp->vzoom == 0xffff) {
					spp->vzoomsp =
					spp->vzoomac = 0;
				}
				if ((spp->hzoom > zoom_min) || (spp->vzoom > zoom_min)) {
					spp->status = 0;
					SpriteCounter--;
				}
				if (((spp->pos[X] < -0xc00000) && (spp->spd[X] < 0)) ||
					((spp->pos[X] >  0xc00000) && (spp->spd[X] > 0))) {
					spp->status = 0;
					SpriteCounter--;
				}
				if (((spp->pos[Y] < -0xa00000) && (spp->spd[Y] < 0)) ||
					((spp->pos[Y] >  0xa00000) && (spp->spd[Y] > 0))) {
					spp->status = 0;
					SpriteCounter--;
				}
				if ((spp->hzoom < zoom_min) && (spp->vzoom < zoom_min)) {
					if (((spp->status & 0x8000) == 0) || ((gcb.GlobalTimer & 4) == 0)) DispSpriteGs(spp);
				}
			}
			d0++;
		}
	spp++;
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	スプライト表示
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void DispSpriteGs(SPRWORK *spp)
{
	GsSPRITE	gss;
	CZCODE		*cap;

	cap = *(((CZCODE **) anm) + spp->chr);
	gss.attribute = spp->pmode;
	if ((spp->hzoom == 0xffff) && (spp->vzoom == 0xffff)) gss.attribute |= ZOOM_OFF;
	gss.tpage = (cap->code[3] & 0xff);
	gss.w = (cap->code[1] & 0xff);
	gss.h = ((cap->code[1] >> 8) & 0xff);
	gss.u = ((cap->code[1] >> 16) & 0xff);
	gss.v = ((cap->code[1] >> 24) & 0xff);
	gss.mx = gss.w / 2;

	if ((spp->flip & _ZmRC) == _ZmRC) {
		gss.mx = gss.w;
	} else if ((spp->flip & _ZmLC) == _ZmLC) {
		gss.mx = 0;
	}

	gss.my = gss.h / 2;
	gss.x = (spp->pos[X] >> 16);
	gss.y = (spp->pos[Y] >> 16);
	gss.cx = (spp->pal >> 5) & 0x1f0;
	gss.cy = spp->pal & 0x1ff;
	gss.scalex = 0x10000000 / (spp->hzoom + 1);
	gss.scaley = 0x10000000 / (spp->vzoom + 1);
	gss.r = spp->col[R];
	gss.g = spp->col[G];
	gss.b = spp->col[B];
	gss.rotate = spp->angle;

	GsSortSprite( &gss, &spriteot[ PSDIDX ], spp->pos[Z]);
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ３Ｄスプライトエントリー                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

SPRITE3D* Sprite3dEntry(u_short status, u_short pal, u_short chr,  VECTOR *pv)
{
	register CZCODE		*cap;
	register SPRITE3D	*spp = spr3d;

	if (Sprite3dCounter >= SPRITE3DMAX) return (-1);
	while (spp->status) spp++;

	spp->status = status;
	spp->counter = 0;
	spp->timer = 0;
	spp->chr = chr;
	spp->angle = 0;
	spp->pos[X] = pv->vx;
	spp->pos[Y] = pv->vy;
	spp->pos[Z] = pv->vz;
	spp->spd[X] =
	spp->spd[Y] =
	spp->spd[Z] =
	spp->acc[X] =
	spp->acc[Y] =
	spp->acc[Z] = 0;
	cap = *(((CZCODE **) anm) + chr);
	spp->ft4[0][3] =
	spp->ft4[1][3] = ((pal << 16) | (cap->code[1] >> 16));
	spp->ft4[0][5] =
	spp->ft4[1][5] = ((((1 << 5) | ((cap->code[3] << 24) >> 24)) << 16) | (cap->code[1] >> 16)) + ((cap->code[1] << 24) >> 24) - 0x0001;
	spp->ft4[0][7] =
	spp->ft4[1][7] = ((cap->code[1] >> 16)) + (((cap->code[1] >> 8) << 24) >> 16) - 0x0100;
	spp->ft4[0][9] =
	spp->ft4[1][9] = ((cap->code[1] >> 16)) + ((cap->code[1] << 16) >> 16) - 0x0101;

	Sprite3dCounter++;
	return (SPRITE3D *) spp;
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	スプライト３Ｄシステム
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void Sprite3dControll()
{
	struct {
		SVECTOR wv;
	} *sc = (void *)getScratchAddr(0);
	register	long *tag;
	register	CZCODE *cap;
	register	SPRITE3D *spp = spr3d;
	int d0, counter = Sprite3dCounter;
	long flg,xy;
	short x,y,z,w,h,r,g,b;

	gte_SetTransMatrix(&GsWSMATRIX);
	gte_SetRotMatrix(&GsWSMATRIX);
	for (d0 = 0; d0 < counter; spp++) {
		if (spp->status) d0++;
		r = g = b = 0x80;
		switch (spp->status) {
			case 1:
				if (++spp->timer == 2) {
					spp->status = 0;
					Sprite3dCounter--;
				}
				break;
			case 2:	// 飛び散り
				if (spp->counter == 0) {
//					spp->spd[X] = ((rand() % 100) - 50) << 12;
					spp->spd[Y] = ((rand() % 100) - 50) << 12;
					spp->spd[Z] = ((rand() % 100) - 50) << 12;
					spp->acc[X] = -spp->spd[X] / 64;
					spp->acc[Y] = -spp->spd[Y] / 64;
					spp->acc[Z] = -spp->spd[Z] / 64;
					spp->counter++;
				}
				spp->spd[X] += spp->acc[X];
				spp->spd[Y] += spp->acc[Y];
				spp->spd[Z] += spp->acc[Z];
				if (spp->spd[X] == 0) spp->acc[X] = 0;
				if (spp->spd[Y] == 0) spp->acc[Y] = 0;
				if (spp->spd[Z] == 0) spp->acc[Z] = 0;
				spp->pos[X] += spp->spd[X];
				spp->pos[Y] += spp->spd[Y];
				spp->pos[Z] += spp->spd[Z];
				r = g = b = 0x80 - (spp->timer << 3);
				if (++spp->timer >= 16) {
					spp->status = 0;
					Sprite3dCounter--;
				}
				break;
			case 4:	// 煙アニメ
				spp->pos[Y] -= ((32 - spp->timer) << 11);
				spp->chr = efe1_ofs + (spp->timer >> 2);
			case 3:	// フェードアウト
				r = g = b = 0x80 - (spp->timer << 2);
				if (++spp->timer >= 32) {
					spp->status = 0;
					Sprite3dCounter--;
				}
				break;
			case 5:	// フェードアウト
				r = g = b = 0xff - (spp->timer << 4);
				if (++spp->timer >= 16) {
					spp->status = 0;
					Sprite3dCounter--;
				}
				break;
		}
		if (spp->status) {
			sc->wv.vx = spp->pos[X] >> 12;
			sc->wv.vy = spp->pos[Y] >> 12;
			sc->wv.vz = spp->pos[Z] >> 12;
			gte_ldv0(&sc->wv);
			gte_rtps();			/* RotTransPers */
			gte_stflg(&flg);
			if ((flg & 0x80000000) == 0) {
				gte_stsxy(&xy);
				gte_stsz(&z);
				if (z > 0) {
					cap = *(((CZCODE **) anm) + spp->chr);
					spp->ft4[PSDIDX][3] = ((spp->ft4[PSDIDX][3] & 0xffff0000) | (cap->code[1] >> 16));
					spp->ft4[PSDIDX][5] = ((((1 << 5) | ((cap->code[3] << 24) >> 24)) << 16) | (cap->code[1] >> 16)) + ((cap->code[1] << 24) >> 24) - 0x0001;
					spp->ft4[PSDIDX][7] = ((cap->code[1] >> 16)) + (((cap->code[1] >> 8) << 24) >> 16) - 0x0100;
					spp->ft4[PSDIDX][9] = ((cap->code[1] >> 16)) + ((cap->code[1] << 16) >> 16) - 0x0101;
					w = (((cap->code[1] << 24)) / z) >> 12; //12
					h = ((((cap->code[1] >> 8) << 24)) / z) >> 12; //12
					x = (short)((xy << 16) >> 16) - (w / 2);
					y = (short)(xy >> 16) - (h / 2);
					spp->ft4[PSDIDX][1] = ((0x2e << 24) | (b << 16) | (g << 8) | r);
					spp->ft4[PSDIDX][2] = (((u_long)y << 16) | (((u_long)x << 16) >> 16));
					spp->ft4[PSDIDX][4] = (((u_long)y << 16) | (((u_long)(x + w) << 16) >> 16));
					spp->ft4[PSDIDX][6] = (((u_long)(y + h) << 16) | (((u_long)x << 16) >> 16));
					spp->ft4[PSDIDX][8] = (((u_long)(y + h) << 16) | (((u_long)(x + w) << 16) >> 16));

					gte_stszotz(&z);
					tag = (u_long *) (ot[ PSDIDX ].org + (z >> (14 - OT_LENGTH)));
					spp->ft4[PSDIDX][0] = (u_long)(((*tag << 8) >> 8) | 0x09000000);
					*tag = ((u_long) &spp->ft4[PSDIDX][0] << 8) >> 8;
				}
			}
		}
	}
}


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
//	スプライトをならべてＢＧ表示
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define	max_width	64
void SpriteBgSet(Uint8 tpage, Uint16 pal, Sint16 x, Sint16 y, Uint32 attr, Uint16 wsize, Uint16 hsize)
{
	Uint32	pri;
	GsSPRITE	sp,sprite;

		pri = (1 << BGOT_LENGTH) - 1;
		sprite.attribute = attr | ZOOM_OFF | LIGHT_OFF;
		sprite.tpage = tpage;
		sprite.x = x;
		sprite.y = y;
		sprite.u = 0;
		sprite.v = 0;
		sprite.cx = 0;
		sprite.cy = pal;
		sprite.r =
		sprite.g =
		sprite.b = BGFadeOffset;
		sprite.mx =
		sprite.my = 0;
		sprite.scalex =
		sprite.scaley = ONE;
		while(wsize > 0) {
			if (wsize >= max_width)
				sprite.w = max_width;
			else
				sprite.w = wsize;
			if (hsize <= 256)
				sprite.h = hsize;
			else
				sprite.h = 256;
			if ((sprite.x > -160 - max_width) && (sprite.x <160)) {
				sp = sprite;

				if (sp.x + sp.w > 160)
					sp.w = 160 - sp.x;
				GsSortSprite(&sp, &bgot[ PSDIDX ], pri);			// Sprite Entry
				if (hsize > 256) {
					sprite.tpage += 16;
					sprite.y += 256;
					sprite.h = hsize - 256;
					sp = sprite;
					GsSortSprite(&sp, &bgot[ PSDIDX ], pri);			// Sprite Entry
					sprite.tpage -= 16;
					sprite.y -= 256;
				}
			}
			sprite.x += max_width;
			sprite.u += max_width;
			if (sprite.u == 0) {
				if ((attr & DIRECT15) == DIRECT15)
					sprite.tpage += 4;
				else if ((attr & CLUT8) == CLUT8)
					sprite.tpage += 2;
				else
					sprite.tpage++;
			}
			wsize -= sprite.w;
		}
}


