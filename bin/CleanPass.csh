#! /bin/tcsh -f
# Clean Up logs and root files from Alignment Pass
foreach d (`ls -1d */?F`)
  cd ${d}; pwd;
  @ count = 0
  foreach f (`ls -1S *B.log`)
     @ count++;  
     if ($count == 1) continue;
     rm ${f}
  end
  echo "count $count";
  rm -f *Aligner.root  *MuDst.root
  rm -f fisyak.log  *xml sched*
  cd -;
end
