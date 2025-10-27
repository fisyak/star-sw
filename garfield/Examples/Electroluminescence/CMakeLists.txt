cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Electroluminescence)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Define executables---------------------------------------------------------
add_executable(Electroluminescence_example example.C)
target_link_libraries(Electroluminescence_example Garfield::Garfield)

add_executable(userHandle userHandle.C)
target_link_libraries(userHandle Garfield::Garfield)
