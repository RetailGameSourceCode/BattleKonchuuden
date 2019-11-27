#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 06 MAKING BATCH [ SUB PROCESS ]                  */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : P06.MAK                                                  */
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
P06_DIR=../p06
PSX_DIR=/psx/lib

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OVERLAY DEFINES                                                          */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
P06_GRP=-Wa,sprcs06

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../p06/zukan.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_P06 =     ../p06/zukan.obj \
              ../p06/pinit.obj \
              ../p06/anmdata.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/zukan.lib: $(OBJ_P06)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/zukan.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
ZUKAN_DEP =        ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/zukan.h           \
                   ../lib/istatic.h         \
                   ../redlib/sndno.h        \
                   ../p06/pinit.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P06_DIR)/zukan.obj: $(P06_DIR)/zukan.c $(P01_DIR)/pdata.tbl $(ZUKAN_DEP)
    $(CC) $(CCFLGS) $(P06_GRP) $(P06_DIR)/zukan.c
	dmpsx -b $(P06_DIR)/zukan.obj

$(P06_DIR)/pinit.obj: $(P06_DIR)/pinit.c $(P01_DIR)/model/model.rep $(P06_DIR)/sprite/panel.rep \
                      $(P01_DIR)/pdata.tbl $(P01_DIR)/player.tbl $(ZUKAN_DEP)
    $(CC) $(CCFLGS) $(P06_GRP) $(P06_DIR)/pinit.c

$(P06_DIR)/anmdata.obj: $(P06_DIR)/anmdata.c $(ZUKAN_DEP)
    $(CC) $(CCFLGS) $(P06_GRP) $(P06_DIR)/anmdata.c

