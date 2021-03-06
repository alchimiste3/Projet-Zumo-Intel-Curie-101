# Projet-Zumo-Intel-Curie-101

### Auteurs :
* Quentin Laborde (Étudiant en quatrième année à Polytech Nice Sophia en Science informatique)
* Clément Sibut (Étudiant en quatrième année à Polytech Nice Sophia en Science informatique)

## Presentation du projet

Projet lancer au cour d'un stage en binome pendant l'ete 2016 au LEAT.

L’objectif du stage est de mettre en place un petit groupe d'objets mobile (des robots avec des cartes Curie) connecter entre eux et s'organisant autour d’un point centrale. Chacun de ces robots doit pouvoir apprendre et reconnaître son environnement et pouvoir retrouver son “chemin” grâce à l’apprentissage. Le but est de faire parcourir l’environnement par les robots en couvrant le plus de surface en la plus grande autonomie possible vise à vie de l'utilisateur qui pourra interagir avec les robots à partir d’un ordinateur.
Les applications à long terme sont très variés et dans de nombreux domaine différent  comme par exemple la surveillance, la cartographie, l’exploration, etc. 

Ce document indique comment installer et initialiser le matériel pour faire fonctionner le système. Si vous voulez plus de précision sur le contenu, vous pouvez consulter directement le code commenté ou lire nos deux rapports de stage.

## Les Parties

Il y a 3 parties dans le projet repartie dans 3 dossier :

1. La programmation de la carte Arduino (et du robot).
2. L'interface utilisateur sur ordi en Qt.
3. L'affichage graphique du déplacement du robot avec processing.

Ajouter à ça, on a des libs C++ pour la partie Arduino et un dossier contenant des tests, des essaye et des versions antérieures de notre code.

## Pour installer : 

Cette partie vous explique comment installer notre projet pour chaques parties.

### Les pres-requis

Pour installer et utiliser notre projet, il y a plusieur pres-requis a avoir

Materiel utiliser: Un "robot Zumo for Arduino", une carte Intel Curie 101.
Les logiciel utiliser : Arduino IDE, QtCreator et Processing.
 
 
### Arduino

Pour instaler la partie Arduino et lancer le robot (partie mobile du syteme):

-Copier/coller les librairie c++ du dossier libArduino dans les libraire de Arduino IDE (le plus souvant elle est dans le dossier personnelle).

-Lancer l'IDE Arduino en avec un double click sur le fichier .ino. 


Maintenant, vous devais paramètrer Arduino pour utiliser la carte : le plus simple est de suivre le debut du TD vue en cour de Capteurs/Actionneurs : 

> Install the Intel Curie Board,

> Install the associate libraries.

> First of all, you'll need to install the Intel® Curie Boards core using the Arduino Boards Manager.
> This is found in the Tools menu under Boards -> Boards Manager, where you can search 'Intel Curie
> Boards'.

> On Linux, some distributions need to be configured to perform the upload. After installing the core,
> execute:
> sudo ~/.arduino15/packages/Intel/tools/arduino101load/1.6.4+1.18/scripts/create_dfu_udev_rule

Ensuite, dans l'IDE, sélectionner (dans Outils) le bon type de carte (Genuino 101) et le bon programmateur (AVRISP mkll). Compiler le code puis tranferer-le dans la carte grace au câble USB (normalement le bon port est déjà sélectionne mais il faut parfois le changer). Clipser la carte sur le robot et démarrez-le, le robot doit être immobile lors de l'allumage pour que l'IMU s'initialise correctement (vous pourrai par la suite laisser le carte sur la robot quand vous la brancher sur le port USB).

Après avoir démarré le robot, attender quelques secondes puis lancer l'interface utilisateur (Application QT) qui va se connecter au service BLE du robot. Maintenant, vous pouvez contrôler le robot à partir de l'interface.

Si vous laissez le robot brancher par USB, vous pouvez afficher des lignes de texte lors de l'exécution : après le transférer du code, attender quelques secondes puis lancer le moniteur (dans Outils). vous pouvez voir en direct l'exécution de la boucle (loop) Arduino. Pour utiliser le moniteur et éviter des bugs, vous devez transférer le programme avec le robot déjà allumer et brancher au port USB.

### Application QT

> Installer Qt ainsi que le module Qt Chart

> Ouvrir le .pro dans QT Creator

> Demarrer la carte 

> Démarrer le projet dans QT Creator

Pour générer la documentation, il faut d'abord installer le paquet doxygen puis executer la commande doxygen dans le repertoire

### Compiler l'application QT pour Android

> Installer Ant et Java s'ils ne sont pas déjà installés

> Installer le Android SDK

> Installer le Android NDK

> Mettre à jour le SDK et choisir la version la plus récente avec la commande
./android update sdk

> Installer les dépendances suivantes : 
sudo apt-get install libstdc++6:i386 libgcc1:i386 zlib1g:i386 libncurses5:i386
sudo apt-get install libsdl1.2debian:i386

> Configuration de Qt Creator 
Aller dans Outils > Options > Android
Localiser Java, le SDK et le NDK
Aller dans l'onglet Projet > Ajouter un kit > Choisir Android
Maintenant, juste en dessus de la fleche verte pour compiler/exécuter, il est possible de choisir le kit à utiliser

> Configuration du téléphone : Activation du mode Debug
Aller dans Paramètres > Système > A propos de l'appareil, Appuyer 7 fois sur "Numéro de version"
Aller dans Paramètres > Système > Options de développement, Activer le débogage USB

> Compilation pour Android
Il suffit maintenant de brancher le téléphone, démarrer la compilation, le choisir dans la liste et saisir le code PIN

Pour plus de détails aller ici : http://doc.qt.io/qt-5/androidgs.html

### Proccesing

-lancer le fihcier .pde avec Processing

## Les truc a faire

Bien sur, pour l'instant notre projet est loin d'être finie et il reste beaucoup de choses à faire et à améliorer.
* Amélioration de l'initialisation du réseau neuronal : pour l'instant l'installation utilise plus de SRAM que la carte n'en dispose. Ce n'est pas un problème dans notre code mais un problème de compatibilité entre la carte Curie et le réseau. Le problème sera peut-être résolu plus tard par les concepteurs.
* Amélioration de la précision de l'apprentissage : pour l'instant certains mouvements ne sont pas bien différenciés par les neurones. C'est principalement à cause du type d'apprentissage lui-même qui est polyvalent mais pas d'une grande précision. 
* Amélioration de la syntaxe des commandes : ce n'est pas vraiment un problème mais il faudrait introduire une norme dans la syntaxe des commandes.
* Amélioration du suivie de ligne (véritable parcoure sur un chemin complexe) : pour l'instant le suivi de ligne et très basique et il faudrait le complexifier avec des chemins utilisation différente. Un autre problème est le capteur de ligne lui-même qui a tendance à ne plus fonctionner par intermittence. 

La stabilité de la carte et du robot est aussi un problème persistant : la carte Arduino qui peut planter totalement et faire planter le programme Arduino qui s'exécute, c'est un problème matériel pas logiciel.

Il faudrait aussi améliorer l'interface pour qu'elle soit adaptée à l'écran sur Android, la création et la modification d'actions est rendue complexe sur Android à cause des nouvelles fenetres qui s'ouvrent.
