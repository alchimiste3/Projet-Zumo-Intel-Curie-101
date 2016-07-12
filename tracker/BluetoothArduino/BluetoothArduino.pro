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
    mainwindow.cpp \
    mouvement.cpp \
    action.cpp \
    ajouterwindow.cpp

HEADERS += \
    device.h \
    Madgwick/MadgwickAHRS.h \
    MatrixMath/MatrixMath.h \
    traitementdonnees.h \
    mainwindow.h \
    mouvement.h \
    action.h \
    ajouterwindow.h

FORMS += \
    mainwindow.ui \
    ajouterwindow.ui
