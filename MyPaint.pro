#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T21:27:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPaint
TEMPLATE = app


SOURCES += main.cpp\
        mainunit.cpp \
    graph.cpp

HEADERS  += mainunit.h \
    graph.h

FORMS    += mainunit.ui

CONFIG  += c++11

RESOURCES += \
    Icons.qrc
