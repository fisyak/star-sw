# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(AnalyticField)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# --- Build executables.
add_executable(mwpc mwpc.C)
target_link_libraries(mwpc Garfield::Garfield)

add_executable(gallery gallery.C)
target_link_libraries(gallery Garfield::Garfield)

add_executable(fieldlines fieldlines.C)
target_link_libraries(fieldlines Garfield::Garfield)

add_executable(integrate integrate.C)
target_link_libraries(integrate Garfield::Garfield)

add_executable(dipole dipole.C)
target_link_libraries(dipole Garfield::Garfield)

add_executable(isochrons isochrons.C)
target_link_libraries(isochrons Garfield::Garfield)

add_executable(polar polar.C)
target_link_libraries(polar Garfield::Garfield)

add_executable(wedge wedge.C)
target_link_libraries(wedge Garfield::Garfield)

add_executable(strip strip.C)
target_link_libraries(strip Garfield::Garfield)

add_executable(pixels pixels.C)
target_link_libraries(pixels Garfield::Garfield)

add_executable(charges charges.C)
target_link_libraries(charges Garfield::Garfield)

add_executable(sag sag.C)
target_link_libraries(sag Garfield::Garfield)

add_executable(plotForces plotForces.C)
target_link_libraries(plotForces Garfield::Garfield)

add_executable(optimise optimise.C)
target_link_libraries(optimise Garfield::Garfield)

foreach(_file ar_50_c2h6_50_B_angle.gas)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
