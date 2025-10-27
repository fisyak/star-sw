# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Grid)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Define executables----------------------------------------------------------
add_executable(plotfield plotfield.C)
target_link_libraries(plotfield Garfield::Garfield)

add_executable(savefield savefield.C)
target_link_libraries(savefield Garfield::Garfield)

add_executable(bfield bfield.C)
target_link_libraries(bfield Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file Efield.txt solenoid.txt)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
