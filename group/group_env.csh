#!/bin/csh
#       $Id: group_env.csh,v 1.266 2022/06/22 16:16:12 jeromel Exp $
#	Purpose:	STAR group csh setup
#
# Revisions & notes
#    2001-2022  Maintained J. Lauret
#    24 Apr 01  J. Lauret  Disabled echoing in ! prompt.
#                          DO NOT MODIFY THIS !!!
#     2 Apr 01  J. Lauret  Insure path added
#     3 Mar 98  T. Wenaus  HP Jetprint added (for sol)
#    17 Feb 98  Created Y.Fisyak (BNL)
#
# Should be loaded by star_login itself loaded executed by
# our individual .login files.
#
#
if ( $?DECHO ) echo "======================================== start group_env.csh $1"
set ECHO = 1;
set FAIL = "";

setenv INTERACTIVE 0
if ( ! $?prompt) then
    # when there is not prompt, we are usually in batch
    # or captive mode. Condor tends to copy env though
    set ECHO = 0
else
    # otherwise, set this for convenience but make a few
    # more checks 
    if ( $?SSH_TTY || $?DISPLAY ) then
	setenv INTERACTIVE 1
    endif
endif
if ($?STAR == 1 && ! $?DECHO)   set ECHO = 0
if ($?SILENT == 1) set ECHO = 0

# This variable was added for the ECHOD debug mode
if ( $?self ) then
    set GRPE_pself=${self}
endif
set self="group_env"
if (! $?STAR_LEVEL ) then
  setenv STAR_LEVEL pro
endif
if ( $?DECHO && $?STAR_LEVEL ) then
    # set ECHO = 1
    if ($INTERACTIVE) echo "$self :: Receiving STAR_LEVEL ${STAR_LEVEL}"
endif

source $GROUP_DIR/unix_programs.csh

# possible path for utilities
setenv AFS       /usr/afsws


# check if AFS_RHIC is readable
set READ_AFS=`echo $AFS_RHIC | $GREP Path_Not_Found`

if ( $?DECHO) echo "$self :: READ_AFS is [$READ_AFS]"

if (! $?STAR_ROOT) then
    if ( $?DECHO) echo "$self :: checking STAR_ROOT"
    if ( "$READ_AFS" == "") then
	if ( $?DECHO) echo "$self ::  Defining STAR_ROOT as AFS based if -d checks"
	if ( -d ${AFS_RHIC}/star ) then
	    setenv STAR_ROOT ${AFS_RHIC}/star
        endif
    else
       if ( -d /usr/local/star ) then
	    # this is valid
	    if ( $?DECHO) echo "$self ::  Defining STAR_ROOT as /usr/local/star"
	    setenv STAR_ROOT /usr/local/star
       else
	    # We will fail (we know that)
	    if ($INTERACTIVE) echo "$self ::  Did not find a valid STAR_ROOT"
	    setenv STAR_ROOT /Path_Not_Found_STAR_Login_Failure
	    set FAIL="$FAIL STAR_ROOT"
       endif
    endif
endif

## Clear this out. First block STAF, second STAR
if ($?STAR_HOST_SYS) then
  if (-x ${GROUP_DIR}/dropit) then
     setenv                    PATH             `${GROUP_DIR}/dropit ${STAR_HOST_SYS} -p ${PATH}`
     setenv                    LD_LIBRARY_PATH  `${GROUP_DIR}/dropit ${STAR_HOST_SYS} -p ${LD_LIBRARY_PATH}`
     if ($?SHLIB_PATH)  setenv SHLIB_PATh       `${GROUP_DIR}/dropit ${STAR_HOST_SYS} -p ${SHLIB_PATH}`
     if ($?MAN_PATH)    setenv MAN_PATH         `${GROUP_DIR}/dropit ${STAR_HOST_SYS} -p ${MAN_PATH}`
  endif
endif
if ($?STAR) then
  if (-x ${GROUP_DIR}/dropit) then
     setenv                    PATH             `${GROUP_DIR}/dropit ${STAR} -p ${PATH}`
     setenv                    LD_LIBRARY_PATH  `${GROUP_DIR}/dropit ${STAR} -p ${LD_LIBRARY_PATH}`
     if ($?SHLIB_PATH)  setenv SHLIB_PATh       `${GROUP_DIR}/dropit ${STAR} -p ${SHLIB_PATH}`
     if ($?MAN_PATH)    setenv MAN_PATH         `${GROUP_DIR}/dropit ${STAR} -p ${MAN_PATH}`
  endif
endif
if ( $?DECHO) echo "$self :: Executing STAR_SYS"
source ${GROUP_DIR}/STAR_SYS;#  echo "STAR_HOST_SYS = ${STAR_HOST_SYS}"

# Define /opt/star (or equivalent)
    if (-r ${AFS_RHIC}/opt/star) then
      setenv OPTSTAR ${AFS_RHIC}/opt/star
    else 
      if (-r /opt/star) then 
        setenv OPTSTAR /opt/star
      endif
   endif
   setenv XOPTSTAR ${OPTSTAR}
   if (-r ${OPTSTAR}/${STAR_HOST_SYS}) then 
     setenv XOPTSTAR ${OPTSTAR}/${STAR_HOST_SYS}
   endif
