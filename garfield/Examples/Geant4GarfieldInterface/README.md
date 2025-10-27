:warning: To compile and link this program, a version of Geant4.10 has to be installed

To run the program in batch mode, please type 
```
./exampleGeant4Interface -m ./run.mac
```
In `run.mac` one can set the material of the absorber that is used, and the type and energy of the particle that are fired with the particle gun.
The ionization model (PAIPhot or PAI model in Geant4, Heed in Garfield++) and the valid particle types and energy ranges can be set in the file `physics.mac`.
The program can also be run with visualization, for that type 
```
./exampleGeant4Interface
```
and then press the "run" button.
