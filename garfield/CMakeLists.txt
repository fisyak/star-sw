# Build Garfield++ library and examples
# Authors: Klaus Zenker, Pere Mato, Stefano Caiazza
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Garfield VERSION 0.3
                 DESCRIPTION "Toolkit for the detailed simulation of particle detectors based on ionization measurement in gases and semiconductors"
                 HOMEPAGE_URL "https://garfieldpp.web.cern.ch/garfieldpp/"
                 LANGUAGES Fortran CXX)

option(GARFIELD_WITH_CUDA "Build CUDA code if possible" ON)
option(GARFIELD_CUDA_USE_FLOAT "Use float with CUDA code (for some performances issues on some hardware) default:double" FALSE)
option(GARFIELD_WITH_DEGRADE "Build Degrade." ON)
option(GARFIELD_WITH_EXAMPLES "Build Garfield++ examples" ON)
option(GARFIELD_WITH_DOC "Whether or not to create doxygen doc target." OFF)
option(GARFIELD_WITH_TESTS "Build Garfield++ tests" ON)
option(GARFIELD_WITH_GSL "Build Garfield++ with GSL (useless if C++>=17)" OFF)


# Setting the default build type to be Release.
# Otherwise the default mode is Debug.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build.")
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(GARFIELD_WITH_CUDA)
  cmake_policy(PUSH)
  include(CheckLanguage)
  check_language(CUDA)
  if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    cmake_policy(SET CMP0104 NEW)
    if(NOT CMAKE_CUDA_ARCHITECTURES STREQUAL "")
      set(CMAKE_CUDA_ARCHITECTURES "native")
    endif()
    add_subdirectory(GPU)
  else()
    message(WARNING "No CUDA support !")
    unset(GARFIELD_WITH_CUDA)
    unset(GARFIELD_WITH_CUDA CACHE)
    option(GARFIELD_WITH_CUDA "Build CUDA code if possible" OFF)
  endif()
  cmake_policy(POP)
endif()

