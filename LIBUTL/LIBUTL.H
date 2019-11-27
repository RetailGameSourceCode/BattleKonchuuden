/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : UTILITY LIBRARY                                          */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBUTL.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBUTL_H_
#define _LIBUTL_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/* PROTOTYPE DIFINITIONS                                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern void UtlChar2Bin( u_short len, u_char *fr_dt, u_short *to_dt );
extern void UtlBin2Char( u_short len, u_short dt_wd, u_char *to_dt );
extern void UtlHexChar2Bin( u_short len, u_char *fr_dt, u_short *to_dt );
extern void UtlHexBin2Char( u_short len, u_short fr_dt, u_char *to_dt );
extern void UtlChar2Fig( u_short len, u_char *fr_dt, u_long *to_dt );
extern void UtlHexChar2Fig( u_short len, u_char *fr_dt, u_long *to_dt );
extern void UtlFig2Char( u_short len, u_long fr_dt, u_char *to_dt );
extern void UtlPack2Unpack( u_short len, u_char *fr_dt, u_char *to_dt );
extern void UtlUnpack2Pack( u_short len, u_char *fr_dt, u_char *to_dt );
extern void UtlSort( u_char act, u_short len, u_char *dt );
extern u_char UtlComp( u_char *cmp1, u_char *cmp2, u_short cnt );
extern int UtlFindStr( char *str1, char *str2 );
extern short UtlCosScroll( short a, short b, short total_time, short timer );
extern short UtlSinScroll( short a, short b, short total_time, short timer );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBUTL_H_ */
