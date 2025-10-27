import ROOT
import Garfield
import math
import ctypes

gas = ROOT.Garfield.MediumMagboltz()
gas.LoadGasFile('ar_93_co2_7_3bar.gas')
gas.LoadIonMobility('IonMobility_Ar+_Ar.txt')

cmp = ROOT.Garfield.ComponentAnalyticField()
cmp.SetMedium(gas)
# Wire radius [cm]
rWire = 25.e-4
# Outer radius of the tube [cm]
rTube = 0.71
# Voltages
vWire = 2730.
vTube = 0.
# Add the wire in the centre.
cmp.AddWire(0, 0, 2 * rWire, vWire, 's')
# Add the tube.
cmp.AddTube(rTube, vTube, 0)

# Make a sensor.
sensor = ROOT.Garfield.Sensor(cmp);
sensor.AddElectrode(cmp, 's')
# Set the signal time window.
tstep = 0.5;
tmin = -0.5 * tstep
nbins = 1000
sensor.SetTimeWindow(tmin, tstep, nbins)
# Set the delta reponse function.
times = ROOT.std.vector('double')()
values = ROOT.std.vector('double')()
with open('mdt_elx_delta.txt', 'r') as infile:
  for line in infile:
    t, f = map(float, line.strip().split())
    times.push_back(1.e3 * t)
    values.push_back(f)
sensor.SetTransferFunction(times, values)

# Set up Heed.
track = ROOT.Garfield.TrackHeed(sensor)
track.SetParticle('muon')
track.SetEnergy(170.e9)

# RKF integration.
drift = ROOT.Garfield.DriftLineRKF(sensor)
drift.SetGainFluctuationsPolya(0., 20000.)

driftView = ROOT.Garfield.ViewDrift()
cD = ROOT.TCanvas('cD', '', 600, 600)
driftView.SetCanvas(cD)
plotDrift = True
if plotDrift:
  drift.EnablePlotting(driftView)
  track.EnablePlotting(driftView)

cS = ROOT.TCanvas('cS', '', 600, 600)
plotSignal = True

rTrack = 0.3
x0 = rTrack
y0 = -math.sqrt(rTube * rTube - rTrack * rTrack)

nTracks = 1
for j in range(nTracks):
  sensor.ClearSignal()
  track.NewTrack(x0, y0, 0, 0, 0, 1, 0)
  for cluster in track.GetClusters():
    for electron in cluster.electrons:
      drift.DriftElectron(electron.x, electron.y, electron.z, electron.t)
  if plotDrift:
    cD.Clear()
    cmp.PlotCell(cD)
    driftView.Plot(True, False)
    cD.Update()
  sensor.ConvoluteSignals()
  nt = ctypes.c_int(0)
  if sensor.ComputeThresholdCrossings(-2., 's', nt) == False:
    continue
  if plotSignal:
    sensor.PlotSignal('s', cS)
    cS.Update()

