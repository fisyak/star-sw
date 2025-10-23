# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Geant4Garfield)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Find Geant4 package, activating all available UI and Vis drivers by default- You can
# set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui to build a batch
# mode only executable

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 COMPONENTS ui_all vis_all)
else()
  find_package(Geant4)
endif()

if(NOT Geant4_FOUND)
  message("Geant4 is not found. Example cannot be built.")
  return()
endif()

# ---Setup Geant4 include directories and compile definitions--------------------
include(${Geant4_USE_FILE})

# ---Locate sources and headers for this project---------------------------------
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)

# ---Add the executable, and link it to the Geant4 libraries---------------------
add_executable(exampleGeant4Interface exampleGarfield.cc ${sources} ${headers})
target_link_libraries(exampleGeant4Interface ${Geant4_LIBRARIES} Garfield::Garfield)
target_include_directories(exampleGeant4Interface
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---Copy all scripts to the build directory-------------------------------------
set(EXAMPLEGARFIELD_SCRIPTS
    icons.mac
    gui.mac
    physics.mac
    init_vis.mac
    run.mac
    vis.mac
    ar_70_co2_30_1000mbar.gas)

foreach(_script ${EXAMPLEGARFIELD_SCRIPTS})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_script}
                 ${CMAKE_CURRENT_BINARY_DIR}/${_script} COPYONLY)
endforeach()
