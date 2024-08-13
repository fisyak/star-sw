#! /bin/tcsh -f
# cd ~/bin/; onl CURRENT | SortRun.pl | tee RunXXIVDefs.pm
# git diff . RunXXIVDefs.pm
# git ci -m "Update"  RunXXIVDefs.pm
#CreateRunDirs.pl 0 100
@ countJ = 0
foreach d (`ls -1d ???/2*`)
  if (! -d ${d}) continue;
  cd $d;
  if (-r Done || -r Submitted) then
    cd -
   continue
  endif
  @ countJ++;  
  ~fisyak/bin/daqdR.pl
  if ($?) then
    ls -1d *bla.root
    if ($?) then
      rm sched*;
      touch Done
    endif
    cd -;
    continue;
  endif
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2021_Cosmics.xml
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2022_Cosmics.xml
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit ~fisyak/xml/daq_2021_Cosmics.xml
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2023_Cosmics.xml
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2019_Cosmics.xml
#    /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit  -p bnl_condor_online_CpuModelNumber6X  ~fisyak/xml/daq_${YEAR}_Cosmics.xml
#  /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit  -p bnl_condor_online_CpuModelNumber6X  ~fisyak/xml/daq.DEV2.xml
    /gpfs01/star/subsys-tpc/fisyak/STAR/packages/scripts/star-submit ~fisyak/xml/daq.TFG24c.xml
#    /gpfs01/star/subsys-tpc/fisyak/STAR/packages/scripts/star-submit -p bnl_condor_production  ~fisyak/xml/daq.TFG24c.xml
  touch Submitted
  cd -
#  if ($countJ >= 40) then 
#	break;
#  endif
end
#end
#  /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber63 ~fisyak/xml/daq_2021StiCA.Minuit.TFG19m.xml
#  /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2021StiCA.Minuit.TFG20a.xml
#  /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~fisyak/xml/daq_2021.xml
#================================= Summurizing  ===============================================
exit 0;
@ count = 0
foreach done (`ls -1d ???/*/Done`)
  set d = `dirname ${done}`
  cd ${d}; pwd;
  ls -ltr | tail -1 | grep Chain.log	
  if ($?) then	
    rm -rf .sl*
    ln -s ~fisyak/macros/.sl73_* .	
    root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst",kTRUE)' >&  Chain.log  &
    root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst",kTRUE)' >&  PChain.log  &
    @ count++;  echo "count $count";
    if ($count > 120) then 
        cd -
	break;
    endif
  endif
  cd -;
end
if ($count > 0) then
  sleep 10; 
  touch `grep total ???/2*/Chain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`
endif
