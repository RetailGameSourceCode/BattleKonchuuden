/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SOUND DA LIBRARY                                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBSDA.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBSDA_H_
#define _LIBSDA_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CONTROLLER MACRO                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SDA_BLOCK                0    /* DA Mode: Block                     */
#define  SDA_NON_BLOCK            1    /* DA Mode: Non Block                 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SDA_READY                0    /* DA Status: Ready                   */
#define  SDA_ACTIVE               1    /* DA Status: Active                  */
#define  SDA_SET                  2    /* DA Status: Set                     */
#define  SDA_RESET                3    /* DA Status: Reset                   */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRUCTURES                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   CdlFILE                    file;    /* File Location                      */
   u_int                      stat;    /* Status                             */
   u_char           ModeParam[ 4 ];    /* Mode  Parameter                    */
   u_char          PauseParam[ 8 ];    /* Pause Parameter                    */
} DA_DATA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern void SdaInitDa( u_char *p, u_short l, u_short r, CdlLOC *offloc );
extern u_int SdaGetDaStatus( u_int mode );
extern void SdaPlayDa();
extern void SdaPauseDa( u_int mode );
extern void SdaStopDa();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBCTL_H_ */
