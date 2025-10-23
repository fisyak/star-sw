if(GARFIELD_WITH_CUDA)
add_library(GarfieldGPU STATIC AvalancheMicroscopicGPU.cu
                               GPUFunctions.cu
                               RandomEngineGPU.cu
                               TetrahedralTreeGPU.cu
                               MediumGPU.cu
                               SensorGPU.cu
                               ComponentGPU.cu)
set_target_properties(GarfieldGPU PROPERTIES
                                  POSITION_INDEPENDENT_CODE ON
                                  CXX_STANDARD 17
                                  CXX_STANDARD_REQUIRED ON
                                  CXX_EXTENSIONS OFF
                                  CUDA_EXTENSIONS OFF
                                  CUDA_SEPARABLE_COMPILATION ON
                                  COMPILE_OPTIONS "-Wall;-Wextra;-Wfatal-errors;-Wno-deprecated-gpu-targets")
target_include_directories(GarfieldGPU PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_definitions(GarfieldGPU PRIVATE USEGPU)
endif()
