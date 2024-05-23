      subroutine DerW2S(xyzW, nxyzW, xyzS, rw2s, tw2s, W2ST)
      implicit none
      real*8 xyzW(3), nxyzW(3), xyzS(3), parS(6), parW(6), rw2s(9), tw2s(3)
      real*8 xW, yW, zW, nxW, nyW, nzW, yS 
      real*8 r0, r1, r2, r3, r4, r5, r6, r7, r8, t0, t1, t2
      real*8  W2ST(12,6) ! parS, parW
* Rotation matrix
      r0 = rw2s(1)
      r1 = rw2s(2)
      r2 = rw2s(3)
      r3 = rw2s(4)
      r4 = rw2s(5)
      r5 = rw2s(6)
      r6 = rw2s(7)
      r7 = rw2s(8)
      r8 = rw2s(9)
      t0 = tw2s(1)
      t1 = tw2s(2)
      t2 = tw2s(3)
*     dRdpW2Ss(m,p) = dm/dp

      xW = xyzW(1)
      yW = xyzW(2)
      zW = xyzW(3)
      nxW = nxyzW(1)
      nyW = nxyzW(2)
      nzW = nxyzW(3)
      yS = xyzS(2)
      W2ST(1,1) = 1
      W2ST(1,2) = 0
      W2ST(1,3) = 0
      W2ST(1,4) = 0
      W2ST(1,5) = 0
      W2ST(2,1) = (nzW*r2+nyW*r1+nxW*r0)/(nzW*r5+nyW*r4+nxW*r3)
      W2ST(2,2) = (nzW*r8+nyW*r7+nxW*r6)/(nzW*r5+nyW*r4+nxW*r3)
      W2ST(2,3) = 0
      W2ST(2,4) = 0
      W2ST(2,5) = 0
      W2ST(3,1) = 0
      W2ST(3,2) = 1
      W2ST(3,3) = 0
      W2ST(3,4) = 0
      W2ST(3,5) = 0
      W2ST(4,1) = ((nzW*r2+nyW*r1+nxW*r0)*((-r8*zW)-r7*yW-r6*xW-t2))/(nzW*r5+nyW*r4+nxW*r3)-((nzW*r2+nyW*r1+nxW*r0)*(nzW*r8+nyW*r7+
     & nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2
      W2ST(4,2) = ((nzW*r8+nyW*r7+nxW*r6)*((-r8*zW)-r7*yW-r6*xW-t2))/(nzW*r5+nyW*r4+nxW*r3)-((nzW*r8+nyW*r7+nxW*r6)**2*((-r5*zW)-
     & r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2+(((-nzW*r5)-nyW*r4-nxW*r3)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)
     & +r5*zW+r4*yW+r3*xW+t1
      W2ST(4,3) = 0
      W2ST(4,4) = (-nzW*r8)-nyW*r7-nxW*r6
      W2ST(4,5) = nzW*r5+nyW*r4+nxW*r3
      W2ST(5,1) = (((-nzW*r8)-nyW*r7-nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)+r8*zW+r7*yW+r6*xW+t2
      W2ST(5,2) = ((nzW*r2+nyW*r1+nxW*r0)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)-r2*zW-r1*yW-r0*xW-t0
      W2ST(5,3) = nzW*r8+nyW*r7+nxW*r6
      W2ST(5,4) = 0
      W2ST(5,5) = (-nzW*r2)-nyW*r1-nxW*r0
      W2ST(6,1) = (-(((-nzW*r2)-nyW*r1-nxW*r0)*(nzW*r2+nyW*r1+nxW*r0)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2)+
     & ((nzW*r2+nyW*r1+nxW*r0)*(r2*zW+r1*yW+r0*xW+t0))/(nzW*r5+nyW*r4+nxW*r3)-2*r5*zW-2*r4*yW+yS-2*r3*xW-2*t1
      W2ST(6,2) = ((nzW*r8+nyW*r7+nxW*r6)*(r2*zW+r1*yW+r0*xW+t0))/(nzW*r5+nyW*r4+nxW*r3)-(((-nzW*r2)-nyW*r1-nxW*r0)*(nzW*r8+nyW*r7+
     & nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2
      W2ST(6,3) = (-nzW*r5)-nyW*r4-nxW*r3
      W2ST(6,4) = nzW*r2+nyW*r1+nxW*r0
      W2ST(6,5) = 0
      W2ST(7,1) = (-((nzW*r2+nyW*r1+nxW*r0)*r3)/(nzW*r5+nyW*r4+nxW*r3))-r0
      W2ST(7,2) = (-(r3*(nzW*r8+nyW*r7+nxW*r6))/(nzW*r5+nyW*r4+nxW*r3))-r6
      W2ST(7,3) = 0
      W2ST(7,4) = 0
      W2ST(7,5) = 0
      W2ST(8,1) = (-((nzW*r2+nyW*r1+nxW*r0)*r4)/(nzW*r5+nyW*r4+nxW*r3))-r1
      W2ST(8,2) = (-(r4*(nzW*r8+nyW*r7+nxW*r6))/(nzW*r5+nyW*r4+nxW*r3))-r7
      W2ST(8,3) = 0
      W2ST(8,4) = 0
      W2ST(8,5) = 0
      W2ST(9,1) = (-((nzW*r2+nyW*r1+nxW*r0)*r5)/(nzW*r5+nyW*r4+nxW*r3))-r2
      W2ST(9,2) = (-(r5*(nzW*r8+nyW*r7+nxW*r6))/(nzW*r5+nyW*r4+nxW*r3))-r8
      W2ST(9,3) = 0
      W2ST(9,4) = 0
      W2ST(9,5) = 0
      W2ST(10,1) = ((nyW*r2-nzW*r1)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)-((nzW*r2+nyW*r1+nxW*r0)*(nyW*r5-nzW*r4)*
     & ((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2+((nzW*r2+nyW*r1+nxW*r0)*(r4*zW-r5*yW))/(nzW*r5+nyW*r4+nxW*r3)+
     & r1*zW-r2*yW
      W2ST(10,2) = (-((nyW*r5-nzW*r4)*(nzW*r8+nyW*r7+nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2)+
     & ((nyW*r8-nzW*r7)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)+
     & ((nzW*r8+nyW*r7+nxW*r6)*(r4*zW-r5*yW))/(nzW*r5+nyW*r4+nxW*r3)+r7*zW-r8*yW
      W2ST(10,3) = nzW*r1-nyW*r2
      W2ST(10,4) = nzW*r4-nyW*r5
      W2ST(10,5) = nzW*r7-nyW*r8
      W2ST(11,1) = ((nzW*r0-nxW*r2)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)-((nzW*r2+nyW*r1+nxW*r0)*(nzW*r3-nxW*r5)*
     & ((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2+((nzW*r2+nyW*r1+nxW*r0)*(r5*xW-r3*zW))/(nzW*r5+nyW*r4+nxW*r3)-
     &  r0*zW+r2*xW
      W2ST(11,2) = (-((nzW*r3-nxW*r5)*(nzW*r8+nyW*r7+nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2)+
     & ((nzW*r6-nxW*r8)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)+((nzW*r8+nyW*r7+nxW*r6)*(r5*xW-r3*zW))/
     & (nzW*r5+nyW*r4+nxW*r3)-r6*zW+r8*xW
      W2ST(11,3) = nxW*r2-nzW*r0
      W2ST(11,4) = nxW*r5-nzW*r3
      W2ST(11,5) = nxW*r8-nzW*r6
      W2ST(12,1) = ((nxW*r1-nyW*r0)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)-((nzW*r2+nyW*r1+nxW*r0)*(nxW*r4-nyW*r3)*
     & ((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2+((nzW*r2+nyW*r1+nxW*r0)*(r3*yW-r4*xW))/(nzW*r5+nyW*r4+nxW*r3)+
     & r0*yW-r1*xW
      W2ST(12,2) = (-((nxW*r4-nyW*r3)*(nzW*r8+nyW*r7+nxW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)**2)+
     & ((nxW*r7-nyW*r6)*((-r5*zW)-r4*yW+yS-r3*xW-t1))/(nzW*r5+nyW*r4+nxW*r3)+
     & ((nzW*r8+nyW*r7+nxW*r6)*(r3*yW-r4*xW))/(nzW*r5+nyW*r4+nxW*r3)+r6*yW-r7*xW
      W2ST(12,3) = nyW*r0-nxW*r1
      W2ST(12,4) = nyW*r3-nxW*r4
      W2ST(12,5) = nyW*r6-nxW*r7
      end
      
