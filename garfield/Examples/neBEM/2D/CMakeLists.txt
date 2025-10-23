cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(neBEM2d)

#--- Find Garfield package
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

#--- Build executables
add_executable(triangle triangle.C)
target_link_libraries(triangle Garfield::Garfield)

add_executable(dielectric dielectric.C)
target_link_libraries(dielectric Garfield::Garfield)

add_executable(wire wire.C)
target_link_libraries(wire Garfield::Garfield)
