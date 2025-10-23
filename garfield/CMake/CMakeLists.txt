# Configuring the package for exporting
include(CMakePackageConfigHelpers)

# This is a valid destination for both Win and Unix
set(CMAKE_INSTALL_DIR share/Garfield/cmake)

# Creating the target export file
install(
  EXPORT "GarfieldTargets"
  FILE "GarfieldTargets.cmake"
  NAMESPACE Garfield::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Garfield")

# Creates the versioning file
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/GarfieldConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

# Prepares the configuration file
configure_package_config_file("${CMAKE_CURRENT_LIST_DIR}/GarfieldConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/GarfieldConfig.cmake"
                              INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Garfield")

# Installs the configuration file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GarfieldConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/GarfieldConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Garfield")

find_package(Python)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/setup.sh.in
               ${PROJECT_BINARY_DIR}/setupGarfield.sh @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/setup.csh.in
               ${PROJECT_BINARY_DIR}/setupGarfield.csh @ONLY)

install(FILES ${PROJECT_BINARY_DIR}/setupGarfield.sh
              ${PROJECT_BINARY_DIR}/setupGarfield.csh
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Garfield)

if(Python_FOUND)
  configure_file("${PROJECT_SOURCE_DIR}/CMake/__init__.py.in" "${PROJECT_BINARY_DIR}/generated/__init__.py" @ONLY)
  install(FILES "${PROJECT_BINARY_DIR}/generated/__init__.py"
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/Garfield")
endif()
