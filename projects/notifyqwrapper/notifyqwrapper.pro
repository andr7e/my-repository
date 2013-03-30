#-------------------------------------------------
#
# Project created by QtCreator 2013-03-30T11:56:59
#
#-------------------------------------------------


TARGET = notifyqwrapper
TEMPLATE = lib

DEFINES += NOTIFYQWRAPPER_LIBRARY

SOURCES += qsysnotify.cpp \
    proxy.cpp

HEADERS += qsysnotify.h\
    proxy.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE11E8F1B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = notifyqwrapper.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lnotify
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lnotify
else:symbian: LIBS += -lnotify
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lnotify

INCLUDEPATH += $$PWD/../../../../usr/include/libnotify
DEPENDPATH += $$PWD/../../../../usr/include/libnotify
