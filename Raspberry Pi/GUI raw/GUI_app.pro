#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T15:13:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    writewindow.cpp \
    readwindow.cpp \
    logwindow.cpp \
    readwindow_hall.cpp \
    writewindow_hall.cpp

HEADERS  += mainwindow.h \
    writewindow.h \
    readwindow.h \
    logwindow.h \
    readwindow_hall.h \
    writewindow_hall.h

FORMS    += mainwindow.ui \
    writewindow.ui \
    readwindow.ui \
    logwindow.ui \
    readwindow_hall.ui \
    writewindow_hall.ui

RC_ICONS = /home/pi/GUI_app/gui_app_icon.ico
