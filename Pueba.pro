#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T15:38:41
#
#-------------------------------------------------

QT       += core gui
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pueba
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pruebas.cpp \
    estructura.cpp \
    botella.cpp \
    hilointerfaz.cpp

HEADERS  += mainwindow.h \
    estructuras.h \
    prueba.h \
    botellas.h \
    hilointerfaz.h

FORMS    += mainwindow.ui \
    botellas.ui

RESOURCES += \
    fila.qrc \
    imagenes.qrc
