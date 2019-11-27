/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : ALL SYSTEM                                               */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : DEBUG LIBRARY                                            */
/*  File Attribute: HEADER                                                   */
/*  File Name     : LIBDBG.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _LIBDBG_H_
#define _LIBDBG_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  VRAM MACRO                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  TPAGE_MAX               32    /* TPage Max                          */
#define  UNIT_TPAGE_SIZE      32768    /* 64(w) * 256(h) * 2(byte)           */
#define  UNIT_TPAGE_W            64    /* TPage Width                        */
#define  UNIT_TPAGE_H           256    /* TPage Height                       */
#define  UNIT_H_W              1024    /* TPage Horizontal Width             */
#define  UNIT_H_H                 1    /* TPage Horizontal Height            */
#define  UNIT_V_W                 1    /* TPage Vertical   Width             */
#define  UNIT_V_H               512    /* TPage Vertical   Height            */
#define  UNIT_FONT_H             11    /* Font Height                        */
#define  UNIT_FONT_W              8    /* Font Width                         */
#define  UNIT_H_SIZE              UNIT_H_W * UNIT_H_H * 2
#define  UNIT_V_SIZE              UNIT_V_W * UNIT_V_H * 2
#define  RGB(r,g,b)               (b<<10)|(g<<5)|r

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  DBG_PAD2L_UP             (PADLup   <<16)
#define  DBG_PAD2L_DN             (PADLdown <<16)
#define  DBG_PAD2L_LT             (PADLleft <<16)
#define  DBG_PAD2L_RT             (PADLright<<16)
#define  DBG_PAD2_STT             (PADstart <<16)
#define  DBG_PAD2_SEL             (PADselect<<16)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FRAME RATE MACRO                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  FRAME_60                 0    /* Frame Count 1/60                   */
#define  FRAME_30                 1    /* Frame Count 1/30                   */
#define  HCNT_MAX               263    /* H-Count Max About 263 Line [1/60]  */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern void DbgInitFont( short x, short y,
                    u_char r, u_char g, u_char b, u_char cm );
extern void DbgInitFrameBuff( u_char r, u_char g, u_char b );
extern void DbgViewFrameBuff( u_long padd );
extern void DbgSetHcount();
extern void DbgGetHcount( int mode, long *line, u_char *rate );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _LIBDBG_H_ */
