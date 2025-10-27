cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GainFluctuations)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable-----------------------------------------------------------
add_executable(arco2 arco2.C)
target_link_libraries(arco2 Garfield::Garfield)

add_executable(distance distance.C)
target_link_libraries(distance Garfield::Garfield)
