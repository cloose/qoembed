### qoembed library ###

set(qoembed_SRCS
    error.cpp
    jsonparser.cpp
    link.cpp
    oembedmanager.cpp
    photo.cpp
    provider.cpp
    request.cpp
    response.cpp
    rich.cpp
    video.cpp
    xmlparser.cpp
)

add_definitions(-DQOEMBED_LIBRARY)

add_library(qoembed SHARED ${qoembed_SRCS})
qt5_use_modules(qoembed Core Network Xml)

target_include_directories(qoembed INTERFACE "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

#
# Setup path variables for installation
#
include(GNUInstallDirs)
set(CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/QOEmbed")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/QOEmbed")

#
# Generate package configuration for find_package()
#
include(CMakePackageConfigHelpers)
configure_package_config_file(QOEmbedConfig.cmake.in QOEmbedConfig.cmake
                              INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
                              PATH_VARS INCLUDE_INSTALL_DIR)

#
# Generate package version file for find_package()
#
write_basic_package_version_file(QOEmbedConfigVersion.cmake
    VERSION ${QOEMBED_VERSION}
    COMPATIBILITY SameMajorVersion)

#
# Installation
#
install(TARGETS qoembed 
        EXPORT QOEmbedTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES error.h
              link.h
              oembedmanager.h
              photo.h
              provider.h
              qoembed_global.h
              request.h
              response.h
              rich.h
              video.h
        DESTINATION ${INCLUDE_INSTALL_DIR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/QOEmbedConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/QOEmbedConfigVersion.cmake"
        DESTINATION ${CMAKECONFIG_INSTALL_DIR})

install(EXPORT QOEmbedTargets FILE QOEmbedTargets.cmake
        DESTINATION ${CMAKECONFIG_INSTALL_DIR})
