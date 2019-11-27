/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : MAIN SYSTEM PROCEDURES                                   */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : MAINSYS.C                                                */
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
#include "../lib/czarpad.h"
#include "../lib/pad.h"

/*----- User External   Files -----*/
#include "initsys.ext"
#include "ldaddr.ext"

/*----- User Table      Files -----*/
#include "mainsys.tbl"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MAIN                                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int main( int argc, char **argv )
{
   u_short         buf_sts;
   u_char          sts, rate;
   int             rtn;
   int             line;

   InitSystem();                                 /* Initialize System        */

   for ( ; ; )
     {
      buf_sts = PSDIDX;

      GsOUT_PACKET_P = packet[ buf_sts ];

      /* Clear Ordering Table */
      GsClearOt( 0, 0, &ot[ buf_sts ] );

      FntPrint( "Line_%d_Rate_%d%%\n", line, rate );
      line = VSync(1);

//      CtlGetController();                        /* Get Controller Data      */
      PadGet();
	{
		int i;

		for (i = 0; i < 2; i++) {
			if ((Pad[i].id == 0x02) || 	// １６ボタンアナログ
				(Pad[i].id == 0x04) || 	// １６ボタン
				(Pad[i].id == 0x05)) {	// アナログジョイスティック
				PadDat[i].rpt = Pad[i].rpt;
				PadDat[i].dat = Pad[i].dat;
				PadDat[i].trg = Pad[i].trg;
			} else {
				PadDat[i].rpt = 
				PadDat[i].dat = 
				PadDat[i].trg = 0;
			}
		}
	}

      sts = FadeSub( &ot[ buf_sts ] );

      /* Process */
      if (( pcb.req > PRCS_00 ) && ( sts == 0 ))
        {
          if ( pcb.no != pcb.req )
            {
              bg_col[R] = 0x00;                        /* Clear color                   */
              bg_col[G] = 0x00;
              bg_col[B] = 0x00;

              pcb.pno = pcb.no;
              pcb.no  = pcb.req;

              if ( pcb.no == PRCS_08 ) {
                rtn = FioDivReadFile( "DT\\SIR.BIN",
                                      (u_char *)LoadAddress8,
                                      gcb.ovs[ pcb.no ].ss,
                                      gcb.ovs[ pcb.no ].ns );
              } else {
                rtn = FioDivReadFile( "DT\\SIR.BIN",
                                      (u_char *)LoadAddress,
                                      gcb.ovs[ pcb.no ].ss,
                                      gcb.ovs[ pcb.no ].ns );
              }

#ifndef PREPRE
              printf("PRCS_%d\n",pcb.no);
#endif
            }
          pcb.req = 0;
        }

      if ( prcs_tbl[ pcb.no ].func != NULL )  prcs_tbl[ pcb.no ].func();

      /* Software Reset */
#if PREPRE
#if 0
      if (( PadDat[0].dat & PADSL ) && ( PadDat[0].trg & PADST ) && (pcb.srst == 0))
        {
          memcpy( ( unsigned long *) 0x801ef800,(unsigned long * ) 0x801e0000,4096);

          XA_CLR();
          BGM_VOL_0();
          DATA_CLOSE(1);
          SOUND_E();
          ResetGraph(3);
          CdFlush();
          PadStopCom();
          StopCallback();
//        Return_PP();
          _96_init();
          LoadExec("cdrom:\\MAINMENU.;1",0x801fff00,0);
        }
#else
      if (( pcb.no != PRCS_05 ) && ( pcb.no != PRCS_02 ))
        {
          if (( PadDat[0].dat & PADL1 ) && ( PadDat[0].dat & PADR1 ) &&
              ( PadDat[0].dat & PADSL ) && ( PadDat[0].trg & PADST ) && (pcb.srst == 0))
            {
              gcb.ClearMode = 0;
              pcb.req = PRCS_02;

              memcpy( ( unsigned long *) 0x801ef800,(unsigned long * ) 0x801e0000,4096);

              XA_CLR();
              BGM_VOL_0();
              DATA_CLOSE(1);
              SOUND_E();
            }
        }
#endif
#else
      if ( pcb.no != PRCS_02 )
        {
          if (( PadDat[0].dat & PADL1 ) && ( PadDat[0].dat & PADR1 ) &&
              ( PadDat[0].dat & PADSL ) && ( PadDat[0].trg & PADST ) && (pcb.srst == 0))
            {
              gcb.ClearMode = 0;
              pcb.req = PRCS_02;

              memcpy( ( unsigned long *) 0x801ef800,(unsigned long * ) 0x801e0000,4096);

              XA_CLR();
              BGM_VOL_0();
              DATA_CLOSE(1);
              SOUND_E();
            }
        }
#endif

      CountSystemTime();

//      SndFade();

    if ( pcb.no != PRCS_06 )
      DrawSync(0);                               /* Wait Drawing             */

      line = VSync(1) - line;
      rate = ((line * 100) / 512);

      VSync(0);                                  /* Wait V-BLANK (1/60)      */

      ResetGraph(1);

    if (gcb.ClearMode != 3)
      GsSwapDispBuff();                          /* Swap Double Buffer       */

      /* Set SCREEN CLEAR PACKET OT */
      switch (gcb.ClearMode) {
		case 0:
		    if ( pcb.no != PRCS_06 )
	        {
              RECT rect;

              setRECT( &rect, 0, 8, 320, 224 );
              GsSetClip2D( &rect );                    /* Display Masking               */
	        }
	        GsSortClear( bg_col[R], bg_col[G], bg_col[B], &ot[ buf_sts ] );
			break;
		case 1:
	        {
	          GsBOXF boxf;
              RECT rect;

              setRECT( &rect, 0, 0, 320, 240 );
              GsSetClip2D( &rect );                    /* Display Masking               */
              GsSetDrawBuffClip();
	          boxf.attribute = SBLEND;
	          boxf.x = -160;
	          boxf.y = -120;
	          boxf.w = 320;
	          boxf.h = 240;
	          boxf.r = bg_col[R];
	          boxf.g = bg_col[G];
	          boxf.b = bg_col[B];
	          GsSortBoxFill( &boxf, &ot[ buf_sts ], (1 << OT_LENGTH) - 1);
	        }
			break;
		case 2:
	        {
	          GsBOXF boxf;
              RECT rect;

              setRECT( &rect, 0, 0, 320, 240 );
              GsSetClip2D( &rect );                    /* Display Masking               */
              GsSetDrawBuffClip();
	          boxf.attribute = ABLEND;
	          boxf.x = -160;
	          boxf.y = -120;
	          boxf.w = 320;
	          boxf.h = 240;
	          boxf.r = bg_col[R];
	          boxf.g = bg_col[G];
	          boxf.b = bg_col[B];
	          GsSortBoxFill( &boxf, &ot[ buf_sts ], (1 << OT_LENGTH) - 1);
	        }
			break;
      }

      /* Drawing OT */
    if (gcb.ClearMode != 3)
      GsDrawOt( &ot[ buf_sts ] );

#ifndef PREPRE
      /* Debug Display */
      if ( PadDat[ 0 ].trg & PADSL )
        {
         if ( pcb.dbg == 0 )  pcb.dbg = 1;
         else                 pcb.dbg = 0;
        }
#endif

      if ( pcb.dbg == 1 )  FntFlush( -1 );

      if ( FioGetMachine() == FIO_MC_DEV )
        {
          DbgViewFrameBuff( (u_long)(PadDat[0].dat | ( PadDat[1].dat << 16)) );

          pollhost();
        }

     }

   return( 1 );
}
