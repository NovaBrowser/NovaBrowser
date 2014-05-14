#-------------------------------------------------
#
# Project created by QtCreator 2014-01-07T17:30:11
#
#-------------------------------------------------

QT       += core gui
QT += xmlpatterns
QT += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

TARGET = NovaBrowser_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    apptab.cpp \
    browsetab.cpp \
    sidebar.cpp \
    sec_mainview.cpp \
    sec_apptab.cpp \
    sec_browsetab.cpp \
    nbcookiejar.cpp \
    nbhistory.cpp \
    qwmessagebox.cpp \
    qwwindow.cpp \
    nbjsapiobject.cpp

HEADERS  += mainview.h \
    apptab.h \
    browsetab.h \
    sidebar.h \
    sec_mainview.h \
    sec_apptab.h \
    sec_browsetab.h \
    nbcookiejar.h \
    nbhistory.h \
    qwmessagebox.h \
    qwwindow.h \
    nbjsapiobject.h

RESOURCES += \
    application.qrc
