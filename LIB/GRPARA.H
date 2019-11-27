/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : GRAPHICS AREA TAGS                                       */
/*  File Attribute: HEADER                                                   */
/*  File Name     : GRPARA.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _GRPARA_H_
#define _GRPARA_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ORDERING TABLE                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define OT_LENGTH	13		/* オーダリングテーブルの解像度 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  GPU PACKET                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define PACKETMAX	3000	/* Max GPU packets */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GsOT          ot[2];						/* オーダリングテーブルハンドラ */
extern GsOT_TAG      ot_tag[2][1<<OT_LENGTH];	/* オーダリングテーブル実体     */
extern PACKET        packet[2][PACKETMAX*24];	/* GPU Packet Buffer            */
extern unsigned char bg_col[3];					/* CLEAR COLOR / BACK COLOR / FOG(FAR) COLOR etc */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _GRPARA_H_ */
