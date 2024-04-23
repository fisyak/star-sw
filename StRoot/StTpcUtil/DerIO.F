      subroutine DerIO(xyz, nxyz, parO, parWheel, dRdpIOs)
      implicit none
      real*8 xyz(3), nxyz(3), parO(6), parWheel(6), dRdpIOs(6,6)
      real*8 x, y, z, nx, ny, nz
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
      x = xyz(1)
      y = xyz(2)
      z = xyz(3)
      nx = nxyz(1)
      ny = nxyz(2)
      nz = nxyz(3)
      dRdpIOs(1,1) = (-(g_O*(((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+
     & (b_O*b_Wheel+1)*nx))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx))-1
      dRdpIOs(1,2) = g_O-(((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+(b_O*b_Wheel+1)*nx)/(((-b_Wheel*g_O)+
     & a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)
      dRdpIOs(1,3) = (a_O*(((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+(b_O*b_Wheel+1)*nx))/(((-b_Wheel*g_O)+
     & a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-b_O
      dRdpIOs(1,4) = ((((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+(b_O*b_Wheel+1)*nx)*((a_O*a_Wheel+1)*z+
     & a_O*a_Wheel*z+z+(a_O-a_Wheel)*y+b_Wheel*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-
     & g_O*z+((-g_O)-a_Wheel*b_O)*z-a_Wheel*b_O*z+(a_Wheel*g_O-b_O)*y-b_Wheel*g_O*x
      dRdpIOs(1,5) = ((((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+(b_O*b_Wheel+1)*nx)*((-g_O*z)+
     & (a_O*b_Wheel-g_O)*z+a_O*b_Wheel*z+a_Wheel*g_O*y+((-b_Wheel*g_O)-a_O)*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)+((-b_O*b_Wheel)-1)*z-b_O*b_Wheel*z-z+a_Wheel*y+(b_O-b_Wheel)*x
      dRdpIOs(1,6) = ((((-a_Wheel*g_O)-b_Wheel+b_O)*nz+((-g_O)-a_Wheel*b_O)*ny+
     & (b_O*b_Wheel+1)*nx)*((a_Wheel*g_O+b_Wheel)*z+a_Wheel*g_O*z+b_Wheel*z+g_O*y-x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)+(a_Wheel-b_Wheel*g_O)*z-b_Wheel*g_O*z+a_Wheel*z+y+g_O*x
      dRdpIOs(2,1) = -2*g_O
      dRdpIOs(2,2) = -2
      dRdpIOs(2,3) = 2*a_O
      dRdpIOs(2,4) = 2*(a_O*a_Wheel+1)*z+2*a_O*a_Wheel*z+2*z+2*(a_O-a_Wheel)*y+2*b_Wheel*x
      dRdpIOs(2,5) = (-2*g_O*z)+2*(a_O*b_Wheel-g_O)*z+2*a_O*b_Wheel*z+2*a_Wheel*g_O*y+2*((-b_Wheel*g_O)-a_O)*x
      dRdpIOs(2,6) = 2*(a_Wheel*g_O+b_Wheel)*z+2*a_Wheel*g_O*z+2*b_Wheel*z+2*g_O*y-2*x
      dRdpIOs(3,1) = b_O-(g_O*((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx))/(((-b_Wheel*g_O)+
     & a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)
      dRdpIOs(3,2) = (-((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx))-a_O
      dRdpIOs(3,3) = (a_O*((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-1
      dRdpIOs(3,4) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((a_O*a_Wheel+1)*z+a_O*a_Wheel*z+z+
     & (a_O-a_Wheel)*y+b_Wheel*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-a_Wheel*z+
     & (a_O-a_Wheel)*z+a_O*z+((-a_O*a_Wheel)-1)*y+a_O*b_Wheel*x
      dRdpIOs(3,5) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((-g_O*z)+(a_O*b_Wheel-g_O)*z+
     & a_O*b_Wheel*z+a_Wheel*g_O*y+((-b_Wheel*g_O)-a_O)*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+
     & (g_O-a_O*b_Wheel)*nx)-b_Wheel*z+(b_O-b_Wheel)*z+b_O*z-a_Wheel*b_O*y+(b_O*b_Wheel+1)*x
      dRdpIOs(3,6) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((a_Wheel*g_O+b_Wheel)*z+
     & a_Wheel*g_O*z+b_Wheel*z+g_O*y-x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)+
     & (a_O*b_Wheel-a_Wheel*b_O)*z+a_O*b_Wheel*z-a_Wheel*b_O*z-b_O*y-a_O*x
      dRdpIOs(4,1) = 0
      dRdpIOs(4,2) = 0
      dRdpIOs(4,3) = 0
      dRdpIOs(4,4) = ((-g_O)-a_Wheel*b_O)*nz+(a_Wheel*g_O-b_O)*ny-b_Wheel*g_O*nx
      dRdpIOs(4,5) = ((-b_O*b_Wheel)-1)*nz+a_Wheel*ny+(b_O-b_Wheel)*nx
      dRdpIOs(4,6) = (a_Wheel-b_Wheel*g_O)*nz+ny+g_O*nx
      dRdpIOs(5,1) = -2*g_O
      dRdpIOs(5,2) = -2
      dRdpIOs(5,3) = 2*a_O
      dRdpIOs(5,4) = 2*(a_O*a_Wheel+1)*z+2*a_O*a_Wheel*z+2*z+2*(a_O-a_Wheel)*y+2*b_Wheel*x
      dRdpIOs(5,5) = (-2*g_O*z)+2*(a_O*b_Wheel-g_O)*z+2*a_O*b_Wheel*z+2*a_Wheel*g_O*y+2*((-b_Wheel*g_O)-a_O)*x
      dRdpIOs(5,6) = 2*(a_Wheel*g_O+b_Wheel)*z+2*a_Wheel*g_O*z+2*b_Wheel*z+2*g_O*y-2*x
      dRdpIOs(6,1) = b_O-(g_O*((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)
      dRdpIOs(6,2) = (-((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx))-a_O
      dRdpIOs(6,3) = (a_O*((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+
     & (a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-1
      dRdpIOs(6,4) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((a_O*a_Wheel+1)*z+a_O*a_Wheel*z+z+
     & (a_O-a_Wheel)*y+b_Wheel*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)-a_Wheel*z+
     & (a_O-a_Wheel)*z+a_O*z+((-a_O*a_Wheel)-1)*y+a_O*b_Wheel*x
      dRdpIOs(6,5) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((-g_O*z)+(a_O*b_Wheel-g_O)*z+
     & a_O*b_Wheel*z+a_Wheel*g_O*y+((-b_Wheel*g_O)-a_O)*x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-
     & a_O*b_Wheel)*nx)-b_Wheel*z+(b_O-b_Wheel)*z+b_O*z-a_Wheel*b_O*y+(b_O*b_Wheel+1)*x
      dRdpIOs(6,6) = (((b_O*b_Wheel+a_O*a_Wheel+1)*nz+(a_O-a_Wheel)*ny+(b_Wheel-b_O)*nx)*((a_Wheel*g_O+b_Wheel)*z+a_Wheel*g_O*z+
     & b_Wheel*z+g_O*y-x))/(((-b_Wheel*g_O)+a_Wheel-a_O)*nz+(a_O*a_Wheel+1)*ny+(g_O-a_O*b_Wheel)*nx)+(a_O*b_Wheel-a_Wheel*b_O)*z+
     & a_O*b_Wheel*z-a_Wheel*b_O*z-b_O*y-a_O*x
      end
