#ifndef ACTION_H
#define ACTION_H

typedef enum TypeAction {
    Avancer,
    Reculer,
    TournerDroite,
    TournerGauche
} TypeAction;

class Action
{
    TypeAction type;
    int nbMs;
public:
    Action(TypeAction typeAction, int nbMs);
    TypeAction getTypeAction();
    int getNbMs();
};

#endif // ACTION_H