#endif
# X indicates points to the AFS reference
#if ( ! $?XOPTSTAR ) then
#    if (-d ${OPTSTAR}/${STAR_HOST_SYS}) setenv XOPTSTAR ${OPTSTAR}/${STAR_HOST_SYS}
#    # keep a reference to the AFS one
#    # this -r test may fail - don't do it
#    if ( "$READ_AFS" == "" ) then
##	setenv XOPTSTAR ${AFS_RHIC}/star/packages/.DEV2/misc/opt/star/${STAR_HOST_SYS}
#	setenv XOPTSTAR $OPTSTAR #${AFS_RHIC}/opt/star
#    endif
#endif
# define but feedback later
if ( $?DECHO) echo "$self :: Defining GROUP_DIR STAR_PATH"
if ( ! $?GROUP_DIR )   setenv GROUP_DIR ${STAR_ROOT}/group     # Defined to AFS Group Dir
if ( $?STAR_PATH == 0) setenv STAR_PATH ${STAR_ROOT}/packages;


if ( $?DECHO) echo   "$self :: Value of GROUP_DIR = ${GROUP_DIR}"

# make this additional test ahead
if ( ! -r ${STAR_PATH} ) then
    set FAIL="$FAIL STAR_PATH"
endif


if ( "$FAIL" != "") then
    if ($?DECHO) echo "$self :: FAIL is [$FAIL], something is not right (checking)"

    # we can add this only now because setup may be AFS-free
    if ( "$READ_AFS" != "" ) then
	set FAIL="$FAIL AFS_RHIC"
    endif

    if ($ECHO) then
	echo ""
	echo "***************************************************************"
	echo "  ERROR Cannot find a valid Path for                           "
	echo "    $FAIL                                                      "
	echo "  STAR Login is incomplete                                     "
	echo "                                                               "

	# we can try to guess the reason but it may not be the whole story
	set failafs=0
	if ( `echo $FAIL | $GREP AFS` != "" &&  `echo $FAIL | $GREP STAR_PATH` != "") then
	    # if AFS detection failed and STAR_PATH was not defined we have no options
	    set failafs=1
	endif
	if ( `echo ${STAR_ROOT} | $GREP $AFS_RHIC` != "" &&  `echo ${STAR_PATH} | $GREP ${STAR_ROOT}` != "" && `echo $FAIL | $GREP STAR_PATH` != "") then
	    # ! -r STAR_PATH but defined as AFS resident is the second sign of failure
	    # it does seem like the above but this second test is necessary due to client
	    # file caching
	    set failafs=1
	endif

	if ( $failafs ) then
	echo "  Reason: It appears the AFS lookup has failed and             "
	else
	# any other reason, display a generic message
	echo "  Reason: Improper or incomplete installation                  "
	endif
	echo "          You do not have a local installation of the STAR     "
	echo "          software stack.                                      "
	echo "                                                               "
	echo "    If you are installing for the first time, ignore & proceed "
	echo "    with installation. Our documentation is available at       "
        echo "    http://drupal.star.bnl.gov/STAR/comp/sofi/installing       "
	echo "***************************************************************"
	echo ""
	# disable messages
	if( ! $?DECHO) set ECHO = 0
    endif
else
    if ($?DECHO && $INTERACTIVE) echo "$self :: FAIL is NULL, we are fine so far"
    if ($ECHO) then
	echo ""
	echo "         ----- STAR Group Login from $GROUP_DIR/ -----"
	echo ""
	echo "Setting up STAR_ROOT = ${STAR_ROOT}"
	echo "Setting up STAR_PATH = ${STAR_PATH}"
    endif
endif


setenv WWW_HOME http://www.star.bnl.gov/
if ($ECHO) echo   "Setting up WWW_HOME  = $WWW_HOME"


# Defined in CORE. GROUP_PATH/GROUPPATH are global
# while GROUP_DIR may be local
if ( ! $?GROUP_PATH )  setenv GROUP_PATH ${STAR_ROOT}/group

# Default value (some if not already defined)
if ($?STAR_LEVEL == 0) setenv STAR_LEVEL pro

if ( $?DECHO) echo "$self :: Setting STAR_VERSION"

setenv STAR_VERSION ${STAR_LEVEL}
#if (${STAR_LEVEL}  == "old" || ${STAR_LEVEL}  == "pro" || ${STAR_LEVEL}  == "new" || ${STAR_LEVEL}  == "dev" || ${STAR_LEVEL}  == ".dev") then
#  # i.e. replace with link value instead
#  if ( $?DECHO ) echo "$self :: Will test -r ${STAR_PATH}/${STAR_LEVEL}"
#  # exit
#
#  if( -r ${STAR_PATH}/${STAR_LEVEL}) then
#    # be carefull, it may not be "seen" as a soft link
#    # at all ... Some AFS client do not show the link.
#    # No even speaking of absolute path ...
#    if ( $?DECHO ) echo "$self :: Will ls -ld ${STAR_PATH}/${STAR_LEVEL}"
#    set a = `ls -ld ${STAR_PATH}/${STAR_LEVEL}`
#    set b = `ls -ld ${STAR_PATH}/${STAR_LEVEL} | cut -f2 -d">"`
#    if ( $?DECHO ) echo "$self :: Checked $a $b"
#    if ( "$a" != "$b") then
#	setenv STAR_VERSION $b
#    else
#	setenv STAR_VERSION ${STAR_LEVEL}
#    endif
#  endif
#endif
  if ( $?DECHO ) echo "$self :: Will test -r ${STAR_PATH}/${STAR_LEVEL}"


#if ( $?DECHO) echo "$self :: Setting STAF_VERSION"
#
#if ($?STAF_LEVEL == 0) then
# if ( -r ${STAR_PATH}/StAF/${STAR_LEVEL}) then
#    setenv STAF_LEVEL ${STAR_LEVEL}
# else
#    setenv STAF_LEVEL pro
# endif
#endif

