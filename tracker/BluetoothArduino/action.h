#ifndef ACTION_H
#define ACTION_H
#include <QString>
#include <QDebug>

typedef enum TypeAction {
    ChangerVitesse = 0,
    Avancer = 1,
    Reculer = 2,
    TournerDroite = 3,
    TournerGauche = 4,
    Arreter = 5,
    Accelerer = 6,
    Ralentir = 7
} TypeAction;

class Action
{
    TypeAction type;
    float nbS;
    QString nomAction;
    int para;
public:
    Action(TypeAction typeAction, QString nomAction,  float nbS, int para = -1);
    TypeAction getTypeAction();
    QString getNomAction();
    float getNbS();
    int getPara();
    QString getCommande();
};


#endif // ACTION_H
