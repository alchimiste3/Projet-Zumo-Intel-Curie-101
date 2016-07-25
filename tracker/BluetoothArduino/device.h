#ifndef DEVICE_H
#define DEVICE_H
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothUuid>
#include <QLowEnergyService>
#include <QLowEnergyController>
#include <QTimer>
#include <QFile>
#include <QThread>
#include <QDebug>
#include <QTime>
#include "devicescanner.h"
#include "traitementdonnees.h"
#include "analyseurpaquet.h"

class Device : public QObject
{
    Q_OBJECT
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothDeviceInfo device;
    QLowEnergyController* controller;
    QLowEnergyService *service;
    QLowEnergyService *motionService;
    QLowEnergyCharacteristic positionCharacteristic;
    const QString keyCh1 = "3752c0a0-0d25-11e6-97f5-0002a5d5c51c";
    const QString keyCh2 = "3752c0a0-0d25-11e6-97f5-0002a5d5c51d";
    QFile* file;
    int cptData;
    QString paquets;
    TraitementDonnees* traitement;
    QTime timer;
    int ancienTemps;
    QString derniereCommandeEnvoye;
public:
    Device();
    void scan();
    void decouperPaquet(QString paquets);
public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void deviceDisconnected();
    void serviceScanDone(QBluetoothUuid serviceUuid);
    void deviceConnected();
    void serviceDetailsDiscovered(QLowEnergyService::ServiceState);
    void motionServiceDetailsDiscovered(QLowEnergyService::ServiceState);
    void positionCharacteristicUpdate(QLowEnergyCharacteristic ch ,QByteArray byteArray);
    void envoyerCommande(QString commande);
    int getTempsEcoule();
    void rssiUpdate(int rssi);
signals:
    void majValues(float, float, float, float,float,float,float,float,float,float);
};

#endif // DEVICE_H
