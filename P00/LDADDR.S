;*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
;*  System Name   : INSECT POKEMON                                           */
;*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
;*  Language      : ASSEMBLER                                                */
;*                                                                           */
;*  File Contents : LOAD ADDRESSS PROCEDURES                                 */
;*  File Attribute: SOURCE                                                   */
;*  File Name     : LDADDR.S                                                 */
;*                                                                           */
;*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
              opt       c+

prcs01        group
prcs08        group

              xdef      LoadAddress
              xdef      LoadAddress8

              section   .rdata

LoadAddress   dw        group(prcs01)
LoadAddress8  dw        group(prcs08)
