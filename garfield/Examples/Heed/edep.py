import ROOT
import Garfield

ROOT.Garfield.SetDefaultStyle()

# Histograms
ROOT.TH1.StatOverflows(True)
hElectrons = ROOT.TH1F("hElectrons", "Number of electrons", 200, 0, 200)
hEdep = ROOT.TH1F("hEdep", "Energy Loss", 100, 0., 10.)
hClusterSize = ROOT.TH1F("hClusterSize", "Cluster size", 100, 0.5, 100.5)

gas = ROOT.Garfield.MediumMagboltz("ar", 90., "co2", 10.)
gas.SetTemperature(293.15)
gas.SetPressure(760.)

# Width of the gas gap [cm].
width = 1.

# Make a component.
cmp = ROOT.Garfield.ComponentConstant()
cmp.SetArea(0., -10., -10., width, 10., 10.)
cmp.SetMedium(gas)
cmp.SetElectricField(100., 0., 0.)

# Make a sensor.
sensor = ROOT.Garfield.Sensor(cmp)

# Set up HEED.
track = ROOT.Garfield.TrackHeed(sensor)
track.SetParticle("pi")
track.SetMomentum(120.e9)
track.Initialise(gas, True)

nEvents = 10000
for i in range(nEvents):
  # if i % 1000 == 0: print i, "/", nEvents
  # Initial position and direction 
  x0 = 0.
  y0 = 0.
  z0 = 0.
  t0 = 0.
  dx0 = 1.
  dy0 = 0.
  dz0 = 0.
  track.NewTrack(x0, y0, z0, t0, dx0, dy0, dz0)
  # Total energy loss along the track
  esum = 0.
  # Total number of electrons produced along the track
  nsum = 0
  # Loop over the clusters.
  for cluster in track.GetClusters():
    esum += cluster.energy
    nc = cluster.electrons.size()
    nsum += nc
    hClusterSize.Fill(nc)
  hElectrons.Fill(nsum)
  hEdep.Fill(esum * 1.e-3);
 
c1 = ROOT.TCanvas()
hElectrons.GetXaxis().SetTitle("number of electrons") 
hElectrons.Draw()
c1.SaveAs("ne.pdf")

c2 = ROOT.TCanvas()
hEdep.GetXaxis().SetTitle("energy loss [keV]")
hEdep.Draw()
c2.SaveAs("edep.pdf")

c3 = ROOT.TCanvas()
hClusterSize.GetXaxis().SetTitle("electrons / cluster")
hClusterSize.Draw()
c3.SetLogy()
c3.SaveAs("clusterSizeDistribution.pdf")
