cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Magboltz VERSION 11.19)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
add_library(Magboltz SHARED magboltz.f)
target_compile_options(Magboltz PRIVATE -std=legacy)
set_target_properties(Magboltz PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION "${PROJECT_VERSION_MAJOR}")
add_library(Magboltz::Magboltz ALIAS Magboltz)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/MagboltzConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/generated/MagboltzConfig.cmake" INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Magboltz")
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/generated/MagboltzConfigVersion.cmake" VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMinorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/MagboltzConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/generated/MagboltzConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Magboltz")
install(TARGETS Magboltz EXPORT MagboltzTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT MagboltzTargets
        FILE MagboltzTargets.cmake
        NAMESPACE Magboltz::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Magboltz")
