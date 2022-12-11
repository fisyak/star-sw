#!/bin/tcsh -f
#/star/u/kehw/hlt/vc.build/build.csh

#icc -v

# cd ../Vc
# git pull
# cd -

#cd ./build
if (! -d Vc) mkdir Vc
cd Vc
rm -rf ./*
if (! $?NODEBUG) then
    set ROOTBUILD="debug"
else
    set ROOTBUILD="opt"
endif
setenv LDFLAGS -m32
setenv VC_ROOT ../../Vc/
switch ( $STAR_HOST_SYS )  
#    case *x8664_gcc7*:
#	setenv VC_ROOT ../../Vc.1.3.3
    case *x8664*: 
	setenv LDFLAGS -m64
    breaksw
    default:
    breaksw
endsw 
#    -DCMAKE_C_COMPILER=`root-config --cc`                      \
#    -DCMAKE_CXX_COMPILER=`root-config --cxx`                  \
#    -DCMAKE_CXX_FLAGS=$LDFLAGS \
which cmake
#set cflags = `root-config --cflags | sed -e 's/ -I.*//' -e 's/ -mss.*//'`;
set cflags = `root-config --ldflags`
set cxxflags = `root-config --ldflags`
cmake -L                                        \
    -DCMAKE_INSTALL_PREFIX=$XOPTSTAR    \
    -DCMAKE_BUILD_TYPE=$ROOTBUILD           \
    -DBUILD_TESTING=OFF                          \
    -DCMAKE_C_COMPILER_FORCED=OFF \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_C_FLAGS=\'${cflags}\' \
    -DCMAKE_C_FLAGS=${LDFLAGS} \
    -DCMAKE_CXX_FLAGS=${LDFLAGS} \
    ${VC_ROOT}
#    -DCMAKE_C_FLAGS=\'`root-config --cflags | sed -e 's/ -I.*//'`\' \
#    -DCMAKE_CXX_FLAGS=\'`root-config --ldflags`\' \
#    -DCMAKE_CXX_FLAGS=\"${cxxflags}\" \
#    -DCMAKE_C_FLAGS=`root-config --auxcflags` \
#    -DCMAKE_CXX_FLAGS=`root-config --auxcflags` \

make -j 10 install
touch ../Vc.Done
# make -j test
# make install
