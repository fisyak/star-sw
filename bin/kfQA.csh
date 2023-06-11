#! /bin/tcsh -f
#ls -1d [0-2]*_[1-9].root | awk -F\_ '{print $1/1000}' | awk -F\. '{print "string:"$1}' | sort -u 
#ls -1d [0-2]*.root |  awk -F\. '{print "string:"$1}' | sort -u 
#ls -1d [0-2]*_*.root |  awk -F\_ '{print "string:"$1}' | sort -u 
foreach f (`find . -name "[0-2]*_*.root" -size +100000c  |  awk -F\_ '{print ""$1}' | sort -u | sed -e 's#./##'`)
 if (-r R${f}.root) continue;
 echo "string:${f}"
end

