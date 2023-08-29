#! /bin/tcsh -f
set GLOB = ' AuAu_* *GeV* dAu*'
if ($#argv > 0)   set GLOB = "$argv";
# foreach d (`ls -1d *`)
foreach d (`ls -1dtr ${GLOB}| sort -u`)
  cd ${d}
  ls -ltr *.root | tail -1 | grep All
  if ($?) then
    echo "rm All*"
    rm All*
    hadd.pl
    /gpfs01/star/subsys-tpc/fisyak/STAR/packages/scripts/star-submit hadd.xml
  endif
  cd -
end
