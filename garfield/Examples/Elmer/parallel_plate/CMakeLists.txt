cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ElmerPP)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(pp pp.cc)
target_link_libraries(pp Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file parallel_plate/dielectrics.dat
#              parallel_plate/mesh.header
#              parallel_plate/mesh.elements
#              parallel_plate/mesh.nodes
#              parallel_plate/parallel_plate.result
)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
