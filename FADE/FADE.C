/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : FADE SYSTEM PROCEDURES                                   */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : FADE.C                                                   */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>
#include <libcd.h>

/*----- User Header     Files -----*/
#include "../lib/aki_def.h"
#include "../lib/mainsys.h"
#include "../lib/libctl.h"
#include "../lib/libdat.h"
#include "../lib/libdbg.h"
#include "../lib/libemc.h"
#include "../lib/libfio.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/fade.h"

FADEWORK fade;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FADE SYSTEM                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
u_char FadeSub(GsOT *ot)
{
	GsBOXF boxf;

		switch(fade.status) {
			case 0:
				break;
			case 1:		// フェードイン
				if (fade.col == 1) fade.status = 0;
				boxf.attribute = SBLEND;
				fade.col += fade.rate;
				if (fade.col <= 1) fade.col = 1;
				break;
			case 2:		// フェードアウト
				if (fade.col == 0xff) {
					fade.status = 0;
					ResetGraph(3);
					GsClearDispArea( 0x00, 0x00, 0x00 );
					VSync(0);                                  /* Wait V-BLANK (1/60)      */
					GsSwapDispBuff();                          /* Swap Double Buffer       */
					GsClearDispArea( 0x00, 0x00, 0x00 );
				} else {
					boxf.attribute = SBLEND;
					fade.col += fade.rate;
					if (fade.col >= 0x100) fade.col = 0xff;
				}
				break;
			case 3:		// ホワイトフェードイン
				if (fade.col == 1) fade.status = 0;
				boxf.attribute = ABLEND;
				fade.col += fade.rate;
				if (fade.col <= 1) fade.col = 1;
				break;
			case 4:		// ホワイトフェードアウト
				if (fade.col == 0xff) fade.status = 0;
				boxf.attribute = ABLEND;
				fade.col += fade.rate;
				if (fade.col >= 0x100) fade.col = 0xff;
				break;
		}
		if (fade.status) {
			boxf.x = -160;
			boxf.y = -240;
			boxf.w = 320;
			boxf.h = 480;
			boxf.r =
			boxf.g =
			boxf.b = fade.col;
			GsSortBoxFill( &boxf, ot, 0);
		}
	return (fade.status);
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FADE INIT                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void FadeInit(char mode, short rate)
{
	fade.status = mode;
	switch(fade.status) {
		case 0:
			break;
		case 1:		// フェードイン
		case 3:		// ホワイトフェードイン
			fade.col = 0x100;
			fade.rate = -rate;
			break;
		case 2:		// フェードアウト
		case 4:		// ホワイトフェードアウト
			fade.col = 0x000;
			fade.rate = rate;
			break;
	}
}


