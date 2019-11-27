/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : EXTEND MEMORY CARD LIBRARY                               */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBEMC.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBEMC_H_
#define _LIBEMC_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MEMORY CARD MACRO                                                        */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define EMC_BLOCK_MAX            15    /* Block Max                          */
#define EMC_SECTOR_SIZE         128    /* Sector Size                        */
#define EMC_BLOCK_SIZE         8192    /* Block Size                         */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define EMC_UNUSE                 0    /* Unuse                              */
#define EMC_USE                   1    /* Use                                */
#define EMC_FAILURE               0    /* Failure                            */
#define EMC_SUCCESS               1    /* Success                            */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define EMC_ICON_TYPE1         0x11    /* Icon Animation Type 1              */
#define EMC_ICON_TYPE2         0x12    /* Icon Animation Type 2              */
#define EMC_ICON_TYPE3         0x13    /* Icon Animation Type 3              */
#define EMC_ICON_CLUT            20    /* Icon Clut                          */
#define EMC_ICON_IMAGE           64    /* Icon Image                         */
#define EMC_ICON_IMAGE_OFFSET   128    /* Icon Image Offset                  */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define EMC_ERR_NONE            (0)    /* Error None                         */
#define EMC_ERR_CARD_NOT_EXIST (-1)    /* Error Card Not Exist               */
#define EMC_ERR_CARD_INVALID   (-2)    /* Error Card Invalid                 */
#define EMC_ERR_NEW_CARD       (-3)    /* Error New Card                     */
#define EMC_ERR_NOT_FORMAT     (-4)    /* Error Not Format                   */
#define EMC_ERR_FILE_NOT_EXIST (-5)    /* Error File Not Exist               */
#define EMC_ERR_ALREADY_EXIST  (-6)    /* Error Already Exist                */
#define EMC_ERR_BLOCK_FULL     (-7)    /* Error Block Full                   */
#define EMC_ERR_EXTEND    (-0x8000)    /* Error Extend                       */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define EMC_ERR_NEW           (-10)    /* Error New                          */
#define EMC_ERR_ENTRY         (-11)    /* Error Entry                        */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  STRUCTURES                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   char                 Magic[ 2 ];    /* Magic                              */
   char                       Type;    /* Type                               */
   char                 BlockEntry;    /* Block Entry                        */
   char                Title[ 64 ];    /* Title                              */
   char              Reserve[ 28 ];    /* Reserve                            */
   char                 Clut[ 32 ];    /* Clut                               */
   char           Icon[ 3 ][ 128 ];    /* Icon                               */
} MEM_CARD_HEADER;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   u_char              title[ 64 ];    /* Icon Title                         */
   u_long                    *clut;    /* Icon Clut                          */
   u_long                  *image1;    /* Icon Image 1                       */
   u_long                  *image2;    /* Icon Image 2                       */
   u_long                  *image3;    /* Icon Image 3                       */
} MEM_CARD_INFO;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern MEM_CARD_INFO mc_info;

extern int EmcGetSectorSize( int byte );
extern int EmcGetBlockSize( int byte );
void EmcSetMemCard( u_char type, u_char *addr, u_char *title );
extern long EmcErrorMemCard( u_long rslt );
extern void EmcInitMemCard( long val );
extern long EmcSearchMemCardFile( long chan, char *file );
extern long EmcCheckMemoryCardBlock( long chan );
extern long EmcCreateMemCard( long chan, char *file, u_long len,
                              u_char *title, u_char type, u_long *clut,
                              u_long *image1, u_long *image2, u_long *image3 );
extern long EmcReadMemCard( long chan, char *file, u_long *addr,
                                                   short snum, short soff );
extern long EmcWriteMemCard( long chan, char *file, u_long *addr,
                                                    short snum, short  soff );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBEMC_H_ */
