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

#include "sprite/zukanfix.c"
#include "sprite/namevs.c"
#include "sprite/panel.c"

CzAnimData *Zu_SequenceTbl[] = {
	zuk0000,
	zuk0001,
	zuk0002,
	zuk0003,
	zuk0004,
	zuk0005,
	zuk0006,

	zu_namevs0000,
	zu_namevs0001,

	panel0000,
};




