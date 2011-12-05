cmake_minimum_required(VERSION 2.8)

project(distributedWord)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/engine/p2p
    ${PROJECT_SOURCE_DIR}/engine/helper
    ${PROJECT_SOURCE_DIR}/gui/QDistributedWord
    #~ /usr/include/gtkmm-2.4
    #~ /usr/include/gdkmm-2.4
    #~ /usr/lib/gtkmm-2.4/include
    #~ /usr/lib/gdkmm-2.4/include
    #~ /usr/lib/pangomm-1.4/include
    #~ /usr/lib/glibmm-2.4/include
    #~ /usr/include/glibmm-2.4
    #~ /usr/include/glib-2.0
    #~ /usr/lib/glib-2.0/include    
    ${GTKMM_INCLUDE_DIRS}
    )
link_directories(
    ${GTKMM_LIBRARY_DIRS}  )
    
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
    ${PROJECT_SOURCE_DIR}/lib/Modification.cc
    )

add_executable(gDistributedWord
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
    ${PROJECT_SOURCE_DIR}/lib/Modification.cc
    ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/GtkTextHandler.cc
    ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/main.cc
    #~ ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/extra.c
    #~ ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/fileselect.c
    #~ ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/find.c
    #~ ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/findreplace.c
    #~ ${PROJECT_SOURCE_DIR}/gui/gDistributedWord/menu.c
    )
    
#~ FIND_PACKAGE(Qt4 REQUIRED)
#~ SET(q_HEADERS
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/distributedtextedit.h
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.h
#~ )
#~ QT4_WRAP_CPP(q_HEADERS_MOC ${q_HEADERS})
#~ QT4_WRAP_UI(q_FORMS_HEADERS
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.ui
#~ )
#~ INCLUDE(${QT_USE_FILE})
#~ ADD_DEFINITIONS(${QT_DEFINITIONS})
#~ add_executable(qDistributedWord
    #~ ${q_HEADERS_MOC}
    #~ ${q_FORMS_HEADERS}
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/distributedtextedit.cpp
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/main.cpp
    #~ ${PROJECT_SOURCE_DIR}/gui/QDistributedWord/mainwindow.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/node/Node.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/crypto/sha1.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/mongoose.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/request/Request.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/thread/Thread.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/HTTP_Client.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/node/Node.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/ProtocolSingleton.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/callbacks/callbacks.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/helper/mongoose_http_server/callbacks/chord_callbacks.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/chord/AbstractChord.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/protocols/chord/ChordNode.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/transport/http/http_operations.cpp
    #~ ${PROJECT_SOURCE_DIR}/engine/p2p/transport/http/TransportHTTP.cpp
    #~ ${PROJECT_SOURCE_DIR}/lib/TextHandler.cc
    #~ )
    
#~ TARGET_LINK_LIBRARIES(qDistributedWord ${QT_LIBRARIES})

target_link_libraries(distributedWord
    pthread
    rt
    dl    
    )
target_link_libraries(gDistributedWord
    pthread
    rt
    dl    
    ${GTKMM_LIBRARIES})