#--- Set default installation prefix ------------------------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(DEFINED ENV{GARFIELD_INSTALL} )
    set(CMAKE_INSTALL_PREFIX
        $ENV{GARFIELD_INSTALL}
        CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
  elseif(DEFINED ENV{GARFIELD_HOME} )
    set(CMAKE_INSTALL_PREFIX
        $ENV{GARFIELD_HOME}/install
        CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
  else()
    set(CMAKE_INSTALL_PREFIX
        ${PROJECT_SOURCE_DIR}/install
        CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
  endif()
else()
  message(
    STATUS "The installation folder is set to its default value ${CMAKE_INSTALL_PREFIX}")
endif()
message(STATUS "Install path: ${CMAKE_INSTALL_PREFIX}")
message(
  STATUS
    "If you want to change this path call cmake -DCMAKE_INSTALL_PREFIX=my_install_path ..."
)

# Adding the CMake folder to the search path for modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

#--- Use GNU-style hierarchy for installing build products --------------------
include(GNUInstallDirs)

#--- Dependencies -------------------------------------------------------------
if(DEFINED ENV{ROOTSYS})
  list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
elseif(DEFINED ROOTSYS)
  list(APPEND CMAKE_PREFIX_PATH ${ROOTSYS})
elseif(DEFINED ROOT_CMAKE_DIR)
  list(APPEND CMAKE_PREFIX_PATH ${ROOT_CMAKE_DIR})
# else()
#   message(
#     STATUS
#       "Please consider to set ROOTSYS or use -DROOTSYS=..."
#       "If still there is a problem, point to the directory which includes FindROOT.cmake using -DROOT_CMAKE_DIR=..."
# )
endif()

find_package(ROOT 6.0 REQUIRED COMPONENTS Geom Gdml MathCore)
#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY) --
if(${ROOT_VERSION} VERSION_LESS "6.20.0")
  # It only makes sense for ROOT < 6.20.
  # Afterwards it is loaded automatically by the find_package
  get_filename_component(Root_Use_File_Dir ${ROOT_USE_FILE} DIRECTORY)
  include("${Root_Use_File_Dir}/modules/RootNewMacros.cmake")
endif()

#--- Set the C++ standard (depending on the ROOT version) ---------------------
if(NOT DEFINED CMAKE_CXX_STANDARD)
  if(DEFINED ROOT_CXX_STANDARD)
    set(GARFIELD_CXX_STANDARD ${ROOT_CXX_STANDARD})
  elseif(${ROOT_CXX_FLAGS} MATCHES ".*-std=c\\+\\+([0-9][0-9])")
    set(GARFIELD_CXX_STANDARD ${CMAKE_MATCH_1})
  elseif(${ROOT_CXX_FLAGS} MATCHES ".*-std=c\\+\\+1z")
    set(GARFIELD_CXX_STANDARD 17)
  endif()
else()
  set(GARFIELD_CXX_STANDARD ${CMAKE_CXX_STANDARD})
endif()

if(GARFIELD_WITH_GSL OR (GARFIELD_CXX_STANDARD LESS 17))
  unset(GARFIELD_WITH_GSL)
  unset(GARFIELD_WITH_GSL CACHE)
  option(GARFIELD_WITH_GSL "Build Garfield++ with GSL (useless if C++>=17)" ON)
  find_package(GSL REQUIRED)
endif()
find_package(OpenMP)

# Add Magboltz
add_subdirectory(Magboltz)

# Add Degrade
if(GARFIELD_WITH_DEGRADE)
  add_subdirectory(Degrade)
endif()

# Create GarfieldRandom library
add_library(GarfieldRandom SHARED
  Source/Random.cc
  Source/RandomEngineRoot.cc
  Source/RandomEngineSTL.cc
)
target_include_directories(GarfieldRandom PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)
target_link_libraries(GarfieldRandom PRIVATE ROOT::MathCore)
set_property(TARGET GarfieldRandom PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET GarfieldRandom PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET GarfieldRandom PROPERTY CXX_STANDARD ${GARFIELD_CXX_STANDARD})

# Creating the main Garfield library
add_library(Garfield SHARED
            Source/AvalancheGrid.cc
            Source/AvalancheGridSpaceCharge.cc
            Source/AvalancheMC.cc
            Source/AvalancheMicroscopic.cc
            Source/Component.cc
            Source/ComponentAnalyticField.cc
            Source/ComponentAnsys121.cc
            Source/ComponentAnsys123.cc
            Source/ComponentCST.cc
            Source/ComponentChargedRing.cc
            Source/ComponentComsol.cc
            Source/ComponentConstant.cc
            Source/ComponentElmer.cc
            Source/ComponentElmer2d.cc
            Source/ComponentFieldMap.cc
            Source/ComponentGrid.cc
            Source/ComponentNeBem2d.cc
            Source/ComponentNeBem3d.cc
            Source/ComponentNeBem3dMap.cc
            Source/ComponentParallelPlate.cc
            Source/ComponentTcad2d.cc
            Source/ComponentTcad3d.cc
            Source/ComponentTcadBase.cc
            Source/ComponentUser.cc
            Source/ComponentVoxel.cc
            Source/DriftLineRKF.cc
            Source/GeometryRoot.cc
            Source/GeometrySimple.cc
            Source/KDTree.cc
            Source/Medium.cc
            Source/MediumCdTe.cc
            Source/MediumDiamond.cc
            Source/MediumGaAs.cc
            Source/MediumGaN.cc
            Source/MediumGas.cc
            Source/MediumMagboltz.cc
            Source/MediumSilicon.cc
            Source/NeBemInterface.cpp
            Source/Numerics.cc
            Source/OpticalData.cc
            Source/Polygon.cc
            Source/QuadTree.cc
            Source/Sensor.cc
            Source/Shaper.cc
            Source/Solid.cc
            Source/SolidBox.cc
            Source/SolidExtrusion.cc
            Source/SolidHole.cc
            Source/SolidRidge.cc
            Source/SolidSphere.cc
            Source/SolidTube.cc
            Source/SolidWire.cc
            Source/TetrahedralTree.cc
            Source/TGeoTet.cc
            Source/Track.cc
            Source/TrackBichsel.cc
            Source/TrackElectron.cc
            Source/TrackHeed.cc
            Source/TrackPAI.cc
            Source/TrackSimple.cc
            Source/TrackSrim.cc
            Source/TrackTrim.cc
            Source/ViewBase.cc
            Source/ViewCell.cc
            Source/ViewDrift.cc
            Source/ViewFEMesh.cc
            Source/ViewField.cc
            Source/ViewGeometry.cc
            Source/ViewIsochrons.cc
            Source/ViewMedium.cc
            Source/ViewSignal.cc
            $<$<BOOL:${GARFIELD_WITH_DEGRADE}>:Source/TrackDegrade.cc>
)

if(GARFIELD_CUDA_USE_FLOAT)
  target_compile_definitions(Garfield PRIVATE GARFIELD_CUDA_USE_FLOAT)
endif()
target_compile_options(Garfield PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
      -Wall
      -Wextra
      -pedantic
      -Wfatal-errors
      -Wno-missing-braces
      -Wshadow>
      $<$<CXX_COMPILER_ID:MSVC>:/W3>)
target_link_libraries(Garfield PUBLIC GarfieldRandom)
set_property(TARGET Garfield PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET Garfield PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET Garfield PROPERTY CXX_STANDARD ${GARFIELD_CXX_STANDARD})
add_library(Garfield::Garfield ALIAS Garfield)

# Creating the main Garfield library
set(GARFIELD_PUBLIC_HEADERS
Include/Garfield/AvalancheGrid.hh
Include/Garfield/ComponentFieldMap.hh
Include/Garfield/MediumDiamond.hh
Include/Garfield/Random.hh
Include/Garfield/SolidWire.hh
Include/Garfield/Vector.hh
Include/Garfield/AvalancheGridSpaceCharge.hh
Include/Garfield/ComponentGrid.hh
Include/Garfield/FundamentalConstants.hh
Include/Garfield/MediumGaAs.hh
Include/Garfield/RandomEngine.hh
Include/Garfield/TGeoTet.hh
Include/Garfield/ViewBase.hh
Include/Garfield/AvalancheMC.hh
Include/Garfield/ComponentNeBem2d.hh
Include/Garfield/GarfieldConstants.hh
Include/Garfield/MediumGaN.hh
Include/Garfield/Symmetry.hh
Include/Garfield/RandomEngineRoot.hh
Include/Garfield/TetrahedralTree.hh
Include/Garfield/ViewCell.hh
Include/Garfield/AvalancheMicroscopic.hh
Include/Garfield/ComponentNeBem3d.hh
Include/Garfield/Geometry.hh
Include/Garfield/MediumGas.hh
Include/Garfield/RandomEngineSTL.hh
Include/Garfield/Track.hh
Include/Garfield/ViewDrift.hh
Include/Garfield/Component.hh
Include/Garfield/ComponentNeBem3dMap.hh
Include/Garfield/GeometryRoot.hh
Include/Garfield/MediumMagboltz.hh
Include/Garfield/Sensor.hh
Include/Garfield/TrackBichsel.hh
Include/Garfield/ViewFEMesh.hh
Include/Garfield/ComponentAnalyticField.hh
Include/Garfield/ComponentParallelPlate.hh
Include/Garfield/GeometrySimple.hh
Include/Garfield/MediumPlastic.hh
Include/Garfield/Shaper.hh
Include/Garfield/TrackDegrade.hh
Include/Garfield/ViewField.hh
Include/Garfield/ComponentAnsys121.hh
Include/Garfield/ComponentTcad2d.hh
Include/Garfield/MediumSilicon.hh
Include/Garfield/Solid.hh
Include/Garfield/TrackElectron.hh
Include/Garfield/ViewGeometry.hh
Include/Garfield/ComponentAnsys123.hh
Include/Garfield/ComponentTcad3d.hh
Include/Garfield/KDTree.hh
Include/Garfield/MultiProcessInterface.hh
Include/Garfield/SolidBox.hh
Include/Garfield/TrackHeed.hh
Include/Garfield/ViewIsochrons.hh
Include/Garfield/ComponentCST.hh
Include/Garfield/ComponentTcadBase.hh
Include/Garfield/Numerics.hh
Include/Garfield/SolidExtrusion.hh
Include/Garfield/TrackPAI.hh
Include/Garfield/ViewMedium.hh
Include/Garfield/ComponentComsol.hh
Include/Garfield/ComponentUser.hh
Include/Garfield/MagboltzInterface.hh
Include/Garfield/OpticalData.hh
Include/Garfield/SolidHole.hh
Include/Garfield/TrackSimple.hh
Include/Garfield/ViewSignal.hh
Include/Garfield/ComponentConstant.hh
Include/Garfield/ComponentVoxel.hh
Include/Garfield/Medium.hh
Include/Garfield/SolidRidge.hh
Include/Garfield/TrackSrim.hh
Include/Garfield/ComponentElmer.hh
Include/Garfield/DegradeInterface.hh
Include/Garfield/MediumCdTe.hh
Include/Garfield/Polygon.hh
Include/Garfield/SolidSphere.hh
Include/Garfield/TrackTrim.hh
Include/Garfield/ComponentElmer2d.hh
Include/Garfield/DriftLineRKF.hh
Include/Garfield/MediumConductor.hh
Include/Garfield/QuadTree.hh
Include/Garfield/SolidTube.hh
Include/Garfield/Utilities.hh
Include/Garfield/ParticleTypes.hh
Include/Garfield/AvalancheMicroscopicTypes.hh
Include/Garfield/ComponentChargedRing.hh
Include/Garfield/Exceptions.hh
)
set_target_properties(Garfield PROPERTIES PUBLIC_HEADER "${GARFIELD_PUBLIC_HEADERS}")
target_link_libraries(Garfield PUBLIC ROOT::Tree ROOT::RIO)

target_link_libraries(Garfield PUBLIC ROOT::Geom
                                      ROOT::Gdml
                                      ROOT::Graf3d
                                      Garfield::Heed
                                      Magboltz::Magboltz
                                      $<$<BOOL:${GARFIELD_WITH_GSL}>:GSL::gsl>
                                      $<$<BOOL:${GARFIELD_WITH_DEGRADE}>:Degrade::Degrade>
                                      $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>
                                      $<$<BOOL:${GARFIELD_WITH_CUDA}>:GarfieldGPU>)
target_compile_definitions(Garfield PRIVATE $<$<BOOL:${GARFIELD_WITH_CUDA}>:USEGPU> $<$<NOT:$<BOOL:${GARFIELD_WITH_GSL}>>:WITHOUT_GSL>)
target_include_directories(Garfield INTERFACE $<INSTALL_INTERFACE:include>
                                    PRIVATE $<$<BOOL:${GARFIELD_WITH_CUDA}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/GPU>> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/NeBem>
                                    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)

#--- Create ROOT dictionary ---------------------------------------------------
root_generate_dictionary(GarfieldDict "${GARFIELD_PUBLIC_HEADERS}" LINKDEF "${CMAKE_CURRENT_SOURCE_DIR}/Include/Garfield/LinkDef.h" MODULE Garfield)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libGarfield_rdict.pcm DESTINATION ${CMAKE_INSTALL_LIBDIR} OPTIONAL)

#--- If you cannot create symbolic links turn FALSE the library version -------
option(BUILD_WITH_VERSION_NUMBER
       "If you cannot create symbolic links turn FALSE the library version" TRUE)
if(BUILD_WITH_VERSION_NUMBER)
  set_target_properties(Garfield PROPERTIES SOVERSION ${Garfield_VERSION})
endif()
mark_as_advanced(BUILD_WITH_VERSION_NUMBER)

# Add neBEM
# TODO Decouple Nebem interface from the Garfield components
# The Nebem interface is somewhat coupled with Garfield itself.
# We should decouple them to keep them independent, but until then
# they have to be compiled in the same library to make it work
set(nebem_sources
  NeBem/ComputeProperties.c
  NeBem/Isles.c
  NeBem/luc.c
  NeBem/neBEM.c
  NeBem/neBEMInterface.c
  NeBem/nrutil.c
  NeBem/ReTriM.c
  NeBem/svdcmp.c
  NeBem/Vector.c)

# Until CMake 3.18 the source file properties are only visible to targets
# added in the same directory therefore we cannot add Nebem through the
# add_subdirectory mechanism unless we change the cpp file extension so that
# CMake can recognize them automatically as CXX and not C
set_source_files_properties(${nebem_sources} PROPERTIES LANGUAGE CXX)
target_sources(Garfield PRIVATE ${nebem_sources})

# Add Heed
add_subdirectory(Heed)

#--- Install the header files -------------------------------------------------
install(TARGETS Garfield GarfieldRandom EXPORT "${PROJECT_NAME}Targets"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Garfield")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Data
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Garfield/)

#--- Target for Doxygen documentation -----------------------------------------
if(GARFIELD_WITH_DOC)
  add_subdirectory(Doc)
endif()

#--- Build the examples -------------------------------------------------------
if(GARFIELD_WITH_EXAMPLES)
  message(
    STATUS
      "Garfield++ examples will be built. In order disable this option use -DWITH_EXAMPLES=OFF"
  )
  add_subdirectory(Examples)
else()
  message(STATUS "Building of examples is switched off.")
endif()

add_subdirectory(CMake)

if(GARFIELD_WITH_TESTS)
  include(CTest)
  add_subdirectory(Tests)
endif()
