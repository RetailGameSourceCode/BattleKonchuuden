
/*----------------------------------------------------------------------------+
|                                                                             |
|     Name   : LZ(Lempel-Ziv) Compression Data Decoder Header File Ver 0.06   |
| Description: LZ法によって圧縮されたデータを展開します。                     |
|                                                                             |
|                                   1996-01-24 (Wed) 13:16:53                 |
|                                              Copyright (C) 1995 Indick-Czar |
+----------------------------------------------------------------------------*/

#if !defined _LZ_H_
#define _LZ_H_

/*----------------------------------------------------------------------------+
|    Include File                                                             |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Constant Declaration                                                     |
+----------------------------------------------------------------------------*/
enum {
	LZS_IDLE,											/* Idling */
	LZS_ACTIVE,											/* Decoding */
};

/*----------------------------------------------------------------------------+
|    Prototype Declaration                                                    |
+----------------------------------------------------------------------------*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

signed int LzDecInit(unsigned char *cmp, unsigned char *buf, volatile unsigned char *vf);
signed int LzDec(void);
signed int LzDecB(void);
unsigned int LzGetStatus(void);
unsigned long LzGetRemain(void);
unsigned long LzCallBack(void (*func)(void));
unsigned char LzSetDecLevel(unsigned char lv);
unsigned char LzGetDecLevel(void);
void LzInit(void);
unsigned char *LzGetDecAddress(void);
void LzSetClearEndFlag(unsigned char *p);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
/*----------------------------------------------------------------------------+
|    Global Variable Declaration                                              |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
|    Macro Declaration                                                        |
+----------------------------------------------------------------------------*/

#endif
