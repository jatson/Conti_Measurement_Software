#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T14:28:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Continental_Measurement_System
TEMPLATE = app

FORMS += \
    Continental_Measurement_System/colorchangedialog.ui \
    Continental_Measurement_System/mdffileinfodialog.ui \
    Continental_Measurement_System/measuringwindow.ui \
    Continental_Measurement_System/signalselect.ui \
    Continental_Measurement_System/widgetb.ui \
    Continental_Measurement_System/widgeta.ui

HEADERS += \
    Continental_Measurement_System/colorchangedialog.h \
    Continental_Measurement_System/mdffileinfodialog.h \
    Continental_Measurement_System/measuringwindow.h \
    Continental_Measurement_System/mysignal.h \
    Continental_Measurement_System/signalchart.h \
    Continental_Measurement_System/signallabel.h \
    Continental_Measurement_System/signalselect.h \
    Continental_Measurement_System/MDF/MDFBaseData.h \
    Continental_Measurement_System/MDF/MDFCC.h \
    Continental_Measurement_System/MDF/MDFCCLinear.h \
    Continental_Measurement_System/MDF/MDFCCTextTable.h \
    Continental_Measurement_System/MDF/MDFCG.h \
    Continental_Measurement_System/MDF/MDFChannel.h \
    Continental_Measurement_System/MDF/MDFConversion.h \
    Continental_Measurement_System/MDF/MDFData.h \
    Continental_Measurement_System/MDF/MDFDG.h \
    Continental_Measurement_System/MDF/MDFHeader.h \
    Continental_Measurement_System/MDF/MDFID.h \
    Continental_Measurement_System/MDF/MDFLib.h \
    Continental_Measurement_System/MDF/MDFPR.h \
    Continental_Measurement_System/MDF/MDFTX.h \
    Continental_Measurement_System/qcustomplot/qcustomplot.h \
    Continental_Measurement_System/widgetb.h \
    Continental_Measurement_System/widgeta.h \
    Continental_Measurement_System/modelmanager.h

SOURCES += \
    Continental_Measurement_System/colorchangedialog.cpp \
    Continental_Measurement_System/main.cpp \
    Continental_Measurement_System/mdffileinfodialog.cpp \
    Continental_Measurement_System/measuringwindow.cpp \
    Continental_Measurement_System/mysignal.cpp \
    Continental_Measurement_System/signalchart.cpp \
    Continental_Measurement_System/signallabel.cpp \
    Continental_Measurement_System/signalselect.cpp \
    Continental_Measurement_System/MDF/MDFBaseData.cpp \
    Continental_Measurement_System/MDF/MDFCC.cpp \
    Continental_Measurement_System/MDF/MDFCCLinear.cpp \
    Continental_Measurement_System/MDF/MDFCCTextTable.cpp \
    Continental_Measurement_System/MDF/MDFCG.cpp \
    Continental_Measurement_System/MDF/MDFChannel.cpp \
    Continental_Measurement_System/MDF/MDFConversion.cpp \
    Continental_Measurement_System/MDF/MDFDG.cpp \
    Continental_Measurement_System/MDF/MDFHeader.cpp \
    Continental_Measurement_System/MDF/MDFID.cpp \
    Continental_Measurement_System/MDF/MDFLib.cpp \
    Continental_Measurement_System/MDF/MDFPR.cpp \
    Continental_Measurement_System/MDF/MDFTX.cpp \
    Continental_Measurement_System/qcustomplot/qcustomplot.cpp \
    Continental_Measurement_System/widgetb.cpp \
    Continental_Measurement_System/widgeta.cpp \
    Continental_Measurement_System/modelmanager.cpp

RESOURCES += \
    Continental_Measurement_System/resources/MyResources.qrc

DISTFILES += \
    Continental_Measurement_System/resources/icons/Line Chart.png \
    Continental_Measurement_System/resources/icons/Window Left Panel.png \
    Continental_Measurement_System/resources/icons/Window Performance.png

