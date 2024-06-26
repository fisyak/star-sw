*
* $Id: umpa.inc,v 1.1 2005/06/09 00:05:19 fisyak Exp $
*
* $Log: umpa.inc,v $
* Revision 1.1  2005/06/09 00:05:19  fisyak
* Add stuff for reconstruction
*
* Revision 1.1  2005/05/26 22:28:20  fisyak
* Add stuff necessary for reconstruction packages
*
* Revision 1.1.1.1  1996/02/15 17:48:56  mclareni
* Kernlib
*
*
*
* umpa.inc
*
          LUII  =  1
          LYI   =  1
          LZI   =  1
          DO 12     I  =  1, N
             LUIJ  =  LUII
             LYJ   =  LYI
             SUM   =  SIGNF( Z(LZI) )
             DO 11  J  =  I, N
                SUM   =  F(U(LUIJ),Y(LYJ),SUM)
                LUIJ  =  LUIJ + JU
                LYJ   =  LYJ + JY
  11            CONTINUE
             Z(LZI)  =  SUM
             LUII    =  LUII + KU
             LYI     =  LYI + JY
             LZI     =  LZI + IZ
  12         CONTINUE
          RETURN
          END
