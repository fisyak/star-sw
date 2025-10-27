cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Diode3d)

if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

#---Build executable------------------------------------------------------------
add_executable(diode3D diode3D.cpp)
target_link_libraries(diode3D Garfield::Garfield)

#---Copy all files locally to the build directory-------------------------------
foreach(_file diode_des.dat diode_msh.grd)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()

