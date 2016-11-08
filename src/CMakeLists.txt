cmake_minimum_required(VERSION 2.8)

project(mylib)

set(SOURCE_HEADERS
        mwcsv.h
        utils.h
        mwimage.h
        mwresolution.h)

set(SOURCE_FILES
        mwcsv.cpp
        utils.cpp
        mwimage.cpp
        mwresolution.cpp)

# make static library called libmyxrm
# that we are going to link to
# in the root file
add_library(mylib
        STATIC
        ${SOURCE_FILES})