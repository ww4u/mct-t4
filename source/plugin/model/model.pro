TEMPLATE=lib
QT       += gui widgets
CONFIG += static

TARGET = ../../../../lib/model

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

SOURCES = \
    model.cpp \
    diagnosistable.cpp \
    errmgrmodel.cpp \
    delegate\comboxdelegate.cpp \
    delegate\checkdelegate.cpp \
    delegate\dspindelegate.cpp \
    megaloglistmodel.cpp \
    widget/logoutwidget.cpp \
    delegate/ispindelegate.cpp


HEADERS = \
    model.h \
    diagnosistable.h \
    errmgrmodel.h \
    delegate\comboxdelegate.h \
    delegate\checkdelegate.h \
    delegate\dspindelegate.h \
    megaloglistmodel.h \
    widget/logoutwidget.h \
    delegate/ispindelegate.h





