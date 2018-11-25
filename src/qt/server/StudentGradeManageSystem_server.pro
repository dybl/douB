QT += core\
    network
QT -= gui

CONFIG += c++11

TARGET = StudentGradeManageSystem_server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    config.cpp \
    course.cpp \
    environment.cpp \
    user.cpp \
    convey_server.cpp \
    convey_thread.cpp

DISTFILES +=

HEADERS += \
    config.h \
    course.h \
    environment.h \
    user.h \
    include.h \
    convey_server.h \
    convey_thread.h

RC_FILE = icon.rc
