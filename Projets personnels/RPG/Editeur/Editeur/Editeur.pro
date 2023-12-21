#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T13:41:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editeur
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        mainwindow_alteration.cpp \
        mainwindow_capacite.cpp \
        mainwindow_carte.cpp \
        mainwindow_effet.cpp \
        mainwindow_evenement.cpp \
        mainwindow_groupemonstres.cpp \
        mainwindow_heros.cpp \
        mainwindow_magasin.cpp \
        mainwindow_monstre.cpp \
        mainwindow_objet.cpp \
        mainwindow_tileset.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/ -lJeuLib -lJeuES
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/ -lJeuLib -lJeuES

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/libJeuLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/libJeuLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../bin/libJeuLib.a
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../bin/libJeuLib.a

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/libJeuES.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/libJeuES.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../bin/libJeuES.a
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../bin/libJeuES.a
