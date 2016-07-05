#ifndef DEVICE_H
#define DEVICE_H
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QLowEnergyController>
#include <QTimer>
#include <QFile>
#include <QDebug>


class Device : public QObject
{
    Q_OBJECT
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QLowEnergyController* controller;
    QLowEnergyService *service;
    QLowEnergyCharacteristic positionCharacteristic;
    const QString key = "3752c0a0-0d25-11e6-97f5-0002a5d5c51c";
    QFile* file;
    int cptData;
    QString paquets;
public:
    Device();
    void scan();
public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void deviceDisconnected();
    void serviceScanDone(QBluetoothUuid serviceUuid);
    void deviceConnected();
    void serviceDetailsDiscovered(QLowEnergyService::ServiceState);
    void positionCharacteristicUpdate(QLowEnergyCharacteristic ch ,QByteArray byteArray);
};

#endif // DEVICE_H
