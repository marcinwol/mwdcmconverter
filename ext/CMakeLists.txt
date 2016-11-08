cmake_minimum_required(VERSION 2.8)

# now build myext library from other files
project(myext)

set(SOURCE_HEADERS
        filesignature.h.h
        format.h
        ostream.h)

set(SOURCE_FILES
        filesignature.cpp
        format.cc
        ostream.cc)

# make static library called libmyxrm
# that we are going to link to
# in the root file
add_library(myext
        STATIC
        ${SOURCE_FILES})


