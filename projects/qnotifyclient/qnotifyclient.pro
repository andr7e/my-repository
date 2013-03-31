#-------------------------------------------------
#
# Project created by QtCreator 2013-03-31T15:00:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnotifyclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lnotifyqwrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lnotifyqwrapper
else:symbian: LIBS += -lnotifyqwrapper
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lnotifyqwrapper

INCLUDEPATH += $$PWD/../../../../usr/include/libnotifyqwrapper
DEPENDPATH += $$PWD/../../../../usr/include/libnotifyqwrapper
