/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : SPRITE OFFSET                                            */
/*  File Attribute: HEADER                                                   */
/*  File Name     : ANMDATA.H                                                */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _ANMDATA_H_
#define _ANMDATA_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  SPRITE OFFSET                                                            */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define zuk_ofs		(0)
#define zu_namevs_ofs	(zuk_ofs + 7)
#define zu_panel_ofs	(zu_namevs_ofs + 2)

extern CzAnimData *Zu_SequenceTbl[];

#endif  /* _ANMDATA_H_ */
