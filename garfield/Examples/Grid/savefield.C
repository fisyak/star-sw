#include <TApplication.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TROOT.h>

#include <cmath>

#include "Garfield/ComponentAnalyticField.hh"
#include "Garfield/ComponentGrid.hh"
#include "Garfield/MediumSilicon.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Define the medium.
  MediumSilicon si;

  // Thickness of silicon [cm].
  constexpr double gap = 50.e-4;
  // Length in the x and z direction [cm].
  constexpr double width = 3 * gap;

  // Make a component with analytic weighting field for a pixel.
  constexpr double pitch = 50.e-4;
  ComponentAnalyticField wField;
  wField.SetMedium(&si);
  wField.AddPlaneY(0., -1.);
  wField.AddPlaneY(gap, 0.);
  wField.AddPixelOnPlaneY(gap, -0.5 * pitch, 0.5 * pitch, -0.5 * pitch,
                          0.5 * pitch, "pixel");

  ComponentGrid grid;
  grid.SetMesh(150, 50, 150, 0., width, 0., gap, 0., width);
  grid.SaveWeightingField(&wField, "pixel", "wfield.txt", "ijk");
  /*
  const double xmin = 0.;
  const double xmax = width;
  const std::size_t nX = 150;
  const double dx = (xmax - xmin) / nX;
  const double zmin = 0.;
  const double zmax = width;
  const std::size_t nZ = 150;
  const double dz = (zmax - zmin) / nZ;
  const double ymin = 0.;
  const double ymax = gap;
  const std::size_t nY = 50;
  const double dy = (ymax - ymin) / nY;

  const std::string filename = "wfield.txt";
  std::ofstream outfile;
  outfile.open(filename.c_str(), std::ios::out);
  for (std::size_t i = 0; i < nX; ++i) {
    const double x = xmin + (i + 0.5) * dx;
    std::cout << i << " (x = " << x << ")\n";
    for (std::size_t j = 0; j < nY; ++j) {
      const double y = ymin + (j + 0.5) * dy;
      for (std::size_t k = 0; k < nZ; ++k) {
        const double z = zmin + (k + 0.5) * dz;
        double wx = 0., wy = 0., wz = 0.;
        wField.WeightingField(x, y, z, wx, wy, wz, "pixel");
        double v = wField.WeightingPotential(x, y, z, "pixel");
        outfile << i << "  " << j << "  " << k << "  "
                << wx << "  " << wy << "  " << wz << "  " << v << "  0\n";
      }
    }
  }
  outfile.close();
  */
}
