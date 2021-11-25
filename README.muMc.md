1. Setup .DEV2 with compiler and optimization version.
  (a) Reset GROUP_DIR set version .DEV2
  source /afs/rhic.bnl.gov/star/packages/.DEV2/setupDEV2.csh
  (b) Default complier is your default compiler. To change it 
  setup gcc
  setup 32b
  (c) Default optimization level is DEBUG. To set optimized version
  setenv NODEBUG yes
  starver .DEV2
  (d) The version with gcc 4.9.2 (DEBUG) can be update any time.
Because of this you are adviced to use gcc 4.8.5 which wil be updated very rarely.

2. Many macros can be used from my private directory ~fisyak/macros
  You have advices to add to your ~/.rootrc lines (see ~fisyak/.rootrc)
+Unix.*.Root.DynamicPath:    :$HOME/macros:/afs/rhic.bnl.gov/star/users/fisyak/macros
+Unix.*.Root.MacroPath:      :$HOME/macros:/afs/rhic.bnl.gov/star/users/fisyak/macros

3. There are some scripts from /afs/rhic.bnl.gov/star/users/fisyak/bin which are used to submit jobs.
You are adviced to add to your PATH 
   setenv PATH ${PATH}:/afs/rhic.bnl.gov/star/users/fisyak/bin

4. 2014 AuAu200 simulation
   (a) /afs/rhic.bnl.gov/star/users/fisyak/xml/hMC2014.xml
   (b) In the xml-file directory name used to order to switch option for reconstruction
For example, you create directory
   mkdir hMC2014noHFTStiCAKFV.DEV2
   (c) The line
<input URL="command:RunId.pl 1 200" />
defines that it should simulated and reconstructed 200 files with random numbers from 1 to 200
   (d) To submit jobs you can use

star-submit hMC2014.xml
   I have submitted obs in directory 
/afs/rhic.bnl.gov/star/users/fisyak/work/reco/2014/hMC2014noHFTStiCAKFV.DEV2
5. To run muMc.C just do
   setenv STARFPE NO
   root.exe -q -b -x 'muMc.C(1e8,"./*MuDst.root")'
6. To get png-files and html
   root.exe -q muMc.C
