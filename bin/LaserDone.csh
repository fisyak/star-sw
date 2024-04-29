#! /bin/tcsh -f
foreach f (`ls -1d *ofl`)
    set run = `grep Run ${f} | awk '{print $5}'`
    set cint = `basename ${f} .HOLD.ofl`
    echo "${f} => run ${run} => cint = ${cint}"
    echo "mv 2*${run}B.log  ${cint}* LaserPlots*${run}.root Done/"
    mv 2*${run}B.log  ${cint}* LaserPlots*${run}.root Done/
end
