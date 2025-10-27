cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(TCAD)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(pixel pixel.C)
target_link_libraries(pixel Garfield::Garfield)

add_executable(pixel_mt pixel_mt.C)
target_link_libraries(pixel_mt Garfield::Garfield)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(pixel_mt OpenMP::OpenMP_CXX)
endif()

# ---Copy all files locally to the build directory-------------------------------
foreach(_file pixel_des.dat pixel_des.grd)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()

add_subdirectory(Diode3d)
