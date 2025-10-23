cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Ansys121)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(stripAnsys121 strip.C)
target_link_libraries(stripAnsys121 Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file ELIST.lis MPLIST.lis NLIST.lis PRNSOL.lis)
  configure_file(fieldmaps/strip/${_file} ${CMAKE_CURRENT_BINARY_DIR}/fieldmap/${_file} COPYONLY)
endforeach()
