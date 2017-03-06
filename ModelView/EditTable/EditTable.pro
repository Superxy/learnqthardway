#-------------------------------------------------
#
# Project created by QtCreator 2017-03-06T18:44:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditTable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymodel.cpp

HEADERS  += mainwindow.h \
    mymodel.h

FORMS    += mainwindow.ui
