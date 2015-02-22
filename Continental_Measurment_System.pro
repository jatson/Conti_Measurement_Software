#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T10:55:46
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Continental_Measurment_System
TEMPLATE = app


SOURCES += main.cpp\
    measuringwindow.cpp \
    widgeta.cpp \
    widgetb.cpp \
    signalselect.cpp \
    MDFBaseData.cpp\
    MDFCCLinear.cpp\
    MDFCG.cpp\
    MDFChannel.cpp\
    MDFConversion.cpp\
    MDFDG.cpp\
    MDFHeader.cpp\
    MDFID.cpp\
    MDFLib.cpp\
    MDFTX.cpp \
    MDFPR.cpp \
    MDFCC.cpp \
    MDFCCTextTable.cpp \
    signalchart.cpp \
    mysignal.cpp \
    signallabel.cpp \
    colorchangedialog.cpp \
    mdffileinfodialog.cpp \
    opensavedialog.cpp


HEADERS  += measuringwindow.h \
    widgeta.h \
    widgetb.h \
    signalselect.h \
    MDFBaseData.h\
    MDFData.h\
    MDFCCLinear.h\
    MDFCG.h\
    MDFChannel.h\
    MDFConversion.h\
    MDFDG.h\
    MDFHeader.h\
    MDFID.h\
    MDFLib.h\
    MDFTX.h \
    MDFPR.h \
    MDFCC.h \
    MDFCCTextTable.h \
    signalchart.h \
    mysignal.h \
    signallabel.h \
    colorchangedialog.h \
    mdffileinfodialog.h \
    opensavedialog.h


FORMS    += measuringwindow.ui \
    widgeta.ui \
    widgetb.ui \
    signalselect.ui \
    colorchangedialog.ui \
    mdffileinfodialog.ui \
    opensavedialog.ui

RESOURCES += \
    MyResources.qrc
