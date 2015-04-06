TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    ext \
    src \   
    app


app.depends = ext
app.depends = src

OTHER_FILES += \
    defaults.pri


binary.files += app/mwdcmconverter
binary.path = /opt/mwimage
INSTALLS += binary

