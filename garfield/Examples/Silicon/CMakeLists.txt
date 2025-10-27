cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Silicon)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(planar planar.C)
target_link_libraries(planar Garfield::Garfield)

add_executable(planar_movie planar_movie.C)
target_link_libraries(planar_movie Garfield::Garfield)
