# Tambahkan komponen Qt yang diperlukan

QT += core gui widgets serialport printsupport charts webenginewidgets

INCLUDEPATH += $$PWD/widgets $$PWD/utils
DEFINES += QT_NO_VERSION_TAGGING

# Sumber file
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    maps.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h

FORMS += mainwindow.ui
RESOURCES += \
    resources.qrc
