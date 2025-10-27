# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Heed)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(edep edep.C)
target_link_libraries(edep Garfield::Garfield)

add_executable(heed_bfield heed_bfield.C)
target_link_libraries(heed_bfield Garfield::Garfield)

add_executable(qdepSi qdepSi.C)
target_link_libraries(qdepSi Garfield::Garfield)

add_executable(rangeSi rangeSi.C)
target_link_libraries(rangeSi Garfield::Garfield)

add_executable(fe55 fe55.C)
target_link_libraries(fe55 Garfield::Garfield)

add_executable(heed_plotdedx plotdedx.C)
target_link_libraries(heed_plotdedx Garfield::Garfield)
set_target_properties(heed_plotdedx PROPERTIES OUTPUT_NAME "plotdedx")
