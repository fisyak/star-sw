import ROOT
import Garfield

ROOT.Garfield.PlottingEngine.SetPalette(ROOT.kGreyScale)

# Gas mixture.
gas = ROOT.Garfield.MediumMagboltz("ne", 85.72, "co2", 9.52, "n2", 4.76)

# Define the cell layout.
cmp = ROOT.Garfield.ComponentAnalyticField()
cmp.SetMedium(gas)
# Distance between rows of wires [cm].
gap = 0.2
# Periodicity (wire spacing) [cm].
period = 0.25
cmp.SetPeriodicityX(period)
# Wire diameters [cm].
ds = 0.0020 # sense wires
dc = 0.0075 # cathode wires
dg = 0.0075 # gate wires
# Voltage settings.
vs = 1460. # sense wires
vg =  -70. # gate wires

# Add the sense (anode) wires.
cmp.AddWire(0, gap, ds, vs)
# Add the cathode wires.
cmp.AddWire(0.5 * period, 2 * gap, dc, 0.)
# Add the gate wires.
xg1 = 0.25 * period
xg2 = 0.75 * period
yg = 2. * gap + 0.3
cmp.AddWire(xg1, yg, dg, vg)
cmp.AddWire(xg2, yg, dg, vg)
# Add the planes.
cmp.AddPlaneY(0., 0.)
cmp.AddPlaneY(249.7, -100000)

# Plot isopotential contours.
fieldView = ROOT.Garfield.ViewField(cmp)
xmin = -3 * period
xmax =  3 * period
ymin = 0.
ymax = 5 * gap
fieldView.SetArea(xmin, ymin, xmax, ymax)
fieldView.SetVoltageRange(-400., 1000.)
fieldView.SetNumberOfContours(40)
fieldView.Plot("v", "CONT1")
# Plot field lines.
xf = ROOT.std.vector('double')()
yf = ROOT.std.vector('double')()
zf = ROOT.std.vector('double')()
fieldView.EqualFluxIntervals(xmin, ymax, 0, xmax, ymax, 0, xf, yf, zf, 50)
fieldView.PlotFieldLines(xf, yf, zf, True, False) 

# Plot the cell layout.
cellView = ROOT.Garfield.ViewCell(cmp)
cellView.SetCanvas(fieldView.GetCanvas())
cellView.SetArea(xmin, ymin, xmax, ymax)
cellView.Plot2d()

