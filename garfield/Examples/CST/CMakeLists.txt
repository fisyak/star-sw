# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(CST)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(cst cst.C)
target_link_libraries(cst Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file drift_std_200_320_2500.efm)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
