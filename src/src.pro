include(../defaults.pri)

CONFIG   += console

CONFIG   -= app_bundle
CONFIG   -= qt
CONFIG += staticlib


TEMPLATE = lib

TARGET = mwapp

SOURCES += utils.cpp \ 
    mwimage.cpp \
    mwresolution.cpp \
    mwcsv.cpp

HEADERS += utils.h \ 
    mwimage.h \
    mwresolution.h \
    mwcsv.h

