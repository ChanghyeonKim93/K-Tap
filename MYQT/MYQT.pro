#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T17:15:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MYQT
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    serialThread.cpp \

HEADERS  += mainwindow.h \
    qcustomplot.h \
    serialThread.h \

FORMS    += mainwindow.ui
