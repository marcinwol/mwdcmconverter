

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

TARGET = mwdcmconverter

SOURCES += main.cpp

LIBS +=  ../src/libmwapp.a
LIBS +=  ../ext/libmwext.a

include(../defaults.pri)

#HEADERS +=
