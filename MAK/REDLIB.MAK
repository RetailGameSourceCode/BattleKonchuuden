#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : INSECT POKEMON                                           */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS SND MAKING BATCH [ MAIN PROCESS ]                */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : REDLIB.MAK                                               */
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
RED_DIR=../redlib

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../redlib/redlib.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_RED =     ../redlib/ak_sound.obj   ../redlib/ak_sntbl.obj \
              ../redlib/ak_work.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  LIB MAIKING                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/lib/redlib.lib: $(OBJ_RED)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/redlib.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(RED_DIR)/ak_sound.obj: $(RED_DIR)/ak_sound.c
    $(CC) $(CCFLGS) $(RED_DIR)/ak_sound.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(RED_DIR)/ak_sntbl.obj: $(RED_DIR)/ak_sntbl.c
    $(CC) $(CCFLGS) $(RED_DIR)/ak_sntbl.c

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(RED_DIR)/ak_work.obj: $(RED_DIR)/ak_work.c
    $(CC) $(CCFLGS) $(RED_DIR)/ak_work.c

