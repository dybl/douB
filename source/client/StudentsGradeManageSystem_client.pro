#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T19:10:41
#
#-------------------------------------------------

QT  += core gui\
    network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentsGradeManageSystem
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    mainwindow_student.cpp \
    mainwindow_teacher.cpp \
    envir_widget.cpp \
    fun.cpp \
    convey.cpp \
    mainwindow_admin.cpp \
    information_course.cpp \
    information_user.cpp

HEADERS  += \
    login.h \
    include.h \
    mainwindow_student.h \
    mainwindow_teacher.h \
    envir_widget.h \
    fun.h \
    convey.h \
    model_struct.h \
    mainwindow_admin.h \
    information_course.h \
    information_user.h

FORMS    += \
    login.ui \
    mainwindow_student.ui \
    mainwindow_teacher.ui \
    mainwindow_admin.ui \
    information_course.ui \
    information_user.ui

CONFIG += c++11

DISTFILES +=

RESOURCES += \
    resourse.qrc

RC_FILE = icon.rc 
