import ROOT
import Garfield

si = ROOT.Garfield.MediumSilicon()

cmp = ROOT.Garfield.ComponentConstant()
cmp.SetElectricField(0., 5000., 0.)
# Thickness of the silicon layer [cm]
d = 100.e-4
cmp.SetArea(-d, 0., -d, d, d, d)
cmp.SetMedium(si) 
# Define the weighting field and weighting potential
# parallel-plate electrode at y = 0).
cmp.SetWeightingField(0, 1. / d, 0., "readout")
cmp.SetWeightingPotential(0, 0, 0, 1.)

sensor = ROOT.Garfield.Sensor(cmp)
sensor.AddElectrode(cmp, "readout")
# Set the time bins for the induced current.
nTimeBins = 1000
tmin =  0.
tmax = 10.
tstep = (tmax - tmin) / nTimeBins
sensor.SetTimeWindow(tmin, tstep, nTimeBins)
 
# Read the TRIM output file. 
tr = ROOT.Garfield.TrackTrim(sensor)
# Import the first 100 ions.
if not tr.ReadFile("EXYZ.txt", 100):
  print("Reading TRIM EXYZ file failed.")
  sys.exit(0)

drift = ROOT.Garfield.DriftLineRKF(sensor)
drift.SetMaximumStepSize(10.e-4)

# Plot the track and the drift lines.
driftView = ROOT.Garfield.ViewDrift()
tr.EnablePlotting(driftView)
drift.EnablePlotting(driftView)
  
# Simulate an ion track.
tr.NewTrack(0., 0., 0., 0., 0., 1., 0.)
# Loop over the clusters.
for cluster in tr.GetClusters():
  # Simulate electron and ion drift lines starting 
  # from the cluster position. 
  # Scale the induced current by the number of electron/ion pairs 
  # in the cluster.
  drift.DriftElectron(cluster.x, cluster.y, cluster.z, cluster.t, cluster.n)
  drift.DriftHole(cluster.x, cluster.y, cluster.z, cluster.t, cluster.n)

driftView.SetArea(-2.e-4, 0., 2.e-4, 100.e-4);
driftView.Plot(True)

signalView = ROOT.Garfield.ViewSignal(sensor)
signalView.PlotSignal("readout", "tei")

