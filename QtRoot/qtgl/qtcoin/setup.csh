setenv IVROOT  $XOPTSTAR
setenv PATH `dropit Coin`
setenv LD_LIBRARY_PATH `dropit Coin -p $LD_LIBRARY_PATH`
setenv PATH $IVROOT/bin:$PATH
setenv LD_LIBRARY_PATH $IVROOT/lib:$LD_LIBRARY_PATH
setenv QTROOTSYSDIR $STAR/.$STAR_HOST_SYS
setenv COIN_NO_CHECK_GL_ERROR 1 
setenv COIN_FULL_INDIRECT_RENDERING 1 