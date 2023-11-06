if ($?DECHO)  echo "$0 setup ================================================================================"
#setenv IVROOT  $XOPTSTAR
setenv PATH `dropit Coin`
setenv LD_LIBRARY_PATH `dropit Coin -p $LD_LIBRARY_PATH`
if ($?IVROOT) then
setenv PATH $IVROOT/bin:$PATH
setenv LD_LIBRARY_PATH $IVROOT/lib:$LD_LIBRARY_PATH
endif
if ($?STAR_HOST_SYS_OPT) then
setenv QTROOTSYSDIR $STAR/.$STAR_HOST_SYS_OPT
else
setenv QTROOTSYSDIR $STAR/.$STAR_HOST_SYS
endif
setenv COIN_NO_CHECK_GL_ERROR 1 
setenv COIN_FULL_INDIRECT_RENDERING 1 
if ($?DECHO)  echo "$0 setup ================================================================================"
