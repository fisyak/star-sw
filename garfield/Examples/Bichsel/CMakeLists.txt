cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Bichsel)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(Bichsel Bichsel.C)
target_link_libraries(Bichsel Garfield::Garfield)
