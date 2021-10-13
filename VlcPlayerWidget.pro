#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T13:00:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VlcPlayerWidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS HAVE_DIRFD HAVE_FDOPENDIR HAVE_LLDIV HAVE_GETPID HAVE_SWAB HAVE_STRUCT_POLLFD HAVE_STRUCT_TIMESPEC HAVE_SEARCH_H HAVE_REALPATH HAVE_STATIC_ASSERT  HAVE_FLOCKFILE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+="E:\CppProjects\vlc\include"
INCLUDEPATH+="E:\CppProjects\vlc\include\vlc"
INCLUDEPATH+="E:\CppProjects\vlc\lib"

QMAKE_CXXFLAGS += /W4005

SOURCES += main.cpp\
        widget.cpp \
    vlcplayerwidget.cpp

HEADERS  += widget.h \
    vlcplayerwidget.h

FORMS    += widget.ui
LIBS+=-L"D:/Program Files/VideoLan/vlc/lib"
LIBS += -lvlc -lvlccore
