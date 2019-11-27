/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : HDLINK LIBRARY                                           */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBHDL.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBHDL_H_
#define _LIBHDL_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern u_char *DatGetHdlAddress( u_char *cmp, u_char no );
extern u_char DatGetHdlAppendNumber( u_char *cmp );
extern void DatGetHdlInfo( u_char *addr, u_char no,
                               int *ss, int *ns, long *offset, long *len );
extern u_char *DatGetPackAddress( u_char *cmp, u_int no );
extern u_char DatGetPackAppendNumber( u_char *cmp );
extern void DatGetPackInfo( u_char *addr, u_int no, int *ss, int *ns );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBHDL_H_ */
