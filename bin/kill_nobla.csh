#! /bin/tcsh -f
set dirs = `condor_q -wide | grep -w R | awk -F\' '{last_slash = match($3, /[^\/]*$/) - 1;  dirname = substr($3, 1, last_slash);    print dirname;}' | sort -u`
foreach d ($dirs) 
 echo "dir = ${d}"
 ls -ltr ${d}/*log.gz
 if ($?) continue;
 ls -ltr ${d}/*bla.root
 if (! $?) continue;
    echo "${d} is cleaned"
    condor_q -wide | grep -w R | grep ${d} | awk '{print $1}' | xargs condor_rm
end 
