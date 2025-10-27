cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(neBEM)

#--- Find Garfield package
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

#--- Build executables
add_executable(RPCbyneBEM RPCbyneBEM.C)
target_link_libraries(RPCbyneBEM Garfield::Garfield)

add_executable(MWPCbyneBEM MWPCbyneBEM.C)
target_link_libraries(MWPCbyneBEM Garfield::Garfield)

add_executable(BiconicalGemByneBEM BiconicalGemByneBEM.C)
target_link_libraries(BiconicalGemByneBEM Garfield::Garfield)

add_executable(parallelPlates parallelPlates.C)
target_link_libraries(parallelPlates Garfield::Garfield)

add_executable(crossingWires crossingWires.C)
target_link_libraries(crossingWires Garfield::Garfield)

add_executable(parallelPlatesWeightingField parallelPlatesWeightingField.C)
target_link_libraries(parallelPlatesWeightingField Garfield::Garfield)

add_executable(tube tube.C)
target_link_libraries(tube Garfield::Garfield)

add_subdirectory(2D)
