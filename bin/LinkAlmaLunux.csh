foreach d (_x8664_gcc11 _x8664_gcc11_opt _x8664_gcc11_opt_R6 _x8664_gcc11_R6)
  foreach v (al92 al95 al96 al97) 
     ln -s .al98${d} .${v}${d}
  end
end
