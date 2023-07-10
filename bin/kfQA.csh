#! /bin/tcsh -f
#ls -1d [0-2]*_[1-9].root | awk -F\_ '{print $1/1000}' | awk -F\. '{print "string:"$1}' | sort -u 
#ls -1d [0-2]*.root |  awk -F\. '{print "string:"$1}' | sort -u 
#ls -1d [0-2]*_*.root |  awk -F\_ '{print "string:"$1}' | sort -u 
#foreach f (`find . -name "[0-2]*_*.root" -size +100000c  |  awk -F\_ '{print ""$1}' | sort -u | sed -e 's#./##'`)
# if (-r R${f}.root) continue;
# echo "string:${f}"
#end

foreach f (`find . -maxdepth 1 -name "*.root" -size +8100000c | sed -e 's|./||' -e 's|st_physics_||' -e 's/hlt_//' -e 's|st_fmsslow_||' -e 's|st_minbias_||' -e 's|st_hlt_||' -e 's|adc_||' -e 's|hlt_||' | awk -F_ '{print $1}' | sort -u`)
 if (-r R${f}.root) continue;
 echo "string:${f}"
end