#setenv STAF_VERSION ${STAF_LEVEL}
#if ($STAF_LEVEL  == "old" || $STAF_LEVEL  == "pro" || $STAF_LEVEL  == "new" || $STAF_LEVEL  == "dev" || $STAF_LEVEL  == ".dev") then
#  if( -r ${STAR_PATH}/StAF/${STAF_LEVEL}) then
#    set a = `ls -ld ${STAR_PATH}/StAF/${STAF_LEVEL}`
#    set b = `ls -ld ${STAR_PATH}/StAF/${STAF_LEVEL} | cut -f2 -d">"`
#    if ( "$a" != "$b") then
#	setenv STAF_VERSION $b
#    else
#	setenv STAF_VERSION ${STAF_LEVEL}
#    endif
#  endif
#endif

#+
# use alternate gcc installations
# Needs to be here because STAR_SYS will set vars based on the
# command 'gcc'
#-
if (! $?LD_LIBRARY_PATH ) setenv LD_LIBRARY_PATH ""
if ( $?OPTSTAR ) then
    if (!  $?optstar ) setenv  optstar  ${OPTSTAR}
    if (! $?xoptstar ) setenv xoptstar ${XOPTSTAR}
endif



if (! $?ROOT_VERSION) setenv ROOT_VERSION ""
# STAR
setenv STAR      ${STAR_PATH}/${STAR_VERSION}   ;   if ($ECHO) echo   "Setting up STAR      = ${STAR}"
if ($?STAR_NEW_ENVIRONMENT) then
    setenv MINE_LIB        .${STAR_HOST_SYS_OPT}/lib
    setenv MINE_BIN        .${STAR_HOST_SYS_OPT}/bin
    setenv MINE_OBJ        .${STAR_HOST_SYS_OPT}/obj
    setenv MINE_INCLUDE    .${STAR_HOST_SYS_OPT}/include
else
    setenv MINE_INCLUDE    .${STAR_HOST_SYS}/include
    if (! $?NODEBUG) then
	setenv MINE_LIB         .${STAR_HOST_SYS}/lib${ROOT_VERSION}
	setenv MINE_BIN         .${STAR_HOST_SYS}/bin${ROOT_VERSION}
	setenv MINE_OBJ         .${STAR_HOST_SYS}/obj${ROOT_VERSION}
    else
	setenv MINE_LIB         .${STAR_HOST_SYS}/LIB${ROOT_VERSION}
	setenv MINE_BIN         .${STAR_HOST_SYS}/BIN${ROOT_VERSION}
	setenv MINE_OBJ         .${STAR_HOST_SYS}/OBJ${ROOT_VERSION}
    endif
endif
setenv STAR_LIB      ${STAR}/${MINE_LIB} ;     
setenv STAR_OBJ      ${STAR}/${MINE_OBJ} ;     
setenv STAR_BIN      ${STAR}/${MINE_BIN} ;     
setenv STAR_INCLUDE  ${STAR}/${MINE_INCLUDE} ; 
setenv GARFIELD_HOME ${STAR}/garfield
setenv HEED_DATABASE ${GARFIELD_HOME}/Heed/heed++/database

if ($ECHO) echo   "Setting up STAR_LIB  = ${STAR_LIB}"
setenv G3SYS           ${STAR}/StarVMC/geant3
if( ! $?DOMAINNAME) then
  setenv DOMAINNAME `hostname -d`
endif



#
# ATTENTION - This support for $SITE need extending
# at each new site.
#
# Each Grid site should have an entry.
# Only sites having local DB rules could have an entry.
#
if ( $?SITE ) then
#echo "SITE ===> $SITE"
else
    setenv DOMAINNAME `hostname -d`
#    echo "DOMAINNAME ==> $DOMAINNAME"
    switch ($DOMAINNAME)
	case "nersc.gov":    # <--- or whatever domainame returns
	    setenv SITE "LBL"
	    breaksw

	case "rhic.bnl.gov":
	case "rcf.bnl.gov":
	case "star.bnl.gov":
	case "sdcc.bnl.gov":
	    setenv SITE "BNL"
	    breaksw

	case "starp.bnl.gov":
	    setenv SITE "BNLONL"
	    breaksw

	case "if.usp.br":
	    setenv SITE "USP"
	    breaksw

	case "cluster.phy.uic.edu":
	    setenv SITE "UIC"
	    breaksw

        case "sdfarm.kr":
            setenv SITE "KISTI"
            breaksw

	case "starp.bnl.gov":
        case "l4.bnl.local":
            setenv SITE "HLT"
            breaksw

	default:
	    # Not implemented
	    setenv SITE "generic"
	    breaksw
    endsw
endif




# db related
if ( $?SITE ) then
    #if ( ! $?DB_SERVER_LOCAL_CONFIG ) then
	if ( -r ${STAR_PATH}/conf/dbLoadBalancerLocalConfig_${SITE}.xml ) then
	    # 2008/08 new location and unique for all libraries - SL08e or above
	    setenv DB_SERVER_LOCAL_CONFIG ${STAR_PATH}/conf/dbLoadBalancerLocalConfig_${SITE}.xml
	else
	    # old method and value for backward compat - this is the part preventing
	    # from protecting against redefining. In fact, if not in the global
	    # area, we MUST redefine. File was removed from this path starting from
	    # SL10g
	    setenv DB_SERVER_LOCAL_CONFIG ${STAR}/StDb/servers/dbLoadBalancerLocalConfig_${SITE}.xml
	endif
    #endif
  if ($ECHO) echo   "Setting up DB_SERVER_LOCAL_CONFIG = ${DB_SERVER_LOCAL_CONFIG}" 
endif


if ($ECHO)    echo   "Setting up STAR_BIN  = ${STAR_BIN}"

# Common stuff
setenv STAR_SCRIPTS ${STAR_PATH}/scripts
setenv STAR_CGI  ${STAR_PATH}/cgi
setenv STAR_MGR  ${STAR}/mgr
setenv STAR_PAMS ${STAR}/pams;            if ($ECHO) echo   "Setting up STAR_PAMS = ${STAR_PAMS}"

