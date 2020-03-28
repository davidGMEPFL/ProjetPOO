#Projet programmation orientée objet (SSV)

##REPONSES du groupe 56 (Checoury Annah-Ouriella-Violette & Nigri David) 

*************************************************
##Q1.1 Comment coder les trois opérateurs précédemment décrits en évitant toute duplication de code dans le fichier CircularBody.cpp ?


- En utilisant des appels aux méthodes déjà codéees "contains" et à la méthode "isColliding", on évite toute duplication inutile de code.

*************************************************
##Q1.2 Quelle surcharge choisissez-vous pour les opérateurs qu'il vous a été demandé de coder (interne ou externe) et comment justifiez-vous ce choix ?

- Tous les opérateurs de comparaisons sont surchargés de façon interne, puisqu'ils impliquent toujours une instance de la classe à gauche de l'opérateur, et qu'ils ne modifient pas la classe.
- L'opérateur d'affichage est codé par surcharge externe puisque on n'a pas accès à la classe ostream.  


*************************************************
##Q1.3 Quels arguments de méthodes, parmi celles qu'il vous été demandé de coder ci-dessus, vous semble t-il judicieux de passer par référence constante ?


- Tout les arguments que l'on peut passer par référence sont passés par référence pour économiser des places en mémoire. Etant donné qu'on n'a aucun intêrét à créer des variables intermédiaires dans nos méthodes, on passe tout les arguments par référence (et même par référence constante, puisque les arguements ne sont pas modifiés non plus.)

*************************************************
##Q1.4 Quelles méthodes parmi celles que l'on vous a demandé de coder vous semble t-il judicieux de déclarer comme const ?

- Seules les méthodes "setRadius" et "setPosition" ont pour vocation de changer les attributs de la classe. Ainsi, toutes les autres sont déclarées Const.
