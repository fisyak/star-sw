      subroutine btofDeriv(dcaPars, tof, xyzV, xyzH,  betaV, M2q2, Deriv)
      implicit none
      real   dcaPars(6)
      real   xyzV(3), xyzH(3);
      real*8 betaV, M2q2
      real*8 Deriv(2,6) ! d(1/beta,M2/q2) / d (mImp, mZ, mPsi, mPti, mTan, tof)
      real*8 mImp, mZ, mPsi, mPti, mTan, mCurv
      real*8 tof, dXY, dZ, R1, R2
      real   Phi, length, p2q, path, s_perp, pTq, pZq, R
      real*8 Hz
      real*8 d2d(2,6), JVarsD(6,6)
      real*8 kCLight / 29.9792458 / ! [cm/nsec]
      integer i,j,k
*
      mImp  = dcaPars(1) 
      mZ    = dcaPars(2) 
      mPsi  = dcaPars(3)  
      mPti  = dcaPars(4) 
      mTan  = dcaPars(5) 
      mCurv = dcaPars(6) 
      Hz    = mCurv/mPti;
      dXY   = sqrt((xyzH(1) - xyzV(1))**2 + (xyzH(2) - xyzV(2))**2)
      dZ    = xyzH(3) - xyzV(3);
      R1    = sqrt(xyzV(1)**2 + xyzV(2)**2)
      R2    = sqrt(xyzH(1)**2 + xyzH(2)**2)
      pTq   = -1./mPti
      pZq   =  pTq*mTan
      p2q   = pTq**2 + pZq**2
      R     = 1./mCurv
      Phi   = asin(dXY/(2*R))
      s_perp= 2*R*Phi
      path  = sqrt(s_perp**2 + dZ**2)
      length= tof*kCLight
      betaV = length/path
      M2q2  = p2q*(betaV**1 - 1)
c     d2d : jacobian( [betaV(mPti,dXY,dZ,tof), dM2q2(mPti,mTan,dXY,dZ,tof) ], [mPti, mTan, dXY, dZ, tof] );
      d2d(1,1) = -(kCLight*((4*dXY*asin((Hz*dXY*mPti)/2.d+0))/(Hz*mPti**
     &2*sqrt(1-(Hz**2*dXY**2*mPti**2)/4.d+0))-(8*asin((Hz*dXY*mPti)/2.d+
     &0)**2)/(Hz**2*mPti**3))*((4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*m
     &Pti**2)+dZ**2)**((-3.d+0)/2.d+0)*tof)/2.d+0
      d2d(1,2) = 0
      d2d(1,3) = -(2*kCLight*asin((Hz*dXY*mPti)/2.d+0)*((4*asin((Hz*dXY*
     &mPti)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)**((-3.d+0)/2.d+0)*tof)/(Hz
     &*mPti*sqrt(1-(Hz**2*dXY**2*mPti**2)/4.d+0))
      d2d(1,4) = -dZ*kCLight*((4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mP
     &ti**2)+dZ**2)**((-3.d+0)/2.d+0)*tof
      d2d(1,5) = kCLight/sqrt((4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mP
     &ti**2)+dZ**2)
      d2d(2,1) = ((-(2*mTan**2)/mPti**3)-2/mPti**3)*((kCLight**2*tof**2)
     &/((4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)-1)-(kCLi
     &ght**2*((4*dXY*asin((Hz*dXY*mPti)/2.d+0))/(Hz*mPti**2*sqrt(1-(Hz**
     &2*dXY**2*mPti**2)/4.d+0))-(8*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*
     &mPti**3))*(mTan**2/mPti**2+1/mPti**2)*tof**2)/((4*asin((Hz*dXY*mPt
     &i)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)**2
      d2d(2,2) = (2*mTan*((kCLight**2*tof**2)/((4*asin((Hz*dXY*mPti)/2.d
     &+0)**2)/(Hz**2*mPti**2)+dZ**2)-1))/mPti**2
      d2d(2,3) = -(4*kCLight**2*asin((Hz*dXY*mPti)/2.d+0)*(mTan**2/mPti*
     &*2+1/mPti**2)*tof**2)/(Hz*mPti*sqrt(1-(Hz**2*dXY**2*mPti**2)/4.d+0
     &)*((4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)**2)
      d2d(2,4) = -(2*dZ*kCLight**2*(mTan**2/mPti**2+1/mPti**2)*tof**2)/(
     &(4*asin((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)**2
      d2d(2,5) = (2*kCLight**2*(mTan**2/mPti**2+1/mPti**2)*tof)/((4*asin
     &((Hz*dXY*mPti)/2.d+0)**2)/(Hz**2*mPti**2)+dZ**2)
c     JVarsD:jacobian([mPti,mTan,dXY(mImp),dZ(mZ,mTan),tof],  [mImp,mZ,mPsi,mPti,mTan,tof])  
      JVarsD(1,1) = 0
      JVarsD(1,2) = 0
      JVarsD(1,3) = 0
      JVarsD(1,4) = 1
      JVarsD(1,5) = 0
      JVarsD(1,6) = 0
      JVarsD(2,1) = 0
      JVarsD(2,2) = 0
      JVarsD(2,3) = 0
      JVarsD(2,4) = 0
      JVarsD(2,5) = 1
      JVarsD(2,6) = 0
      JVarsD(3,1) = 1
      JVarsD(3,2) = 0
      JVarsD(3,3) = 0
      JVarsD(3,4) = 0
      JVarsD(3,5) = 0
      JVarsD(3,6) = 0
      JVarsD(4,1) = 0
      JVarsD(4,2) = 1
      JVarsD(4,3) = 0
      JVarsD(4,4) = 0
      JVarsD(4,5) = R2-R1
      JVarsD(4,6) = 0
      JVarsD(5,1) = 0
      JVarsD(5,2) = 0
      JVarsD(5,3) = 0
      JVarsD(5,4) = 0
      JVarsD(5,5) = 0
      JVarsD(5,6) = 1
      do i = 1, 2
        do j = 1, 6
           Deriv(i,j) = 0;
           do k = 1, 6
              Deriv(i,j) = Deriv(i,j) + d2d(i,k) * JVarsD(k, j)
           enddo
        enddo
      enddo
      end
