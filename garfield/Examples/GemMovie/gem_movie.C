#include <TApplication.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TSystem.h>

#include <array>
#include <iostream>
#include <vector>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("ar", 80., "co2", 20.);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.Initialise(true);
  // Set the Penning transfer efficiency.
  gas.EnablePenningTransfer();
  // Load the ion mobilities.
  gas.LoadIonMobility("IonMobility_Ar+_Ar.txt");

  // Load the field map.
  ComponentAnsys123 fm;
  fm.EnableDeleteBackgroundElements(false);
  fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm");
  fm.EnableMirrorPeriodicityX();
  fm.EnableMirrorPeriodicityY();
  fm.PrintRange();

  // Associate the gas with the corresponding field map material.
  fm.SetGas(&gas);
  fm.PrintMaterials();

  // Dimensions of the GEM [cm]
  constexpr double pitch = 0.014;

  // Create the sensor.
  Sensor sensor(&fm);
  sensor.SetArea(-5 * pitch, -5 * pitch, -0.02, 5 * pitch, 5 * pitch, 0.025);

  AvalancheMicroscopic aval(&sensor);

  AvalancheMC drift(&sensor);
  drift.SetTimeSteps(0.05);

  ViewField fieldView(&fm);
  fieldView.SetPlane(0, -1, 0, 0, 0, 0);
  fieldView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
  fieldView.SetVoltageRange(-160., 160.);

  TCanvas canvas("cCanvas", "", 600, 600);
  canvas.SetLeftMargin(0.16);
  fieldView.SetCanvas(&canvas);
  constexpr bool plotField = false;

  ViewFEMesh meshView;
  meshView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
  meshView.SetComponent(&fm);
  meshView.SetPlane(0, -1, 0, 0, 0, 0);
  meshView.SetFillMesh(true);
  meshView.SetColor(2, kGray);
  meshView.SetCanvas(&canvas);

  ViewDrift driftView;
  aval.EnableExcitationMarkers(false);
  aval.EnableIonisationMarkers(false);
  aval.EnableAttachmentMarkers(false);
  aval.EnablePlotting(&driftView);
  drift.EnablePlotting(&driftView);
  driftView.SetPlane(0, -1, 0, 0, 0, 0);
  driftView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02);
  driftView.SetCanvas(&canvas);

  TLatex label;

  // Add the initial electron.
  const double x0 = 0.;
  const double y0 = 0.;
  const double z0 = 0.02;
  const double t0 = 0.;
  const double e0 = 0.1;
  aval.AddElectron(x0, y0, z0, t0, e0);

  std::vector<std::array<double, 5> > prev = {{x0, y0, z0, t0, e0}};
  double tmin = 0.;
  double dt = 0.1;
  const std::size_t nFrames = 207;
  for (std::size_t i = 0; i < nFrames; ++i) {
    if (i % 10 == 0) std::cout << "Frame " << i << "\n";
    driftView.Clear();
    if (!aval.GetElectrons().empty()) {
      aval.SetTimeWindow(tmin, tmin + dt);
      aval.ResumeAvalanche();
      std::vector<std::array<double, 5> > next;
      for (const auto& electron : aval.GetElectrons()) {
        const double x1 = electron.path.front().x;
        const double y1 = electron.path.front().y;
        const double z1 = electron.path.front().z;
        const double t1 = electron.path.front().t;
        bool existing = false;
        for (const auto& p : prev) {
          constexpr double tol = 1.e-5;
          if (fabs(x1 - p[0]) < tol && fabs(y1 - p[1]) < tol &&
              fabs(z1 - p[2]) < tol && fabs(t1 - p[3]) < tol) {
            existing = true;
            break;
          }
        }
        if (!existing) drift.AddIon(x1, y1, z1, t1);
        const double x2 = electron.path.back().x;
        const double y2 = electron.path.back().y;
        const double z2 = electron.path.back().z;
        const double t2 = electron.path.back().t;
        const double e2 = electron.path.back().energy;
        next.push_back({x2, y2, z2, t2, e2});
      }
      prev.swap(next);
    }
    if (!drift.GetIons().empty()) {
      drift.SetTimeWindow(tmin, tmin + dt);
      drift.ResumeAvalanche();
    }
    if (plotField && i < 5) {
      fieldView.Plot("v", "CONT1");
      driftView.Plot2d(false, true);
    } else {
      driftView.Plot2d(true, true);
    }
    meshView.Plot(true);
    canvas.cd();
    char text[100];
    if (i < 100) {
      snprintf(text, 100, "#it{t} = %04.1f ns", tmin + dt);
    } else {
      snprintf(text, 100, "#it{t} = %04.2f #mus", 1.e-3 * (tmin + dt));
    }
    label.DrawLatexNDC(0.3, 0.88, text);
    canvas.Update();
    gSystem->ProcessEvents();
    constexpr bool gif = false;
    if (!gif) {
      char filename[50];
      snprintf(filename, 50, "frames/frame_%03zu.png", i);
      canvas.SaveAs(filename);
    } else {
      if (i == nFrames - 1) {
        canvas.Print("gem_movie.gif++");
      } else {
        canvas.Print("gem_movie.gif+3");
      }
    }
    tmin += dt;
    if (i == 99) {
      dt = 10.;
      drift.SetTimeSteps(1.);
    } else if (i == 108) {
      dt = 100.;
      drift.SetTimeSteps(10.);
    }
  }

  app.Run();
}
