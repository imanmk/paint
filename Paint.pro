
CONFIG += qt warn_on
CONFIG += debug
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(printsupport): QT += printsupport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    paintarea.cpp \
    toolbar.cpp

HEADERS += \
    mainwindow.h \
    paintarea.h \
    toolbar.h

RES_DIR = icon

RESOURCES += \
    resource.qrc
