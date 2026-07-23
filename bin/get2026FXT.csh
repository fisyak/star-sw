#! /bin/tcsh -f
foreach p (9p8GeV 8p65GeV 13p5GeV)
   get_file_list.pl  -keys 'path,basename,events' -cond 'filetype=online_daq,trgsetupname=production_'${p}'_fixedTarget_2026' -limit 0 | tee ${p}_fixedTarget_2026.list
end
