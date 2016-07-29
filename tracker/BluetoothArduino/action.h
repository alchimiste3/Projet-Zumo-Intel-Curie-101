#ifndef ACTION_H
#define ACTION_H
#include <QString>
#include <QDebug>

/**
 *  @enum Enumeration représentant le type de l'action
 *
 */
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

/**
 * @brief The Action class
 * La classe Action permet de représenter un mouvement que le robot doit effectuer
 */
class Action
{
    TypeAction type;
    float nbS;
    QString nomAction;
    int para;
public:
    Action(TypeAction typeAction, QString nomAction,  float nbS = 0, int para = -1);
    /**
     * @brief getTypeAction
     * @return
     * Permet de récupérer le type de mouvement à effectuer
     */
    TypeAction getTypeAction();
    /**
     * @brief getNomAction
     * @return
     *
     * Permet de récupérer le nom de l'action
     */
    QString getNomAction();
    /**
     * @brief getNbS
     * @return
     * Permet de récupérer la durée de l'action à effectuer
     */
    float getNbS();
    /**
     * @brief getPara
     * @return
     * Permet de récupérer le paramètre de l'action, -1 s'il n'y en a pas
     */
    int getPara();
    /**
     * @brief getCommande
     * @return
     * Permet de récupérer la commande à envoyer au robot au format texte
     */
    QString getCommande();
};


#endif // ACTION_H
