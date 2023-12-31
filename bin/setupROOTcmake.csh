#! /usr/bin/env tcsh 
if (! $?NODEBUG) then
    set ROOT_BUILD="Debug"
else
    set ROOT_BUILD="Release"
endif
echo "ROOT_BUILD = $ROOT_BUILD"
# -Dafs=ON 
#cmake cmake ${ROOT}/${ROOT_LEVEL}/root -DCMAKE_INSTALL_PREFIX=${ROOTSYS} -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_LINKER=clang++ -Dall=ON -Dcxx11=ON -Dlibcxx=ON -Dcacoa=ON -Dgdml=ON -Dgsl_shared=ON -Dminuit2=ON -Dqt=ON -Drootfit=ON -Dtable=ON -Dvc=ON 
#cmake cmake ${ROOT}/${ROOT_LEVEL}/root -DCMAKE_INSTALL_PREFIX=${ROOTSYS} -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_LINKER=g++ -Dall=ON -Dcxx11=ON -Dlibcxx=ON -Dcacoa=ON -Dgdml=ON -Dgsl_shared=ON -Dminuit2=ON -Dqt=ON -Drootfit=ON -Dtable=ON -Dvc=ON 
setenv GSL_ROOT_DIR ${XOPTSTAR}
#setenv PYTHIA6_LIBRARY ${STAR_LIB}
setenv PYTHIA6_LIBRARY ${XOPTSTAR}/lib
#setenv PYTHIA6_INCLUDE_DIR ${XOPTSTAR}/include
#setenv PYTHIA6_INCLUDE_DIR ${STAR}/.${STAR_HOST_SYS}/include
#setenv PYTHIA8_LIBRARY ${XOPTSTAR}/lib
#setenv PYTHIA8_INCLUDE_DIR ${XOPTSTAR}}/include
setenv PYTHIA6_DIR ${XOPTSTAR}
setenv PYTHIA8_DIR ${XOPTSTAR}
setenv CC `which gcc`
setenv CXX `which g++`
setenv FC `which gfortran`
echo "FC = $FC"
setenv QT_LIBRARY_DIR ${QTDIR}/lib
setenv QT_INCLUDE_DIR ${QTDIR}/include
setenv QT_MOC_EXECUTABLE ${QTDIR}/bin/moc
setenv Qt4 ${QTDIR}
rm -f CMakeCache.txt
#cmake cmake ${ROOT}/${ROOT_LEVEL}/root -DCMAKE_INSTALL_PREFIX=${ROOTSYS} -DCMAKE_BUILD_TYPE=Debug -Dall=ON -Dcxx11=ON -Dlibcxx=ON -Dcacoa=ON -Dgdml=ON -Dgsl_shared=ON -Dminuit2=ON -Dqt=ON -Drootfit=ON -Dtable=ON -Dvc=ON 
#cmake ${ROOT}/${ROOT_LEVEL}/root -DCMAKE_INSTALL_PREFIX=${ROOTSYS} -DCMAKE_BUILD_TYPE="${ROOT_BUILD}" -Wno-dev \
# -DCMAKE_C_COMPILER="${CC}" -DCMAKE_CXX_COMPILER="${CXX}" -DCMAKE_Fortran_COMPILER="${FC}" -Dfortran=ON \
# -Dall=ON \
# -Dlibcxx=ON -Dcacoa=ON -Dgdml=ON -Dminuit2=ON -Dqt=OFF -Drootfit=ON -Dvc=OFF -Dunuran=oFF \
# -Dpyroot=ON \
# -Dpythia6=ON  -Dpythia8=ON \
# -Dbuiltin_vdt=ON \
# -Dtbb=OFF \
# -Dvecgeom=OFF  \
# -DXROOTD_ROOT_DIR="${XOPTSTAR}" \
# -DCMAKE_CXX_FLAGS="-fdiagnostics-color=always -msse4.2" \
# -DCMAKE_C_FLAGS="-fdiagnostics-color=always -msse4.2" \
# -Dtable=ON \
# -Dvmc=ON \
# -Dimt=OFF \
# -Druntime_cxxmodules=ON \
# -Dbuiltin_gtest=OFF \
# -Dr=OFF \
# -Dcude=OFF 
# -Dgsl_shared=ON   since 6.30.00
# -Dbuiltin_afterimage=ON \
# -Dpyroot=ON \
# -Droot7=OFF \  for 6.23.01
#-Dcxx11=ON 
#-DCMAKE_CXX_STANDARD
# problems with tbb => -Dimt=OFF 
#-Dtbb=OFF  \
#-D builtin_tbb=OFF \
# -Dbuiltin_cfitsio=On 
#  -Dbuiltin_xrootd=ON 
#-DPYTHIA6_DIR=${XOPTSTAR} \
#-DPYTHIA8_DIR=${XOPTSTAR} \
#-DPYTHIA8_INCLUDE_DIR=${XOPTSTAR}}/include \
#-Dbuiltin_cfitsio=On -DCMAKE_CXX_FLAGS="-fdiagnostics-color=always -msse -msse2 -msse3 -msse4.1 -mssse3" \
#-DCMAKE_C_FLAGS="-fdiagnostics-color=always -msse -msse2 -msse3 -msse4.1 -mssse3" \
# cmake --build . -- install -j8
cmake ${ROOT}/${ROOT_LEVEL}/root -DCMAKE_INSTALL_PREFIX=${ROOTSYS} -DCMAKE_BUILD_TYPE="${ROOT_BUILD}" \
-DCMAKE_C_COMPILER="${CC}" -DCMAKE_CXX_COMPILER="${CXX}" -DCMAKE_Fortran_COMPILER="${FC}" -Dfortran=ON \
-Dpythia6=ON  -Dpythia8=ON \
-DXROOTD_ROOT_DIR="${XOPTSTAR}" \
-DCMAKE_CXX_FLAGS="-fdiagnostics-color=always -msse4.2" \
-DCMAKE_C_FLAGS="-fdiagnostics-color=always -msse4.2" \
-Dmathmore=ON \
-Dtable=ON \
-Dvmc=ON 
#-DCMAKE_VERBOSE_MAKEFILE=ON \
#cmake --build . -- install -j8
