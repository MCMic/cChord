#-------------------------------------------------
#
# Project created by QtCreator 2011-11-29T16:08:29
#
#-------------------------------------------------

QT       += core gui

TARGET = QDistributedWord
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    distributedtextedit.cpp

HEADERS  += mainwindow.h \
    distributedtextedit.h

INCLUDEPATH = .. \
    ../engine/p2p \
    ../engine/help

FORMS    += mainwindow.ui


