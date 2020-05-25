=====================================================================


**Simulation d'une colonie de Bactéries dans une assiette de Petri en étudiant leur évolution et leurs mutations.**


Chaque Bactérie possède des paramètres qui lui sont propres, et qui determineront son comportement et ses capacités de survie.

Dans le cadre de notre projet on traite trois types de bactéries bien distinctes : les bactéries simples, les bactéries à tentacules et les bactéries avec comportement de groupe.

Chacune possède son propre mode de déplacement, d'alimentation et de mutation. 
Elles ont tout de même en commun un certain nombre d'attributs, comme leur énergie, leur position, leur couleur... mais dont les valeurs varient pour chaque bactérie.

Il n'y a pas d'interactions entre bactéries, à part pour les `SwarmBacterium` qui suivent un "Leader". Néanmoins, les bactéries interagissent avec les nutriments distribués sur l'assiette et générés de manière aléatoire.

L'évolution des bactéries au cours du temps est étudiée au moyen de graphes déssinés sous l'application. Quatres graphes ont été programmés:


  * un graphe général représentant la quantité de chaque type de bactéries, le nombre de sources de nutriments, et la température,
  * un graphe représentant la quantité totale de nutriments,
  * un graphe représentant la moyenne des variables `Tumble Better` et `Tumble Worse` liées à la probabilité de basculement des `SimpleBacterium`,
  * un graphe avec la moyenne des longueur de tentacules et la moyenne des vitesses des tentacules,
* enfin, un dernier graphe avec la moyenne des vitesses des bactéries (ces dernières valeurs sont relevées différemment selon le type de bactéries, mais correspondent globalement à leur paramètre mutable).



##COMPILATION ET EXÉCUTION:

Ce projet utilise  [Cmake](https://cmake.org/) pour compiler

* en ligne de commande :
    - dans le dossier build: cmake ../src
    - make nom_cible pour la génération de la cible

* Dans QTCreator:
       - mise en place du projet : ouvrir le fichier src/CmakeLists.txt
       - choisir la cible à exécuter application


##CIBLES PRINCIPALES:

* application -> correspond à l'application finale.
* swarmTest -> permet de tester le comportement des bactéries en groupe
* twitchingTest -> permt de tester le comportement des bactéries à tentacules
*...


## FICHIERS DE CONFIGURATION

Les fichiers de configuration à utiliser pour application sont app.json. 
Il permet de simuler l'environnement avec des paramètres pas nécessairement optimaux, mais qui permettent d'observer toutes les bactéries se développer, se reproduire, consommer et parfois mourir. 


## COMMANDES

Les commandes pour l'utilisation d'une cible particulière sont données dans un panneau d'aide à gauche de la fenêtre de simulation.

Rapidement, les touches ´T´, ´S´ permettent respectivement de placer une TwitchingBacterium ou une SimpleBacterium à la position du curseur, alors que les touches ´1´ et ´2´ placent des SwarmBacterium et leur assignent un Swarm. 

La touches ´R´ est utile pour nettoyer la simulation en se débarrassant de toutes les instances créées, et la touche ´C´ permet de recharger les paramètres de la simulation, après avoir modifier le fichier de configuration en cours d'execution. 

Enfin, les touches `Tab`, `PageUp` et `PageDown` permettront de changer directement sur la fenêtre graphique la température et l'exposant du gradient. Ces touches permettront également de changer l'affichage des graphiques, pour passer de l'un à l'autre.



### MODIFICATION DE CONCEPTION

Le codage du projet a été réalisé en adéquation avec l'énoncé (pas de modifications personnelles d'éléments de conception suggérés).


