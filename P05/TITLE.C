/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : TITLE MAP                                                */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : TITLE.C                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>

/*----- User Header     Files -----*/
#include "../lib/libctl.h"
#include "../lib/libfio.h"
#include "../lib/grpara.h"
#include "../lib/sysara.h"
#include "../lib/comara.h"
#include "../lib/mainsys.h"

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TITLE                                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
int Title()
{
	FntPrint("TITLE");

   return( 0 );
};

