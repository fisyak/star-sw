#! /bin/tcsh -f
@ countJ = 0
foreach done (`ls -1d ???/*`)
#  set d = `dirname ${done}`
  set d = ${done}
  cd ${d}; pwd;
  ls -ltr *.root *.gz *B.log *Chain.log  | tail -1 | grep Chain	
#  ls -ltr Chain.log
  if ($?) then	
    @ count = `ps au | grep root.exe | wc -l`; # ++;  echo "count $count";
    if ($count > 40) then 
        cd -
	echo "$count limit reached"
	break;
    endif
    rm -rf .sl*
    ln -s ~fisyak/macros/.sl73_* .	
#    root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst",kTRUE)' >&  Chain.log  &
#    root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst",kTRUE)' >&  PChain.log  &
   root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst")' >&  Chain.log  &
   root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst")' >&  PChain.log  &
    @ countJ++
  endif
  cd -;
end
exit 0;
if ($countJ > 0) then
  sleep 10; 
  touch `grep total ???/2*/Chain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`
  touch `grep total ???/2*/PChain.log | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`P
endif
