#-------------------------------------------------
#
# Project created by QtCreator 2020-03-15T22:17:12
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SomeThingToSayClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    db/dbutil.cpp \
    login/widget_findPwd.cpp \
    login/widget_login.cpp \
    login/widget_reg.cpp \
    main/widget_main.cpp \
    main/widget_message.cpp \
    menu/widget_select.cpp \
    mysocket.cpp \
    main/widget_post.cpp \
    user.cpp \
    main/widget_set.cpp \
    main/widget_comment.cpp \
    main/widget_userComment.cpp \
    main/widget_mainTop.cpp

HEADERS  += \
    db/dbutil.h \
    login/widget_findPwd.h \
    login/widget_login.h \
    login/widget_reg.h \
    main/widget_main.h \
    main/widget_message.h \
    menu/widget_select.h \
    mysocket.h \
    public.h \
    main/widget_post.h \
    user.h \
    main/widget_set.h \
    main/widget_comment.h \
    main/widget_userComment.h \
    main/widget_mainTop.h

FORMS += \
    login/widget_findPwd.ui \
    login/widget_login.ui \
    login/widget_reg.ui \
    main/widget_message.ui \
    menu/widget_select.ui \
    main/widget_post.ui

RESOURCES += \
    image.qrc
