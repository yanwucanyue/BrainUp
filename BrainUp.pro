#-------------------------------------------------
#
# Project created by QtCreator 2013-06-29T17:46:17
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrainUp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/CRecordData.cpp \
    controller/CRecordCtrl.cpp \
    model/CRecognizeDate.cpp

HEADERS  += mainwindow.h \
    model/CRecordData.h \
    controller/CRecordCtrl.h \
    model/CRecognizeDate.h

FORMS    += mainwindow.ui
