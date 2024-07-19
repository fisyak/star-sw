#! /bin/tcsh -f
@ countJ = 0
foreach d (`ls -1d ???/2*`)
  if (! -d ${d}) continue;
  cd $d;
  if (-r Done || -r Submitted) then
    cd -
   continue
  endif
  @ countJ++;  
  ~fisyak/bin/daqdR.pl
  if ($?) then
    ls -1d *bla.root
    if ($?) then
      rm sched* *xml;
      touch Done
    endif
    cd -;
    continue;
  else 
    touch NotYetDone
  endif
  cd -
end
foreach done (`ls -1d ???/*/*Done`)
  set d = `dirname ${done}`
  cd ${d}; pwd;
  ls -ltr | tail -1 | grep Chain	
  if ($?) then	
    @ count = `ps au | grep root.exe | wc -l`; # ++;  echo "count $count";
    if ($count > 40) then 
        cd -
	break;
    endif
    rm -rf .sl*
    ln -s ~fisyak/macros/.sl73_* .	
    root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst")' >&  Chain.log  &
    root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst")' >&  PChain.log  &
    @ countJ++;
  endif
  ls -ltr | tail -1 | grep PChain	
  if ($?) then	
    @ count = `ps au | grep root.exe | wc -l`; # ++;  echo "count $count";
    if ($count > 40) then 
        cd -
	break;
    endif
    rm -rf .sl*
    ln -s ~fisyak/macros/.sl73_* .	
    root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst")' >&  PChain.log  &
    @ countJ++;
  endif
  cd -;
end
if ($countJ > 0) then
  sleep 10; 
  touch `grep total ???/2*/Chain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`
  touch `grep total ???/2*/PChain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGBP\n", n/1.e6,s)}'`
endif
