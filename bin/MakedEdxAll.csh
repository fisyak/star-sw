#! /bin/tcsh -f
# foreach d (`ls -1d *`)
foreach d (`ls -1dtr AuAu_* *GeV* | sort -u`)
  cd ${d}
  ls -ltr *.root | tail -1 | grep All
  if ($?) then
    rm All*
    hadd.pl
    lsf hadd.xml
  endif
  cd -
end
