
/*----------------------------------------------------------------------------+
|                                                                             |
|     Name   : Czar Debug Library Header File                                 |
| Description: Czar Debugライブラリーのプロトタイプ宣言                       |
|                                                                             |
|                                   1996-05-05 (Sun) 23:49:07                 |
|                                              Copyright (C) 1996 Indick-Czar |
+----------------------------------------------------------------------------*/

#if !defined _CZAR_DEBUG_H_
#define _CZAR_DEBUG_H_

/*----------------------------------------------------------------------------+
|    Include File                                                             |
+----------------------------------------------------------------------------*/
#include	<sys/types.h>
#include	<libsn.h>
#include	<libetc.h>
#include	<libgte.h>
#include	<libgpu.h>
#include	<libgs.h>

/*----------------------------------------------------------------------------+
|    Constant Declaration                                                     |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Data Type Declaration                                                    |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Prototype Declaration                                                    |
+----------------------------------------------------------------------------*/
signed int PrintInit(unsigned short tpage, GsOT *p);
signed int Print(signed char *p);
signed int Locate(unsigned short px, unsigned short py);
signed int SetColor(unsigned char col);
signed int GetColor(void);
signed int SetTime(unsigned int time);
signed int SetNum(unsigned int n);
unsigned char *CzMemDump(unsigned char x, unsigned char y, unsigned char *p);
void ActiveScope(unsigned short dat, unsigned short trg);

/*----------------------------------------------------------------------------+
|    Global Variable Declaration                                              |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Macro Declaration                                                        |
+----------------------------------------------------------------------------*/

#endif
