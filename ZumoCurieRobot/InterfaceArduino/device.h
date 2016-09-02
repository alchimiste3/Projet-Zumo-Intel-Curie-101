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

/**
 * @brief The Device class
 * @todo Mise à jour du rssi en temps réel
 * Cette classe permet de scanner les devices BLE
 */
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
    const QString nomReseauBLE = "RdWrS";
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

    /**
     * @brief decouperPaquet
     * @param paquets
     * Decoupe les paquets recues en fonction de leur type et réalise les traitements liés
     */
    void decouperPaquet(QString paquets);
public slots:
    /**
     * @brief deviceDiscovered
     * @param deviceInfo
     * Permet de traiter un device chaque fois qu'on en detecte un
     * Lorsque le device que l'on cherchait a été trouvé, on arrete le scan et on se connecte au device
     */
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);

    /**
     * @brief deviceDisconnected
     * Les deconnections ne sont pas gérées pour le moment
     */
    void deviceDisconnected();

    /**
     * @brief serviceScanDone
     * Lorsqu'un service a été découvert, on l'identifie et on commence à chercher les informations des characteristic
     */
    void serviceScanDone(QBluetoothUuid serviceUuid);

    /**
     * @brief deviceConnected
     * Lorsqu'on se connecte à un device on  cherche ses services asscociés
     */
    void deviceConnected();

    /**
     * @brief serviceDetailsDiscovered
     * Appelé quand une characteristic associé au service a été découverte, mise en place du système de notification
     */
    void serviceDetailsDiscovered(QLowEnergyService::ServiceState);

    /**
     * @brief positionCharacteristicUpdate
     * @param ch
     * @param byteArray
     * Methode qui permet de traiter les données recues quand on recoit une notification
     */
    void positionCharacteristicUpdate(QLowEnergyCharacteristic ch ,QByteArray byteArray);

    /**
     * @brief envoyerCommande
     * @param commande
     * Envoyer une commande au robot par Bluetooth en utilisant la characteristic correspondant à keyCh2
     */
    void envoyerCommande(QString commande);

    /**
     * @return
     * Renvoie le temps écoulé depuis le lancement de l'application
     * Chaque point sur le graphe sera associé à un temps
     */
    int getTempsEcoule();

signals:
    /**
     * @brief majValues
     * Signal émis lorsque l'on veut envoyer les données à Processing, dans l'ordre : yaw,ax,ay,az,vx,vy,vz,px,py,pz
     */
    void majValues(float, float, float, float,float,float,float,float,float,float);

    /**
     * @brief majReconaissance
     * Signal émis lors de la reconaisse d'un mouvement, le premier paramètre contient le numéro d'action / neurone
     * Le second paramètre contient la durée de l'action
     */
    void majReconaissance(int, int);
};

#endif // DEVICE_H
