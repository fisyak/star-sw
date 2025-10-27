import ROOT
import Garfield
import os
import math
import ctypes

q = 1. / ROOT.Garfield.ElementaryCharge

# Make a dummy component.
cmp = ROOT.Garfield.ComponentUser()
# Create a sensor.
sensor = ROOT.Garfield.Sensor()
label = "pad"
sensor.AddElectrode(cmp, label)
   
noise = 1000.
 
# Set transfer function.
shaper = ROOT.Garfield.Shaper(1, 25., 1., "unipolar")
sensor.SetTransferFunction(shaper)

cpp_code = """
auto fT = [](const double t) {
  constexpr double tau = 25.;
  return (t / tau) * exp(1 - t / tau);
};
std::function<double(double)> ft = fT;
"""
ROOT.gInterpreter.Declare(cpp_code)
#sensor.SetTransferFunction(ROOT.ft)

infile = open('ft.txt', 'r')
times = ROOT.std.vector('double')()
values = ROOT.std.vector('double')()
for line in infile:
  line = line.strip()
  line = line.split()
  times.push_back(float(line[0]))
  values.push_back(float(line[1]))
infile.close()
#sensor.SetTransferFunction(times, values)

# Set the time bins.
nTimeBins = 1000
tmin = 0.
tmax = 200.
tstep = (tmax - tmin) / nTimeBins
sensor.SetTimeWindow(tmin, tstep, nTimeBins)

sensor.PlotTransferFunction()

hN = ROOT.TH1F("Noise", ";signal [e^{-}];entries", 100, -5 * noise, 5 * noise) 
# Plot the signal if requested.
plotSignal = False
signalView = ROOT.Garfield.ViewSignal(sensor)

fft = False
nEvents = 1000
for i in range(nEvents):
  # Reset the signal.
  sensor.ClearSignal()
  # Add noise.
  sensor.AddWhiteNoise(noise, True, 1.)
  # Apply the transfer function.
  sensor.ConvoluteSignals(fft)
  if plotSignal:
    signalView.PlotSignal(label, "t")
    ROOT.gSystem.ProcessEvents()
  for j in range(400, nTimeBins):
    hN.Fill(q * sensor.GetSignal(label, j))

cN = ROOT.TCanvas()
hN.Draw("")
hN.Fit("gaus")
cN.Update()

