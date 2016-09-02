#include "action.h"

Action::Action(TypeAction typeAction, QString nomAction, float nbS, int para)
{
    this->type = typeAction;
    this->nomAction = nomAction;
    this->nbS = nbS;
    this->para = para;
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

int Action::getPara()
{
    return para;
}

QString Action::getCommande()
{
    if (para == -1)
        return  QString::number(static_cast<int>(type));
    else
        return QString::number(static_cast<int>(type)) + "," + QString::number(para) + ",";
}
