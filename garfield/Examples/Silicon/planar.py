import ROOT
import Garfield

si = ROOT.Garfield.MediumSilicon()
si.SetTemperature(293.)

cM = ROOT.TCanvas('cM', '', 600, 600)
si.PlotVelocity("eh", cM)

# Thickness of the silicon [cm]
d = 100.e-4

# Make a component with constant drift field and weighting field.
# Bias voltage [V]
vbias = -50.;
uniformField = ROOT.Garfield.ComponentConstant()
uniformField.SetArea(-2 * d, 0., -2 * d, 2 * d, d, 2 * d)
uniformField.SetMedium(si)
uniformField.SetElectricField(0, vbias / d, 0)
uniformField.SetWeightingField(0, -1. / d, 0, 'pad')

# Depletion voltage [V]
vdep = -20.
# Make a component with linear drift field.
linearField = ROOT.Garfield.ComponentUser()
linearField.SetArea(-2 * d, 0., -2 * d, 2 * d, d, 2 * d)
linearField.SetMedium(si)
eLinear = 'ey = ' + repr((vbias - vdep) / d) + ' + 2 * y * ' + repr(vdep / (d * d))
linearField.SetElectricField(eLinear)

# Make a component with analytic weighting field for a strip or pixel.
pitch = 55.e-4
halfpitch = 0.5 * pitch
wField = ROOT.Garfield.ComponentAnalyticField()
wField.SetMedium(si)
wField.AddPlaneY(0, vbias, 'back')
wField.AddPlaneY(d, 0, 'front')
wField.AddStripOnPlaneY('z', d, -halfpitch, halfpitch, 'strip')
wField.AddPixelOnPlaneY(d, -halfpitch, halfpitch, 
                           -halfpitch, halfpitch, 'pixel')

# Create a sensor. 
#sensor = ROOT.Garfield.Sensor(uniformField)
sensor = ROOT.Garfield.Sensor(linearField)
label = 'strip'
sensor.AddElectrode(wField, label)

# Plot the weighting potential.
fieldView = ROOT.Garfield.ViewField(wField)
cF = ROOT.TCanvas('cF', '', 600, 600)
fieldView.SetCanvas(cF)
fieldView.SetArea(-0.5 * d, 0, 0.5 * d, d)
fieldView.PlotContourWeightingField('strip', 'v')

# Set the time bins.
nTimeBins = 1000
tmin =  0.
tmax = 10.
tstep = (tmax - tmin) / nTimeBins
sensor.SetTimeWindow(tmin, tstep, nTimeBins)

# Set up Heed.
track = ROOT.Garfield.TrackHeed(sensor)
# Set the particle type and momentum [eV/c].
track.SetParticle('pion')
track.SetMomentum(180.e9)

# Simulate electron/hole drift lines using MC integration.
drift = ROOT.Garfield.AvalancheMC(sensor)
# Use steps of 1 micron.
drift.SetDistanceSteps(1.e-4)

# Plot the signal if requested.
signalView = ROOT.Garfield.ViewSignal(sensor)
cS = ROOT.TCanvas('cS', '', 600, 600)
signalView.SetCanvas(cS)
signalView.SetRangeX(0., 6.)
plotSignal = True

driftView = ROOT.Garfield.ViewDrift()
driftView.SetArea(-0.5 * d, 0, -0.5 * d, 0.5 * d, d, 0.5 * d)
cD = ROOT.TCanvas('cD', '', 600, 600)
driftView.SetCanvas(cD)
plotDrift = True
if plotDrift:
  track.EnablePlotting(driftView)
  drift.EnablePlotting(driftView)

# Flag to randomise the position of the track.  
smearx = True
nEvents = 10
for i in range(nEvents):
  print(i, '/', nEvents)
  if plotDrift: driftView.Clear()
  # Simulate a charged-particle track.
  xt = 0.;
  if smearx: xt = -0.5 * pitch + ROOT.Garfield.RndmUniform() * pitch
  track.NewTrack(xt, 0, 0, 0, 0, 1, 0)
  # Retrieve the clusters along the track.
  for cluster in track.GetClusters():
    # Loop over the electrons in the cluster.
    for electron in cluster.electrons:
      # Simulate the electron and hole drift lines.
      if plotDrift:
        drift.DisablePlotting()
        if ROOT.Garfield.RndmUniform() < 0.01:
          drift.EnablePlotting(driftView)
      drift.DriftElectron(electron.x, electron.y, electron.z, electron.t)
      drift.DriftHole(electron.x, electron.y, electron.z, electron.t)
  if plotSignal:
    signalView.PlotSignal(label)
    signalView.GetCanvas().Update()
    ROOT.gSystem.ProcessEvents()
  if plotDrift:
    driftView.Plot(True)
    driftView.GetCanvas().Update()
    ROOT.gSystem.ProcessEvents()
