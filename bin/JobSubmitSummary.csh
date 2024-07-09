#! /bin/tcsh -f
@ count = 0
foreach done (`ls -1d ???/*/Done`)
  set d = `dirname ${done}`
  cd ${d}; pwd;
  ls -ltr | tail -1 | grep Chain	
  if ($?) then	
    rm -rf .sl*
    ln -s ~/macros/.sl73_* .	
    root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst")' >&  Chain.log  &
    @ count++;  echo "count $count";
    if ($count > 120) then 
        cd -
	break;
    endif
  endif
  cd -;
end
if ($count > 0) then
  sleep 10; 
  touch `grep total ???/2*/Chain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`
endif
