# Tambahkan komponen Qt yang diperlukan
QT += core gui widgets printsupport serialport
QT += webenginewidgets
INCLUDEPATH += $$PWD/widgets $$PWD/utils
DEFINES += QT_NO_VERSION_TAGGING

# Sumber file
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h

FORMS += mainwindow.ui
