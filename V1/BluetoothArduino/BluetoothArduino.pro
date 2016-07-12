QT += core bluetooth gui widgets

CONFIG += c++11

TARGET = BluetoothArduino
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    device.cpp \
    Madgwick/MadgwickAHRS.cpp \
    MatrixMath/MatrixMath.cpp \
    traitementdonnees.cpp \
    mainwindow.cpp

HEADERS += \
    device.h \
    Madgwick/MadgwickAHRS.h \
    MatrixMath/MatrixMath.h \
    traitementdonnees.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
