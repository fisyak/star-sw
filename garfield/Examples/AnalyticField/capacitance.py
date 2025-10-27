import ROOT
import Garfield

si = ROOT.Garfield.MediumSilicon()
eps = ROOT.Garfield.VacuumPermittivity * si.GetDielectricConstant()

# Thickness of the silicon [cm].
gap = 50.e-4
# Pixel pitch [cm].
pitch = 55.e-4
h = 0.5 * pitch

cmp = ROOT.Garfield.ComponentAnalyticField()
cmp.SetMedium(si)
cmp.AddPlaneY(0., -1., "back")
cmp.AddPlaneY(gap, 0., "front")
cmp.AddPixelOnPlaneY(gap, -h, h, -h, h, "pixel")
 
# Back plane.
w = 3 * pitch
x0 = -0.5 * w
y0 = 0.
z0 = -0.5 * w
q = cmp.IntegrateWeightingFluxParallelogram("pixel", x0, 0., z0, w, 0, 0, 0, 0, w)
q *= eps
print("Backplane", q,  "fF")

x0 = 0.
y0 = 0.999 * gap
z0 = 0.5 * pitch
q = cmp.IntegrateWeightingFluxParallelogram("pixel", x0, y0, z0, pitch, 0, 0, 0, 0, pitch)
q *= eps
print("Neighbour", q, "fF")

x0 = 0.5 * pitch
y0 = 0.999 * gap
z0 = 0.5 * pitch
q = cmp.IntegrateWeightingFluxParallelogram("pixel", x0, y0, z0, pitch, 0, 0, 0, 0, pitch)
q *= eps;
print("Diagonal", q, "fF")
