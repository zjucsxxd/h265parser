#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T16:15:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = h265parser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    h265parser.cpp

HEADERS  += mainwindow.h \
    h265parser.h \
    gdef.h

FORMS    += mainwindow.ui
