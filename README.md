# arduino

## Presentation du projet

Projet lancer au cour d'un stage en binome pendant l'ete 2016 au LEAT.

L’objectif du stage est de mettre en place un petit groupe d'objets mobile (des robots avec des cartes Curie) connecter entre eux et s'organisant autour d’un point centrale. Chacun de ces robots doit pouvoir apprendre et reconnaître son environnement et pouvoir retrouver son “chemin” grâce à l’apprentissage. Le but est de faire parcourir l’environnement par les robots en couvrant le plus de surface en la plus grande autonomie possible vise à vie de l'utilisateur qui pourra interagir avec les robots à partir d’un ordinateur.
Les applications à long terme sont très variés et dans de nombreux domaine différent  comme par exemple la surveillance, la cartographie, l’exploration, etc. 

## Les Parties

Il y a 3 partie dans le projet : La programmation de la carte Arduino (et du robot), l'interface utilisateur sur ordi en Qt et l'affichage graphique du déplacement du robot avec processing.


## Pour installer : 

### Les pres-requis

Materiel utiliser: Un "robot Zumo for Arduino", une carte Intel Curie 101.
Les logiciel utiliser : Arduino IDE, QtCreator et Processing.
 
 
### Arduino

-copier/coller les librairie du git dans les libraire de Arduino IDE, lancer le fichier .ino, compiler-le puis tranfere-le dans la carte. Le robot doit etre immobile lors de l'allumage pour que l'IMU s'initialise.

### QT

-lancer le projet avec QTCreator

### Proccesing

-lancer le fihcier .pde avec Processing

## Les truc a faire 

-calcule de trajectoire (processing surtout) → gros probleme de drift, resourde bug qt, calcule rssi
