#! /usr/bin/env tcsh 
#setenv STAR  STAR
setenv TABLE  TABLE
if (! $?NODEBUG) then
    set ROOTBUILD="debug"
else
    set ROOTBUILD="opt"
endif
set PYTHIA6=""
if (-r $STAR_LIB/libPythia6.so) then
 set  PYTHIA6 =  $STAR_LIB
else if (-r $XOPTSTAR/lib/libPythia6.so) then
 set PYTHIA6 =  $XOPTSTAR/lib
else if (-r ${XOPTSTAR}/spack/lib/libPythia6.so) then
 set PYTHIA6 = ${XOPTSTAR}/spack/lib
endif
setenv DISABLE ""
setenv ENABLE ""
if ($PYTHIA6 != "") then
    setenv ENABLE "--with-pythia6-libdir=$PYTHIA6"
endif
unset PYTHIA6
if (-r ./bin/setxrd.csh && -d $XOPTSTAR/spack) source ./bin/setxrd.csh  $XOPTSTAR/spack
setenv CERN_ROOT_Local $CERN_ROOT
setenv SHIFTLIB "" #"-lshift"
setenv SHIFTLIBDIR ""#$CERN/../usr.local/lib
setenv SHIFTINCDIR ""#$CERN_ROOT/../../usr.local/include/shift
setenv x11libdir /usr/X11R6/lib
setenv xpmlibdir /usr/X11R6/lib
setenv xftlibdir /usr/X11R6/lib
setenv DISABLE "$DISABLE --disable-python --disable-qt --disable-qtgsi --disable-vc --disable-pythia8 --disable-xrootd"
setenv MYSQLINCDIR /usr/include/mysql
if ($USE_64BITS == 0) then
    setenv MYSQLLIBDIR /usr/lib
else 
    setenv MYSQLLIBDIR /usr/lib64
endif
if (-r $XOPTSTAR/spack/include/mysql) then
        setenv MYSQLINCDIR $XOPTSTAR/spack/include/mysql
        setenv MYSQLLIBDIR $XOPTSTAR/spack/lib
endif

#setenv GSL_DIR $ROOTSYS
setenv GSL_DIR $XOPTSTAR # $ROOTSYS
if (-r ${XOPTSTAR}/spack/include/gsl) then 
  setenv GSL_DIR ${XOPTSTAR}/spack/
endif
setenv FFTW3   $ROOTSYS # $XOPTSTAR 
setenv F77 gfortran
switch ( $STAR_HOST_SYS )  
    case *x8664*gcc*:
	setenv ARCH linuxx8664gcc
	setenv x11libdir /usr/lib64
	setenv xpmlibdir /usr/lib64
	setenv xftlibdir /usr/lib64
	if (-r $XOPTSTAR/spack/lib/libX11.so) then
          setenv x11libdir $XOPTSTAR/spack/lib
          setenv ENABLE "$ENABLE --with-x11-libdir=$XOPTSTAR/spack/lib"
          setenv ENABLE "$ENABLE --with-finkdir=$XOPTSTAR/spack --with-x11-libdir=$XOPTSTAR/spack/lib"
   	endif
	if (-r $XOPTSTAR/spack/lib/libXpm.so) then
          setenv xpmlibdir $XOPTSTAR/spack/lib
          setenv ENABLE "$ENABLE --with-xpm-incdir=$XOPTSTAR/spack/include --with-xpm-libdir=$XOPTSTAR/spack/lib"
   	endif
	if (-r $XOPTSTAR/spack/lib/libXft.so) then
          setenv xftlibdir $XOPTSTAR/spack/lib
          setenv ENABLE "$ENABLE --with-xft-libdir=$XOPTSTAR/spack/lib"
   	endif
	if (-r $XOPTSTAR/spacklib64/libGLEW.so) then
	  setenv glewincdir  $XOPTSTAR/spack/include/GL
          setenv glewlibdir $XOPTSTAR/spack/lib64
          setenv ENABLE "$ENABLE --with-glew-incdir=$XOPTSTAR/spack/include/GL --with-xglew-libdir=$XOPTSTAR/spack/lib64"
   	endif
    breaksw
    case *x8664*icc*:
	setenv ARCH linuxx8664icc
	setenv x11libdir /usr/lib64
	setenv xpmlibdir /usr/lib64
	setenv xftlibdir /usr/lib64
	setenv F77 ifort
	setenv DISABLE "$DISABLE --disable-vc --enable-cxx14"
    breaksw
    case i386*:
    case rh*gcc*:
    case sl5*gcc*:
    case sl6*gcc*:
    case sl7*gcc*:
	setenv ARCH  linux
	setenv x11libdir /usr/lib
	setenv xpmlibdir /usr/lib
	setenv xftlibdir /usr/lib
    breaksw
    case sl*gcc*:
	setenv ARCH  linux
    breaksw
    case sl*icc*:
    case rh*icc*:
	setenv ARCH  linuxicc
	setenv F77 ifort
	setenv x11libdir /usr/lib
	setenv xpmlibdir /usr/lib
	setenv xftlibdir /usr/lib
	setenv DISABLE "$DISABLE --disable-vc --enable-cxx14"
    breaksw
    case alpha_dux*:
	setenv ARCH  alphacxx6
	setenv XPM $XOPTSTAR
    breaksw
    case sun4x_5*:
	setenv ARCH solarisCC5
    breaksw
    case hp_ux102:
	setenv ARCH hpuxacc
	setenv XPM $ROOTSYS/lib
    breaksw
    case *darwin*:
	setenv ARCH macosx64
 	setenv MYSQLINCDIR /sw/include/mysql
	setenv MYSQLCLILIB /sw/lib
	setenv GSLDIR /sw
    breaksw
    case *x8664*:
	setenv ARCH linuxx8664gcc
	setenv SHIFTLIBDIR $CERN_ROOT/lib
	setenv SHIFTINCDIR  /afs/rhic.bnl.gov/.asis/share/usr.local/include
	setenv x11libdir /usr/X11R6/lib64
	setenv xpmlibdir /usr/X11R6/lib64
	setenv xftlibdir /usr/X11R6/lib64
    breaksw
    default:
     exit 1
