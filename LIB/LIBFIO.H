/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : FILE I/O LIBRARY                                         */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBFIO.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBFIO_H_
#define _LIBFIO_H_

/*----- Language Header Files -----*/
#include <libcd.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FILE I/O MACRO                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  FIO_CD_READY             0    /* CD Ready                           */
#define  FIO_CD_ACTIVE            1    /* CD Active                          */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  FIO_MC_CHK              -1    /* Machine: Check                     */
#define  FIO_MC_PS                0    /*        : PlayStation               */
#define  FIO_MC_DEV               1    /*        : Develop                   */
#define  FIO_DEV_MEM     0x007fffff    /* Develop Memory                     */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  FIO_BLOCK                0    /* Block                              */
#define  FIO_NON_BLOCK            1    /* Non Block                          */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SECT_SIZE             2048
#define  SIM_BUF_SIZE       32*1024
#define  SIM_BUF_ADDR        ((void *)0x80700000)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRUCTURES                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   int                      cd_flg;    /* CD    Flag                         */
   int                     dbg_flg;    /* Debug Flag                         */
   int                        disc;    /* Disc No.                           */
   char                  *toc_buff;    /* TOC Buffer                         */
   char                 name[ 16 ];    /* Check File Name                    */
} FIO;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern FIO fio;

extern int FioGetMachine();
extern int FioReadStatus( int mode );
extern int FioCdSearchFile( CdlFILE *finfo, char *filename );
extern void FioInitCD( char *filename, u_char *toc_buf );
extern void FioInitMachine( char *filename, int flag );
extern void FioInitBootDisc( char *filename, u_char *buff );
extern int FioReadPC( char *filename, u_char *addr );
extern int FioReadCD( char *filename, u_char *addr );
extern int FioReadFile( char *filename, u_char *addr );
extern int FioReadFile2( char *filename, u_char *addr );
extern int FioDivReadPC( char *filename, u_char *addr, int ss, int ns );
extern int FioDivReadCD( char *filename, u_char *addr, int ss, int ns );
extern int FioDivReadFile( char *filename, u_char *addr, int ss, int ns );
extern int FioDivReadFile2( char *filename, u_char *addr, int ss, int ns );
extern int FioWritePC( char *filename, int len, u_char *addr );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBFIO_H_ */
