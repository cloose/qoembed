include_directories(${CMAKE_SOURCE_DIR}/src)

### Dependencies ###

find_package(Qt5WebKitWidgets REQUIRED)

### example 01 ###

set(example01_SRCS
    example01.cpp
    mainwindow.cpp
)

qt5_wrap_ui(example01_SRCS mainwindow.ui)

add_executable(example01 ${example01_SRCS})
target_link_libraries(example01 qoembed)
qt5_use_modules(example01 WebKitWidgets)
