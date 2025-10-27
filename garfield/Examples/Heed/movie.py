import ROOT
import Garfield

ROOT.Garfield.SetSerif()
ROOT.Garfield.SetDefaultStyle()

hElectrons = ROOT.TH1F("hElectrons", ";number of electrons;entries", 200, 0, 200)
hElectrons.SetStats(0)
hElectrons.SetMaximum(10)

gas = ROOT.Garfield.MediumMagboltz("ar")
gas.SetTemperature(293.15)
gas.SetPressure(760.)

# Width of the gas gap [cm].
w = 1.

# Make a component.
cmp = ROOT.Garfield.ComponentConstant()
cmp.SetArea(0., -10., -10., w, 10., 10.)
cmp.SetMedium(gas)
cmp.SetElectricField(100., 0., 0.)

# Make a sensor.
sensor = ROOT.Garfield.Sensor(cmp)

# Set up HEED.
track = ROOT.Garfield.TrackHeed(sensor)
track.SetParticle("muon")
track.SetMomentum(370.e6)
track.Initialise(gas, True)

view = ROOT.Garfield.ViewDrift()
view.SetArea(0., -0.5 * w, -0.5 * w, w, 0.5 * w, 0.5 * w) 
canvas = ROOT.TCanvas("c", "", 1400, 600);
canvas.Divide(2, 1)
view.SetCanvas(canvas.cd(1))

nEvents = 100
for i in range(nEvents):
  view.Clear()
  # if i % 1000 == 0: print i, "/", nEvents
  # Initial position and direction 
  track.NewTrack(0., 0., 0., 0., 1., 0., 0.)
  # Total number of electrons produced along the track.
  nsum = 0
  # Loop over the clusters.
  for cluster in track.GetClusters():
    nc = cluster.electrons.size()
    nsum += nc
    for q in cluster.electrons:
      view.NewDriftLine(ROOT.Garfield.Particle.Electron, 1, q.x, q.y, q.z)
  hElectrons.Fill(nsum)
  view.Plot2d(True, True)
  canvas.cd(2)
  hElectrons.Draw()
  ROOT.gSystem.ProcessEvents()
  filename = 'frames/track_{:03d}.png'.format(i)
  canvas.SaveAs(filename)

