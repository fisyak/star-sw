#! /bin/tcsh -f
#  root.exe -q ${f} brtw.C+ K0sBW.C
foreach d (`ls -1d */*_TFG24c */*_P24ia`)
  cd ${d} 
  set f = `ls -1tr *GeV*.root | tail -1`
  ln -s ~/macros/.sl* .
  root.exe -q ${f} brtw.C+
  cd -
end
