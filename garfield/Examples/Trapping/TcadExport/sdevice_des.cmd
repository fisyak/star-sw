File {
  	Grid    = "2D_3pixel_msh.tdr"
	Parameter= "sdevice.par"
	Plot=   "simulation"
	Current="simulation"
	Output= "simulation"
}

Electrode {
	{Name="pix1_electrode"	Voltage=0.0 Material = "Aluminum"}
	{Name="pix2_electrode" Voltage= 0.0 Material = "Aluminum"}
	{Name="pix3_electrode"	Voltage=0.0 Material = "Aluminum"}
	{Name="bot_electrode"	Voltage=0.0 Material = "Aluminum"}
}

Physics	{
	Fermi
	Temperature = 242.05
	Mobility(
	 	eHighFieldSaturation
	 	hHighFieldSaturation
	 	PhuMob( Phosphorus Klaassen )
	 )
	Recombination(
			SRH(
				DopingDependence 		
				TempDependence		
				ElectricField(Lifetime=Hurkx DensityCorrection=none )
			)
	 		eAvalanche (vanOverstraeten Eparallel)
			hAvalanche (vanOverstraeten Eparallel)  
		)	
	EffectiveIntrinsicDensity(BandGapNarrowing(Slotboom))
}

Physics(MaterialInterface="Oxide/Silicon") {
		Charge(Conc = 1e12 ) 					
}

Physics (material = "Silicon"){
	Traps(
		(Donor Level
		
		fromValBand
		Add2TotalDoping
		Conc = <4*4e15>
		EnergyMid = 0.48
		eXsection = 2.0e-14
		hXsection = 1e-14)
	
		(Acceptor Level
		
		fromCondBand
		Add2TotalDoping
		Conc = <0.75*4e15>
		EnergyMid = 0.525
		eXsection = 5e-15
		hXsection = 1e-14)

		(Acceptor Level
		
		fromValBand
		Add2TotalDoping
		Conc = <36*4e15>
		EnergyMid = 0.90
		eXsection = 1e-16
		hXsection = 1e-16)
	)
}

Plot {
	Potential	ElectricField/Vector eMobility hMobility 
	eLifetime hLifetime hDriftVelocity/Vector hDriftVelocity/Vector
	

}

Math{
	Method = blocked
	SubMethod = pardiso
	NumberOfThreads = maximum
	Digits=5
	Extrapolate
	RelErrControl
	Derivatives
	Notdamped = 50
	Iterations = 15
}

Solve {
	Coupled(iterations = 600){Poisson}
	Coupled(iterations = 600){Poisson Electron Hole}
	Quasistationary(
		InitialStep=1e-3
		Maxstep=0.04
		MinStep=1e-5
		Increment=1.4
		Decrement=2
		Goal{ name="bot_electrode" voltage= -1000}
	){ 
		Coupled {Poisson Electron Hole}
		Plot ( FilePrefix = "simulation_0V" Time = (1.0) NoOverwrite ) 
	}
	Quasistationary(
		InitialStep=1e-3
		Maxstep=0.04
		MinStep=1e-7
		Increment=1.4
		Decrement=2
		Goal{ name="pix2_electrode" voltage= 1.0 }
	){ 
		Coupled {Poisson Electron Hole}
		Plot ( FilePrefix = "simulation_1V" Time = (1.0) NoOverwrite ) 
	}
	
}
