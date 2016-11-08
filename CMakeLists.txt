cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(PROJECT_NAME
        dcmconverter)

project(${PROJECT_NAME})

SET(CMAKE_INSTALL_PREFIX /opt/dcm)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++14 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=false")


# find boost
find_package(Boost COMPONENTS
        system
        filesystem
        thread
        date_time
        chrono
        regex
        serialization
        program_options
        date_time
        REQUIRED)

# include boost headers
include_directories(${Boost_INCLUDE_DIRS})


# set location of magick7 static libraries
set(MAGICK7_LIBS_DIR
        /opt/magick7/lib)

# set location of magick7 headers
set(MAGICK7_HEADERS_DIR
        /opt/magick7/include)

set(MAGICK7_REF_LIBS
        jbig lcms2 tiff freetype  jpeg  lqr-1 glib-2.0 png12 fftw3 pango-1.0
        djvulibre    fontconfig freetype  wmflite  Xext Xt   SM ICE X11  lzma
        gobject-2.0 cairo  pangocairo-1.0 openjp2
        bz2 IlmImf Imath Half Iex IexMath IlmThread pthread xml2 gvc cgraph
        cdt z  m gomp m)

# include monero headers
include_directories(
        ${MAGICK7_HEADERS_DIR}/ImageMagick-7)


add_library(Magick++ STATIC IMPORTED)
set_property(TARGET Magick++
        PROPERTY IMPORTED_LOCATION ${MAGICK7_LIBS_DIR}/libMagick++-7.Q16.a)


add_library(MagickCore STATIC IMPORTED)
set_property(TARGET MagickCore
        PROPERTY IMPORTED_LOCATION ${MAGICK7_LIBS_DIR}/libMagickCore-7.Q16.a)

add_library(MagickWand STATIC IMPORTED)
set_property(TARGET MagickWand
        PROPERTY IMPORTED_LOCATION ${MAGICK7_LIBS_DIR}/libMagickWand-7.Q16.a)


# add ext/ subfolder
add_subdirectory(ext/)

# add src/ subfolder
add_subdirectory(src/)

set(SOURCE_FILES
        app/main.cpp
        app/dcmconverter.cpp)

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        myext
        mylib
        Magick++
        MagickWand
        MagickCore
        ${Boost_LIBRARIES}
        ${MAGICK7_REF_LIBS}
        pthread)

install(TARGETS ${PROJECT_NAME} DESTINATION /opt/mwdcm)