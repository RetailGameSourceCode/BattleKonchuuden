#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : INSECT POKEMON MAKING BATCH [ DEV CODE: 98025 ]          */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : SPRITE.MAK                                               */
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
SPRITE_DIR=../sprite
P01_GRP=
#-Wa,sprcs01

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../sprite/sprite.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_SPRITE =   ../sprite/sprite.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/sprite.lib: $(OBJ_SPRITE)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/sprite.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
SPRITE_DEP =        ../lib/libdbg.h          ../lib/libfio.h          \
                   ../lib/mainsys.h          ../lib/grpara.h          \
                   ../lib/sysara.h           ../lib/comara.h          \
                   ../lib/model.h          \
                   ../sprite/sprite.h      \
                   ../p01/anmdata.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILE                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(SPRITE_DIR)/sprite.obj: $(SPRITE_DIR)/sprite.c $(SPRITE_DEP)
    $(CC) $(CCFLGS) $(P01_GRP) $(SPRITE_DIR)/sprite.c
	dmpsx -b $(SPRITE_DIR)/sprite.obj

