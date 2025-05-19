#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngineCore/QWebEngineSettings>
#include <QCoreApplication>
int main(int argc, char *argv[])
{
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-gpu --disable-software-rasterizer");// Tambahkan di main.cpp
qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9222");
 QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-gpu");
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    // Tambahkan sebelum QApplication

}
