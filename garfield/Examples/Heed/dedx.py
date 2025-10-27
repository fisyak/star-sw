import ROOT
import Garfield

ROOT.Garfield.SetDefaultStyle()

si = ROOT.Garfield.MediumSilicon()

width = 100.e-4

# Make a component.
cmp = ROOT.Garfield.ComponentConstant()
cmp.SetArea(0., -10., -10., width, 10., 10.)
cmp.SetMedium(si)
cmp.SetElectricField(100., 0., 0.)

# Make a sensor.
sensor = ROOT.Garfield.Sensor(cmp)

# Set up HEED.
track = ROOT.Garfield.TrackHeed(sensor)
track.SetParticle("p")
track.SetMomentum(120.e9)
track.Initialise(si, True)
dedx = track.GetStoppingPower()
print(dedx)
