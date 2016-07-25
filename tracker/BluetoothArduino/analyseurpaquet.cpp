#include "analyseurpaquet.h"

AnalyseurPaquet::AnalyseurPaquet()
{

}

TypePaquet AnalyseurPaquet::reconnaitre(QString paquet)
{
    if (paquet.startsWith("null"))
        return TypePaquet::Erreur;
    else if (paquet.startsWith("ag"))
        return TypePaquet::Position;
    else if (paquet.startsWith("r"))
        return TypePaquet::Reconaissance;
}
