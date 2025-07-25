#! /bin/tcsh -f
switch ($STAR_HOST_SYS) 
  case "al*":
    cat sched*.condor | sed '/Priority         = +10/a requirements = (Microarch == "x86_64-v4")\nGetEnv          = True' > submit.condor; 
    breaksw
  default:
    cat sched*.condor | sed '/Priority         = +10/a GetEnv          = True' > submit.condor; 
endsw 
if (! $?) condor_submit submit.condor
