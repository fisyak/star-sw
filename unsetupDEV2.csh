unsetenv AFS*
unsetenv BFARCH
unsetenv CERN*
unsetenv cf
unsetenv CINTSYSDIR
unsetenv CLHEP_BASE_DIR
unsetenv COIN*
unsetenv DB_SERVER_LOCAL_CONFIG
unsetenv DOMAINNAME
unsetenv EDITOR
unsetenv G3SYS
unsetenv GARFIELD_HOME
unsetenv GROUP_DIR GROUPPATH GROUP_PATH
unsetenv HEED_DATABASE
unsetenv JAVA_ROOT
unsetenv KRB5CCNAME
unsetenv LD_LIBRARY_PATH
unsetenv MANPATH
unsetenv MINE_*
unsetenv NODEBUG* old* opt* OPT*
unsetenv PERL5LIB
unsetenv PYTHONPATH
unsetenv QT*
unsetenv ROOT*
unsetenv SCRATCH
unsetenv SILENT SITE
unsetenv *STAR*
unsetenv SystemName
unsetenv TMVASYS
unsetenv USE_*
unsetenv WWW_HOME
unsetenv xoptstar XOPTSTAR xSTARCMPL
if (-r /afs/rhic.bnl.gov/star/group) then
  setenv GROUP_DIR /afs/rhic.bnl.gov/star/group
else
  if (-r /star/nfs4/AFS/star/group) then
    setenv GROUP_DIR /star/nfs4/AFS/star/group
    setenv USE_NFS4 1
  endif
endif
source $GROUP_DIR/star_cshrc.csh
unset noclobber
setup 64bits
source $GROUP_DIR/star_cshrc.csh
unset  noclobber
setup  64bits
setenv NODEBUG yes
source ${GROUP_DIR}/.starver dev
