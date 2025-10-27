find_package(GSL REQUIRED)
find_package(OpenMP) # Just to be independent for the future

set(nebem_sources
  ComputeProperties.c
  Isles.c
  luc.c
  neBEM.c
  neBEMInterface.c
  nrutil.c
  ReTriM.c
  svdcmp.c
  Vector.c)

add_library(neBEM SHARED ${nebem_sources})
set_source_files_properties(${nebem_sources} PROPERTIES LANGUAGE CXX)
target_include_directories(neBEM PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
set_target_properties(neBEM PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF CXX_STANDARD ${GARFIELD_CXX_STANDARD})
target_link_libraries(neBEM PRIVATE GSL::gsl
                                    $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>
)
add_library(neBEM::neBEM ALIAS neBEM)

install(TARGETS neBEM
        EXPORT neBEMTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT neBEMTargets
        FILE neBEMTargets.cmake
        NAMESPACE neBEM::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Garfield")
