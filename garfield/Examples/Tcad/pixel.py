import ROOT
import Garfield
import ctypes
import math

cpp_code = """
double transfer(double t) {
  constexpr double tR =  5.6;
  constexpr double tI =  1.8;
  constexpr double tA = 47.;
  constexpr double c1 = tA / ((tA - tI) * (tA - tI) * (tA - tR));
  constexpr double c2 = 1. / ((tA - tI) * tI * (tI - tR));
  constexpr double c3 = tR / ((tA - tR) * (tI - tR) * (tI - tR));
  constexpr double c4 = (tI * tI - tA * tR) / 
                        ((tA - tI) * (tA - tI) * (tI - tR) * (tI - tR));
  const double f1 = -exp(-t / tA) * c1;
  const double f2 =  exp(-t / tI) * t * c2; 
  const double f3 =  exp(-t / tR) * c3;
  const double f4 =  exp(-t / tI) * c4; 
  // constexpr double g = 0.07 / 0.46938;
  return tA * tR * (f1 + f2 + f3 + f4); 
}
std::function<double(double)> ft = transfer;
"""
ROOT.gInterpreter.Declare(cpp_code)

# Sensor thickness.
d = 100.e-4
# Strip pitch.
pitch = 55.e-4
width = 3 * pitch

si = ROOT.Garfield.MediumSilicon()

# Import a two-dimensional TCAD field map.
fm = ROOT.Garfield.ComponentTcad2d()
fm.Initialise("pixel_des.grd", "pixel_des.dat")
fm.SetRangeZ(-width, width)
fm.SetMedium("Silicon", si)

wfield = ROOT.Garfield.ComponentAnalyticField()
wfield.AddPlaneY(0,    0.)
wfield.AddPlaneY(d, -100.)
hw = 0.5 * width
hp = 0.5 * pitch
wfield.AddStripOnPlaneY('z', d, hw - hp, hw + hp, 'strip')

vField = ROOT.Garfield.ViewField(fm)
vField.PlotContour('v')
# Probe the electric field.
efield = fm.ElectricField(0., 0.5 * d, 0.) 
print(efield)

# Create a sensor. 
sensor = ROOT.Garfield.Sensor(fm)
sensor.AddElectrode(wfield, 'strip')

# Set the time bins.
nSignalBins = 2000
tStep = 0.01;
sensor.SetTimeWindow(0., tStep, nSignalBins)
sensor.SetTransferFunction(ROOT.ft)

# Set up Heed.
track = ROOT.Garfield.TrackHeed(sensor)
# Set the particle type and momentum [eV/c].
track.SetParticle('pi')
track.SetMomentum(180.e9)

# Simulate electron/hole drift lines using MC integration.
drift = ROOT.Garfield.AvalancheMC(sensor)
# Use steps of 1 micron.
drift.SetDistanceSteps(1.e-4)

# Plot the signal if requested.
vSignal = ROOT.Garfield.ViewSignal(sensor)
plotSignal = True

vDrift = ROOT.Garfield.ViewDrift()
plotDrift = True
if plotDrift: 
  vDrift.SetArea(0, 0, width, d); 
  track.EnablePlotting(vDrift)

nEvents = 1 
for i in range(nEvents):
  sensor.ClearSignal()
  # Simulate a charged-particle track.
  x0 = hw + (ROOT.Garfield.RndmUniform() - 0.5) * pitch
  t0 = 0.1
  track.NewTrack(x0, 0, 0, t0, 0, 1, 0)
  # Retrieve the clusters along the track.
  for cluster in track.GetClusters():
    drift.DisablePlotting()
    if plotDrift and ROOT.Garfield.RndmUniform() < 0.05:
      drift.EnablePlotting(vDrift)
    # Loop over the electrons in the cluster.
    for electron in cluster.electrons:
      drift.DriftElectron(electron.x, electron.y, electron.z, electron.t)
    # Loop over the holes in the cluster.
    for hole in cluster.ions:
      drift.DriftHole(hole.x, hole.y, hole.z, hole.t)

  # Convolute the signal with the transfer function.
  sensor.ConvoluteSignals()
  if plotSignal: vSignal.PlotSignal('strip')

if plotDrift:
  twod = True
  vDrift.Plot(twod, True)
