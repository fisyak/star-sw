#! /bin/tcsh -f
# cd ~/work/kfp
set GLOB = '2*/*'
if ($#argv > 0)   set GLOB = "$argv";
foreach d (`ls -1d ${GLOB}`)
  cd ${d}; pwd;
  ls -ltr Title.txt *.root
  if ( ! $?) then
    ls -ltr Title.txt *.root | tail -1 | grep Title
    if ( $? ) then
      if (-r Title.txt)  rm Title.txt
    endif
  endif
  if (! -r Title.txt) then
    ls *.root
    if ( ! $?) then
	set file = `ls -1tr *.root | tail -1`
	if ( -r ${file}) then
	    ln -s ~/macros/.sl* .
	    echo "${d} => ${file}"
	    root.exe ${file}  lBichsel.C brtw.C+ ppbarM2.C+ DrawdEdx.C+
	    root.exe ${file}   DrawSignalBg7.C DrawSignalBg_HL34.C
	endif
    endif
  endif
  cd -
end
