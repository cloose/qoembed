### qoembed library ###

set(qoembed_SRCS
    oembedmanager.cpp
    provider.cpp
    request.cpp
)

add_definitions(-DQOEMBED_LIBRARY)

add_library(qoembed SHARED ${qoembed_SRCS})
qt5_use_modules(qoembed Core Network)

install(TARGETS qoembed DESTINATION lib)
install(FILES provider.h DESTINATION include/libqoembed)
