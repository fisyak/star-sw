<h1>  TFG (Tracking Focus Group) branch of the offline Software libraries for STAR experiment</h1> 
<p> This repository (TFG)  has been forked from the github "official" STAR software (upsteam git@github.com:star-bnl/star-sw.git)
in order to provide express calibration, express production, and express analysis.
This repository is located at  git@github.com:fisyak/star-sw.git (as TFG branch).
The list of stable releases can be found TFG_Releases.md

<h2>How to use  TFG release </h2>
<ul>
<li>  <b>starver .DEV2</b>
<li>  <b>source $STAR/setupDEV2.csh</b>
<li>  <b>starver _desired_TFG_version__</b>, from TFG16a  to TFG21n, .DEV2 == TFG is check out HEAD from TFG repository, it could be unstable.
</ul>
<p>
In order to switch back to the "official" STAR software do: 
<ul>
<li><b>source unsetupDEV2.csh</b>
</ul>
<p>
To use macros available in TFG releases w advice you to add in ~/.rootrc files the next two lines: 

Unix.*.Root.DynamicPath:    :$HOME/macros:$STAR/macros/.$STAR_HOST_SYS:$STAR/macros:$STAR/macros/.$STAR_HOST_SYS:$(LD_LIBRARY_PATH)
Unix.*.Root.MacroPath:      :$HOME/macros:$STAR/macros:$(ROOTSYS)/macros:./StRoot/macros:./StRoot/macros/graphics:./StRoot/macros/analysis:./StRoot/macros/test:./StRoot/macros/examples:./StRoot/macros/html:./StRoot/macros/qa:./StRoot/macros/mudst:$(STAR)/StRoot/macros:$(STAR)/StRoot/macros/graphics:$(STAR)/StRoot/macros/analysis:$(STAR)/StRoot/macros/test:$(STAR)/StRoot/macros/examples:$(STAR)/StRoot
/macros/html:$(STAR)/StRoot/macros/qa:$(STAR)/StRoot/macros/mudst:$(STAR)/StRoot/macros/calib:./StRoot/macros/embedding:$(STAR)/StRoot/macros/embedding:$(ROOTSYS)/macros:$ROOTSYS/tutorials:$(ROOTROOT)/root/tmva/test

or just copy 
<b>cp ~fisyak/.rootrc_noqt ~/.rootrc</b>

<h2>
A tutorial : How to use  KFParticle for analysis can be found at 
https://drupal.star.bnl.gov/STAR/subsys/hlt/kfparticle-tutorial