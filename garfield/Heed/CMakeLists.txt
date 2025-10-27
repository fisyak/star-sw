set(libname "Heed")

add_library(Heed SHARED
            heed++/code/BGMesh.cpp
            heed++/code/ElElasticScat.cpp
            heed++/code/EnTransfCS.cpp
            heed++/code/EnTransfCS_BGM.cpp
            heed++/code/EnergyMesh.cpp
            heed++/code/HeedDeltaElectron.cpp
            heed++/code/HeedDeltaElectronCS.cpp
            heed++/code/HeedMatterDef.cpp
            heed++/code/HeedParticle.cpp
            heed++/code/HeedParticle_BGM.cpp
            heed++/code/HeedPhoton.cpp
            heed++/code/PairProd.cpp
            heed++/code/PhotoAbsCS.cpp
            heed++/code/PhotoAbsCSLib.cpp
            wcpplib/geometry/box.cpp
            wcpplib/geometry/circumf.cpp
            wcpplib/geometry/gparticle.cpp
            wcpplib/geometry/mparticle.cpp
            wcpplib/geometry/plane.cpp
            wcpplib/geometry/polyline.cpp
            wcpplib/geometry/straight.cpp
            wcpplib/geometry/surface.cpp
            wcpplib/geometry/trajestep.cpp
            wcpplib/geometry/vec.cpp
            wcpplib/geometry/volume.cpp
            wcpplib/ioniz/e_cont_enloss.cpp
            wcpplib/math/PolLeg.cpp
            wcpplib/math/cubic.cpp
            wcpplib/math/kinem.cpp
            wcpplib/math/lorgamma.cpp
            wcpplib/matter/AtomDef.cpp
            wcpplib/matter/GasDef.cpp
            wcpplib/matter/MatterDef.cpp
            wcpplib/matter/MoleculeDef.cpp
            wcpplib/particle/eparticle.cpp
            wcpplib/particle/particle_def.cpp
            wcpplib/random/PointsRan.cpp
            wcpplib/random/chisran.cpp
            wcpplib/stream/findmark.cpp
            wcpplib/util/FunNameStack.cpp)
target_link_libraries(Heed PRIVATE GarfieldRandom)
set_property(TARGET Heed PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET Heed PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET Heed PROPERTY CXX_STANDARD ${GARFIELD_CXX_STANDARD})
target_include_directories(Heed PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(Garfield::Heed ALIAS Heed)

install(
  TARGETS ${libname}
  EXPORT "${PROJECT_NAME}Targets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Install the Heed database
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/heed++/database DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Heed)
