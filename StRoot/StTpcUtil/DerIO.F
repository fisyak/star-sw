      subroutine DerIO(xyz, nxyz, parO, parWheel, AT)
      implicit none
      real*8 xyz(3), nxyz(3), parO(6), parWheel(6), AT(6,5) ! 
      real*8 xI, yI, zI, nxI, nyI, nzI
      real*8 a_O, b_O, g_O, x_O, y_O, z_O
      real*8 a_Wheel, b_Wheel
      real*8 da_O, db_O, dg_O, dx_O, dy_O, dz_O
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
      AT(1,1) = 1
      AT(1,2) = b_O
      AT(1,3) = 0
      AT(1,4) = 0
      AT(1,5) = 0
      AT(2,1) = g_O
      AT(2,2) = -a_O
      AT(2,3) = 0
      AT(2,4) = 0
      AT(2,5) = 0
      AT(3,1) = -b_O
      AT(3,2) = 1
      AT(3,3) = 0
      AT(3,4) = 0
      AT(3,5) = 0
      AT(4,1) = (-b_Wheel*g_O*(xI-b_Wheel*zI))-(b_O-a_Wheel*g_O)*(a_Wheel*zI+yI)-(g_O+a_Wheel*b_O)*(zI-a_Wheel*yI+b_Wheel*xI)
      AT(4,2) = a_O*b_Wheel*(xI-b_Wheel*zI)-(a_O*a_Wheel-1)*(a_Wheel*zI+yI)-((-a_Wheel)-a_O)*(zI-a_Wheel*yI+b_Wheel*xI)
      AT(4,3) = (-b_Wheel*g_O*(nxI-b_Wheel*nzI))-(b_O-a_Wheel*g_O)*(a_Wheel*nzI+nyI)-
     & (g_O+a_Wheel*b_O)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(4,4) = (-b_Wheel*(nxI-b_Wheel*nzI))-((-a_Wheel)-a_O)*(a_Wheel*nzI+nyI)-(1-a_O*a_Wheel)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(4,5) = a_O*b_Wheel*(nxI-b_Wheel*nzI)-(a_O*a_Wheel-1)*(a_Wheel*nzI+nyI)-((-a_Wheel)-a_O)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(5,1) = (-((-b_Wheel)-b_O)*(xI-b_Wheel*zI))-a_Wheel*(a_Wheel*zI+yI)-(b_O*b_Wheel-1)*(zI-a_Wheel*yI+b_Wheel*xI)
      AT(5,2) = (-(1-b_O*b_Wheel)*(xI-b_Wheel*zI))-a_Wheel*b_O*(a_Wheel*zI+yI)-((-b_Wheel)-b_O)*(zI-a_Wheel*yI+b_Wheel*xI)
      AT(5,3) = (-((-b_Wheel)-b_O)*(nxI-b_Wheel*nzI))-a_Wheel*(a_Wheel*nzI+nyI)-(b_O*b_Wheel-1)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(5,4) = (-(b_Wheel*g_O+a_O)*(nxI-b_Wheel*nzI))+a_Wheel*g_O*(a_Wheel*nzI+nyI)-(g_O-a_O*b_Wheel)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(5,5) = (-(1-b_O*b_Wheel)*(nxI-b_Wheel*nzI))-a_Wheel*b_O*(a_Wheel*nzI+nyI)-((-b_Wheel)-b_O)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      AT(6,1) = g_O*(xI-b_Wheel*zI)-(b_Wheel*g_O+a_Wheel)*(zI-a_Wheel*yI+b_Wheel*xI)-a_Wheel*zI-yI
      AT(6,2) = (-a_O*(xI-b_Wheel*zI))-b_O*(a_Wheel*zI+yI)-(a_Wheel*b_O-a_O*b_Wheel)*(zI-a_Wheel*yI+b_Wheel*xI)
      AT(6,3) = g_O*(nxI-b_Wheel*nzI)-(b_Wheel*g_O+a_Wheel)*(nzI-a_Wheel*nyI+b_Wheel*nxI)-a_Wheel*nzI-nyI
      AT(6,4) = g_O*(a_Wheel*nzI+nyI)-(b_Wheel-a_Wheel*g_O)*(nzI-a_Wheel*nyI+b_Wheel*nxI)-b_Wheel*nzI+nxI
      AT(6,5) = (-a_O*(nxI-b_Wheel*nzI))-b_O*(a_Wheel*nzI+nyI)-(a_Wheel*b_O-a_O*b_Wheel)*(nzI-a_Wheel*nyI+b_Wheel*nxI)
      end
