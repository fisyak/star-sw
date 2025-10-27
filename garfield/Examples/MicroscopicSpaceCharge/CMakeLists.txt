# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(MicroscopicSpaceCharge)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Build executable------------------------------------------------------------

add_executable(MicroscopicSpaceCharge MicroscopicSpaceCharge.C)
target_link_libraries(MicroscopicSpaceCharge Garfield::Garfield)

