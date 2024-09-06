#! /bin/tcsh -f
set now = `date +%s`;
foreach f (`grep 'probably not closed, trying to recover' ./*/*/Chain.log | awk '{print $5}'`)
  if (! -r ${f}) continue;
  set t =  `stat --format='%Z' ${f}`
  @ dt = ${now} - ${t}
  if (${dt} < 600) continue;
  echo "string:${f}"
end
 
