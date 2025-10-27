cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Silicon)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable----(diode.C)----------------------------------------------
add_executable(diode diode.C)
target_link_libraries(diode Garfield::Garfield)
