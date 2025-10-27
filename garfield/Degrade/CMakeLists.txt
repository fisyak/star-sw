cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Degrade VERSION 3.17)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(Degrade SHARED degrad.f)
target_compile_options(Degrade PRIVATE -std=legacy)
set_target_properties(Degrade PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")
add_library(Degrade::Degrade ALIAS Degrade)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DegradeConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/generated/DegradeConfig.cmake" INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Degrade")
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/generated/DegradeConfigVersion.cmake" VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMinorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/DegradeConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/generated/DegradeConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Degrade")
install(TARGETS Degrade EXPORT DegradeTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT DegradeTargets
        FILE DegradeTargets.cmake
        NAMESPACE Degrade::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Degrade")
