QT += core gui widgets xml network

CONFIG += c++11
TEMPLATE += app

TARGET = MRHT_SDK_Demo
VERSION = 00.01.00.00

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


################### SDK ###################
unix {
INCLUDEPATH += ../src/lib/vxi11
HEADERS += ../../src/vxi11/vxi11.h
HEADERS += ../../src/vxi11/vxi11_user.h
SOURCES += ../../src/vxi11/vxi11_clnt.c
SOURCES += ../../src/vxi11/vxi11_user.c
SOURCES += ../../src/vxi11/vxi11_xdr.c
}

INCLUDEPATH += ../../src/
SOURCES += ./main.cpp \
        ../../src/bus.c \
        ../../src/device.c \
        ../../src/errorcode.c \
        ../../src/megarobot.c \
        ../../src/mrqdevice.c \
        ../../src/project.c \
        ../../src/storage.c \
        ../../src/system.c \
    thread/xthread.cpp \
    sysapi.cpp

HEADERS += \
        ../../src/bus.h \
        ../../src/device.h \
        ../../src/errorcode.h \
        ../../src/MegaGateway.h \
        ../../src/megarobot.h \
        ../../src/mrqdevice.h \
        ../../src/platform.h \
        ../../src/project.h \
        ../../src/storage.h \
        ../../src/system.h \
    thread/xthread.h \
    sysapi.h

################### LIBS ###################
win32 {
INCLUDEPATH += "../../win"
DEPENDPATH += "../../win"
LIBS += -L"../../win" -llibws2_32
LIBS += -L"../../win" -llibiphlpapi
LIBS += -L"../../win" -lvisa32
}


################### QtGUI ###################
INCLUDEPATH += ./mainwindow
INCLUDEPATH += ./widget
INCLUDEPATH += ./dialog
INCLUDEPATH += ./thread

SOURCES +=  \
    mainwindow/mainwindow.cpp \
    widget/mainwidget.cpp

HEADERS += \
    mainwindow/mainwindow.h \
    widget/mainwidget.h

FORMS += \
    mainwindow/mainwindow.ui \
    widget/mainwidget.ui











