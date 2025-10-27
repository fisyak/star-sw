cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(GasFile)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Define executables----------------------------------------------------------
add_executable(generate generate.C)
target_link_libraries(generate Garfield::Garfield)

add_executable(printTable printTable.C)
target_link_libraries(printTable Garfield::Garfield)

add_executable(read read.C)
target_link_libraries(read Garfield::Garfield)

add_executable(merge merge.C)
target_link_libraries(merge Garfield::Garfield)

add_executable(penning penning.C)
target_link_libraries(penning Garfield::Garfield)

add_executable(plotcs plotcs.C)
target_link_libraries(plotcs Garfield::Garfield)

add_executable(plotvsEN plotvsEN.C)
target_link_libraries(plotvsEN Garfield::Garfield)

add_executable(plotExtrap plotExtrap.C)
target_link_libraries(plotExtrap Garfield::Garfield)


# ---Copy all files locally to the build directory-------------------------------
foreach(_file ar_80_co2_20_0T.gas ar_80_co2_20_2T.gas ar_93_co2_7.gas ic4h10_0007mbar_100-25kVcm.gas ic4h10_1013mbar_100-100kVcm.gas)
  configure_file(${_file} ${_file} COPYONLY)
endforeach()
