#include <TApplication.h>

#include <iostream>

#include "Garfield/ComponentNeBem3d.hh"
#include "Garfield/GeometrySimple.hh"
#include "Garfield/MediumConductor.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/MediumPlastic.hh"
#include "Garfield/SolidBox.hh"
#include "Garfield/SolidHole.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ViewGeometry.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  MediumMagboltz gas("He", 87.5, "CF4", 12.5);

  MediumConductor Cu;
  MediumPlastic Kp;
  Kp.SetDielectricConstant(4.0);

  // Geometry.
  GeometrySimple geo;

  double kptx = 0.0;
  double kpty = 0.0;
  double kptz = 0.0;
  double lenLX = 0.0120;
  double lenLY = 0.0120;
  double kptLZ = 0.0050;
  double maxdia = 0.0070;
  double mindia = 0.0050;
  double lwcprx = 0.0;
  double lwcpry = 0.0;
  double lwcprLZ = 0.0005;
  double lwcprz = kptz - (kptLZ / 2.0) - (lwcprLZ / 2.0);
  double indgap = 0.05;
  double anodex = 0.0;
  double anodey = 0.0;
  double anodeLZ = 0.0;
  double anodez = lwcprz - (lwcprLZ / 2.0) - indgap - (anodeLZ / 2.0);
  double upcprx = 0.0;
  double upcpry = 0.0;
  double upcprLZ = 0.0005;
  double upcprz = kptz + (kptLZ / 2.0) + (upcprLZ / 2.0);
  double drftgap = 0.05;
  double drftx = 0.0;
  double drfty = 0.0;
  double drftLZ = 0.0;
  double drftz = upcprz + (upcprLZ / 2.0) + drftgap + (drftLZ / 2.0);
  double drftV = -750;
  double upcprV = -250;
  double lwcprV = 250;
  double anodeV = 750;

  std::cout << "kptz: " << kptz << std::endl;
  std::cout << "lwcprz: " << lwcprz << std::endl;
  std::cout << "anodez: " << anodez << std::endl;
  std::cout << "upcprz: " << upcprz << std::endl;
  std::cout << "drftz: " << drftz << std::endl;

  SolidBox cathode(drftx, drfty, drftz, lenLX / 2.0, lenLY / 2.0, drftLZ / 2.0);
  cathode.SetBoundaryPotential(drftV);
  geo.AddSolid(&cathode, &Cu);

  SolidHole topCu(upcprx, upcpry, upcprz, maxdia / 2.0, maxdia / 2.0,
                  lenLX / 2.0, lenLY / 2.0, upcprLZ / 2.0);
  topCu.SetSectors(3);
  topCu.SetBoundaryPotential(upcprV);
  geo.AddSolid(&topCu, &Cu);

  SolidHole topKapton(kptx, kpty, (kptz + (kptLZ / 4.0)), maxdia / 2.0,
                      mindia / 2.0, lenLX / 2.0, lenLY / 2.0, kptLZ / 4.0);
  topKapton.SetSectors(3);
  topKapton.SetBoundaryDielectric();
  geo.AddSolid(&topKapton, &Kp);

  SolidHole btmKapton(kptx, kpty, (kptz - (kptLZ / 4.0)), mindia / 2.0,
                      maxdia / 2.0, lenLX / 2.0, lenLY / 2.0, kptLZ / 4.0);
  btmKapton.SetSectors(3);
  btmKapton.SetBoundaryDielectric();
  geo.AddSolid(&btmKapton, &Kp);

  SolidHole btmCu(lwcprx, lwcpry, lwcprz, maxdia / 2.0, maxdia / 2.0,
                  lenLX / 2.0, lenLY / 2.0, lwcprLZ / 2.0);
  btmCu.SetSectors(3);
  btmCu.SetBoundaryPotential(lwcprV);
  geo.AddSolid(&btmCu, &Cu);

  SolidBox anode(anodex, anodey, anodez, lenLX / 2.0, lenLY / 2.0,
                 anodeLZ / 2.0);
  anode.SetBoundaryPotential(anodeV);
  geo.AddSolid(&anode, &Cu);

  double tgtElSize = 10.e-4;
  int minEl = 3, maxEl = 5;
  int xcopy = 10, ycopy = 10, zcopy = 0;
  ComponentNeBem3d nebem;
  nebem.SetGeometry(&geo);
  nebem.SetTargetElementSize(tgtElSize);
  nebem.SetMinMaxNumberOfElements(minEl, maxEl);
  nebem.SetPeriodicityX(lenLX);
  nebem.SetPeriodicityY(lenLY);
  nebem.SetPeriodicCopies(xcopy, ycopy, zcopy);
  nebem.UseLUInversion();
  // nebem.EnableDebugging();
  nebem.Initialise();

  /*
    {  // field along line 1
    std::ofstream fldfile;
    fldfile.open("FieldLine1.out");

    int nz = 101;
    double delz = (drftz - anodez) / (double)(nz - 1);
    double xp = 0.0, yp = 0.0, zp;
    Medium* medium = nullptr;
    double ex = 0., ey = 0., ez = 0., e = 0.0, v = 0.;
    int status = 0;
    for (int iz = 0; iz < nz; ++iz) {
      zp = anodez + iz*delz;

      nebem.ElectricField(xp, yp, zp, ex, ey, ez, v, medium, status);
      e = (ex*ex + ey*ey + ez*ez);
      e = pow(e, 0.5);
      fldfile << xp << " " << yp << " " << zp << " " << ex << " " << ey << " "
    << ez << " " << e << " " << v << " " << medium << " " << status <<
    std::endl; }  // iz loop fldfile.close();
    }

    {  // field along line 2
    std::ofstream fldfile;
    fldfile.open("FieldLine2.out");

    int nz = 101;
    double delz = (drftz - anodez) / (double)(nz - 1);
    double xp, yp = 0.0, zp;
    double xoffset = 10.0e-4;
    Medium* medium = nullptr;
    double ex = 0., ey = 0., ez = 0., e = 0.0, v = 0.;
    int status = 0;

    xp = (maxdia/2.0) - xoffset;
    for(int iz = 0; iz < nz; ++iz) {
      zp = anodez + iz*delz;

      nebem.ElectricField(xp, yp, zp, ex, ey, ez, v, medium, status);
      e = (ex*ex + ey*ey + ez*ez);
      e = pow(e, 0.5);
      fldfile << xp << " " << yp << " " << zp << " " << ex << " " << ey << " "
    << ez << " " << e << " " << v << " " << medium << " " << status <<
    std::endl; }  // iz loop fldfile.close();
    }

    {  // field along line 3
    std::ofstream fldfile;
    fldfile.open("FieldLine3.out");

    int nz = 101;
    double delz = (drftz - anodez) / (double)(nz - 1);
    double xp, yp = 0.0, zp;
    double xoffset = 10.0e-4;
    Medium* medium = nullptr;
    double ex = 0., ey = 0., ez = 0., e = 0.0, v = 0.;
    int status = 0;

    xp = (maxdia/2.0) + xoffset;
    for(int iz = 0; iz < nz; ++iz) {
      zp = anodez + iz*delz;

      nebem.ElectricField(xp, yp, zp, ex, ey, ez, v, medium, status);
      e = (ex*ex + ey*ey + ez*ez);
      e = pow(e, 0.5);
      fldfile << xp << " " << yp << " " << zp << " " << ex << " " << ey << " "
    << ez << " " << e << " " << v << " " << medium << " " << status <<
    std::endl; }  // iz loop fldfile.close();
    }

    {  // field on suface
    std::ofstream fldfile;
    fldfile.open("FieldSurface.out");

    int nx = 101, nz = 101;
    double zoffset = 100.0e-4;
    double delx = lenLX / (double)(nx - 1);
    double delz = ((upcprz+zoffset) - (lwcprz-zoffset)) / (double)(nz - 1);
    double xp, yp = 0.0, zp;
    Medium* medium = nullptr;
    double ex = 0., ey = 0., ez = 0., e = 0.0, v = 0.;
    int status = 0;
    for(int ix = 0; ix < nx; ++ix) {
      xp = (-lenLX / 2.0) + ix*delx;
      for(int iz = 0; iz < nz; ++iz) {
        zp = (lwcprz-zoffset) + iz*delz;

        nebem.ElectricField(xp, yp, zp, ex, ey, ez, v, medium, status);
        e = (ex*ex + ey*ey + ez*ez);
        e = pow(e, 0.5);
        fldfile << xp << " " << yp << " " << zp << " " << ex << " " << ey << " "
    << ez << " " << e << " " << v << " " << medium << " " << status <<
    std::endl; }  // iz loop fldfile << std::endl; }  // ix loop
    fldfile.close();
    }
  */
  // return 0;

  // Plot device geometry in 2D
  /*
  ViewGeometry geomView2d(&geo);
  geomView2d.SetArea(-lenLX, -lenLY, anodez, lenLX, lenLY, drftz);
  geomView2d.SetPlane(0, 1, 0, 0, 0, 0.0);
  geomView2d.Plot2d();

  ViewGeometry geomView2dClose(&geo);
  geomView2dClose.SetArea(-lenLX, -lenLY, upcprz, lenLX, lenLY, lwcprz);
  geomView2dClose.SetPlane(0, 1, 0, 0, 0, 0.0);
  geomView2dClose.Plot2d();
  */

  // Plot device geometry in 3D
  /*
  ViewGeometry geomView(&geo);
  geomView.Plot();
  */

  // Medium* medium = nullptr; // Already declared for file output
  /*
  double ex = 0., ey = 0., ez = 0., v = 0.;
  int status = 0;
  nebem.ElectricField(0, 0, 0, ex, ey, ez, v, medium, status);
  std::printf("E = (%15.8f, %15.8f %15.8f), V = %15.8f, status = %d\n", ex, ey,
  ez, v, status);

  ViewField PfieldProfileView(&nebem);
  PfieldProfileView.PlotProfile(kptx, kpty, anodez, kptx, kpty, drftz);

  ViewField EfieldProfileView(&nebem);
  EfieldProfileView.PlotProfile(kptx, kpty, anodez, kptx, kpty, drftz, "e");

  ViewField PfieldView(&nebem);
  PfieldView.SetArea(-lenLX/2.0, -lenLY/2.0, lwcprz-10.0e-4, lenLX/2.0,
  lenLY/2.0, upcprz+10.0e-4); PfieldView.SetPlane(0, 1, 0, 0, 0, 0);
  PfieldView.PlotContour();

  app.Run(true);

  */

  ViewField EfieldView(&nebem);
  EfieldView.SetArea(-lenLX / 2.0, -lenLY / 2.0, lwcprz - 10.0e-4, lenLX / 2.0,
                     lenLY / 2.0, upcprz + 10.0e-4);
  EfieldView.SetPlane(0, 1, 0, 0, 0, 0);
  EfieldView.PlotContour("e");

  app.Run(true);
}
