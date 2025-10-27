cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Signals)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# --- Build executables.
add_executable(noise noise.C)
target_link_libraries(noise Garfield::Garfield)

add_executable(Signalstest test.C)
target_link_libraries(Signalstest Garfield::Garfield)

# --- Copy all files locally to the build directory.
foreach(_file ft.txt)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
