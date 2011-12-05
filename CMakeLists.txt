cmake_minimum_required(VERSION 2.8)

project(distributedWord)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/engine/p2p
    ${PROJECT_SOURCE_DIR}/engine/helper
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord
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
    
FIND_PACKAGE(Qt4 REQUIRED)
SET(q_HEADERS
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/distributedtextedit.h
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.h
)
QT4_WRAP_CPP(q_HEADERS_MOC ${q_HEADERS})
QT4_WRAP_UI(q_FORMS_HEADERS
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.ui
)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
add_executable(qDistributedWord
    ${q_HEADERS_MOC}
    ${q_FORMS_HEADERS}
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/distributedtextedit.cpp
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/main.cpp
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.cpp
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
    
TARGET_LINK_LIBRARIES(qDistributedWord ${QT_LIBRARIES})

target_link_libraries(distributedWord
    pthread
    rt
    dl)