endsw
    setenv ENABLE_CXX11 ""
    setenv EXTRA_FLAGS " --cflags=-fdiagnostics-color=always --cxxflags=-fdiagnostics-color=always"
switch ( $STAR_HOST_SYS )  
    case *AVX*:
	setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=-mavx";
	breaksw
    default:
	setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=-msse4.2";
        breaksw
endsw
     echo "STAR_HOST_SYS = $STAR_HOST_SYS"
switch ( $STAR_HOST_SYS )  
    case *al9*_x8664_*:
     setenv DISABLE "$DISABLE --disable-memstat"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-cast-function-type  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-class-memaccess  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-deprecated-declarations  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-ignored-qualifiers  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-implicit-fallthrough  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-misleading-indentation  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-stringop-truncation "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-register  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=-Wno-cast-function-type  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=-Wno-format-truncation  "
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=-Wno-misleading-indentation  "
    breaksw
    case *gcc12*:
     setenv DISABLE "$DISABLE --disable-python --disable-xrootdxs --disable-pythia8"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS" # --cflags=--std=c++17 --cxxflags=-Wno-register"
     breaksw
    case *gcc1*:
     setenv DISABLE "$DISABLE --disable-xrootd --disable-pythia8"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-Wno-ignored-qualifiers" # --cflags=--std=c++17 --cxxflags=-Wno-register"
     breaksw
    case *gcc9*:
    case *gcc8*:
    case *gcc7*:
     setenv ENABLE_CXX11 "--enable-cxx17"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS" # --cflags=--std=c++17"
     breaksw 
     case *gcc631:
     echo "STAR_HOST_SYS = $STAR_HOST_SYS"
     setenv DISABLE "$DISABLE --disable-xrootd --disable-pythia8"
     breaksw
     case *_x8664_gcc6*:
     setenv ENABLE_CXX11 "--enable-cxx11"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++14"
     breaksw
    case *gcc6*:
     breaksw
    case *gcc6*:
     setenv ENABLE_CXX11 "--enable-cxx11"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++14"
     breaksw
    case *_x8664_gcc5*:
    case *_x8664_gcc492*:
     setenv ENABLE_CXX11 "--enable-cxx11"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++14"
     breaksw
    case *gcc492*:
     setenv ENABLE_CXX11 "--enable-cxx11"
    case *gcc5*:
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++14"
     breaksw
    case *_x8664_gcc48*:
     setenv ENABLE_CXX11 "--enable-cxx11"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++11"
     breaksw
    case *gcc48*:
     setenv ENABLE_CXX11 "--enable-cxx11"
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cflags=--std=c++11"
     breaksw
     case *gcc447*:
     setenv ENABLE_CXX11 ""
     setenv EXTRA_FLAGS ""
     setenv DISABLE "$DISABLE --disable-python --disable-qt --disable-qtgsi --enable-vc"
     breaksw	
     case *x8664*icc*:
     case *icc*:
     setenv EXTRA_FLAGS " $EXTRA_FLAGS --cxxflags=-axAVX  --cflags=-axAVX" # May generate AVX,SSE4.2, SSE4.1, SSSE3, SSE3, SSE2, and SSE 
     breaksw
    case *darwin*:
      setenv ENABLE_CXX11 "--enable-cxx11"
      setenv EXTRA_FLAGS  "--cflags=-fcolor-diagnostics --cxxflags=-fcolor-diagnostics"
    breaksw
    default:
#     exit 1
    setenv EXTRA_FLAGS " --cflags=-std=c++0x"
 endsw  
echo "EXTRA_FLAGS = $EXTRA_FLAGS"
echo "DISABLE = $DISABLE"
./configure $ARCH \
    --build=$ROOTBUILD \
    --enable-builtin_ftgl       \
    --enable-builtin_freetype   \
    --enable-builtin_glew       \
    --enable-builtin_pcre       \
    --enable-builtin_zlib       \
    --enable-builtin_lzma       \
    --with-gsl-incdir=$GSL_DIR/include \
    --with-gsl-libdir=$GSL_DIR/lib \
    --with-mysql-incdir=$MYSQLINCDIR --with-mysql-libdir=$MYSQLLIBDIR \
    --with-fftw3-incdir=$XOPTSTAR/include --with-fftw3-libdir=$XOPTSTAR/lib \
    --with-f77=$F77 \
    --all \
    $DISABLE \
    $ENABLE \
    $ENABLE_CXX11 $EXTRA_FLAGS
#    --with-pythia6-libdir=$XOPTSTAR/lib 
#    --enable-opengl 
#    --with-xrootd=$XOPTSTAR 
#    --with-pythia8-libdir=$XOPTSTAR/lib 
#    --with-pythia8-incdir=$XOPTSTAR/include 
#unsetenv libdir 
#unsetenv macrodir
#unsetenv plugindir
#    --enable-builtin_afterimage 
#    --enable-builtin_lz4        
#__END__
#mkdir $ROOTSYS
#cd $ROOTSYS
#mkdir Build
#cd Build
#lndir $ROOTROOT/root .
##setenv ROOTSYS ..
#setupROOT.csh
