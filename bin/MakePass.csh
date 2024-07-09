#! /bin/tcsh -f
setup debug
FPE_OFF
foreach d (`ls -1d 20*/*F`)
 set dt = `echo ${d} | sed -e 's#/#_#'`;	
 if (! -d  ${d}/IO)  mkdir ${d}/IO	
 cd  ${d}/IO
 if (! -r .${STAR_HOST_SYS_OPT}) ln -s ~/macros/.${STAR_HOST_SYS_OPT} .
 if (! -r Aligner_IO.root) then
   root.exe -q -b 'lDb.C(1,"Cosmic_'${dt}',TFGdbOpt,CorrZ")' TpcAlignerDraw.C+ 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw.log &
 else 	
  if (! -r Results.IO_Aligner_IO) then
     root.exe -q -b  'lDb.C(1,"Cosmic_'${dt}',TFGdbOpt,CorrZ")' Aligner_IO.root 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw2.log &
  endif
 endif
 if (! -r AlignerW2S.root) then
   root.exe -q -b 'lDb.C(1,"Cosmic_'${dt}',TFGdbOpt,CorrZ")' 'TpcAlignerDraw.C+(1)' 'TpcAlignerDraw.C+(3)'> & TpcAlignerDraw1.log &
 else
   if (! -r ResultsAlignerW2S) then
     root.exe -q -b   'lDb.C(1,"Cosmic_'${dt}',TFGdbOpt,CorrZ")' AlignerW2S.root 'TpcAlignerDraw.C+(3)'> & TpcAlignerDraw3.log &
   endif
 endif
 if (! -r Cosmics.root) then
   root.exe -q -b lMuDst.C 'Cosmics.C+("../*MuDst.root")' > & Cosmics.log &
 endif
 cd -
end
