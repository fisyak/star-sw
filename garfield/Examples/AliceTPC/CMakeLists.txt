cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(AliceTPC)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executables-----------------------------------------------------------
add_executable(full_tpc_sim full_tpc_sim.C)
target_link_libraries(full_tpc_sim Garfield::Garfield)

add_executable(ion_signal ion_signal.C)
target_link_libraries(ion_signal Garfield::Garfield)

add_executable(plot_gas plot_gas.C)
target_link_libraries(plot_gas Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file Ne_90_CO2_10_N2_5_with_mg.gas)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