if ( -r ${STAR_ROOT}/data ) then
setenv STAR_DATA ${STAR_ROOT}/data;     if ($ECHO) echo   "Setting up STAR_DATA = ${STAR_DATA}"
endif
if ( -r /afs/rhic.bnl.gov/star/packages/repository ) then
setenv CVSROOT   /afs/rhic.bnl.gov/star/packages/repository; if ($ECHO) echo   "Setting up CVSROOT   = ${CVSROOT}"
endif


# The block below will be enabled only if there is botha ROOT_LEVEL
# and a CERN_LEVEL file in ${STAR}/mgr/. If so, ROOT and CERN levels
# will be set to the explicit version. Otherwise, some historical
# deefault will be assumed.
if ( $?DECHO ) echo "$self :: ROOT_LEVEL and CERN_LEVEL"
if (! $?ROOT_VERSION) setenv ROOT_VERSION ""
if ( -f ${STAR}/mgr/ROOT_LEVEL${ROOT_VERSION}  && -f ${STAR}/mgr/CERN_LEVEL ) then
  setenv ROOT_LEVEL `cat ${STAR}/mgr/ROOT_LEVEL${ROOT_VERSION}`
  setenv CERN_LEVEL `cat ${STAR}/mgr/CERN_LEVEL`

  # try with post-fix
  if ( -f ${STAR}/mgr/CERN_LEVEL.${STAR_SYS} ) then
    # Overwrite
    setenv CERN_LEVEL `cat ${STAR}/mgr/CERN_LEVEL.${STAR_SYS}`
  endif
  if ( -f ${STAR}/mgr/CERN_LEVEL.${STAR_HOST_SYS} ) then
    # Overwrite
    setenv CERN_LEVEL `cat ${STAR}/mgr/CERN_LEVEL.${STAR_HOST_SYS}`
  endif

  # try with post-fix
  if ( -f ${STAR}/mgr/ROOT_LEVEL${ROOT_VERSION}.${STAR_SYS} ) then
    # Overwrite
    setenv ROOT_LEVEL `cat ${STAR}/mgr/ROOT_LEVEL.${STAR_SYS}`
  endif
  if ( -f ${STAR}/mgr/ROOT_LEVEL.${STAR_HOST_SYS} ) then
    # Overwrite
    setenv ROOT_LEVEL `cat ${STAR}/mgr/ROOT_LEVEL.${STAR_HOST_SYS}`
  endif

  # now check if CERN exists
  if ( $?CERN ) then
    if ( ! -r $CERN/$CERN_LEVEL ) then
	if ( $?DECHO) echo "$self :: Caught $CERN_LEVEL from config in ${STAR}/mgr/ but not found - reverting to pro"
	setenv CERN_LEVEL pro
    endif
  endif

else
    if ($INTERACTIVE) echo "CERN_LEVEL and ROOT_LEVEL has not been set. ABORT."
endif

if ($ECHO) echo   "Setting up ROOT_LEVEL= ${ROOT_LEVEL}"


# At this point, CERN_LEVEL should be defined but if not,
# the global setup will define it to a default
if ( $?CERN_LEVEL ) then
    source $GROUP_DIR/setup CERN ${CERN_LEVEL}
else
    source $GROUP_DIR/setup CERN
endif





if ( $?DECHO ) echo "$self :: Paths alteration for STAR_MGR, STAR_SCRIPTS STAR_CGI etc ... begins"
if ( -x ${GROUP_DIR}/dropit) then
    setenv GROUPPATH `${GROUP_DIR}/dropit -p ${GROUP_DIR} -p mgr -p ${STAR_MGR}  -p mgr/bin -p ${STAR_MGR}/bin -p ${STAR_SCRIPTS} -p ${STAR_CGI} -p ${MINE_BIN} -p ${STAR_BIN}` # -p ${STAF}/mgr -p ${STAF_BIN}`
    setenv PATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/bin -p $PATH`
    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/lib -p $LD_LIBRARY_PATH`
else
    setenv GROUPPATH ${GROUP_DIR}:mgr:${STAR_MGR}:mgr/bin:${STAR_MGR}/bin:${STAR_SCRIPTS}:${STAR_CGI}:${MINE_BIN}:${STAR_BIN} #:${STAF}/mgr:${STAF_BIN}
    setenv PATH  ${XOPTSTAR}/bin:$PATH
    setenv LD_LIBRARY_PATH ${XOPTSTAR}/lib:${LD_LIBRARY_PATH}
endif
 
# test return value of PTEST from dropit
if ( $?DECHO && $?DUMPENV ) then
    if ( -r /tmp/dropit.$USER ) then
	set tmp=`cat /tmp/dropit.$USER`
	echo "$self :: $tmp"
	unset tmp
	rm -f /tmp/dropit.$USER
	if ( -r /tmp/dropit.ENV.$USER ) then
	    echo "$self :: ENV dump now --->"
	    cat /tmp/dropit.ENV.$USER
	    rm -f /tmp/dropit.ENV.$USER
	    echo "$self :: <-- END of ENV dump"
	endif
    endif
endif


# ROOT
if ( $?DECHO ) echo "$self :: Conditional exec of rootenv.csh"
if ( -f $GROUP_DIR/rootenv.csh) then
  source $GROUP_DIR/rootenv.csh
endif

