#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 01 MAKING BATCH [ SUB PROCESS ]                  */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : P01.MAK                                                  */
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
P01_DIR=../p01
PSX_DIR=/psx/lib

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OVERLAY DEFINES                                                          */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
P01_GRP=-Wa,sprcs01

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../p01/polygon.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_P01 =     ../p01/polygon.obj            ../p01/anmdata.obj \
              ../p01/bg.obj                 ../p01/poly_sub.obj \
              ../p01/battle.obj             ../p01/pinit.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/polygon.lib: $(OBJ_P01)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/polygon.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
POLYGON_DEP =      ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/model.h           ../lib/fade.h            \
                   ../lib/polygon.h         \
                   ../sprite/sprite.h       \
                   ../p01/bg.h              \
                   ../p01/poly_sub.h        \
                   ../p01/battle.h          \
                   ../p01/pinit.h           \
                   ../p01/anmdata.h         \
                   ../redlib/sndno.h        \
                   ../redlib/xano.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
ANMDATA_DEP =      ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../p01/sprite/fix.c \
                   ../p01/sprite/efect1.c \
                   ../p01/sprite/renda.c \
                   ../p01/sprite/ap2.c \
                   ../p01/sprite/vs.c \
                   ../p01/sprite/nizi.c \
                   ../p01/sprite/syouri.c \
                   ../p01/sprite/flare.c \
                   ../p01/sprite/beem3.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P01_DIR)/polygon.obj: $(P01_DIR)/polygon.c $(P01_DIR)/pdata.tbl $(P01_DIR)/player.tbl $(POLYGON_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/polygon.c

$(P01_DIR)/poly_sub.obj: $(P01_DIR)/poly_sub.c $(POLYGON_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/poly_sub.c
	dmpsx -b $(P01_DIR)/poly_sub.obj

$(P01_DIR)/bg.obj: $(P01_DIR)/bg.c  $(P01_DIR)/bg/bg.rep $(POLYGON_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/bg.c

$(P01_DIR)/battle.obj: $(P01_DIR)/battle.c $(P01_DIR)/battle.tbl $(POLYGON_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/battle.c

$(P01_DIR)/pinit.obj: $(P01_DIR)/pinit.c $(P01_DIR)/model/model.rep $(P01_DIR)/pdata.tbl $(P01_DIR)/player.tbl $(POLYGON_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/pinit.c

$(P01_DIR)/anmdata.obj: $(P01_DIR)/anmdata.c $(ANMDATA_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(P01_DIR)/anmdata.c

