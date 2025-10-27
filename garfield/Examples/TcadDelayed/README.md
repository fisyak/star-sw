# Simulation of Signals with a Delayed Component based on TCAD Simulations

This example demonstrates how to simulate signals in semiconductor (silicon) sensors, with elements with a non-zero conductivity.
Such situation arise for example when a detector does not / is not fully depleted.
In these cases, an extension of the Shockley-Ramo theorem needs to be used, as presented by [W. Riegler in 2019](https://www.sciencedirect.com/science/article/pii/S0168900219309015).
Instead of a simple (constant in time) weighting field of weighting potential, the extended Shockley-Ramo theorem uses time-dependent weighing field and time dependent weighting vectors.

In very simple cases, these time dependent weighting fields can be calculated analytically.
But for more complex structures TCAD (or other finite element methods) is used for generating the field maps.
Garfield++ supports this type of simulation, via delayed signals calculated from these time dependent weighting fields.

The physical example chose here is a simple 1D P/N junction, which has a high N++ doping at the junction.
This leads to the situation, that only the P-side is depleting, but not the N-side.
The N-side is thus conductive which implies the use of the extended Shockley-Ramo theorem.

This example uses the approach of the weighting vector for the calculation of the transient current signal (see equations (10), (13) and section 2.4 in [W. Riegler](https://www.sciencedirect.com/science/article/pii/S0168900219309015)).
Thus, the TCAD simulation uses a short (250ps) voltage pulse applied to the readout electrode.
Before the pulse, the steady state electric field is saved (E_steady), during the pulse the E_pulse electric field is saved, and after the pulse periodically the E_decay(t) electric fields are saved.

E_pulse and E_steady are used to calculate the weighting field of the prompt response (see equation (17) in [W. Riegler](https://www.sciencedirect.com/science/article/pii/S0168900219309015)) and E_decay(t) and E_steady for the calculation of the delayed response (see equation (18) in [W. Riegler](https://www.sciencedirect.com/science/article/pii/S0168900219309015)).


## TCAD Simulation

The TCAD example simulation is located in the `sentaurus/` folder.
It comprises the following three stages:

- [Structure definition and meshing (sde)](Examples/TcadDelayed/sentaurus/sde_dvs.cmd): Implements the described P/N++/N structure, implemented via the _Scheme_ programming language.
- [Transient simulation (sdevice)](Examples/TcadDelayed/sentaurus/weighting_vector_des.cmd): This is a mixed simulation making use of the meshed sde model and some simple SPICE models.
- [Data export (tdx)](Examples/TcadDelayed/sentaurus/garfield_convert_tcl.cmd): Converts the simulated `.tdr` files into the `.dat / .grd` (ISE) file format, which is supported by Garfield++.

The TCAD simulation was written and tested with Synopys Sentaurus TCAD 2018.06.


## Garfield++ Simulation

The Garfield++ simulation is implemented in the [diode.C](./diode.C) file.
See the comments within this file for more detailed explanation.



## Usage

### TCAD Simulation

The electric field, weighting field and delayed weighting field maps need to be generated Sentaurus TCAD.
To do so, run the following command within this directory to start the Sentaurus Workbench

    STDB=$PWD swb&

Within the workbench

- Open the **sentaurus** project in the _Projects_ panel.
- Run node **n8** (sde) and **n12** (sdevice).

This creates the field maps within `sentaurus/output/` as `.tdr` files.
To convert the `.tdr` files to `.dat / .grd` (necessary for Garfield++) also run node **n14**.

The final files are now located in `sentaurus/output/converted`


### diode.C Compilation
Compile the example Garfield++ script with

    mkdir build
    cd build
    cmake ..
    make

This should create the executable `build/diode`.

Finally run the Garfield++ simulation with

    ./build/diode sentaurus/output/converted/n12

`sentaurus/output/converted/n12` is the prefix of the converted `.grd / .dat` files.

The program will propagate 100 e/h pairs, created close to the P-side surface.
Thus, the resulting signal is mainly due to the drift of electrons.
The total signal, the total electron signal and the delayed electron signal are shown in a plot.
All signals are saved to a `.csv` file.
