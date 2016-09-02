#include <QApplication>
#include "device.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Device d;
    d.scan();
    MainWindow m(&d);
    m.show();
    //qDebug() << devices.at(0).address();

    return a.exec();
}
