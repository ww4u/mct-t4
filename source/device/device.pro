TEMPLATE=lib
CONFIG += static
QT += core

TARGET = ../../../lib/mrx-device


win32 {
# visa
INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"
#LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
#LIBS += -lvisa32
#DEFINES += NI_VISA
#DEFINES += ARCH_32
}

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
    local.cpp \
    assist.cpp
HEADERS = \ 
    assist.h
    