if ( $?DECHO ) echo "$self :: Re-adjusting xxPATH for OPTSTAR and STAR_PATH"
if ( $?DECHO ) echo "$self :: PATH is now $PATH"
if ( -x ${GROUP_DIR}/dropit) then
  # clean-up PATH
  setenv MANPATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/man -p ${MANPATH}`
  setenv PATH    `${GROUP_DIR}/dropit -p ${PATH} GROUPPATH`
  setenv PATH    `${GROUP_DIR}/dropit -p ${PATH} ${STAR}_PATH`
  #if ($?LD_LIBRARY_PATH == 1) setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} ${STAR_PATH}`
  setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "${LD_LIBRARY_PATH}" ${STAR_PATH}`
  if ($?SHLIB_PATH == 1)      setenv SHLIB_PATH      `${GROUP_DIR}/dropit -p ${SHLIB_PATH} ${STAR_PATH}`

  setenv PATH `${GROUP_DIR}/dropit -p ${GROUPPATH} -p /usr/afsws/bin -p /usr/afsws/etc -p ${XOPTSTAR}/bin -p /usr/sue/bin -p /usr/local/bin -p ${PATH}`
  setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/lib -p $LD_LIBRARY_PATH`
else
  if ( $?DECHO ) echo "$self ::  ${GROUP_DIR}/dropit is not -x"
endif


## Put mysql on path if available
if ( -d /usr/local/mysql/bin) then
  if ( -x ${GROUP_DIR}/dropit) setenv PATH `${GROUP_DIR}/dropit -p ${PATH} -p /usr/local/mysql/bin`
endif

if ($?MANPATH == 1) then
  ##VP   setenv MANPATH ${MANPATH}:${STAR_PATH}/man
  setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH} -p ${STAR_PATH}/man`
else
  setenv MANPATH ${STAR_PATH}/man
endif


if ( $?DECHO ) echo "$self :: OS Specific tasks. Our OS=${STAR_SYS}"
switch (${STAR_SYS})
    case "rs_aix*":
        if ( -x ${GROUP_DIR}/dropit) setenv MANPATH `${GROUP_DIR}/dropit -p {$MANPATH} -p ^/usr/share/man`
        breaksw
    case "alpha_osf32c":
	breaksw
    case "hp700_ux90":
	breaksw

    case "hp_ux102":
      if ($?SHLIB_PATH == 0) setenv SHLIB_PATH
      if ( -x ${GROUP_DIR}/dropit) setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} ${STAR_PATH}`
      if ($?MINE_lib == 1 && $?STAR_lib == 1) then
        setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${MINE_lib} -p ${MINE_LIB} -p ${STAR_lib} -p ${STAR_LIB} -p ${SHLIB_PATH}` #  -p ${STAF_LIB}
      else
	if ( -x ${GROUP_DIR}/dropit) setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${SHLIB_PATH} .${STAR_HOST_SYS}/LIB`
##VP         setenv SHLIB_PATH ${MINE_LIB}:${STAR_LIB}:${STAF_LIB}:${SHLIB_PATH}
        setenv SHLIB_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${SHLIB_PATH}` #  -p ${STAF_LIB}
      endif
      setenv LD_LIBRARY_PATH ${SHLIB_PATH}
      setenv BFARCH hp_ux102
      limit  coredumpsize 0
      breaksw


    case "sun4*":
      #  ====================
      # Sun/Solaris version 4
      #  ====================
      if ( ! $?SUNWS ) then
	if ( -r ${STAR_MGR}/sunWS ) then
	    setenv SUNWS `cat ${STAR_MGR}/sunWS`
	    if ( ! -d /opt/$SUNWS ) then
		if ($ECHO) echo "$SUNWS Workshop not found. Reverting to SUNWspro"
		setenv SUNWS "SUNWspro"
	    endif
        else
	    # default packages distribution directory
	    setenv SUNWS "SUNWspro"
	endif
      endif

      if (! $?SUNOPT) setenv SUNOPT /opt

      set WSVERS=`echo $SUNWS  | sed "s/WS//"`   # full version number
      set WSMVER=`echo $WSVERS | sed "s/\..*//"` # major version number

      if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH
      setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p /usr/openwin/lib -p /usr/dt/lib -p /usr/local/lib -p ${LD_LIBRARY_PATH}`


      # Rebuild path - Basic
      if ( -x ${GROUP_DIR}/dropit) then
	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p $SUNOPT/$SUNWS/lib -p $SUNOPT/$SUNWS/SC$WSVERS/lib -p $SUNOPT/$SUNWS/WS$WSMVER/lib`
	setenv PATH `${GROUP_DIR}/dropit -p $SUNOPT/$SUNWS/bin -p ${PATH}`
	setenv MANPATH `${GROUP_DIR}/dropit -p $SUNOPT/$SUNWS/man -p ${MANPATH}`

	setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${LD_LIBRARY_PATH}` # -p ${STAF_LIB} 
      endif

      setenv  BFARCH SunOS5
      if ("${STAR_HOST_SYS}" == "sun4x_56_CC5") setenv BFARCH SunOS5_CC5
      limit   coredump 0
      unlimit descriptors
      breaksw


    case "alpha_dux*":
      limit datasize unlimited
      limit stacksize unlimited
      breaksw

    case "*linux26":   # amd64_linux26 would be valid
    case "x8664_*":
    case "i386_*":
      #  ====================
      # make sure that afws is in the path
      if (! -d /usr/afsws/bin) setenv PATH `${GROUP_DIR}/dropit -p $PATH -p ${AFS_RHIC}/i386_redhat50/usr/afsws/bin`


      # PGI
      if ( $?redhat ) then
	# from SL5 onward, stop loading PGI automatically
        if ( -x "/usr/bin/bc") then 
	    # not tha bc may not be installed
	    set loadPGI=`echo "$redhat < 50" | /usr/bin/bc`
	    if ( $loadPGI  ) then
		if ( $?DECHO ) echo "$self :: RH/SL < 5.0 - will attempt to load PGI"

		source $GROUP_DIR/setup PGI
		if ( $?DECHO ) then
		    echo "$self :: PGI = $PGI"
		endif
	    endif
	    unset loadPGI
	endif
      endif
    case "*darwin*":
    case "x86*":


      ## This is no longer used right ??
      #if (-d /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE) then
      #  setenv KAI /usr/local/KAI/KCC.flex-3.4f-1/KCC_BASE
      #  setenv PATH `${GROUP_DIR}/dropit -p $KAI/bin -p $PATH`
      #endif

      setenv PATH  `${GROUP_DIR}/dropit -p $PATH  -p /usr/local/bin/ddd`
      if ($?LD_LIBRARY_PATH == 0) setenv LD_LIBRARY_PATH


      # Final path adjustement
      if ( -x ${GROUP_DIR}/dropit) then 
