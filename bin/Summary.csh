#! /bin/tcsh -f
@ countJ = 0
foreach done (`ls -1d ???/*`)
#  set d = `dirname ${done}`
#  ls -ltr Chain.log
    @ count = `ps au | grep root.exe | wc -l`; # ++;  echo "count $count";
    if ($count > 120) then 
        cd -
	echo "$count limit reached"
	break;
    endif
  set d = ${done}
  cd ${d}; pwd;
  ls -ltr *.root *.gz *B.log *Chain.log  | tail -1 | grep Chain	
  if ($?) then	
    rm -rf .sl*
    set n = `ls -1d *MuDst.root | wc -l`
    if ($n > 0) then
      ln -s ~fisyak/macros/.sl* .	
      root.exe -q -b 'Chain.C+("./*MuDst.root","MuDst")' >&  Chain.log  &
      root.exe -q -b 'Chain.C+("./*picoDst.root","PicoDst")' >&  PChain.log  &
      @ countJ++
    endif
  endif
  cd -;
end
#exit 0;
if ($countJ > 0) then
  sleep 10; 
  touch `grep total ???/2*/Chain.log | grep -v 'chained 0' | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`
  touch `grep total ???/2*/PChain.log | grep -v 'chained 0' | awk 'BEGIN{n= 0; s = 0}{n += $6; s += $10}END{printf("%7.3fM_%fGB\n", n/1.e6,s)}'`P
endif
