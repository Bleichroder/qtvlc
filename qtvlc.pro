#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T16:09:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtvlc
TEMPLATE = app


SOURCES += main.cpp\
        system.cpp \
    url.cpp \
    listdialog.cpp \
    vlcplayer.cpp \
    vlcpackage.cpp

HEADERS  += system.h \
    url.h \
    listdialog.h \
    vlcplayer.h \
    vlcpackage.h

FORMS    += vlcplayer.ui \
    url.ui \
    listdialog.ui

INCLUDEPATH += D:\QTProject\qtvlc\vlc \

LIBS += D:\QTProject\qtvlc\lib\libvlc.lib \
    D:\QTProject\qtvlc\lib\libvlccore.lib

RESOURCES += \
    pic/media_player.qrc
