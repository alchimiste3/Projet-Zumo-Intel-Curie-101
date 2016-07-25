#ifndef ANALYSEURPAQUET_H
#define ANALYSEURPAQUET_H

#include <QObject>

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
    TypePaquet reconnaitre(QString paquet);
};

#endif // ANALYSEURPAQUET_H
