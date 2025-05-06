setenv NODEBUG yes
setenv USE_64BITS 1 
setenv TFG_STAR 1
if ($?PERL5LIB == 0) setenv PERL5LIB
setenv PERL5LIB ${PERL5LIB}:${HOME}/bin/lib:/usr/share/perl5/usr/share/perl5/vendor_perl;
if ( -r $HOME/star/group/setup_AFS_RHIC) source $HOME/star/group/setup_AFS_RHIC afs
if (-d /opt/rh/devtoolset-6/root/usr/bin) source $GROUP_DIR/setup gcc631
if (-r $STAR_PATH/TFG) then
  setenv STAR_LEVEL TFG
endif
#setenv PATH ${PATH}:${GROUP_DIR}  
source ${GROUP_DIR}/STAR_SYS
if ($?ROOT_LEVEL == 0) setenv ROOT_LEVEL 5.99.99
if ($?CERN && $?CERN_ROOT == 0)  setenv CERN_ROOT $CERN/pro
if ($?GROUP_DIR == 0)  then                                     
            echo "GROUP_DIR is not defined"                    
endif        
source $GROUP_DIR/group_env.csh
if ($?PERL5LIB == 0) setenv PERL5LIB
setenv PERL5LIB ${PERL5LIB}:${HOME}/bin/lib:/usr/share/perl5/usr/share/perl5/vendor_perl;#:/usr/share/perl5/vendor_perl/TAP/Harness/ #/afs/rhic.bnl.gov/star/packages/.DEV2/.misc
setenv PATH ${PATH}:${GROUP_DIR}                                                    
if (-r $GROUP_DIR/group_aliases.csh) source $GROUP_DIR/group_aliases.csh
if (-r $HOME/.aliases) source $HOME/.aliases
if ($?CERNLIB == 0) setenv CERNLIB ${CERN_ROOT}/lib
if ($?OBJY_HOME)  unsetenv OBJY_HOME
#setenv CLASSPATH "/usr/local/Aglets1.1b2/lib/aglets.jar:/usr/local/Aglets1.1b2/public:/usr/java1.1/mm.mysql.jdbc-1.2b"
setenv ROOTBUILD debug
if (-e ${GROUP_DIR}/dropit) setenv PATH `${GROUP_DIR}/dropit`
#echo "8 => $PATH"
setenv PATH ".:$HOME/bin:$HOME/bin/BIN:$PATH"
#setenv PRINT_CMD lpr
#setenv PATH  ${PATH}:/usr/toolworks/totalview/bin:/usr/java/j2sdk1.4.0/bin

limit coredumpsize 0
setenv SystemName "Unknown"
#echo "8 => $PATH"
#if (-d $HOME/bin/$SystemName) then
#    setenv PATH "$HOME/bin/$SystemName/bin:$PATH"
#    setenv LD_LIBRARY_PATH "$HOME/bin/$SystemName/lib:$LD_LIBRARY_PATH"
#endif
#echo "9 => $PATH"
setenv MANPATH ${MANPATH}:/usr/toolworks/totalview.6.2.0-3:/usr/share/man
setenv PATH mgr:${PATH}
setenv PATH ${GROUP_DIR}:${PATH}
if (-x ${GROUP_DIR}/dropit) setenv PATH `${GROUP_DIR}/dropit`
if ($?IVROOT == 0 && $?STAR) then
   if (-r $STAR/QtRoot/qtgl/qtcoin/setup.csh) source $STAR/QtRoot/qtgl/qtcoin/setup.csh 
endif
#if ($STAR_HOST_SYS == 'sl44_icc91') source $STAR/QtRoot/scripts/qt4/setupQt4.csh
#echo "10 => $PATH"
setenv ROOTFONTFACTOR 0.9
if (-r ~/bin/setPath.csh) source ~/bin/setPath.csh
setenv PATH ~/bin/.${STAR_HOST_SYS}:~/bin:${PATH}
# Garfield
#if ($?GARFIELD_ROOT == 0) then 
#  if ("$STAR_HOST_SYS" == "x86_darwin_100") then
#    setenv GARFIELD_ROOT /Users/fisyak/Public/sources/Garfield
#  else
#    setenv GARFIELD_ROOT /star/institutions/bnl/fisyak/Garfield
#  endif
#  setenv PATH `dropit Garfiled -p ${PATH} -p ${GARFIELD_ROOT}/.${STAR_HOST_SYS}/bin`
#  setenv LD_LIBRARY_PATH `dropit -p ${LD_LIBRARY_PATH} -p ${GARFIELD_ROOT}/.${STAR_HOST_SYS}/lib`
#  setenv MANPATH ${MANPATH}:${GARFIELD_ROOT}/man
#endif
#setenv GARFIELD_HOME $STAR/garfield
#setenv HEED_DATABASE ${GARFIELD_HOME}/Heed/heed++/database
#setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${GARFIELD_HOME}/.${STAR_HOST_SYS}/Library
#starver $STAR_LEVEL
# setup afs
if ($?CVSROOT) setenv CVSROOT /afs/rhic.bnl.gov/star/packages/repository
#setenv PATH_SAVE ${PATH}
#setenv LD_LIBRARY_PATH_SAVE ${LD_LIBRARY_PATH}
setenv PATH ${PATH}:${STAR}/scripts/RCF
#if (-d /opt/git/2.1.4/bin) setenv PATH /opt/git/2.1.4/bin:${PATH}
if (-d /opt/rh/rh-git29/root/usr/bin) setenv PATH /opt/rh/rh-git29/root/usr/bin:${PATH}
if (-d /opt/rh/httpd24/root/usr/lib64) setenv LD_LIBRARY_PATH /opt/rh/httpd24/root/usr/lib64:${LD_LIBRARY_PATH}
#if (-d  /net/l402/data/fisyak/STAR/SPACK/spack) then
#    setenv SPACK_ROOT  /net/l402/data/fisyak/STAR/SPACK/spack
#    source $SPACK_ROOT/share/spack/setup-env.csh
#endif
if (-d /opt/git/2.1.4/bin) setenv PATH /opt/git/2.1.4/bin:${PATH}
# unsetenv DB_SERVER_LOCAL_CONFIG
if (! -r ${AFS_RHIC}) setenv AFC_RHIC ${HOME}
#if (-r ${STAR_ROOT}/group.local) setenv  GROUP_DIR ${STAR_ROOT}/group.local
#if ( -e  /home/users/startup/pdsf.cshrc )  source  /home/users/startup/pdsf.cshrc
if ( $?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH
if ( $?PERL5LIB == 0)        setenv PERL5LIB 
if (  $?MANPATH == 0)        setenv MANPATH
if ($?COLORS == 1) unset COLORS
set hn = `hostname`;
switch ($hn) 
  case "rftpexp*":
    setenv SILENT 1
  breaksw
  default:  
    setenv SILENT 0
   breaksw
endsw
#echo "4 => $PATH"
