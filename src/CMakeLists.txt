### qoembed library ###

set(qoembed_SRCS
    jsonparser.cpp
    oembedmanager.cpp
    provider.cpp
    request.cpp
    response.cpp
    xmlparser.cpp
)

add_definitions(-DQOEMBED_LIBRARY)

add_library(qoembed SHARED ${qoembed_SRCS})
qt5_use_modules(qoembed Core Network Xml)

install(TARGETS qoembed DESTINATION lib)
install(FILES provider.h DESTINATION include/libqoembed)
