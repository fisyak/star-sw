unsetenv  TFG_STAR
setenv MANPATH `dropit subsys -p $MANPATH`
setenv LD_LIBRARY_PATH `dropit subsys -p $LD_LIBRARY_PATH`
setenv GROUPPATH `dropit subsys -p $GROUPPATH`
setenv PYTHONPATH `dropit subsys -p $PYTHONPATH`
setenv PATH `dropit subsys`
setenv AFS_RHIC /afs/rhic.bnl.gov
setenv STAR_BASE_PATH
unsetenv CINTSYSDIR
unsetenv CLHEP_BASE_DIR
unsetenv DB_SERVER_LOCAL_CONFIG
unsetenv GARFIELD_HOME
#unsetenv GROUP_DIR
#unsetenv GROUP_PATH
unsetenv GROUPPATH
unsetenv HEED_DATABASE
unsetenv IVROOT
unsetenv LD_LIBRARY_PATH
unsetenv MANPATH
unsetenv OPTSTAR
unsetenv PATH
unsetenv PROD_LOG
unsetenv PYTHONPATH
unsetenv QTDIR
unsetenv ROOTROOT
unsetenv ROOT
unsetenv ROOTSYS
unsetenv STAF_BIN
unsetenv STAF_LIB
unsetenv STAF
unsetenv STAR_BIN
unsetenv STAR_CGI
unsetenv STAR_LIB
unsetenv STARL
unsetenv STAR_MGR
unsetenv STAR_OBJ
unsetenv STAR_PAMS
unsetenv STAR_PATH
unsetenv STAR_ROOT
unsetenv STAR_SCRIPTS
#setenv optstar /afs/rhic.bnl.gov/opt/star
#setenv xoptstar $optstar
#setenv OPTSTAR /afs/rhic.bnl.gov/opt/star
#setenv XOPTSTAR $OPTSTAR
unsetenv optstar
unsetenv xoptstar
unsetenv OPTSTAR
unsetenv XOPTSTAR
setenv STAR /afs/rhic.bnl.gov/star/packages/dev
unsetenv TMVASYS
unsetenv XOPTSTAR
source /afs/rhic.bnl.gov/star/group/templates/cshrc
source /afs/rhic.bnl.gov/star/group/templates/login
starver dev
setup gcc
if ($?QTDIR) then 
  setenv LD_LIBRARY_PATH ${QTDIR}/lib:${LD_LIBRARY_PATH}
  setenv PATH ${QTDIR}/bin:${PATH}
endif
