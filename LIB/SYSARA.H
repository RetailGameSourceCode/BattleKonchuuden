/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SYSTEM AREA TAGS                                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : SYSARA.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _SYSARA_H_
#define _SYSARA_H_

/*----- Language Header Files -----*/
#include <sys/types.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROCESS CONTROL BLOCK                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_char                      req;    /* Request                            */
   u_char                       no;    /* Number                             */
   u_char                      dbg;    /* Debug Flag                         */
   u_char                      pno;    /* Previous Number                    */
   u_char                      srst;   /* Soft Reset                         */
} PCB;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TABLE OF CONTENTS                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_char              buf[ 2048 ];    /* Buffer                             */
} TOC;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern PCB pcb;
extern TOC toc;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _SYSARA_H_ */
