#! /bin/tcsh -f
set GLOB = 'sched*.condor'
if ($#argv > 0)   set GLOB = "$argv";
switch ($STAR_HOST_SYS) 
  case "al*":
#    cat ${GLOB} | sed '/Priority         = +10/a requirements = (Microarch == "x86_64-v4")\nGetEnv          = True' > submit.condor; 
    cat ${GLOB} | sed '/Priority         = +10/a requirements = (Microarch == "x86_64-v4")\n' > submit.condor; 
    breaksw
  default:
#    cat ${GLOB} | sed '/Priority         = +10/a GetEnv          = True' > submit.condor; 
    cat ${GLOB}  > submit.condor; 
endsw 
if (! $?) condor_submit submit.condor
