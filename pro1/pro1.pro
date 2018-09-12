#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T22:52:24
#
#-------------------------------------------------

QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pro1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    benchmark1.cpp \
    benchmark2.cpp

HEADERS  += mainwindow.h \
    benchmark1.h \
    benchmark2.h

FORMS    += mainwindow.ui \
    benchmark1.ui \
    benchmark2.ui
