#! /bin/tcsh -f
  @ count = `ps au | grep hadd | wc -l`
foreach f (`ls -1d */All*.csh`)
  set d = `dirname ${f}`
  set b = `basename ${f} .csh`
  if (-r ${d}/${b}.log || -r ${d}/${b}.root) continue;
  @ count++;
  if ($count > 20) break;
  csh -x ${f} >& ${f}.log &
end 
# E O D
 
