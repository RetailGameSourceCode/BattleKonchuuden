/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : GRAPHIC 2D LIBRARY                                       */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBG2D.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBG2D_H_
#define _LIBG2D_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SPRITE MACRO                                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  SPRT_NORMAL              0    /* Sprite Speed Normal                */
#define  SPRT_FAST                1    /* Sprite Speed Fast                  */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern void G2dGetTimInfo( u_char *addr, GsIMAGE *img );
extern void G2dSetTimFrameBuff( u_char *addr );
extern void G2dSetTimFrameBuff2( u_char *addr, RECT *ir, RECT *cr );
extern u_long G2dGetTMode( GsIMAGE *img );
extern u_short G2dGetTPage( GsIMAGE *img );
extern void G2dCreateSprite( GsSPRITE *sp, GsIMAGE *img, short x, short y );
extern void G2dCreateSprite2( GsSPRITE *sp, GsIMAGE *img, short x, short y );
extern void G2dWindowClip( RECT *rect, GsOT *ot, u_short pri0, u_short pri1 );
extern void G2dEntrySprite( GsSPRITE *sp, GsOT *otp, u_short pri, u_char flg );
extern void G2dEntryCrossSprite( GsSPRITE *sp, GsOT *otp, u_short pri,
                                 u_char flg, u_char r, u_char g, u_char b );
extern void G2dWriteImage( RECT *rect, u_long *p );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBG2D_H_ */
