#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 00 MAKING BATCH [ MAIN PROCESS ]                 */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : P00.MAK                                                  */
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
P00_DIR=../p00

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../p00/mainsys.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_P00 =     ../p00/pubgrp.obj        ../p00/pubsys.obj   \
              ../p00/pubcom.obj        ../p00/mainsys.obj  \
              ../p00/initsys.obj       ../p00/ldaddr.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/mainsys.lib: $(OBJ_P00)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/mainsys.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
PUBGRP_DEP =       ../lib/grpara.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
PUBSYS_DEP =       ../lib/sysara.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
PUBCOM_DEP =       ../lib/comara.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
MAINSYS_DEP =      ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/libdat.h          ../lib/aki_def.h         \
                   ../lib/fade.h            \
                   ../p00/initsys.ext       ../p00/ldaddr.ext        \
                   ../p00/mainsys.tbl

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
INITSYS_DEP =      ../lib/libdbg.h          \
                   ../lib/libfio.h          \
                   ../lib/libdat.h          \
                   ../lib/lz.h              \
                   ../lib/grpara.h          \
                   ../lib/sysara.h          \
                   ../lib/comara.h          \
                   ../lib/mainsys.h         \
                   ../lib/address.h         \
                   ../lib/aki_def.h         \
                   ../lib/libsxa.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/pubgrp.obj: $(P00_DIR)/pubgrp.c $(PUBGRP_DEP)
    $(CC) $(CCFLGS) $(P00_DIR)/pubgrp.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/pubsys.obj: $(P00_DIR)/pubsys.c $(PUBSYS_DEP)
    $(CC) $(CCFLGS) $(P00_DIR)/pubsys.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/pubcom.obj: $(P00_DIR)/pubcom.c $(PUBCOM_DEP)
    $(CC) $(CCFLGS) $(P00_DIR)/pubcom.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/mainsys.obj: $(P00_DIR)/mainsys.c $(MAINSYS_DEP)
    $(CC) $(CCFLGS) $(P00_DIR)/mainsys.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/initsys.obj: $(P00_DIR)/initsys.c $(INITSYS_DEP)
    $(CC) $(CCFLGS) $(P00_DIR)/initsys.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(P00_DIR)/ldaddr.obj: $(P00_DIR)/ldaddr.s
    asmpsx /l ..\p00\ldaddr,..\p00\ldaddr

