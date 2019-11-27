/*
	テクスチャーデータ
*/

#include "../lib/czarsprt.h"

enum {
	CLUTX000 = 0,
	CLUTX016 = 16,
	CLUTX096 = 96,
	CLUTX128 = 128,

	CLUTY480 = 480,
	CLUTY481 = 481,
	CLUTY482 = 482,
	CLUTY483 = 483,
	CLUTY484 = 484,
	CLUTY485 = 485,
	CLUTY486 = 486,
	CLUTY487 = 487,
	CLUTY488 = 488,
	CLUTY489 = 489,
	CLUTY496 = 496,
	CLUTY497 = 497,
	CLUTY498 = 498,
	CLUTY499 = 499,
	CLUTY500 = 500,
	CLUTY501 = 501,
	CLUTY502 = 502,
	CLUTY503 = 503,
	CLUTY504 = 504,
	CLUTY505 = 505,
	CLUTY506 = 506,
	CLUTY507 = 507,
	CLUTY508 = 508,
	CLUTY509 = 509,
	CLUTY510 = 510,
	CLUTY511 = 511,

	TP05 =  5,
	TP06 =  6,
	TP07 =  7,
	TP08 =  8,
	TP09 =  9,
	TP10 = 10,
	TP11 = 11,
	TP12 = 12,
	TP13 = 13,
	TP14 = 14,
	TP15 = 15,

	TP21 = 21,
	TP22 = 22,
	TP23 = 23,
	TP24 = 24,
	TP25 = 25,
	TP26 = 26,
	TP27 = 27,
	TP28 = 28,
	TP29 = 29,
	TP30 = 30,
	TP31 = 31,
};

#include "sprite/fix.c"
#include "sprite/efect1.c"
#include "sprite/golight.c"
#include "sprite/renda.c"
#include "sprite/ap2.c"
#include "sprite/vs.c"
#include "sprite/nizi.c"
#include "sprite/name.c"
#include "sprite/namevs.c"
#include "sprite/syouri.c"
#include "sprite/flare.c"
#include "sprite/beem3.c"
#include "sprite/logo.c"

CzAnimData *SequenceTbl[] = {
	fix0000,
	fix0001,
	fix0002,
	fix0003,
	fix0004,
	fix0005,
	fix0006,
	fix0007,
	fix0008,
	fix0009,
	fix0010,
	fix0011,
	fix0012,
	fix0013,
	fix0014,
	fix0015,
	fix0016,
	fix0017,
	fix0018,
	fix0019,
	fix0020,
	fix0021,
	fix0022,
	fix0023,
	fix0024,
	fix0025,
	fix0026,
	fix0027,
	fix0028,
	fix0029,
	fix0030,
	fix0031,
	fix0032,
	fix0033,
	fix0034,
	fix0035,
	fix0036,
	fix0037,
	fix0038,
	fix0039,
	fix0040,
	fix0041,
	fix0042,
	fix0043,
	fix0044,
	fix0045,
	fix0046,
	fix0047,
	fix0048,
	fix0049,
	fix0050,
	fix0051,
	fix0052,
	fix0053,
	fix0054,
	fix0055,
	fix0056,
	fix0057,
	fix0058,

	efe10000,
	efe10001,
	efe10002,
	efe10003,
	efe10004,
	efe10005,
	efe10006,
	efe10007,
	efe10008,

	gol0000,

	ren0000,
	ren0001,
	ren0002,
	ren0003,
	ren0004,

	ap20000,
	ap20001,
	ap20002,
	ap20003,
	ap20004,
	ap20005,
	ap20006,
	ap20007,
	ap20008,
	ap20009,

	vs0000,
	vs0001,

	nizi0000,

	name0000,
	name0001,

	namevs0000,
	namevs0001,

	syo0000,

	fl0000,
	fl0001,
	fl0002,
	fl0003,
	fl0004,
	fl0005,
	fl0006,
	fl0007,

	bem30000,
	bem30001,
	bem30002,
	bem30003,

	logo0000,
	logo0001,
};




