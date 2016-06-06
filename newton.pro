#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T14:05:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newton
TEMPLATE = app

INCLUDEPATH += /usr/lib
INCLUDEPATH += /usr/local/boost/boost_1_50_0
INCLUDEPATH += /usr/local/lib

#LIBS += -L/usr/lib -lboost_program_options
LIBS += -L/usr/lib -lmpfr
LIBS += -L/usr/lib -lgmp

CONFIG += c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    newton.cpp

HEADERS  += mainwindow.h \
    newton.h \
    Interval.h

FORMS    += mainwindow.ui
