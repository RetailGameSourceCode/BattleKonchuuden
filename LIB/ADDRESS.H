/*----------------------------------------------*/
/*												*/
/*	  file name : addrss.h / RAM Assignment		*/
/*												*/
/*----------------------------------------------*/
#ifndef __ADDRESS_H__
#define __ADDRESS_H__

/*-----< RAM address >------*/
#define EXPAND_ADDR	(0x80100000)	/* 展開用エリア */
#define LOAD_ADDR	(0x80120000)	/* ＣＤからロードするエリア */
#define WORK_ADDR	(0x80140000)	/* ワークエリア */
#define STATIC_ADDR	(0x80180000)	/* 常駐デ－タ */
#define SOUND_ADDR	(0x801e0000)	/* サウンドデ－タ */

#endif	/* __ADDRESS_H__ */
