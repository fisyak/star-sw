#! /bin/tcsh -f
foreach d (`ls -1d 2*`) 
 set n = `ls -1d ${d}/All*.root | wc -l`
 if ($n == 0) then
   continuel
 else 
   if ($n == 1) then
     ln -s ${d}/All*.root R${d}.root
   else
     hadd  R${d}.root ${d}/All*.root >& R${d}.log &
   endif
 endif
end
