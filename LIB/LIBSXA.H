/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SOUND XA LIBRARY                                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBSXA.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBSXA_H_
#define _LIBSXA_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  XA MACRO                                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SXA_BLOCK                0    /* XA Mode: Block                     */
#define  SXA_NON_BLOCK            1    /* XA Mode: Non Block                 */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SXA_READY                0    /* XA Status: Ready                   */
#define  SXA_PLAY                 1    /* XA Status: Play                    */
#define  SXA_PAUSE                2    /* XA Status: Pause                   */
#define  SXA_SET                  3    /* XA Status: Set                     */
#define  SXA_RESET                4    /* XA Stauus: Reset                   */
#define  SXA_ACTIVE               5    /* XA Status: Active                  */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SXA_SECT_SIZE         2336    /* Sector Size                        */
#define  SXA_RING_SIZE            1    /* Ring Size                          */
#define  SXA_TEMP_SIZE            SXA_SECT_SIZE * SXA_RING_SIZE

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SXA_ERR_MAX             16    /* Error Max                          */
#define  SXA_CH_MAX              32    /* Channel Max                        */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SXA_NML_SPEED         0x00    /* Normal Speed                       */
#define  SXA_DBL_SPEED CdlModeSpeed    /* Double Speed                       */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRUCTURES                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_char                     sfno;    /* XA File    No.                     */
   char                         ch;    /* XA Channel No.                     */
   char                     offset;    /* Start Sector Offset                */
   char                        vol;    /* Play Volume                        */
   unsigned short             time;    /* Play Time                          */
   char                      speed;    /* Speed                              */
   char                        pad;    /* Padding                            */
} XA_DATA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern void SxaInitXa( CdlLOC *xa_loc_addr, XA_DATA *xa_dat_addr, char *buff );
extern void SxaVSyncXa();
extern void SxaPlayXa( int xa_no );
extern int SxaSeekXa( int xa_no );
extern void SxaStopXa();
extern void SxaPauseXa( u_int mode );
extern u_int SxaGetXaStatus( u_int mode );
extern u_int SxaGetXaMode();
extern void SxaSetXaSpeed( u_int speed );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBSXA_H_ */
