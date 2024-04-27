      subroutine DerIO(xyz, nxyz, parO, parWheel, AT)
      implicit none
      real*8 xyz(3), nxyz(3), parO(6), parWheel(6), AT(6,5) ! 
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
      AT(1,1) = (g_O*((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-1
      AT(1,2) = (g_O*(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-b_O
      AT(1,3) = 0
      AT(1,4) = 2*g_O
      AT(1,5) = (g_O*(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-b_O
      AT(2,1) = (-((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx)/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx))-g_O
      AT(2,2) = a_O-(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)/((b_Wheel*g_O+
     & a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)
      AT(2,3) = 0
      AT(2,4) = -2
      AT(2,5) = a_O-(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)
      AT(3,1) = b_O-(a_O*((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)
      AT(3,2) = (-(a_O*(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx))-1
      AT(3,3) = 0
      AT(3,4) = -2*a_O
      AT(3,5) = (-(a_O*(((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx))/((b_Wheel*g_O+a_Wheel+a_O)*nz+
     & (1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx))-1
      AT(4,1) = (((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx)*((1-a_O*a_Wheel)*z-a_O*a_Wheel*z+z+
     & ((-a_Wheel)-a_O)*y+b_Wheel*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)+(g_O+a_Wheel*b_O)*z+
     & g_O*z+a_Wheel*b_O*z+(b_O-a_Wheel*g_O)*y+b_Wheel*g_O*x
      AT(4,2) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((1-a_O*a_Wheel)*z-a_O*a_Wheel*z+z+
     & ((-a_Wheel)-a_O)*y+b_Wheel*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-a_Wheel*z+
     & ((-a_Wheel)-a_O)*z-a_O*z+(a_O*a_Wheel-1)*y-a_O*b_Wheel*x
      AT(4,3) = (g_O+a_Wheel*b_O)*nz+(b_O-a_Wheel*g_O)*ny+b_Wheel*g_O*nx
      AT(4,4) = 2*(1-a_O*a_Wheel)*z-2*a_O*a_Wheel*z+2*z+2*((-a_Wheel)-a_O)*y+2*b_Wheel*x
      AT(4,5) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((1-a_O*a_Wheel)*z-a_O*a_Wheel*z+z+
     & ((-a_Wheel)-a_O)*y+b_Wheel*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-a_Wheel*z+((-a_Wheel)-
     & a_O)*z-a_O*z+(a_O*a_Wheel-1)*y-a_O*b_Wheel*x
      AT(5,1) = (((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx)*((g_O-a_O*b_Wheel)*z+g_O*z-a_O*b_Wheel*z-
     & a_Wheel*g_O*y+(b_Wheel*g_O+a_O)*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)+
     & (b_O*b_Wheel-1)*z+b_O*b_Wheel*z-z+a_Wheel*y+((-b_Wheel)-b_O)*x
      AT(5,2) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((g_O-a_O*b_Wheel)*z+g_O*z-a_O*b_Wheel*z-
     & a_Wheel*g_O*y+(b_Wheel*g_O+a_O)*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-b_Wheel*z+
     & ((-b_Wheel)-b_O)*z-b_O*z+a_Wheel*b_O*y+(1-b_O*b_Wheel)*x
      AT(5,3) = (b_O*b_Wheel-1)*nz+a_Wheel*ny+((-b_Wheel)-b_O)*nx
      AT(5,4) = 2*(g_O-a_O*b_Wheel)*z+2*g_O*z-2*a_O*b_Wheel*z-2*a_Wheel*g_O*y+2*(b_Wheel*g_O+a_O)*x
      AT(5,5) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((g_O-a_O*b_Wheel)*z+g_O*z-a_O*b_Wheel*z-
     & a_Wheel*g_O*y+(b_Wheel*g_O+a_O)*x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)-b_Wheel*z+
     & ((-b_Wheel)-b_O)*z-b_O*z+a_Wheel*b_O*y+(1-b_O*b_Wheel)*x
      AT(6,1) = (((a_Wheel*g_O-b_Wheel-b_O)*nz+(g_O+a_Wheel*b_O)*ny+(1-b_O*b_Wheel)*nx)*((b_Wheel-a_Wheel*g_O)*z-a_Wheel*g_O*z+
     & b_Wheel*z-g_O*y-x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)+(b_Wheel*g_O+a_Wheel)*z+
     & b_Wheel*g_O*z+a_Wheel*z+y-g_O*x
      AT(6,2) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((b_Wheel-a_Wheel*g_O)*z-a_Wheel*g_O*z+
     & b_Wheel*z-g_O*y-x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)+(a_Wheel*b_O-a_O*b_Wheel)*z-
     & a_O*b_Wheel*z+a_Wheel*b_O*z+b_O*y+a_O*x
      AT(6,3) = (b_Wheel*g_O+a_Wheel)*nz+ny-g_O*nx
      AT(6,4) = 2*(b_Wheel-a_Wheel*g_O)*z-2*a_Wheel*g_O*z+2*b_Wheel*z-2*g_O*y-2*x
      AT(6,5) = ((((-b_O*b_Wheel)-a_O*a_Wheel+1)*nz+((-a_Wheel)-a_O)*ny+(b_Wheel+b_O)*nx)*((b_Wheel-a_Wheel*g_O)*z-a_Wheel*g_O*z+
     & b_Wheel*z-g_O*y-x))/((b_Wheel*g_O+a_Wheel+a_O)*nz+(1-a_O*a_Wheel)*ny+(a_O*b_Wheel-g_O)*nx)+(a_Wheel*b_O-a_O*b_Wheel)*z-
     & a_O*b_Wheel*z+a_Wheel*b_O*z+b_O*y+a_O*x
      end
