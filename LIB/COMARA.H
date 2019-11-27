/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : COMMON AREA TAGS                                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : COMARA.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _COMARA_H_
#define _COMARA_H_

/*----- Language Header Files -----*/
#include <sys/types.h>

/*----- User Header     Files -----*/
#include "mainsys.h"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  OVER LAY INFORMATION                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   int                          ss;    /* Start  Sector                      */
   int                          ns;    /* Number Sector                      */
} OVS_INF;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  GAME CONTROL BLOCK                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   OVS_INF     ovs[ PRCS_TBL_MAX ];    /* Over Ray Section Information       */
   u_long      GlobalTimer;
   u_long      ClearMode;
   u_long      TitleSelect;
   u_short     bg_no;
   u_short     turn;
   u_short     chrno[2];
   u_short     lv[2];
   u_long      hp[2];
   u_long      dp[2];
   u_long      hpmax[2];
   u_long      dpmax[2];
   u_short     ap[2];
   u_short     at[2];
   u_char      df[2];
   u_char      hrate[2];
   u_char      erate[2];
   u_char      crank[2];
   u_char      arank[2];
   u_long      actuator;
} GCB;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOVIE                                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
    signed char                 no;    /* Number                             */
    u_char                    task;    /* Task                               */
    u_short                   time;    /* Timer                              */
} MOVIE;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GCB   gcb;
extern MOVIE movie;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _COMARA_H_ */
