TEMPLATE=lib
QT       += gui widgets
CONFIG += static

TARGET = ../../../../lib/mrx-t4

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
    t4.cpp \
    t4oppanel.cpp \
    config.cpp \
    motorconfig.cpp \
    actiontable.cpp \
    errormgrtable.cpp \
    controllerstatus.cpp \
    traceplot.cpp \
    joint.cpp


HEADERS = \
    t4.h \
    t4oppanel.h \
    config.h \
    motorconfig.h \
    actiontable.h \
    errormgrtable.h \
    controllerstatus.h \
    traceplot.h \
    joint.h

FORMS += \
    t4oppanel.ui \
    config.ui \
    motorconfig.ui \
    actiontable.ui \
    errormgrtable.ui \
    controllerstatus.ui \
    traceplot.ui \
    joint.ui

RESOURCES += ../../../res/res.qrc

