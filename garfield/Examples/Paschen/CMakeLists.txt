cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Paschen)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executables------------------------------------------------------
add_executable(gastable gastable.C)
target_link_libraries(gastable Garfield::Garfield)

add_executable(paschenariso paschenariso.C)
target_link_libraries(paschenariso Garfield::Garfield)

add_executable(townplot townplot.C)
target_link_libraries(townplot Garfield::Garfield)

# ---Copy all gas files locally to the build directory----------------------
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/ar-*.gas")
foreach(_file ${files})
  get_filename_component(fname ${_file} NAME)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${fname} COPYONLY)
endforeach()
