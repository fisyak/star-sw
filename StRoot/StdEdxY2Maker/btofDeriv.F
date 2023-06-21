      subroutine btofDeriv(par, Deriv)
      implicit none
      real par(10)
      real pars(10)! , mImp, mZ, mPsi, mPti, mTan, mCurv, tof, C, dZ
      real Deriv(2,6)
      real Hz
      equivalence (pars(1), mImp), (pars(2), mZ), (pars(3), mPsi), (pars(4), mPti),
     &            (pars(5), mTan), (pars(6), mCurv), (pars(7), tof), (pars(8), dXY),
     &            (pars(9), dZ), (pars(10), kCLight)
      real JbetaVdM2q2D(2,6), JVarsD(6,6)
      integer i,j,k
      do i = 1, 10
         pars(i) = par(i);
      enddo
      Hz = mCurv/mPti;
c     JbetaVdM2q2D : jacobian([ betaV(mCurv,C,dZ,tof), dM2q2(pPti,mTan,mCurv,C,dZ,tof)], [mPti, mTan, mCurv, dXY, dZ, tof] );    
      JbetaVdM2q2D(1,1) = 0
      JbetaVdM2q2D(1,2) = 0
      JbetaVdM2q2D(1,3) = -(kCLight*((4*dXY*asin((dXY*mCurv)/2.))/
     &(mCurv**2*sqrt(1-(dXY**2*mCurv**2)/4.))-(8*asin((dXY*mCurv)/2.)**2)
     &/mCurv**3)*((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)**((-3.)/2.)*tof)/2.
      JbetaVdM2q2D(1,4) = -(2*kCLight*asin((dXY*mCurv)/2.)*
     &((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)**((-3.)/2.)*tof)
     &/(mCurv*sqrt(1-(dXY**2*mCurv**2)/4.))
      JbetaVdM2q2D(1,5) = -dZ*kCLight*((4*asin((dXY*mCurv)/2.)**2)/
     &mCurv**2+dZ**2)**((-3.)/2.)*tof
      JbetaVdM2q2D(1,6) = kCLight/sqrt((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)
      JbetaVdM2q2D(2,1) = (((-(2*mTan**2*q**2)/mPti**3)-(2*q**2)/mPti**3)
     &*((kCLight*tof)/sqrt((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)-1))/q**2
      JbetaVdM2q2D(2,2) = (2*mTan*((kCLight*tof)/sqrt((4*asin((dXY*mCurv)/2.)**2)/
     &mCurv**2+dZ**2)-1))/mPti**2
      JbetaVdM2q2D(2,3) = -((kCLight*((4*C*asin((dXY*mCurv)/2.))/(mCurv**2*sqrt(1-(dXY**2*mCurv**2)/4.))
     &-(8*asin((dXY*mCurv)/2.)**2)/mCurv**3)*((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)**((-3.)/2.)*
     &((mTan**2*q**2)/mPti**2+q**2/mPti**2)*tof)/q**2)/2.
      JbetaVdM2q2D(2,4) = -(2*kCLight*asin((dXY*mCurv)/2.)*((4*asin((dXY*mCurv)/2.)**2)
     &/mCurv**2+dZ**2)**((-3.)/2.)*((mTan**2*q**2)/mPti**2+q**2/mPti**2)*tof)/
     &(mCurv*sqrt(1-(dXY**2*mCurv**2)/4.)*q**2)
      JbetaVdM2q2D(2,5) = -(dZ*kCLight*((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)**((-3.)/2.)
     &*((mTan**2*q**2)/mPti**2+q**2/mPti**2)*tof)/q**2
      JbetaVdM2q2D(2,6) = (kCLight*((mTan**2*q**2)/mPti**2+q**2/mPti**2))/
     &(sqrt((4*asin((dXY*mCurv)/2.)**2)/mCurv**2+dZ**2)*q**2)
c     JVarsD:jacobian([mPti,mTan,mCurv(mPti),C,dZ(mZ),tof], [mImp,mZ,mPsi,mPti,mTan,tof])
      
      do i = 1, 6
        do j = 1, 6
           JVarsD(i,j) = 0
        enddo
      enddo
      JVarsD(1,4) = 1
      JVarsD(2,5) = 1
      JVarsD(3,4) = -1/(Hz*mPti**2)
      JVarsD(5,2) = 1
      JVarsD(6,6) = 1
      do i = 1, 2
        do j = 1, 6
           Deriv(i,j) = 0;
           do k = 1, 6
              Deriv(i,j) = Deriv(i,j) + JbetaVdM2q2D(i,k) * JVarsD(k, j)
           enddo
        enddo
      enddo
      end
