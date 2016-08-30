# Projet-Zumo-Intel-Curie-101

## Presentation du projet

Projet lancer au cour d'un stage en binome pendant l'ete 2016 au LEAT.

L’objectif du stage est de mettre en place un petit groupe d'objets mobile (des robots avec des cartes Curie) connecter entre eux et s'organisant autour d’un point centrale. Chacun de ces robots doit pouvoir apprendre et reconnaître son environnement et pouvoir retrouver son “chemin” grâce à l’apprentissage. Le but est de faire parcourir l’environnement par les robots en couvrant le plus de surface en la plus grande autonomie possible vise à vie de l'utilisateur qui pourra interagir avec les robots à partir d’un ordinateur.
Les applications à long terme sont très variés et dans de nombreux domaine différent  comme par exemple la surveillance, la cartographie, l’exploration, etc. 

## Les Parties

Il y a 3 partie dans le projet : 
1. La programmation de la carte Arduino (et du robot)
2. L'interface utilisateur sur ordi en Qt
3. L'affichage graphique du déplacement du robot avec processing.


## Pour installer : 

### Les pres-requis

Materiel utiliser: Un "robot Zumo for Arduino", une carte Intel Curie 101.
Les logiciel utiliser : Arduino IDE, QtCreator et Processing.
 
 
### Arduino

-copier/coller les librairie c++ du dossier libArduino dans les libraire de Arduino IDE (le plus souvant elle est dans le dossier personnelle). Lancer l'IDE Arduino en avec un double click sur le fichier .ino. Maintenant, vous devais paramètrer Arduino pour utiliser la carte : le plus simple est de suivre le debut du TD vue en cour de Capteurs/Actionneurs : 



> Install the Intel Curie Board,

> Install the associate libraries.

> First of all, you'll need to install the Intel® Curie Boards core using the Arduino Boards Manager.
> This is found in the Tools menu under Boards -> Boards Manager, where you can search 'Intel Curie
> Boards'.

> On Linux, some distributions need to be configured to perform the upload. After installing the core,
> execute:

> sudo ~/.arduino15/packages/Intel/tools/arduino101load/1.6.4+1.18/scripts/create_dfu_udev_rule

Ensuite, compiler le code puis tranferer-le dans la carte. Le robot doit etre immobile lors de l'allumage pour que l'IMU s'initialise correctement.

### Application QT

> Installer Qt ainsi que le module Qt Chart

> Ouvrir le .pro dans QT Creator

> Demarrer la carte 

> Démarrer le projet dans QT Creator

Pour générer la documentation, il faut d'abord installer le paquet doxygen puis executer la commande doxygen dans le repertoire

### Proccesing

-lancer le fihcier .pde avec Processing

## Les truc a faire

Il reste de nombreuses améliorations et corrections à apporter au projet. Pour plus de détailles sur ce qui a était fait et ce qui reste a faire, consulter nos rapports de stage.
