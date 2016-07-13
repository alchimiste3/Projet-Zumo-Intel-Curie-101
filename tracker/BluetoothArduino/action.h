#ifndef ACTION_H
#define ACTION_H
#include <QString>

typedef enum TypeAction {
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
public:
    Action(TypeAction typeAction, QString nomAction,  float nbS);
    TypeAction getTypeAction();
    QString getNomAction();
    float getNbS();
};

#endif // ACTION_H
