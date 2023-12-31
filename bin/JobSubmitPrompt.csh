#! /bin/tcsh -f
foreach d (`ls -1d  /hlt/cephfs/reco/TpcPrompt/*/*/*`)
#  foreach r (`ls -1d ${d}/*/* | head -1`)
  foreach r (`ls -1d ${d}/*/*`)
     cd ${r}
     getDaqList.pl
     if (! $?) then
	/net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber6X ~/xml/TpcPromptR.xml
     endif
     cd -
  end
end
