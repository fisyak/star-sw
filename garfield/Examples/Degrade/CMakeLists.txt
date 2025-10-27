cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Degrade)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# Build executables
add_executable(mip mip.C)
target_link_libraries(mip Garfield::Garfield)

add_executable(plotdedx plotdedx.C)
target_link_libraries(plotdedx Garfield::Garfield)
