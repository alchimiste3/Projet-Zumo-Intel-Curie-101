#include "action.h"

Action::Action(TypeAction typeAction, int nbMs)
{
    this->type = typeAction;
    this->nbMs = this->nbMs;

}

TypeAction Action::getTypeAction()
{
    return type;
}

int Action::getNbMs()
{
    return nbMs;
}
