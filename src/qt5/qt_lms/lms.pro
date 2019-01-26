QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lms
TEMPLATE = app


SOURCES += main.cpp\
        user_login.cpp \
    admin_form.cpp \
    reader_form.cpp \
    connect_database.cpp \
    add_book_form.cpp \
    alter_book_form.cpp \
    add_reader_form.cpp \
    alter_reader_form.cpp \
    delete_book_form.cpp \
    delete_reader_form.cpp \
    delete_ensure_form.cpp \
    reader_id_form.cpp \
    book_id_form.cpp \
    user_register_form.cpp

HEADERS  += user_login.h \
    admin_form.h \
    reader_form.h \
    connect_database.h \
    add_book_form.h \
    alter_book_form.h \
    add_reader_form.h \
    alter_reader_form.h \
    delete_book_form.h \
    delete_reader_form.h \
    delete_ensure_form.h \
    reader_id_form.h \
    book_id_form.h \
    user_register_form.h

FORMS    += user_login.ui \
    admin_form.ui \
    reader_form.ui \
    add_book_form.ui \
    alter_book_form.ui \
    add_reader_form.ui \
    alter_reader_form.ui \
    delete_book_form.ui \
    delete_reader_form.ui \
    delete_ensure_form.ui \
    reader_id_form.ui \
    book_id_form.ui \
    user_register_form.ui
