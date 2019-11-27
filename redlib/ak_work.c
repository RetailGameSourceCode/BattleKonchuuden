/****************************************************************************************
*						赤沢サウンドツール												*
*														1998/7/21 written by red		*
****************************************************************************************/
#include <sys/types.h>
#include <libetc.h>
//#include <libgte.h>/*graphic system?*/
//#include <libgpu.h>
#include <libcd.h>
#include <libds.h>	/*cd-xa vol*/
#include <libsnd.h>/*sound system*/
#include <libsn.h> 
#include <stdio.h>/*for printf???*/

#include "ak_sound.h"/*赤沢ヘッダファイル*/
//#include "c:/psenv/psx/include/lz.h"/*lzdec*/
//#include "c:/psenv/psx/include/pk_sub.h"/*read_data*/
/****************************************************************************************
*						使用ハンドラ宣言												*
*																						*
****************************************************************************************/

//DslATV CD_VOL;/*xa のボリューム指定*/
CdlATV CD_VOL;// xa ボリューム指定
//KON SE_TBL[];/*サウンドテーブル*/
//CdlFILE	FP;		/*iso9660ファイルディスクリプタ*/
