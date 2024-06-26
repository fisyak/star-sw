* $Id: shxsec.F,v 1.1.1.1 2004/01/15 00:08:49 potekhin Exp $
* $Name:  $
#include <commons/config.h>
      SUBROUTINE SHXSEC(E,INC,SIGT,SIGEL,SIGNEL)
C
#include "gcalor/cinout.inc"
C
C CALCULATES PROTON AND NEUTRON CROSS SECTIONS FOR E > 3.5 GeV
C CALCULATES PI+    AND PI-     CROSS SECTIONS FOR E > 2.5 GeV
C       THE TARGET PARTICLE IS A PROTON
C       E ------- KINETIC ENERGY OF INCIDENT PARTICLE(MEV)
C       INC ----- TYPE OF INCIDENT PARTICLE
C                   0 -- PROTON
C                   1    NEUTRON
C                   2    PI+
C                   3    NOT USED
C                   4    PI-
C       SIGT ---- TOTAL CROSS SECTION(CM**2)
C       SIGEL --- ELASTIC CROSS SECTION(CM**2)
C       SIGNEL -- NONELASTIC CROSS SECTION(CM**2)
C
      REAL*8 E1
      IN = INC + 1
      E1 = E*1.D-3
      GO TO (20,30,50,10,80),IN
   10 CALL CERROR('CRSEC1')
C
   20 SIGT = 37.5D0 + 7.D0/(DSQRT(E1))
      SIGEL = 7.D0 + 21.03D0/(E1**0.873D0)
      GO TO 110
C
C
   30 IF(E1.GT.8.D0) GO TO 40
      SIGT = 42.D0
      SIGEL = -0.222D0*E1+12.48D0
      GO TO 110
   40 SIGT = 37.5D0 + 26.45D0/(E1**0.852D0)
      SIGEL = 6.0D0 + 73.144D0/(E1**1.32D0)
      GO TO 110
C
C
   50 IF(E1.GT.3.D0) GO TO 60
      SIGT = -4.66D0*E1 + 42.95D0
      SIGEL = -1.40D0*E1 + 10.0D0
      GO TO 110
   60 IF(E1.GT.6.D0) GO TO 70
      SIGT = -0.7567D0*E1 + 31.24D0
      SIGEL = -0.166D0*E1 + 6.298D0
      GO TO 110
   70 SIGT = 21.50D0 + 18.914D0/(E1**.7155D0)
      SIGEL = 3.5D0 + 9.93D0/(E1**.953D0)
      GO TO 110
C
C
   80 IF(E1.GT.5.D0) GO TO 90
      SIGT = -1.66D0*E1 + 37.34D0
      GO TO 100
   90 SIGT = 23.60D0 + 25.51D0/(E1**0.959D0)
  100 SIGEL = 3.8D0 + 7.273D0/(E1**0.896D0)
C
C
  110 SIGT = SIGT*1.E-27
      SIGEL = SIGEL*1.E-27
      SIGNEL = SIGT - SIGEL
C
      IF((IN.LE.2).AND.(E1.LT.3.4949D0)) WRITE(IO,10000) E1
      IF((IN.GT.2).AND.(E1.LT.2.4949D0)) WRITE(IO,10100) E1
10000 FORMAT(' HETC:  PROTON OR NEUTRON CROSS-SECTIONS ARE BEING
     + REQUESTED FOR AN ENERGY LESS THAN 3.5-GEV in SHXSEC E=',G18.7)
10100 FORMAT(' HETC:  PI+ OR PI- CROSS-SECTIONS ARE BEING REQUESTED
     + FOR AN ENERGY LESS THAN 2.5-GEV in SHXSEC E=',G18.7)
      RETURN
      END
