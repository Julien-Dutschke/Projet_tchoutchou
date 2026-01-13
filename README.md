# Projet tchoutchou

## Explication

Le projet TchouTchou est un projet de 42 visant a simuler le déplacement de trains dans un réseau ferroviaire.

Le réseau et les trains sont représentés par des fichiers décrivant leur comportement, et, a partir de ces derniers,
la simulation doit prendre le relai, et effectuer le parcours donné.

## Compilation

La compilation est actuellement hybride. elle utilise soit Make, soit Tup.

ATTENTION! le projet est **exclusivement** testé sur un système linux. Il n'y a **AUCUNE** garantie de fonctionnement sur
un système non unix.

### Compiler avec make

- installer g++, et make (ou clang++, et mettre la variable d'environnement CXX a clang++)
- aller a la racine du projet
- taper "make"

Le binaire se trouvera dans le dossier courant

### Compiler avec tup

- installer g++, et tup (ou clang++), et mettre la variable d'environnement CXX au compilateur choisi.
- aller n'importe ou dans le projet
- si on veut des variants (debug, release...), taper "tup variant configs/*"
- taper "tup build-release" (pour la version release), "tup build-debug" (pour la version debug), ou "tup" (pour les deux)

le binaire se trouvera a la racine du projet, dans un sous-dossier "build-[nom du variant]".

S'il n'y a pas de variant d'actif, alors il sera placé a la racine du projet.

### recompiler le projet

#### make
- il sera nécessaire de faire "make re" a la racine du projet (si les fichiers .hpp ont changés et non les .cpp).
- des fichiers peuvent trainer d'une compilation précédente (les .o), ils peuvent être supprimés sans risque.

#### tup
- taper "tup" "tup release" ou "tup debug" n'importe ou dans l'arborescence de dossier du projet.

### potentiels soucis

- tup n'aime pas que make soit passé avant lui. il faudra supprimer tous les .o que make génère
- make s'en fiche de l'existence de tup.
- si le makefile change et que des fichiers sont renommés, des .o zombies resteront dans le projet
- Pour nettoyer tup, supprimer juste les dossiers build-*. s'il n'y a pas de variant actif, soit utiliser git (git clean -fdx), soit créer les variants, et supprimer leurs dossiers.
