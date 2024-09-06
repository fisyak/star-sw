#! /bin/tcsh -f
set GLOB = ' 2* AuAu* *GeV* dAu* pp*'
if ($#argv > 0)   set GLOB = "$argv";
# foreach d (`ls -1d *`)
set domain = `hostname -d`
foreach d (`ls -1dtr ${GLOB}| sort -u`)
  cd ${d}
  ls -ltr *.root | tail -1 | grep All
  if ($?) then
    echo "rm All*"
    rm All*
    hadd.pl
    switch ($domain) 
      case "*local":
      case "*starp.bnl.gov":
      /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber63 hadd.xml
    breaksw
      default:
	/gpfs01/star/subsys-tpc/fisyak/STAR/packages/scripts/star-submit hadd.xml
    breaksw
  endsw
	
  endif
  cd -
end
