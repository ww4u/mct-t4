TEMPLATE=lib
QT       += gui widgets
CONFIG += static

TARGET = ../../../../lib/xplugin

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
    xplugin.cpp \
    xpage.cpp \
    xpluginintf.cpp \
    xpluginworkingthread.cpp

HEADERS = \
    xplugin.h \
    xpage.h \
    xpluginintf.h \
    xpluginworkingthread.h



