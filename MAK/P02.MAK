#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 02 MAKING BATCH [ SUB PROCESS ]                  */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : P02.MAK                                                  */
#*                                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  MAKEFILE DEFINES                                                         */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
CC=ccpsx
#CCFLGS=-g -G0 -c -v -comments-c++ -Wall -D_DEBUG
CCFLGS=-g -O4 -G0 -c -v -comments-c++ -Wall -D_RELEASE

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
DEV_DIR=..
P02_DIR=../p02
PSX_DIR=/psx/lib

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OVERLAY DEFINES                                                          */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
P02_GRP=-Wa,sprcs02

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../p02/menu.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_P02 =     ../p02/menu.obj     ../p02/anmdata.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/menu.lib: $(OBJ_P02)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/menu.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
MENU_DEP =         ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/menu.h            \
                   ../redlib/sndno.h        \
                   ../p02/menu.tbl

ANMDATA_DEP =      ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../p02/sprite/fixmenu.c \
                   ../p02/sprite/fixmenu2.c \
                   ../p02/sprite/fixb2b.c \
                   ../p02/sprite/fix2.c \
                   ../p02/sprite/fix.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P02_DIR)/menu.obj: $(P02_DIR)/menu.c $(MENU_DEP)
    $(CC) $(CCFLGS) $(P02_GRP) $(P02_DIR)/menu.c

$(P02_DIR)/anmdata.obj: $(P02_DIR)/anmdata.c $(ANMDATA_DEP)
    $(CC) $(CCFLGS) $(P02_GRP) $(P02_DIR)/anmdata.c

