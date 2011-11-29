cmake_minimum_required(VERSION 2.8)

project(distributedWord)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/engine/p2p
    ${PROJECT_SOURCE_DIR}/engine/helper
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pg")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -mtune=generic  -static-libgcc  -static-libstdc++")

add_executable(distributedWord
    ${PROJECT_SOURCE_DIR}/main.cc
    ${PROJECT_SOURCE_DIR}/engine/p2p/node/Node.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/crypto/sha1.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/mongoose.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/request/Request.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/thread/Thread.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/HTTP_Client.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/node/Node.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/ProtocolSingleton.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/callbacks/callbacks.cpp
    ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/callbacks/chord_callbacks.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/chord/AbstractChord.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/chord/ChordNode.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/transport/http/http_operations.cpp
    ${PROJECT_SOURCE_DIR}/engine/p2p/transport/http/TransportHTTP.cpp
    ${PROJECT_SOURCE_DIR}/lib/TextHandler.cc
    )
    
target_link_libraries(distributedWord
    pthread
    rt
    dl)
