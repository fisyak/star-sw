*
* $Id: grmul.F,v 1.1.1.2 2009/02/01 17:10:26 fisyak Exp $
*
* $Log: grmul.F,v $
* Revision 1.1.1.2  2009/02/01 17:10:26  fisyak
* Merge with .DEV2
*
* Revision 1.1.1.1  2008/12/10 20:47:55  fisyak
* Merge with macos version
*
* Revision 1.1.1.1  2005/05/25 22:37:36  fisyak
* Alice version of geant3 (-minicern)
*
* Revision 1.1.1.1  2002/07/24 15:56:25  rdm
* initial import into CVS
*
* Revision 1.1.1.1  2002/06/16 15:18:39  hristov
* Separate distribution  of Geant3
*
* Revision 1.1.1.1  1999/05/18 15:55:17  fca
* AliRoot sources
*
* Revision 1.1.1.1  1995/10/24 10:20:54  cernlib
* Geant
*
*
#include "geant321/pilot.h"
*CMZ :  3.21/02 29/03/94  15.41.30  by  S.Giani
*-- Author :
      SUBROUTINE GRMUL(RMAT,IROT,RMATN)
C.
C.    ******************************************************************
C.    *                                                                *
C     *      ROUTINE MULTIPLIES ROTATION MATRIX RMAT BY THE            *
C     *       IROT TH MATRIX IN THE GEANT ROTATION MATRIX BANK         *
C     *     TO PRODUCE THE MATRIX RMATN SUCH THAT RMATN IS             *
C     *       THE RESULT OF FIRST RMAT THEN IROT.                      *
C     *                                                                *
C.    *    ==>Called by : GTRMUL                                       *
C.    *         Author  A.McPherson  *********                         *
C.    *                                                                *
C.    ******************************************************************
C.
#include "geant321/gcbank.inc"
      DIMENSION RMAT(10),RMATN(10)
C.
C.    ------------------------------------------------------------------
C.
      IF(IROT.EQ.0) THEN
         DO 10 I=1,10
            RMATN(I)=RMAT(I)
   10    CONTINUE
      ELSE
         JR=LQ(JROTM-IROT)
         RMATN(10)=1.
         IF(RMAT(10).EQ.0.0) THEN
            DO 20 I=1,9
               RMATN(I)=Q(JR+I)
   20       CONTINUE
         ELSE
C
            DO 30 KO=1,9
               RMATN(KO)=0.0
C
               KO1=(KO-1)/3+1
               KO2=KO-(KO1-1)*3
C
               DO 30 IN=1,3
                  KI1=KO2+(IN-1)*3
                  KI2=IN+(KO1-1)*3
                  RMATN(KO)=RMATN(KO)+RMAT(KI1)*Q(JR+KI2)
   30       CONTINUE
         ENDIF
      ENDIF
      END
