#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T16:47:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
    menustyle.cpp \
    mainwindow.cpp \
    MemMgWindow.cpp \
    ProjMgWindow.cpp \
    Sqlite.cpp \
    ScrollArea.cpp \
    ActionBar.cpp \
    MyButton.cpp \
    MemContentWindow.cpp \
    MemInfoWindow.cpp

HEADERS  += \
    menustyle.h \
    mainwindow.h \
    MemMgWindow.h \
    ProjMgWindow.h \
    Sqlite.h \
    ScrollArea.h \
    ActionBar.h \
    MyButton.h \
    MemContentWindow.h \
    MemInfoWindow.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    icons.qrc
