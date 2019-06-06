#-------------------------------------------------
#
# Project created by QtCreator 2019-04-13T03:00:13
#
#-------------------------------------------------

QT       += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arkanoid
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
    brick.cpp \
    gameobject.cpp \
    main.cpp \
    mainwindow.cpp \
    ball.cpp \
    helper.cpp \
    board.cpp \
    map.cpp \
    movablecircle.cpp \
    movableobject.cpp \
    movablerectangle.cpp \
    colorfulobject.cpp \
    destroyableobject.cpp \
    vector2d.cpp

HEADERS += \
    brick.h \
    constants.h \
    gameobject.h \
    mainwindow.h \
    ball.h \
    helper.h \
    board.h \
    map.h \
    movablecircle.h \
    movableobject.h \
    movablerectangle.h \
    colorfulobject.h \
    destroyableobject.h \
    vector2d.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