#        setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH}` # -p .${STAR_HOST_SYS}/LIB`
        setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${MINE_LIB} -p ${STAR_LIB} -p ${LD_LIBRARY_PATH}` # -p ${STAF_LIB}
      endif
      if ( $?DECHO ) echo "LD_LIBRARY_PATH = $LD_LIBRARY_PATH"
      #  cygwin tcsh has no 'limit' command embedded
      if ( `echo ${STAR_SYS} | $GREP _nt` == "") then
	limit  coredump 0
	setenv BFARCH Linux2
      endif
      breaksw


    default:
	#  ====================
        if ( $?DECHO ) echo "$self :: The OS was not recognized - entire setup was skipped"
	breaksw
endsw

if ( $?DECHO ) echo "$self :: PATH is now $PATH"

# ==================================================================
# Extra package support
# ==================================================================
if ( $?DECHO ) echo "$self :: Additional packages check"

# in case of GPFS installed from RPM, add this path
if ( -d /usr/lpp/mmfs/bin/ ) then
    set path=($path /usr/lpp/mmfs/bin/)
endif




# Support for JAVA/JDK
if ( ! $?JAVA_ROOT ) then
    # Search for a default path
    foreach p ( /usr/java /usr/lib/jvm )
	if ( -d $p ) then
	    set a = `/bin/ls $p | /usr/bin/tail -1`
	    if ( "$a" != "") then
		if ( -d $p/$a/jre ) then
		    setenv JAVA_ROOT $p/$a/jre
		else 
		    setenv JAVA_ROOT $p/$a
		endif
		break
	    endif
	endif
    end   
    if ( ! $?JAVA_ROOT ) then
	if ( -d /opt/VDT ) then
	    set a = `ls /opt/VDT | $GREP -e jdk -e j2sdk | tail -1`
	    if ( "$a" != "") then
		setenv JAVA_ROOT /opt/VDT/$a
	    endif
	endif
    endif
endif
if ( ! $?JAVA_ROOT) then 
  if ( $?CMAKE_PREFIX_PATH) then
    if ( -d $CMAKE_PREFIX_PATH ) then
      setenv JAVA_ROOT $CMAKE_PREFIX_PATH
    endif
  endif
endif
if ( $?JAVA_ROOT ) then
    if ( -d $JAVA_ROOT/ ) then
	if ( `echo $PATH | $GREP kerberos` != "") then
	    # Will need to find a better way ... java has
	    # a 'kinit'
	    set path=(/usr/kerberos/bin $JAVA_ROOT/bin $path)
	else
	    set path=($JAVA_ROOT/bin $path)
	endif
	if ( -d $JAVA_ROOT/man ) then
	    setenv MANPATH ${MANPATH}:$JAVA_ROOT/man
	endif
	#CLASSPATH anyone ??
    endif
endif


# Support for GraXML
#if ( ! $?GRAXML_HOME && -d ${STAR_PATH}/GeoM ) then
#    if ( -d ${STAR_PATH}/GeoM/${STAR_LEVEL}/GraXML ) then
#	setenv GRAXML_HOME ${STAR_PATH}/GeoM/${STAR_LEVEL}/GraXML
#    else
#	# revert to a default if exists
#	if ( -r ${STAR_PATH}/GeoM/dev/GraXML ) then
#	    setenv GRAXML_HOME ${STAR_PATH}/GeoM/dev/GraXML
#	endif
#    endif
#endif
#if ( $?GRAXML_HOME ) then
#    set path=($path $GRAXML_HOME/bin)
#endif


#
# This is forced to work if the file exists.
# Just add the package name with non-obvious paths.
# The name of teh file should be LEVELS.$envVarToSet
# The content should have 32bits= and 64bits= tags
#
set PKGS="Vc_DIR"
foreach pkg ( $PKGS )
    set FF=""
    if ( -f $STAR/mgr/LEVELS.$pkg ) then
	set FF=$STAR/mgr/LEVELS.$pkg
    endif
    if ( -f mgr/LEVELS.$pkg ) then
	set FF=mgr/LEVELS.$pkg
    endif
    if ( "$FF" != "") then
	if ( $USE_64BITS == 1 ) then
	    set prefix=64bits
	else
	    set prefix=32bits
	endif
        # verification need to be non-empty and match
	set test=`cat $FF | sed 's/#.*//' | grep $prefix`
	if ( "$test" != "" ) then
	    # we have validated the file
	    if ( $?DECHO ) echo "$self :: Loading $pkg $prefix"
	    set test=`echo $test | sed 's/.*=//'`
	    setenv $pkg $test
	endif
    else
	# If we switch library and the file is NOT there, we 
	# need to undefine
	unsetenv $pkg
    endif
end


#
#if ( $STAR_LEVEL  == "dev" || $STAR_LEVEL  == ".dev" || $STAR_LEVEL  == "adev" ) then
#    # not a very intuitive path ..
#    setenv Vc_DIR /cvmfs/star.sdcc.bnl.gov/star-spack/spack/opt/spack/linux-rhel7-x86_64/gcc-4.8.5/vc_-1.4.1-7m2zajp3rqt6usw3zlgtmfrlxbbw5yvn
#else
#    #if ( $?Vc_DIR ) then
#    #	unsetenv Vc_DIR
#    #endif
#endif 


# Support for subversion if installed in a sub-directory
# Will start with simple one location
if ( -d /usr/local/subversion ) then
    setenv SVNDIR /usr/local/subversion
    set path=($path $SVNDIR/bin )
    setenv MANPATH ${MANPATH}:$SVNDIR/man
    setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$SVNDIR/lib
endif


# Support for Qt
#    if (! $?QTDIR) then
    if ( -r "${XOPTSTAR}/qt4") then
      setenv  QTDIR ${XOPTSTAR}/qt4
    else
      if ($USE_64BITS == 1) then
        if ( -d /usr/lib64/qt4) setenv QTDIR /usr/lib64/qt4
      else
        if ( -d /usr/lib/qt4) setenv QTDIR /usr/lib/qt4
      endif
    endif
#    endif
if ( $?QTDIR ) then
    setenv MANPATH ${QTDIR}/man:${MANPATH}
    setenv LD_LIBRARY_PATH ${QTDIR}/lib:${LD_LIBRARY_PATH}
    setenv PATH ${QTDIR}/bin:${PATH}
endif
if ($?DECHO) echo "begin of setup IVROOT ================================================================================"
unsetenv IVROOT
#if ( -d $XOPTSTAR/include/Inventor ) setenv IVROOT $XOPTSTAR
if ( -r $XOPTSTAR/include/simage.h ) setenv IVROOT $XOPTSTAR
if ($?IVROOT == 0 && $?STAR && $?STAR_HOST_SYS ) then
   if ( -r ${STAR}/QtRoot/qtgl/qtcoin/setup.csh) source ${STAR}/QtRoot/qtgl/qtcoin/setup.csh 
endif
if ($?DECHO) echo "end of setup IVROOT ================================================================================"


# ==================================================================
# END
# The above setups may mess path and append without checking
# if already defined. dropit will "fix" duplicates
if ( -x ${GROUP_DIR}/dropit ) then
    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "${LD_LIBRARY_PATH}"`
    setenv PATH  `${GROUP_DIR}/dropit -p "${PATH}"`
