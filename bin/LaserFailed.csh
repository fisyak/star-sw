#! /bin/tcsh -f
foreach f (`ls -1d Laser*`)
    if (-r  Failed.1/${f}) then
       mv ${f} Failed
    else
       mv ${f} Failed.1
    endif
end
