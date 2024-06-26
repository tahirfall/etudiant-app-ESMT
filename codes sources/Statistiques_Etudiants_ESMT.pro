#-------------------------------------------------
#
# Project created by QtCreator 2023-03-05T13:26:04
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Statistiques_Etudiants_ESMT
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        authentification.cpp \
    controller.cpp \
    user.cpp \
    usermodel.cpp \
    dbaccess.cpp \
    uimain.cpp \
    accueil.cpp \
    etudiant.cpp \
    service.cpp \
    uilist.cpp \
    themewidget.cpp

HEADERS += \
        authentification.h \
    controller.h \
    user.h \
    usermodel.h \
    dbaccess.h \
    uimain.h \
    accueil.h \
    etudiant.h \
    service.h \
    uilist.h \
    themewidget.h

FORMS += \
        authentification.ui \
    accueil.ui \
    uilist.ui \
    themewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
