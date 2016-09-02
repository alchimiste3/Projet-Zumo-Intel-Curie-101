#include "devicescanner.h"

DeviceScanner::DeviceScanner(QBluetoothDeviceDiscoveryAgent *discoveryAgent, QObject *parent) : QObject(parent)
{
    this->discoveryAgent = discoveryAgent;
    rssi = 0;
}

void DeviceScanner::run()
{
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)),  Qt::DirectConnection);
    discoveryAgent->start();
    qDebug() << "run : " << discoveryAgent->errorString();
}

int DeviceScanner::getRssi()
{
    return rssi;
}

void DeviceScanner::deviceDiscovered(QBluetoothDeviceInfo deviceInfo)
{
    discoveryAgent->stop();
    rssi = deviceInfo.rssi();
    qDebug() << "rssi recu" << deviceInfo.rssi();
    emit rssiReady(rssi);
}
