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

install(TARGETS qoembed DESTINATION lib)
install(FILES provider.h DESTINATION include/libqoembed)
