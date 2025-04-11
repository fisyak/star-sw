#! /bin/tcsh -f
#  gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m -r900 -GraphicsAlphaBits=4 -sOutputFile=${b}.png ${b}.ps
foreach f (`ls -1d *.ps`)
  set b = `basename ${f} .ps`;
  ls -ltr ${b}* | tail -1 | grep png 
  if (! $?) continue;
  gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m -r900 -sOutputFile=${b}.png ${b}.ps
end
