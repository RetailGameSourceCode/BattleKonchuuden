#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 08 MAKING BATCH [ SUB PROCESS ]                  */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : P08.MAK                                                  */
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
P08_DIR=../p08
PSX_DIR=/psx/lib

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OVERLAY DEFINES                                                          */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
P08_GRP=-Wa,sprcs08

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../p08/akmcrd.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_P08 =     ../p08/akinit.obj \
              ../p08/akmcrd.obj \
              ../p08/ak_mctbl.obj \
              ../p08/redwork.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/akmcrd.lib: $(OBJ_P08)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/akmcrd.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
AKMCRD_DEP =        ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/akmcrd.h           \
                   ../lib/istatic.h         \
                   ../redlib/sndno.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P08_DIR)/akinit.obj: $(P08_DIR)/akinit.c $(AKMCRD_DEP)
    $(CC) $(CCFLGS) $(P08_GRP) $(P08_DIR)/akinit.c

$(P08_DIR)/akmcrd.obj: $(P08_DIR)/akmcrd.c $(AKMCRD_DEP)
    $(CC) $(CCFLGS) $(P08_GRP) $(P08_DIR)/akmcrd.c

$(P08_DIR)/ak_mctbl.obj: $(P08_DIR)/ak_mctbl.c $(AKMCRD_DEP)
    $(CC) $(CCFLGS) $(P08_GRP) $(P08_DIR)/ak_mctbl.c

$(P08_DIR)/akwork.obj: $(P08_DIR)/akwork.c $(AKMCRD_DEP)
    $(CC) $(CCFLGS) $(P08_GRP) $(P08_DIR)/akwork.c

