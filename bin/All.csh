#! /bin/tcsh -f
set GLOB = ' 2* AuAu* *GeV* dAu* pp*'
if ($#argv > 0)   set GLOB = "$argv";
# foreach d (`ls -1d *`)
set domain = `hostname -d`
foreach d (`ls -1dtr ${GLOB}| sort -u`)
#foreach d (`ls -1d */*.root | sed -e 's#/.*##' | sort -u`)
  cd ${d}; pwd;
  ls -ltr *.root | tail -1 | grep All 
  if ($?) then
    echo "rm All*"
    rm All*
    hadd.pl # FilesPerJob=10
    foreach f (`ls -1d hadd*.condor`)
      condor_submit ${f}
    end
#    if ($STAR_SYS != "x8664_al9") then
#    switch ($domain) 
#      case "*local":
#      case "*starp.bnl.gov":
#      /net/l402/data/fisyak/STAR/packages/.DEV2/scripts/star-submit -p bnl_condor_online_CpuModelNumber63 hadd.xml
#      breaksw
#      default:
#	/gpfs01/star/subsys-tpc/fisyak/STAR/packages/scripts/star-submit hadd.xml
#        /star/nfs4/AFS/star/packages/scripts/sums-submit-beta hadd.xml
#      breaksw
#    endsw
#    endif	
  endif
  cd -
end
