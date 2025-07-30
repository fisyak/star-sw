unsetenv  TFG_STAR
setenv STAR_LEVEL dev; 
#source $GROUP_DIR/setup_AFS_RHIC nfs4
setenv GROUP_DIR /afs/rhic.bnl.gov/star/group
source $GROUP_DIR/star_cshrc.csh
unset noclobber
setup 64bits
