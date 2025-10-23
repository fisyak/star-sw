# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Srim)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executables----------------------------------------------------------
add_executable(srim srim.C)
target_link_libraries(srim Garfield::Garfield)

add_executable(trim trim.C)
target_link_libraries(trim Garfield::Garfield)

add_executable(srimbfield srimbfield.C)
target_link_libraries(srimbfield Garfield::Garfield)

add_executable(trimsignal trimsignal.C)
target_link_libraries(trimsignal Garfield::Garfield)

add_executable(checkhwf checkhwf.C)
target_link_libraries(checkhwf Garfield::Garfield)

# ---Copy all files locally to the build directory------------------------------
foreach(_file Alpha_in_Ar.txt EXYZ.txt)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
