#! /bin/tcsh -f
foreach f (`ls -1d */All*.csh`)
    set b = `echo ${f} | sed -e 's/csh//'`;
    if (-r ${b}root) continue; 
    if (-r ${b}log) continue; 
    if (-r ${b}csh.log) continue; 
    @ count = `ps au | grep All | wc -l`; # ++;  echo "count $count";
    if ($count > 20) then 
        cd -
	echo "$count limit reached"
	break;
    endif
    csh -x ${f} >& ${f}.log &
end
exit 0;
