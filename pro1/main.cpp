#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtGui/QtGui>
#include <QtGui>
#include <QtGui/QPixmap>
#include <QtCore/QCoreApplication>
#include <ui_mainwindow.h>
#include <QDialog>
#include <ui_benchmark1.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForCStrings(codec);
    MainWindow w;
    w.show();

    return a.exec();
}
