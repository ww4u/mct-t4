#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T16:00:52
#
#-------------------------------------------------

QT       += core gui charts xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mct
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION = 0.0.0.0

INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/Include"

INCLUDEPATH += ../include
INCLUDEPATH += ../source/widget
INCLUDEPATH += ../source/wnd
INCLUDEPATH += ../source/device
INCLUDEPATH += ../source/sys
INCLUDEPATH += ../source/model

SOURCES += \
        ../source/main/main.cpp \
        ../source/wnd/mainwindow.cpp \
    ../source/wnd/h2ops.cpp \
    ../source/wnd/h2action.cpp \
    ../source/wnd/aboutdlg.cpp \
    ../source/model/megatablemodel.cpp \
    ../source/model/h2actionmodel.cpp \
    ../source/model/h2actionitem.cpp \
    ../source/model/comboxdelegate.cpp \
    ../source/model/checkdelegate.cpp \
    ../source/widget/megalcdnumber.cpp \
    ../source/widget/megamessagebox.cpp \
    ../source/wnd/h2status.cpp \
    ../source/sys/sysapi.cpp \
    ../source/sys/megaxml.cpp \
    ../source/widget/megasplinechart.cpp \
    ../source/model/diagnosisitem.cpp \
    ../source/model/diagnosismodel.cpp \
    ../source/model/errmgritem.cpp \
    ../source/model/errmgrmodel.cpp \
    ../source/model/debugitem.cpp \
    ../source/model/debugmodel.cpp \
    ../source/wnd/h2configuration.cpp \
    ../source/wnd/h2errmgr.cpp \
    ../source/wnd/h2jogmode.cpp \
    ../source/wnd/h2homing.cpp \
    ../source/wnd/helppanel.cpp \
    ../source/wnd/xconfig.cpp \
    ../source/wnd/h2measurement.cpp \
    ../source/widget/megainterface.cpp \
    ../source/mrp/mdatarow.cpp \
    ../source/mrp/mdataset.cpp \
    ../source/wnd/h2product.cpp \
    ../source/wnd/roboconfig.cpp \
    ../source/wnd/xrobo.cpp \
    ../source/wnd/h2robo.cpp \
    ../source/device/bus.cpp \
    ../source/device/device.cpp \
    ../source/device/MegaRobot.cpp \
    ../source/device/mrqDevice.cpp


HEADERS += \
        ../source/wnd/mainwindow.h \
    ../source/wnd/h2ops.h \
    ../source/wnd/h2action.h \
    ../source/wnd/aboutdlg.h \
    ../source/model/megatablemodel.h \
    ../source/model/h2actionmodel.h \
    ../source/model/h2actionitem.h \
    ../source/model/comboxdelegate.h \
    ../source/model/checkdelegate.h \
    ../source/widget/megalcdnumber.h \
    ../source/wnd/h2status.h \
    ../source/widget/megamessagebox.h \
    ../source/sys/sysapi.h \
    ../source/sys/megaxml.h \
    ../source/widget/megasplinechart.h \
    ../source/model/diagnosisitem.h \
    ../source/model/diagnosismodel.h \
    ../source/model/errmgritem.h \
    ../source/model/errmgrmodel.h \
    ../source/model/debugitem.h \
    ../source/model/debugmodel.h \
    ../source/wnd/h2configuration.h \
    ../source/wnd/h2errmgr.h \
    ../source/wnd/h2jogmode.h \
    ../source/wnd/h2homing.h \
    ../source/wnd/helppanel.h \
    ../source/wnd/xconfig.h \
    ../source/wnd/h2measurement.h \
    ../source/widget/megainterface.h \
    ../source/mrp/mdatarow.h \
    ../source/mrp/mdataset.h \
    ../source/wnd/h2product.h \
    ../source/wnd/roboconfig.h \
    ../source/wnd/xrobo.h \
    ../source/wnd/h2robo.h \
    ../source/device/bus.h \
    ../source/device/device.h \
    ../source/device/MegaGateway.h \
    ../source/device/MegaRobot.h \
    ../source/device/mrqDevice.h


RESOURCES += ../source/res/res.qrc

RC_ICONS = ../source/res/image/megarobo.ico

FORMS += \
        ../source/wnd/mainwindow.ui \
    ../source/wnd/h2ops.ui \
    ../source/wnd/h2action.ui \
    ../source/wnd/aboutdlg.ui \
    ../source/wnd/h2status.ui \
    ../source/wnd/h2configuration.ui \
    ../source/wnd/h2errmgr.ui \
    ../source/wnd/h2jogmode.ui \
    ../source/wnd/h2homing.ui \
    ../source/wnd/helppanel.ui \
    ../source/wnd/h2measurement.ui \
    ../source/widget/megainterface.ui \
    ../source/wnd/h2product.ui \
    ../source/wnd/roboconfig.ui

LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc"
LIBS += -lvisa32

LIBS += -L"../3rdlib"
LIBS += -llibws2_32 -llibiphlpapi

