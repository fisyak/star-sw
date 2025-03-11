#! /bin/tcsh -f
@ countJ = 0
foreach done (`ls -1d *.csh`)
    if (-r ${done}.log) continue;
#  set d = `dirname ${done}`
#  ls -ltr Chain.log
	@ count = `ps au | grep root.exe | wc -l`; # ++;  echo "count $count";
    if ($count >= 40) then 
	echo "$count limit reached"
	break;
    endif
    csh -x ${done} >& ${done}.log &
    sleep 10;
end

