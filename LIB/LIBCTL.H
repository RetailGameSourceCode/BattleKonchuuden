/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : CONTROLLER LIBRARY                                       */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBCTL.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBCTL_H_
#define _LIBCTL_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CONTROLLER MACRO                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define RCV_DAT_LEN              34    /* Recieve Data Buffer Length         */
#define PORT_MAX                  2    /* Port Max                           */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define PAD_MAX                   1    /* Pad Connect Max                    */
#define PAD_RB_MAX                2    /* Pad Repeat Button Max              */
#define PAD_RLV_MAX               8    /* Pad Repeat Level Max               */
#define PAD_ACT_MAX               2    /* Pad Actuater Max                   */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define TAP_PAD_MAX               4    /* Tap Pad Max                        */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define PAD_UNLOCK                0    /* Pad Unlock                         */
#define PAD_LOCK                  1    /* Pad Lock                           */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define SCE_MOUSE              0x01    /* Mouse                              */
#define NAMCO_16BTN_ANA        0x02    /* 16 Button Analog       [NAMCO.Ltd] */
#define KONAMI_GUN_CTRL        0x03    /* Gun Controller        [KONAMI.Ltd] */
#define SCE_16BTN              0x04    /* 16 Button                          */
#define SCE_ANA_JOYSTICK       0x05    /* Analog Joystick                    */
#define NAMCO_GUN_CTRL         0x06    /* Gun Controller         [NAMCO.Ltd] */
#define SCE_ANA_CTRL           0x07    /* Analog Controller                  */
#define SCE_MULTI_TAP          0x08    /* Multi Tap                          */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define DRV_PAD                   0    /* Pad Driver                         */
#define DRV_TAP                   1    /* Tap Driver                         */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define PADLU                PADLup
#define PADLR                PADLright
#define PADLD                PADLdown
#define PADLL                PADLleft
#define PADRU                PADRup
#define PADRR                PADRright
#define PADRD                PADRdown
#define PADRL                PADRleft
#define PADST                PADstart
#define PADSL                PADselect
#define PADR                 (PADRU | PADRD | PADRL | PADRR)
#define PADB                 PADR
#define PADL                 (PADLU | PADLD | PADLL | PADLR)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRUCTURES                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_short     Timer[ PAD_RB_MAX ];    /* Stored Pad Repeat Timer            */
   u_char      Speed[ PAD_RB_MAX ]
                   [ PAD_RLV_MAX ];    /* Pad Repeat Parameter               */
   u_char      Level[ PAD_RB_MAX ];    /* Repeat Level                       */
   u_char                       rr;    /* Recieve Result                     */
   u_char                       tk;    /* Terminal Kind                      */
   u_char                      flg;    /* Flag [ Player No. ]                */
   u_char                     send;    /* Send Flag                          */
   u_char     Motor[ PAD_ACT_MAX ];    /* Motor                              */
   u_char   Actflag[ PAD_ACT_MAX ];    /* Actuator Flag                      */
   u_char   Actimer[ PAD_ACT_MAX ];    /* Actuator Timer                     */
   u_char            Actalign[ 6 ];    /* Actuator Align                     */
   u_char                 pad[ 2 ];    /* Padding                            */
} PADMAN;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_short                     dat;    /* Data                               */
   u_short                     trg;    /* Trigger                            */
   u_short                     rpt;    /* Repeat                             */
   u_short                     old;    /* Pad Data Before 1 Frame            */
} PADDAT;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_char                      drv;   /* Controller Driver                   */
   u_char                      ptn;   /* Patern                              */
   u_char                      flg;   /* Flag [ Controller Lock ]            */
   u_char                      pad;   /* Padding                             */
} CTLMAN;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_short                     dat;    /* 16 Button Recieve Data             */
   u_char                 pad[ 2 ];    /* Padding                            */
} RECDAT;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   char         buf[ RCV_DAT_LEN ];    /* Recieve Data Buffer                */
} CONTROLLER;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern PADMAN     PadMan[ PORT_MAX * TAP_PAD_MAX ];
extern PADDAT     PadDat[ PORT_MAX * TAP_PAD_MAX ];
extern CTLMAN     CtlMan;
extern RECDAT     RecDat[ PORT_MAX ][ TAP_PAD_MAX ];
extern CONTROLLER Ctrl[ PORT_MAX ];

extern void CtlInitControllerManager( u_char driver );
extern void CtlGetController();
extern void CtlInitPadManager();
extern void CtlGetPad();
extern void CtlInitTapManager();
extern void CtlGetTap();
extern void CtlCheckDevice( u_char *d0, u_char *d1 );
extern void CtlSetPadVibration1( u_char num, u_short time );
extern void CtlSetPadVibration2( u_char num, u_short time, u_short lvl );
extern u_char CtlGetPadPortNumber( u_int no );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBCTL_H_ */
