import ROOT
import Garfield
import ctypes

# Load the field map.
fm = ROOT.Garfield.ComponentAnsys123()
fm.Initialise("ELIST.lis", "NLIST.lis", "MPLIST.lis", "PRNSOL.lis", "mm")
fm.EnableMirrorPeriodicityX()
fm.EnableMirrorPeriodicityY()
fm.PrintRange()

# Dimensions of the GEM [cm]
pitch = 0.014

fieldView = ROOT.Garfield.ViewField(fm)
cF = ROOT.TCanvas('cF', '', 600, 600)
fieldView.SetCanvas(cF)
# Set the normal vector of the viewing plane (xz plane).
fieldView.SetPlaneXZ()
# Set the plot limits in the current viewing plane.
fieldView.SetArea(-0.5 * pitch, -0.02, 0.5 * pitch, 0.02)
fieldView.SetVoltageRange(-160., 160.)
fieldView.GetCanvas().SetLeftMargin(0.16)
fieldView.PlotContour()

# Setup the gas.
gas = ROOT.Garfield.MediumMagboltz("ar", 80., "co2", 20.)
gas.SetTemperature(293.15)
gas.SetPressure(760.)
gas.Initialise(True)

# Set the Penning transfer efficiency.
rPenning = 0.51
gas.EnablePenningTransfer(rPenning, 0., "ar")
# Load the ion mobilities.
gas.LoadIonMobility('IonMobility_Ar+_Ar.txt')
 
fm.SetGas(gas)
fm.PrintMaterials()

# Assemble the sensor.
sensor = ROOT.Garfield.Sensor(fm)
sensor.SetArea(-5 * pitch, -5 * pitch, -0.01, 5 * pitch,  5 * pitch, 0.025)

aval = ROOT.Garfield.AvalancheMicroscopic(sensor)

drift = ROOT.Garfield.AvalancheMC(sensor)
drift.SetDistanceSteps(2.e-4)

driftView = ROOT.Garfield.ViewDrift()
plotDrift = True
if plotDrift:
  aval.EnablePlotting(driftView)
  drift.EnablePlotting(driftView)

# Count the total number of ions and the back-flowing ions.
nTotal = 0
nBF = 0
nEvents = 10
for i in range(nEvents):
  # print i, '/', nEvents
  # Randomize the initial position. 
  x0 = -0.5 * pitch + ROOT.Garfield.RndmUniform() * pitch
  y0 = -0.5 * pitch + ROOT.Garfield.RndmUniform() * pitch
  z0 = 0.02
  t0 = 0.
  e0 = 0.1
  aval.AvalancheElectron(x0, y0, z0, t0, e0, 0., 0., 0.)
  ne, ni = aval.GetAvalancheSize()
  for electron in aval.GetElectrons():
    p0 = electron.path[0]
    drift.DriftIon(p0.x, p0.y, p0.z, p0.t)
    nTotal += 1
    endpoint = drift.GetIons().front().path.back()
    if endpoint.z > 0.005: nBF += 1

print('Ratio of back-flowing ions:', float(nBF) / float(nTotal))
cD = ROOT.TCanvas('cD', '', 600, 600)
meshView = ROOT.Garfield.ViewFEMesh(fm)
plotMesh = True 
if plotDrift:
  if plotMesh:
    meshView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02)
    meshView.SetCanvas(cD)
    # x-z projection.
    meshView.SetPlane(0, -1, 0, 0, 0, 0)
    meshView.SetFillMesh(True)
    #  Set the color of the kapton.
    meshView.SetColor(2, ROOT.kYellow + 3)
    meshView.EnableAxes()
    meshView.SetViewDrift(driftView)
    meshView.Plot()
  else:
    driftView.SetCanvas(cD)
    driftView.SetPlane(0, -1, 0, 0, 0, 0)
    driftView.SetArea(-2 * pitch, -0.02, 2 * pitch, 0.02)
    driftView.Plot(True)
