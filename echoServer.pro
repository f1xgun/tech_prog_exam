QT -= gui

QT += network #Для работы с сетью

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    functions.cpp \
        main.cpp \
    mytcpserver.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    functions.h \
    mytcpserver.h

TARGET = hallServer