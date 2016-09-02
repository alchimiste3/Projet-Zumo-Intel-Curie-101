QT += core bluetooth gui widgets charts

CONFIG += c++11

TARGET = InterfaceArduino
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    device.cpp \
    Madgwick/MadgwickAHRS.cpp \
    MatrixMath/MatrixMath.cpp \
    traitementdonnees.cpp \
    mainwindow.cpp \
    mouvement.cpp \
    action.cpp \
    ajouterwindow.cpp \
    linechart.cpp \
    serie.cpp \
    devicescanner.cpp \
    apprendrewindow.cpp \
    analyseurpaquet.cpp

HEADERS += \
    device.h \
    Madgwick/MadgwickAHRS.h \
    MatrixMath/MatrixMath.h \
    traitementdonnees.h \
    mainwindow.h \
    mouvement.h \
    action.h \
    ajouterwindow.h \
    linechart.h \
    serie.h \
    devicescanner.h \
    apprendrewindow.h \
    analyseurpaquet.h

FORMS += \
    mainwindow.ui \
    ajouterwindow.ui \
    apprendrewindow.ui
