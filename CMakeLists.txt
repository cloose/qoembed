cmake_minimum_required(VERSION 2.8.11)

project(qoembed)

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
