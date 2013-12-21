#include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/src)

### provider unit test ###

set(providertest_SRCS
    providertest.cpp
)

add_executable(providertest ${providertest_SRCS})
target_link_libraries(providertest qoembed)
qt5_use_modules(providertest Network Test)

add_test(NAME providertest COMMAND providertest)

### oembedmanager unit test ###

set(oembedmanagertest_SRCS
    oembedmanagertest.cpp
)

add_executable(oembedmanagertest ${oembedmanagertest_SRCS})
target_link_libraries(oembedmanagertest qoembed)
qt5_use_modules(oembedmanagertest Network Test)

add_test(NAME oembedmanagertest COMMAND oembedmanagertest)

### request unit test ###

set(requesttest_SRCS
    requesttest.cpp
)

add_executable(requesttest ${requesttest_SRCS})
target_link_libraries(requesttest qoembed)
qt5_use_modules(requesttest Test)

add_test(NAME requesttest COMMAND requesttest)
