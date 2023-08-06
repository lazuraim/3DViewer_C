QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_affine.c \
    ../s21_parser.c \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    lib/3rdParty/giflib/dgif_lib.c \
    lib/3rdParty/giflib/egif_lib.c \
    lib/3rdParty/giflib/gif_err.c \
    lib/3rdParty/giflib/gif_font.c \
    lib/3rdParty/giflib/gif_hash.c \
    lib/3rdParty/giflib/gifalloc.c \
    lib/3rdParty/giflib/quantize.c \
    lib/gifimage/qgifimage.cpp

HEADERS += \
    ../s21_3DViewer.h \
    ../s21_3DViewer.h \
    mainwindow.h \
    myopenglwidget.h \
    lib/3rdParty/giflib/gif_hash.h \
    lib/3rdParty/giflib/gif_lib.h \
    lib/3rdParty/giflib/gif_lib_private.h \
    lib/gifimage/qgifglobal.h \
    lib/gifimage/qgifimage.h \
    lib/gifimage/qgifimage_p.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    lib/gifimage/gifimage.pro

DISTFILES += \
    lib/3rdParty/giflib/AUTHORS \
    lib/3rdParty/giflib/COPYING \
    lib/3rdParty/giflib/README \
