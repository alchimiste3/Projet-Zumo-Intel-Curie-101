#include "action.h"

Action::Action(TypeAction typeAction, QString nomAction, float nbS)
{
    this->type = typeAction;
    this->nomAction = nomAction;
    this->nbS = nbS;

}

TypeAction Action::getTypeAction()
{
    return type;
}

QString Action::getNomAction()
{
    return nomAction;
}

float Action::getNbS()
{
    return nbS;
}
