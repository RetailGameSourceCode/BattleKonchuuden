/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : FADE SUBROUTINE                                          */
/*  File Attribute: HEADER                                                   */
/*  File Name     : FADE.H                                                   */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _FADE_H_
#define _FADE_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FADE DEFINE                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define FADE_IN		(1)
#define FADE_OUT	(2)
#define WHITE_IN	(3)
#define WHITE_OUT	(4)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  FADE WORK                                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	char			status;
	short			col;
	short			rate;
} FADEWORK ;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern FADEWORK fade;

extern void FadeInit(char mode, short rate);
extern u_char FadeSub(GsOT *ot);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _FADE_H_ */
