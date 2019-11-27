#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  System Name   : SUCHIE ADV                                               */
#*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
#*  Language      : GNU MAKE                                                 */
#*                                                                           */
#*  File Contents : PROCESS 12 MAKING BATCH [ QUIZ PROCESS ]                 */
#*  File Attribute: MAKEFILE                                                 */
#*  File Name     : TEST.MAK                                                 */
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
TEST_DIR=../test
TEST_GRP=-Wa,sprcs06

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#   LIB DEFINES                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
LB=psylib
LBLST=../test/test.lst
LBFLGS=/u

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
OBJ_TEST =	../test/test.obj \
			../test/anmdata.obj \
			../test/player.obj \
			../test/shot.obj \
			../test/effect.obj \
			../test/enemy.obj \
			../test/tama.obj

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  OBJECT LINK                                                              */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(DEV_DIR)/test.lib: $(OBJ_TEST)
    $(LB) $(LBFLGS) $(DEV_DIR)/lib/test.lib @$(LBLST)
    psymake /f sir.mak

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE DEPENDS                                                           */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
QUIZ_DEP =    ../lib/libfio.h          \
              ../lib/lz.h              ../test/aki_def.h

#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#*  SOURCE COMPILES                                                          */
#*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
$(TEST_DIR)/test.obj: $(TEST_DIR)/test.c $(QUIZ_DEP)
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/test.c

$(TEST_DIR)/anmdata.obj: $(TEST_DIR)/anmdata.c $(QUIZ_DEP) \
						 $(TEST_DIR)/chr/boss2.c
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/anmdata.c

$(TEST_DIR)/player.obj: $(TEST_DIR)/player.c $(QUIZ_DEP)
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/player.c

$(TEST_DIR)/shot.obj: $(TEST_DIR)/shot.c $(QUIZ_DEP) $(TEST_DIR)/shot.h
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/shot.c

$(TEST_DIR)/effect.obj: $(TEST_DIR)/effect.c $(QUIZ_DEP)
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/effect.c

$(TEST_DIR)/enemy.obj: $(TEST_DIR)/enemy.c $(QUIZ_DEP) $(TEST_DIR)/enemy.h
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/enemy.c

$(TEST_DIR)/tama.obj: $(TEST_DIR)/tama.c $(QUIZ_DEP) $(TEST_DIR)/tama.h
    $(CC) $(CCFLGS) $(TEST_GRP) $(TEST_DIR)/tama.c

