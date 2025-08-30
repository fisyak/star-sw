#
# This file is used for local setups / env defines
# which needs to be done prior to executing the
# group_env script
#
# Developpers can still re-define XROOTDSYS in their cshrc
# to switch to a beta version for testing purposes.
#

# This should not happen
if( ! $?AFS_RHIC)   setenv AFS_RHIC  /afs/rhic.bnl.gov
### TODO: once we get rid of AFS, this path could change

# Switch to CVMFS if defined
if ( ! $?STAR_BASE_PATH ) setenv STAR_BASE_PATH ""

# to ease integration, we can do one more step - if nothing
# is defined as USE_, define it as USE_NFS4
if ( ! $?USE_CVMFS && ! $?USE_AFS ) then
    # setenv USE_NFS4 1
endif


if ( $?USE_NFS4 ) then
    if ( -d "/star/nfs4/AFS/star" ) then
	setenv STAR_BASE_PATH /star/nfs4/AFS/star
    endif

else if ( $?USE_CVMFS ) then
    if ( -d "/cvmfs/star.sdcc.bnl.gov") then
	setenv STARCVMFS /cvmfs/star.sdcc.bnl.gov
	setenv STAR_BASE_PATH ${STARCVMFS}

	# Assume Linux only? but this logic is in STAR_SYS
	source ${GROUP_DIR}/STAR_SYS
	if ( $?DECHO ) echo "$self :: setting STAR_SYS to ${STAR_SYS}"
    else
	unsetenv USE_CVMFS
	# this is an issue so we should display a message
	#if ( $?ECHO ) then
	    echo " ******************************************************"
	    echo " *** CVMFS on but /cvmfs/star.sdcc.bnl.gov not seen ***"
	    echo " ***     Falling back to AFS based installation     ***"
	    echo " ******************************************************"	
	#endif
    endif
else
    # itroduced but not used
    setenv USE_AFS 1
endif



# Define DOMAINNAME if does not exists
if( ! $?DOMAINNAME) then
    if ( -x "domainname" ) then
       setenv DOMAINNAME `domainname`
    else
       # Be aware that NIS/YP could be disabled 
       setenv DOMAINNAME "(none)"
    endif
    if ( "$DOMAINNAME" == "(none)") then 
       setenv DOMAINNAME `hostname | sed 's/^[^\.]*\.//'`
    endif
endif



switch ($DOMAINNAME)
   # BNL
   case "rhic.bnl.gov":
   case "rcf.bnl.gov":
   case "usatlas.bnl.gov":
    # This detects everything
    if ( ! $?XROOTDSYS ) then
	# in AFS land?
	# Needs some attention for CVMFS
	if ( $STAR_BASE_PATH != "" && ! $?USE_CVMFS ) then
	    set xrootd=${STAR_BASE_PATH}/star/ROOT/Xrootd/prod
	else
	    set xrootd=${AFS_RHIC}/star/ROOT/Xrootd/prod
	endif

	if ( -d $xrootd ) then
	    setenv XROOTDSYS $xrootd
	endif
    endif

    # We have it valid for Linux only
    # Needs some attention for CVMFS
    if ( $STAR_BASE_PATH != "" && ! $?USE_CVMFS ) then
	set PP=${STAR_BASE_PATH}/Grid/OSG/WNC
    else
	set PP=${AFS_RHIC}/star/Grid/OSG/WNC
    endif
    if ( -d $PP ) then
	if ( `uname` == "Linux") then
	    setenv WNOSG $PP
	endif
    endif

    # users coming with this defined would mess perl up (RT  #2307)
    if ( $?LC_CTYPE ) then
    	unsetenv LC_CTYPE
    endif
    breaksw



  default:
    # DO NOTHING
endsw     




if ($?TFG_STAR == 0) then 
# Experimental
# scl is a command on Sl7, a script wrapper on A9/RH8 
# installed as  /etc/scl/func_scl.csh and is NOT executable
if ( -e "/etc/scl/func_scl.csh" ) then
    set SCLCMD="source /etc/scl/func_scl.csh list-collections"
else
    if ( -x "/usr/bin/scl" ) then
	set SCLCMD="/usr/bin/scl -l"
    else
	set SCLCMD=""
    endif
endif


# if ( "$SCLCMD" != "" ) then
#     set dts=`$SCLCMD | /usr/bin/tail -1`
#     if ( "$dts" != "") then
# 	set test=`echo $PATH | grep $dts`
# 	if ( "$test" == "") then
# 	    if ( -d /opt/rh/$dts/root/usr ) then
# 		if ( $?DECHO ) then
# 		    echo "$self :: Devtoolset version $dts is available"
# 		endif
# 		# ---> that's one possibility but requires more massage
# 		#      PATH wise
# 		#/usr/bin/scl enable $dts '/bin/tcsh -l'
# 		#logout
# 		#<--- 
# 		#if ( ! $?USE_GCC_DIR ) then
# 		#    if ( $?DECHO ) echo "$self :: setting GCC DIR to $dts"
# 		#    setenv USE_GCC_DIR /opt/rh/$dts/root/usr 
# 		#endif
# 	    endif
# 	endif
#     else
# 	if ( $?DECHO ) echo "We are using devtoolset $dts"
#     endif
# endif
# endif
