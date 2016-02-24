#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T23:53:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextureMapping
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    vector3d.cpp \
    camera.cpp \
    vertex.cpp \
    mesh.cpp \
    matrix3x3.cpp \
    vector2d.cpp

HEADERS  += widget.h \
    vector3d.h \
    camera.h \
    vertex.h \
    mesh.h \
    matrix3x3.h \
    vector2d.h

FORMS    += widget.ui


QMAKE_CXXFLAGS += -openmp
#LIBS += -openmp

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

#add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_CXXFLAGS += -O3

CONFIG += c++11

DISTFILES +=
