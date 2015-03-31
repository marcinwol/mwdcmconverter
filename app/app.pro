

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

TARGET = mwdcmconverter

SOURCES += main.cpp \
    mwdcmconverter.cpp

LIBS +=  ../src/libmwapp.a
LIBS +=  ../ext/libmwext.a

include(../defaults.pri)

#HEADERS +=

HEADERS += \
    mwdcmconverter.h
