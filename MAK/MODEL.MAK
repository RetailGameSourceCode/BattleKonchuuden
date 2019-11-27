#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : INSECT POKEMON MAKING BATCH [ DEV CODE: 98025 ]          */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : MODEL.MAK                                                */
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
MODEL_DIR=../model
P01_GRP=
#-Wa,sprcs01

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../model/model.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_MODEL =   ../model/model.obj  \
              ../model/surmap.obj \
              ../model/surmap2.obj \
              ../model/wire.obj \
              ../model/wire2.obj \
              ../model/color.obj \
              ../model/tpage.obj \
              ../model/optcmf.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/model.lib: $(OBJ_MODEL)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/model.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
MODEL_DEP =        ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h         ../lib/grpara.h          \
                   ../lib/sysara.h          ../lib/comara.h          \
                   ../lib/model.h         \
                   ../p00/initsys.ext       ../p00/ldaddr.ext        \
                   ../p00/mainsys.tbl

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/model.obj: $(MODEL_DIR)/model.c $(MODEL_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/model.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/surmap.obj: $(MODEL_DIR)/surmap.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/surmap.c
	dmpsx -b $(MODEL_DIR)/surmap.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/surmap2.obj: $(MODEL_DIR)/surmap2.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/surmap2.c
	dmpsx -b $(MODEL_DIR)/surmap2.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/wire.obj: $(MODEL_DIR)/wire.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/wire.c
	dmpsx -b $(MODEL_DIR)/wire.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/wire2.obj: $(MODEL_DIR)/wire2.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/wire2.c
	dmpsx -b $(MODEL_DIR)/wire2.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/color.obj: $(MODEL_DIR)/color.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/color.c
	dmpsx -b $(MODEL_DIR)/color.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/tpage.obj: $(MODEL_DIR)/tpage.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/tpage.c
	dmpsx -b $(MODEL_DIR)/tpage.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(MODEL_DIR)/optcmf.obj: $(MODEL_DIR)/optcmf.c
    $(CC) $(CCFLGS) $(P01_GRP) $(MODEL_DIR)/optcmf.c
	dmpsx -b $(MODEL_DIR)/optcmf.obj

