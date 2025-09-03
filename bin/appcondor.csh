#! /bin/tcsh -f
switch ($STAR_HOST_SYS) 
  case "al*":
    cat sched*.condor | sed '/Priority         = +10/a requirements = (Microarch == "x86_64-v4")\nGetEnv          = True'| sed -e 's#/bin/sh#/bin/csh#' -e 's#exec#exec apptainer exec -e -B /direct -B /star -B /afs -B /gpfs -B /sdcc/lustre02 /cvmfs/star.sdcc.bnl.gov/containers/rhic_sl7.sif csh -x#' > submit.condor; 
    breaksw
  default:
    cat sched*.condor | sed '/Priority         = +10/a GetEnv          = True' > submit.condor; 
endsw 
#if (! $?) condor_submit submit.condor
