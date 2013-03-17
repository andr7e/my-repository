#-------------------------------------------------
#
# Project created by QtCreator 2012-12-26T18:47:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qSpaceShip2D
TEMPLATE = app


SOURCES += main.cpp \
    ship.cpp \
    game2d.cpp \
    levels.cpp \
    unit.cpp

HEADERS  += \
    unit.h \
    ship.h \
    enemy.h \
    game2d.h
