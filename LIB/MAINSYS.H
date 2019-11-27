/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : MAIN SYSTEM PROCEDURES                                   */
/*  File Attribute: HEADER                                                   */
/*  File Name     : MAINSYS.H                                                */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _MAINSYS_H_
#define _MAINSYS_H_

#define  PREPRE (1)
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PRPCESS DEFINES                                                          */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define  PRCS_00                  0    /* Main         Process               */
#define  PRCS_01                  1    /* Battle       Process               */
#define  PRCS_02                  2    /* Menu         Process               */
#define  PRCS_03                  3    /* Strategy     Process               */
#define  PRCS_04                  4    /* Street       Process               */
#define  PRCS_05                  5    /* Title        Process               */
#define  PRCS_06                  6    /* Zukan        Process               */
#define  PRCS_07                  7    /* PDA          Process               */
#define  PRCS_08                  8    /* Memocar      Process               */
#define  PRCS_09                  9    /* Staff        Process               */
#define  PRCS_TBL_MAX            10    /* Process Table Max                  */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROCESS TABLE                                                            */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct
{
   int                   (*func)();    /* Process Function                   */
} PRCS_TBL;

#endif  /* _MAINSYS_H_ */
