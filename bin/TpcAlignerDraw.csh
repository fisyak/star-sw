foreach d (`ls -1d 2*/?F`)
 if (-d ${d}/IO) then
   if (	-r  ${d}/CosmicPlots.data ) continue
 else 
   mkdir ${d}/IO
 endif
 cd  ${d}/IO
 ln -s ~/macros/.sl* .
   root.exe -q -b 'TpcAlignerDraw.C+(0,"../*Aligner.root")' 'TpcAlignerDraw.C+(2)'>& TpcAlignerDraw.log &
   root.exe -q -b 'TpcAlignerDraw.C+(1,"../*Aligner.root")' 'TpcAlignerDraw.C+(3)'> & TpcAlignerDraw1.log &
   root.exe -q -b lMuDst.C 'Cosmics.C+("../*MuDst.root")' > & Cosmics.log &
 cd -
end
