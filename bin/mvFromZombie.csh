#! /bin/tcsh -f
foreach mu (`ls -1d *MuDst.root`)
  set b = `basename ${mu} .MuDst.root`
  set d = `echo ${b} | awk -F_ '{printf("../%03i/%i\n",int(($3-20000000)/1000),$3)}'`
  echo "mv ${b}* ${d}"
  mv ${b}* ${d}
end

  