endif
# ==================================================================


if ( $?DECHO ) then
    echo "$self :: Final touch ..."
    echo "$self :: LD_LIBRARY_PATH -> $LD_LIBRARY_PATH"
    echo "$self :: PATH            -> $PATH"
endif

# We need this aliases even during BATCH
if (-r $GROUP_DIR/group_aliases.csh) source $GROUP_DIR/group_aliases.csh

# Scratch space ... Also in star_login but defined here in case
# undefined
if ($?SCRATCH == 0) then
    setenv SCRATCH /tmp/$LOGNAME
endif


# User Scratch directory
if ( ! -d $SCRATCH ) then
    mkdir -p $SCRATCH && chmod 755 $SCRATCH
endif
if ($ECHO) echo   "Setting up SCRATCH   = $SCRATCH"


# Echo CERN level information
if ($?CERN_ROOT == 0 )setenv CERN_ROOT  $CERN/$CERN_LEVEL

if ($?CERN_ROOT == 1 ) then
    if ($ECHO) echo   "CERNLIB version "$CERN_LEVEL" has been initiated with CERN_ROOT="${CERN_ROOT}
endif

# CLHEP library support
if (! $?CLHEP_BASE_DIR ) then
    setenv CLHEP_BASE_DIR ${XOPTSTAR}
endif


# HP Jetprint
if (-x ${GROUP_DIR}/dropit ) then
if ( -d /opt/hpnp) then
  if ($ECHO) echo   "Paths set up for HP Jetprint"
  setenv MANPATH `${GROUP_DIR}/dropit -p $MANPATH -p /opt/hpnp/man`
  setenv PATH    `${GROUP_DIR}/dropit -p $PATH  -p /opt/hpnp/bin -p /opt/hpnp/admin`
endif
setenv PATH `${GROUP_DIR}/dropit -p $HOME/bin -p $HOME/bin/.${STAR_HOST_SYS} -p $PATH -p $CERN_ROOT/bin -p $CERN_ROOT/mgr .`
endif

# clean-up PATH
if ( $?DECHO ) echo "$self :: Paths cleanup ..."
#if ( -d /cern/../usr.local/lib) setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/cern/../usr.local/lib
if ( -x ${GROUP_DIR}/dropit) then
    if ("$CERN_LEVEL" != "pro") then
	setenv PATH  `${GROUP_DIR}/dropit cern`
	setenv PATH `${GROUP_DIR}/dropit -p ${PATH} -p ${CERN_ROOT}/bin`
    endif
    setenv PATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/bin -p ${PATH}`
    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${XOPTSTAR}/lib -p $LD_LIBRARY_PATH`
