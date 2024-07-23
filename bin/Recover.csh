#! /bin/tcsh -f
grep 'probably not closed, trying to recover' ./*/*/Chain.log | awk '{print "string:"$5}'
