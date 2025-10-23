# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Voxel)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Define executables----------------------------------------------------------
add_executable(voxel_plotfield plotfield.C)
target_link_libraries(voxel_plotfield Garfield::Garfield)

add_executable(voxel_savefield savefield.C)
target_link_libraries(voxel_savefield Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file Efield.txt)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
