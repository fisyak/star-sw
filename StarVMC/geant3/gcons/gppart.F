*
* $Id: gppart.F,v 1.1.1.3 2009/02/18 20:33:34 fisyak Exp $
*
* $Log: gppart.F,v $
* Revision 1.1.1.3  2009/02/18 20:33:34  fisyak
* *** empty log message ***
*
* Revision 1.1.1.1  2002/07/24 15:56:24  rdm
* initial import into CVS
*
* Revision 1.1.1.1  2002/06/16 15:18:37  hristov
* Separate distribution  of Geant3
*
* Revision 1.1.1.1  1999/05/18 15:55:16  fca
* AliRoot sources
*
* Revision 1.1.1.1  1995/10/24 10:20:16  cernlib
* Geant
*
*
#include "geant321/pilot.h"
*CMZ :  3.21/02 29/03/94  15.41.19  by  S.Giani
*-- Author :
      SUBROUTINE G3PPART (NUMB  )
C.
C.    ******************************************************************
C.    *                                                                *
C.    *       Routine to print particle definition JPART               *
C.    *       NUMB     Particle number                                 *
C.    *                                                                *
C.    *    ==>Called by : <USER>, G3PRINT                              *
C.    *       Author    R.Brun  *********                              *
C.    *                                                                *
C.    ******************************************************************
C.
#include "geant321/gcbank.inc"
#include "geant321/gcunit.inc"
      DIMENSION ITITLE(5)
      DIMENSION ITITLE1(5)
      DIMENSION ITITLE2(5)
      DIMENSION ITITLE3(5)
      DIMENSION BAREA(7)
      DIMENSION BETA(4)
      DIMENSION BRATIO(6)
      DIMENSION MODE(6)
      DIMENSION NTYPE(3)
      integer jp1, jp2, jp3
      character*80 chbr,chmod1,chmod2,chmod3
C.
C.    ------------------------------------------------------------------
C.
      IF (JPART.LE.0)  GO TO 99
C
      IF (NUMB  .EQ.0)THEN
         WRITE (CHMAIL,1000)
         CALL GMAIL(0,0)
         N1     = 1
         N2     = IQ(JPART-2)
      ELSE
         N1     = ABS(NUMB)
         N2     = ABS(NUMB)
      ENDIF
C
      IF(NUMB.GE.0) THEN
         WRITE (CHMAIL,1001)
         CALL GMAIL(0,1)
      ENDIF
C
      DO 10 I=N1,N2
         JP = LQ(JPART-I)
         IF (JP.NE.0)THEN
            IOPT = Q(JP+6)
            NL = IQ(JP-1)
            CALL UCOPY(IQ(JP+1),ITITLE,5)
            NW=MIN(NL,13)
            WRITE (CHMAIL,1002) I,ITITLE,IOPT,
     +                          (Q(JP + J),J = 7,NW)
    5       CALL GMAIL(0,0)
            IF(NL-NW.GT.0) THEN
               NS=NW+1
               NW=MIN(NL,NW+5)
               WRITE(CHMAIL,1003) (Q(JP + J),J = NS,NW)
               GO TO 5
            END IF
C     decay modes
            JDK1 = LQ(JP-1)
            JDK2 = LQ(JP-2)
            if (jdk1 .gt. 0 .and. jdk2 .gt. 0) then
               DO  j =1,6
                  BRATIO(j)=Q(JDK1+j)
                  MODE(j)=IQ(JDK2+j)
               enddo
C     
C             Generate branching ratio and select decay mode.
C
               NBR      = 0
               BAREA(1) = 0.
               DO  j=2,7
                  BRADD    = BRATIO(j-1)
                  IF (BRADD.EQ.0.) GO TO 20
                  NBR      = NBR+1
                  BAREA(j) = BAREA(j-1)+BRADD
               enddo
 20            continue
               do id = 1, nbr
C
C             Unpack decay mode.
C
                  MXX      = MODE(ID)
                  NTYPE(1) = MOD(MXX,100)
                  NTYPE(2) = MOD(MXX/100,100)
                  JP1 = LQ(JPART-NTYPE(1))
                  CALL UCOPY(IQ(JP1+1),ITITLE1,5)
                  JP2 = LQ(JPART-NTYPE(2))
                  CALL UCOPY(IQ(JP2+1),ITITLE2,5)
                  write(chbr,'(61x,g10.3)') bratio(id)
                  write(chmod1,'(5a4)') ititle1
                  write(chmod2,'(5a4)') ititle2
                  chmod3 = ' '
                  IF (MXX.gt.10000)THEN
                     NTYPE(3) = MXX/10000
                     JP3 = LQ(JPART-NTYPE(3))
                     CALL UCOPY(IQ(JP3+1),ITITLE3,5)
                     write(chmod3,'(5a4)') ititle3
                  endif
                  chmail = chbr//' '//TRIM(chmod1)//' '//TRIM(chmod2)//' '//TRIM(chmod3)
!                  write(chmail,'(4A)') chbr,chmod1,chmod2,chmod3
            CALL GMAIL(0,0)
               enddo
            endif
         ENDIF
   10 CONTINUE
C
 1000 FORMAT (' ',51('='),3X,'Particle Types',3X,50('='))
 1001 FORMAT (' ','Part',25X,'Options',8X,'Mass',4X,'Charge'
     +,'    Life time                  User words')
 1002 FORMAT (' ',I4,1X,5A4,I8,6X,E11.4,F7.0,3X,5(E12.5,2X))
 1003 FORMAT (61X,5(E12.5,2X))
   99  RETURN
      END
