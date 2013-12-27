cmake_minimum_required(VERSION 2.8.11)

project(qoembed)

# Set version number
set(QOEMBED_MAJOR_VERSION 0)
set(QOEMBED_MINOR_VERSION 1)
set(QOEMBED_PATCH_VERSION 0)
set(QOEMBED_VERSION ${QOEMBED_MAJOR_VERSION}.${QOEMBED_MINOR_VERSION}.${QOEMBED_PATCH_VERSION})

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable CTest
enable_testing()

### Dependencies ###

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)

### Subdirs ###

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)

### Packaging ###

include(CPack)
