TEMPLATE=lib
CONFIG += static
CONFIG += c++11
QT += core

TARGET = ../../../lib/mrx-device

DEFINES += _LIB_DEVICE

win32 {
# visa
INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"
#LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
#LIBS += -lvisa32
#DEFINES += NI_VISA
#DEFINES += ARCH_32
}

INCLUDEPATH += ./libMegaGateway/src

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
    #local.cpp \
    assist.cpp
HEADERS = \ 
    assist.h

#### SDK ####
SOURCES += ./libMegaGateway/src/bus.c \
        ./libMegaGateway/src/device.c \
        ./libMegaGateway/src/errorcode.c \
        ./libMegaGateway/src/megarobot.c \
        ./libMegaGateway/src/mrqdevice.c \
        ./libMegaGateway/src/project.c \
        ./libMegaGateway/src/storage.c \
        ./libMegaGateway/src/system.c


HEADERS += ./libMegaGateway/src/bus.h \
        ./libMegaGateway/src/device.h \
        ./libMegaGateway/src/errorcode.h \
        ./libMegaGateway/src/MegaGateway.h \
        ./libMegaGateway/src/megarobot.h \
        ./libMegaGateway/src/mrqdevice.h \
        ./libMegaGateway/src/platform.h \
        ./libMegaGateway/src/project.h \
        ./libMegaGateway/src/storage.h \
        ./libMegaGateway/src/system.h

linux-arm* {
SOURCES += ./vxi11/vxi11_clnt.c \
            ./vxi11/vxi11_user.c \
            ./vxi11/vxi11_xdr.c
}

