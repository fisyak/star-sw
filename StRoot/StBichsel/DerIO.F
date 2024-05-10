      subroutine DerIO(xyz, nxyz, xyzO, parO, parWheel, AT)
      implicit none
      real*8 xyz(3), nxyz(3), xyzO(3), parO(6), parWheel(6)
      real*8 xI, yI, zI, nxI, nyI, nzI, yO, z
      real*8 a_O, b_O, g_O, x_O, y_O, z_O
      real*8 a_Wheel, b_Wheel
      real*8 da_O, db_O, dg_O, dx_O, dy_O, dz_O
      real*8  AT(4,4) ! no alpha & beta 
*     dRdpIOs(m,p) = dm/dp
      a_O = parO(1)
      b_O = parO(2)
      g_O = parO(3)
      x_O = parO(4)
      y_O = parO(5)
      z_O = parO(6)
      a_Wheel = parWheel(1)
      b_Wheel = parWheel(2)
      xI = xyz(1)
      yI = xyz(2)
      zI = xyz(3)
      nxI = nxyz(1)
      nyI = nxyz(2)
      nzI = nxyz(3)
      yO = xyzO(2)
      z = (xyz(3) + xyzO(3))/2
      AT(1,1) = -1
      AT(1,2) = 0
      AT(1,3) = 0
      AT(1,4) = 0
      AT(2,1) = (((-a_Wheel*g_O)-b_Wheel)*nzI-g_O*nyI+nxI)/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)
      AT(2,2) = (nzI-a_Wheel*nyI+b_Wheel*nxI)/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)
      AT(2,3) = 0
      AT(2,4) = 0
      AT(3,1) = 0
      AT(3,2) = -1
      AT(3,3) = 0
      AT(3,4) = 0
      AT(4,1) = (-(((-a_Wheel*nzI)-nyI)*((-(a_Wheel-b_Wheel*g_O)*zI)+b_Wheel*g_O*z-a_Wheel*z-y_O+yO-yI-g_O*xI))/
     & ((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI))+((nxI-b_Wheel*nzI)*(((-a_Wheel*g_O)-b_Wheel)*nzI-g_O*nyI+nxI)*
     & ((-(a_Wheel-b_Wheel*g_O)*zI)+b_Wheel*g_O*z-a_Wheel*z-y_O+yO-yI-g_O*xI))/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)**2-
     & ((((-a_Wheel*g_O)-b_Wheel)*nzI-g_O*nyI+nxI)*(b_Wheel*zI+b_Wheel*z-xI))/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)+
     & a_Wheel*zI+a_Wheel*z+yI
      AT(4,2) = ((nzI-a_Wheel*nyI+b_Wheel*nxI)*(nxI-b_Wheel*nzI)*((-(a_Wheel-b_Wheel*g_O)*zI)+
     & b_Wheel*g_O*z-a_Wheel*z-y_O+yO-yI-g_O*xI))/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)**2-
     & ((nzI-a_Wheel*nyI+b_Wheel*nxI)*(b_Wheel*zI+b_Wheel*z-xI))/((a_Wheel-b_Wheel*g_O)*nzI+nyI+g_O*nxI)
      AT(4,3) = a_Wheel*nzI+nyI
      AT(4,4) = b_Wheel*nzI-nxI
      end
      
