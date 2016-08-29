#ifndef DEVICESCANNER_H
#define DEVICESCANNER_H

#include <QBluetoothDeviceDiscoveryAgent>
#include <QThread>
#include <QObject>
#include <QDebug>

/**
 * @brief The DeviceScanner class
 * @deprecated Effectuer un nouveau scan pour mettre à jour le rssi est lent et nécessite d'être déconnecté
 */
class DeviceScanner : public QObject
{
    Q_OBJECT
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    int rssi;
public:
    explicit DeviceScanner(QBluetoothDeviceDiscoveryAgent* discoveryAgent,QObject *parent = 0);
    int getRssi();
    void run();

signals:
    void rssiReady(int rssi);
public slots:
    void deviceDiscovered(QBluetoothDeviceInfo deviceInfo);
};

#endif // DEVICESCANNER_H