# Note from 2011/10 - Unofrtunately, MySQL has not been there for a while
    if ( -d ${XOPTSTAR}/lib/mysql ) then
      setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p ${LD_LIBRARY_PATH} -p ${XOPTSTAR}/lib/mysql`
    endif
    setenv LD_LIBRARY_PATH `${GROUP_DIR}/dropit -p "$LD_LIBRARY_PATH ^/usr/lib"`
    if ($USE_64BITS) then 
	setenv LD_LIBRARY_PATH  ${LD_LIBRARY_PATH}:/usr/lib64:/usr/lib64/mysql
    else                  
	setenv LD_LIBRARY_PATH  ${LD_LIBRARY_PATH}:/usr/lib:/usr/lib/mysql
    endif
    setenv MANPATH `${GROUP_DIR}/dropit -p ${MANPATH}`
    setenv PATH `${GROUP_DIR}/dropit -p ${PATH} GROUPPATH`
endif
#
# Display this message as it is likely the environment is
# screwed up if this happens.
#
if ( "$XOPTSTAR" == "") then
    if ($ECHO) then
	    echo ""
	    echo "          ########################################"
	    echo "          ########################################"
	    echo "          ##                                    ##"
	    echo "          ## /!\  XOPTSTAR is undefined  /!\     ##"
	    echo "          ##                                    ##"
	    echo "          ## NO local or AFS based installation ##"
	    echo "          ##                                    ##"
	    echo "          ## You have ONLY a PARTIALLY working  ##"
	    echo "          ## STAR environment                   ##"
	    echo "          ##                                    ##"
	    echo "          ########################################"
	    echo "          ########################################"
	    echo ""

	    # turn some echo OFF now so this message is
	    # not cluttered
	    setenv SILENT 1
    endif
endif




if ($ECHO) then
    echo "STAR setup on" `hostname` "by" `date` " has been completed"
    echo   "LD_LIBRARY_PATH = $LD_LIBRARY_PATH"
    unset ECHO
endif

# restore if previously defined
if ( $?GRPE_pself ) then
    set self=$GRPE_pself
    unset GRPE_pself
endif
#if (!?$PKG_CONFIG_PATH) setenv PKG_CONFIG_PATH
if (-r /opt/rh/httpd24/enable ) then
  setenv PATH /opt/rh/httpd24/root/usr/bin:/opt/rh/httpd24/root/usr/sbin:${PATH}
  setenv MANPATH /opt/rh/httpd24/root/usr/share/man:${MANPATH}
# setenv PKG_CONFIG_PATH /opt/rh/httpd24/root/usr/lib64/pkgconfig${PKG_CONFIG_PATH}:${PKG_CONFIG_PATH}
# setenv LIBRARY_PATH /opt/rh/httpd24/root/usr/lib64:${LIBRARY_PATH}
  setenv LD_LIBRARY_PATH /opt/rh/httpd24/root/usr/lib64:${LD_LIBRARY_PATH}
endif
#if (-r /opt/rh/rh-git218/enable) then 
#  setenv PATH /opt/rh/rh-git218/root/usr/bin:${PATH}
#  setenv MANPATH /opt/rh/rh-git218/root/usr/share/man:${MANPATH}
#  setenv PERL5LIB /opt/rh/rh-git218/root/usr/share/perl5/vendor_perl:${PERL5LIB}
#  setenv LD_LIBRARY_PATH /opt/rh/httpd24/root/usr/lib64:${LD_LIBRARY_PATH}
#endif
if (-r ${HOME}/bin)                   setenv PATH ${HOME}/bin:${PATH}
if (-r ${HOME}/bin/.${STAR_HOST_SYS}) setenv PATH ${HOME}/bin/.${STAR_HOST_SYS}:${PATH}
if (-r ${STAR}/scripts/RCF)           setenv PATH ${PATH}:${STAR}/scripts/RCF
if (-r ${STAR}/bin)                   setenv PATH ${PATH}:${STAR}/bin
if (-x ${GROUP_DIR}/dropit)           setenv PATH `${GROUP_DIR}/dropit`
setenv ROOT_INCLUDE_PATH "${ROOTSYS}/include:.:./StRoot:./.${STAR_HOST_SYS}/include:${STAR}:${STAR}/StRoot:${STAR}/.${STAR_HOST_SYS}/include"
#:$STAR/StRoot/StStarLogger:$STAR/StRoot/StEmcRawMake"
#setenv ROOT_INCLUDE_PATH "${ROOT_INCLUDE_PATH};$STAR/StRoot/StEmcUtil/database:$STAR/StRoot/StEmcUtil/filters:$STAR/StRoot/StEmcUtil/geometry:$STAR/StRoot/StEmcUtil/others:$STAR/StRoot/StEmcUtil/projection:$STAR/StRoot/StEmcUtil/voltageCalib"
#setenv ROOT_INCLUDE_PATH "${ROOT_INCLUDE_PATH}:$STAR/StRoot/StEEmcUtil/EEevent:$STAR/StRoot/StEEmcUtil/database:$STAR/StRoot/StEEmcUtil/EEevent:$STAR/StRoot/StEEmcUtil/EEfeeRaw:$STAR/StRoot/StEEmcUtil/EEmcGeom:$STAR/StRoot/StEEmcUtil/EEmcMC"
#setenv ROOT_INCLUDE_PATH "${ROOT_INCLUDE_PATH}:$STAR/StRoot/StEEmcUtil/EEmcSmdMap:$STAR/StRoot/StEEmcUtil/StEEmcSmd"
#setenv ROOT_INCLUDE_PATH "${ROOT_INCLUDE_PATH}:$STAR/StRoot/StMuDSTMaker/COMMON"

#
# Uncomment to get statistics on version used at
# login level.
#
#set date="`date`"
#cat >> $GROUP_DIR/statistics/star${STAR_VERSION} <<\lndir $ROO EOD
#$USER from $HOST asked for STAR_LEVEL=${STAR_LEVEL} / STAR_VERSION=${STAR_VERSION}  $date
#EOD
#END
#if (-x $GROUP_DIR/dropit ) then
#	setenv PATH            `$GROUP_DIR/dropit $STAR_HOST_SYS /opt/star`
#        setenv LD_LIBRARY_PATH `$GROUP_DIR/dropit -p $LD_LIBRARY_PATH -p /usr/lib`
#endif


#echo "${STAR}"
#echo "$LD_LIBRARY_PATH"
which xtitl >& /dev/null
if (! $?) xtitl
if ( $?DECHO ) echo "======================================== end group_env.csh $1"
