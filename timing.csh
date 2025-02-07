#! /usr/local/bin/tcsh -f
set log=$STAR_HOST_SYS;
if ($?NODEBUG) then 
    set log = build.${STAR_HOST_SYS}.opt.log
else
    set log = build.${STAR_HOST_SYS}.debug.log
endif
if (-r ${log} ) rm ${log}
time cons  -k >& ${log} 
