/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : INITIALIZE SYSTEM PROCEDURES                             */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : INITSYS.C                                                */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libcd.h>
#include <libmcx.h>
#include <stdlib.h>

/*----- User Header     Files -----*/
#include "../lib/aki_def.h"
#include "../lib/mainsys.h"
#include "../lib/libdbg.h"
#include "../lib/libctl.h"
#include "../lib/libdat.h"
#include "../lib/libemc.h"
#include "../lib/libfio.h"
#include "../lib/libsxa.h"
#include "../lib/lz.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/address.h"

/*----- User External   Files -----*/
/* Non */

/*----- User Table      Files -----*/
/* Non */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE OVER LAY SECTION                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void InitOverLaySection()
{
   int             rtn , i;

   /* Get Data Head Information */
   rtn = FioDivReadFile( "DT\\SIR.BIN", (u_char *)LOAD_ADDR, 0, 1 );

   for ( i = PRCS_01; i < PRCS_TBL_MAX; i++ )
     {
       DatGetPackInfo( (u_char *)LOAD_ADDR,
                       i - 1,
                       &gcb.ovs[ i ].ss,
                       &gcb.ovs[ i ].ns );
     }
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE MAIN DATA                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void InitMainData()
{
   *(int *) 0x801ef9f0 = 0;
   pcb.srst = 0;
   pcb.req  = PRCS_08;
   gcb.actuator = 0;
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  COUNT SYSTEM TIME                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void CountSystemTime()
{
   rand();

   gcb.GlobalTimer++;
}

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  INITIALIZE SYSTEM                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
void InitSystem()
{
   RECT            rect;

   ResetGraph(0);		/* GPUリセット */
   InitGeom();			/* GTE初期化 */

   ResetCallback();                         /* Reset All CallBack            */
   GsInitVcount();                          /* Initialize V-counter          */

//   EmcInitMemCard( EMC_UNUSE );             /* Initialize Memory Card        */

   MemCardInit(0);//メモリーカードシステムの初期化
   MemCardStart();//メモリーカードシステムの稼動開始
   McxStartCom(); //PDAシステムの稼動

   PadManagerInit();
//   CtlInitControllerManager( DRV_TAP );     /* Initialize Controller         */

   VSync(0);                                  /* Wait V-BLANK (1/60)      */
   GsInitGraph( 320, 240, GsNONINTER | GsOFSGPU, 1, 0 ); /* Initialize Graphic System     */

   GsDefDispBuff( 0, 0, 0, 240 );           /* Double Buffer Setting         */

   setRECT( &rect, 0, 8, 320, 224 );
   GsSetClip2D( &rect );                    /* Display Masking               */

   GsInit3D();                              /* Init 3D System                */

   ot[0].length = OT_LENGTH;
   ot[0].org    = ot_tag[0];
   ot[1].length = OT_LENGTH;
   ot[1].org    = ot_tag[1];

   bg_col[R] = 0x00;                        /* Clear color                   */
   bg_col[G] = 0x00;
   bg_col[B] = 0x00;

   DsInit();                                /* Init CD                       */

//   VSyncCallback( SxaVSyncXa );             /* V-Sync Callback               */

   FioInitMachine( "SIR.CPE", FIO_MC_CHK );

   FioInitCD( "SIR.TBL", (u_char *)toc.buf );

//   SxaCdSearchFile();                       /* XA CD Search File             */

#ifndef PREPRE
   DbgInitFrameBuff( 0x01, 0x01, 0x1f );
   DbgInitFont( -152, -100, 0x1f, 0x1f, 0x1f, 1 );
#else
   GsClearDispArea( 0x00, 0x00, 0x00 );
#endif

   LzInit();

   SOUND_I();

   InitOverLaySection();

   InitMainData();

   VSync(0);                                  /* Wait V-BLANK (1/60)      */
}
