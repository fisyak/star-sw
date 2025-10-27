Device SimpleDiode {

	File {
		Grid = "generated/@tdr@"
		Plot = "output/n@node@"
		Current = "output/n@node@.plt"
	}

	Electrode {
		{ Name="N" Voltage=0.0 }
		{ Name="P" Voltage=0.0 }
	}


	Physics {
		eQCvanDort
		AreaFactor=1
		Temperature = 293
		Mobility(
			HighFieldSaturation( GradQuasiFermi )
			Enormal
		)
		EffectiveIntrinsicDensity( SlotBoom )
		Recombination()
	}


	Physics (Material = "Silicon" ) {
		Mobility(
			DopingDep
			HighFieldSaturation( GradQuasiFermi )
			Enormal
		)
		Recombination(
			SRH(
				DopingDep
				#ElectricField(
				#	Lifetime=Schenk
				#	DensityCorrection=Local
				#)
			)
		)
	}

	Plot {
	  Current/Vector
		eCurrent/Vector
		hCurrent/Vector

		eDensity hDensity
		eCurrent hCurrent

		ValenceBandEnergy ConductionBandEnergy

		TotalCurrent
		ElectricField/Vector
		Potential

		SpaceCharge

		Doping DonorConcentration AcceptorConcentration

		eMobility hMobility eVelocity hVelocity

		SRHRecombination
	}

}


#Define the system: DUT in paralle with pulsed voltage source
System {
	SimpleDiode dut ( "N"=vbias "P"=gnd ) { }
	Vsource_pset vpulse ( vbias gnd ) { pulse = (@Bias_Voltage@ @< @Bias_Voltage@+@Pulse_Voltage@ >@ 0 50e-12 50e-12 100e-12 1e-6) }
	Set ( gnd = 0.0 )
}


Math {
	Number_Of_Threads=maximum
	Iterations=25
	RelErrControl
	Digits=6
	Method=pardiso
	NotDamped=200
	Extrapolate
	CheckTransientError
	CurrentWeighting
	RecBoxIntegr(1e-2 10 1000)
	RhsFactor=1e30
	ParameterInheritance=None
	CDensityMin=10
}


Solve {
	Coupled{Poisson}
	Coupled{Poisson Electron Hole}
	Coupled{Poisson Electron Hole Circuit}

	Plot (
		FilePrefix = "output/n@node@_steady"
	)

	Transient( InitialTime = 0.0 FinalTime = 300e-12 InitialStep = 5e-12 MaxStep = 10e-12) {
		Coupled {Poisson Electron Hole Circuit}
		Plot (
			Time = (100e-12 )
			FilePrefix = "output/n@node@_pulse"
		)
	}
	Transient( InitialTime = 300e-12 FinalTime = @End_Time@ InitialStep = 10e-12) {
		Coupled {Poisson Electron Hole Circuit}
		Plot (
			Time = (@[ read [open "plot_times.txt" r] ]@ )
			NoOverwrite
			FilePrefix = "output/n@node@_decay"
		)
	}
}
