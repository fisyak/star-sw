import ROOT
import Garfield

gas = ROOT.Garfield.MediumMagboltz()
gas.EnableDebugging()
gas.LoadGasFile('C3H8_1Torr_313K_0.1_to_1800.gas')
gas.SetInterpolationMethodIonMobility(1)
gas.LoadIonMobility('IonMobility_C3H8+_C3H8.txt')

view = ROOT.Garfield.ViewMedium(gas)
view.PlotIonVelocity()
