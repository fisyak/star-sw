# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Trapping)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Build executable------------------------------------------------------------
add_executable(Test Simulation.cpp)
target_link_libraries(Test Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file Wfield.txt Efield.txt Attachment.txt)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
