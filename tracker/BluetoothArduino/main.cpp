#include <QCoreApplication>
#include "device.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Device d;
    d.scan();
    //qDebug() << devices.at(0).address();

    return a.exec();
}
