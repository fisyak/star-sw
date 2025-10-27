import ROOT
import Garfield
from math import *
import ctypes

# Electric field [V/cm]
efield = 30.e3

# Set up the gas.
gas = ROOT.Garfield.MediumMagboltz()
gas.SetComposition("Ar", 90., "CO2", 10.)

# Run Magboltz for the requested electric field.
gas.SetFieldGrid(efield, efield, 1, False)
gas.GenerateGasTable(10)
# alpha = ctypes.c_double(0.)
# gas.ElectronTownsend(efield, 0, 0, 0, 0, 0, alpha)
gas.SetMaxElectronEnergy(200.)

# Create a component with uniform electric field.
gap = 200.e-4
cmp = ROOT.Garfield.ComponentConstant()
cmp.SetArea(-2., -2., -gap, 2., 2., gap)
cmp.SetElectricField(0, 0, efield)
cmp.SetMedium(gas)

sensor = ROOT.Garfield.Sensor(cmp)

aval = ROOT.Garfield.AvalancheMicroscopic(sensor)

# Histogram the electron energy distribution.
hEnergy = ROOT.TH1F('hEnergy', '', 100, 0., 20.)
aval.EnableElectronEnergyHistogramming(hEnergy)

hX = ROOT.TH1F('hX', '', 100, 0, 0)
hY = ROOT.TH1F('hY', '', 100, 0, 0)
hT = ROOT.TH1F('hT', '', 100, 0, 0)

nDrift = 2000
print('Simulating', nDrift, 'electron drift lines...')
for i in range(nDrift):
  if i % 100 == 0: print('{:5d}\r'.format(i), end='')
  e0 = 0.1 if i == 0 else hEnergy.GetRandom()
  aval.DriftElectron(0, 0, 0, 0, e0)
  endpoint = aval.GetElectrons().front().path.back()
  hT.Fill(endpoint.t)
  hX.Fill(endpoint.x)
  hY.Fill(endpoint.x)
print('{:5d}'.format(nDrift))

vd = 1.e3 * gap / hT.GetMean()
print('Drift velocity: {:.2f} cm / us'.format(vd))
dt = 1.e4 * 0.5 * (hX.GetStdDev() + hY.GetStdDev()) / sqrt(gap)
print('Transverse diffusion: {:.2f} um / cm1/2'.format(dt))

hNe = ROOT.TH1F('hNe', '', 100, 0, 0)
nAval = 1000
print('Simulating', nAval, 'avalanches...')
for i in range(nAval):
  if i % 10 == 0: print('{:5d}\r'.format(i), end='')
  e0 = hEnergy.GetRandom()
  aval.AvalancheElectron(0, 0, 0, 0, e0)
  ne, ni = aval.GetAvalancheSize(ne, ni)
  hNe.Fill(ne)
print('{:5d}'.format(nAval))

alpha = log(hNe.GetMean()) / gap 
print('Effective Townsend coefficient: {:.2f}'.format(alpha))
