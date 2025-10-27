# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(RPC)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Build executable------------------------------------------------------------
# Single Gap RPC
add_executable(rpc_sc rpc_space_charge.cc)
target_link_libraries(rpc_sc Garfield::Garfield)

# Multi gap RPC
add_executable(mrpc_sc mrpc_space_charge.cc)
target_link_libraries(mrpc_sc Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file CO2_C2H2F4_isoC4H10_SF6_30_64.5_4.5_1_T_293_P_723.8.gas)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
