#ifndef ANALYSEURPAQUET_H
#define ANALYSEURPAQUET_H

#include <QObject>

/**
  * @enum TypePaquet Correspond au type de paquet reçu par BLE coté client
  */
typedef enum TypePaquet {
    Position = 0,
    Erreur = 1,
    Reconaissance = 2,
    Unknown = 3
} TypePaquet;

class AnalyseurPaquet
{
public:
    AnalyseurPaquet();
    /**
     * @brief reconnaitre
     * @param paquet
     * @return Type de paquet
     * A partir du paquet passé en paramètre détecte le type correspondant
     */
    TypePaquet reconnaitre(QString paquet);
};

#endif // ANALYSEURPAQUET_H
