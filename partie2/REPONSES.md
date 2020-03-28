#Projet programmation orientée objet (SSV)

##REPONSES du groupe 56 (Checoury Annah-Ouriella-Violette & Nigri David) 

*************************************************
##Q1.1 Comment coder les trois opérateurs précédemment décrits en évitant toute duplication de code dans le fichier CircularBody.cpp ?


- En utilisant des appels aux méthodes déjà codéees "contains" et à la méthode "isColliding", on évite toute duplication inutile de code.

*************************************************
##Q1.2 Quelle surcharge choisissez-vous pour les opérateurs qu'il vous a été demandé de coder (interne ou externe) et comment justifiez-vous ce choix ?

- Tous les opérateurs de comparaisons sont surchargés de façon interne, puisqu'ils impliquent toujours une instance de la classe à gauche de l'opérateur, et qu'ils ne modifient pas la classe. Etant donné que la surcharge interne permet d'accéder directement aux attributs de la classe, sans passer par les getters et setters, on préfèrera la surchage interne.
- L'opérateur d'affichage est codé par surcharge externe puisque on n'a pas accès à la classe ostream.  


*************************************************
##Q1.3 Quels arguments de méthodes, parmi celles qu'il vous était demandé de coder ci-dessus, vous semble t-il judicieux de passer par référence constante ?


- Tout les arguments que l'on peut passer par référence sont passés par référence pour économiser des places en mémoire. Etant donné qu'on n'a aucun intêrét à créer des variables intermédiaires dans nos méthodes, on passe tout les arguments par référence (et même par référence constante, puisque les arguements ne sont pas modifiés non plus.)

*************************************************
##Q1.4 Quelles méthodes parmi celles que l'on vous a demandé de coder vous semble t-il judicieux de déclarer comme const ?

- Seules les méthodes "setRadius" et "setPosition" ont pour vocation de changer les attributs de la classe. Ainsi, toutes les autres sont déclarées Const.



*************************************************
##Q2.1 Comment utiliser la classe CircularBody pour modéliser cela ? 

- Il faut que la classe PetriDish hérite de la classe CircularBody, et qu'on ajoute le constructeur de CircularBody au constructeur de PetriDish. Enfin il faut que les bactéries soient toujours à l'intérieur de l'assiette, donc que la méthode Contains retourne toujours True. 



*************************************************
##Q2.2 Quelles méthodes vous semble t-il judicieux de déclarer comme const?

- La méthode drawOn doit être déclarée constante car elle ne doit pas modifier les attributs de l'instance courante. 
- Les méthodes reset, addBacterium et addNutriments ne sont pas const car elles modifient le vecteur de pointeur. 
- La méthode update n'a pas à priori besoin d'être déclarée const car elle pourraient elle aussi influencer le vecteur de pointeur, selon comme on décide de la modifier par la suite.

*************************************************
##Q2.3 Quelle(s) solution(s) proposeriez-vous pour satisfaire cette contrainte?

- Pour éviter les copies on doit obligatoirement supprimer le constructeur de copie et l'opérateur =, qui sont tous 2 définis par défaut. On utilisera donc la syntaxe = delete. 

*************************************************
##Q2.4 Quelle incidence cela a t-il sur la destruction d'une assiette de Petri ? La destruction peut-elle se faire en utilisant une méthode existante de la classe PetriDish.

- Le destructeur de l'assiette de petri doit prendre en charge la libération de la mémoire représentant les bactéries et nutrimemts qu'elle contenait. 
- On peut utiliser la méthode déjà présentée reset dans le destructeur, puisqu'elle a déjà pour rôle de libérer les pointeurs dans le vecteur de l'assiette de petri. 


*************************************************
##Q2.5 Comment proposez-vous de coder le corps des méthodes Lab::drawOn et Lab::update ?

- Puisqu'il ne s'agit que d'opérations sur l'assiette de Petri, on se suffit d'appeler les méthodes de l'attribut assiette de Petri du lab (par exemple, Petri.drawOn).



*************************************************
##Q2.6     ?????????????



*************************************************
##Q2.7 Comment proposez-vous d'utiliser la classe fournie CircularBody (dans le répertoire Lab) pour modéliser cet aspect ?

- Puisque les nutriments sont aussi des corps circulaires, les méthodes et attributs de CircularBody seront probablement utiles pour la classe méthode. On fait donc hériter (par un héritage public) la classe CircularBody à la classe Nutriments.

*************************************************
##Q2.8  A quoi cela peut-il bien servir d'utiliser le type Quantity plutôt que tout simplement un double ?

- Pour améliorer la lisibilité du code: la fonction des variables initialisées avec ce type sera évidente à chaque fois. 
- Cela peut aussi permettre de rajouter une sécurité en contraignant l'argument d'une méthode ou d'une fonction à être du type Quantity, et ainsi ne pas mélanger différentes variables.



*************************************************
##Q2.9     quelle méthode doit-elle être ajoutée à la classe Lab pour permettre l'ajout de nutriments à l'assiette de Petri ? Quelle méthode existante doit être modifiée pour permettre le dessin des sources de nutriments nouvellement ajoutées?

- comment permettre à Nutriment::update de connaître la température de l'assiette de Petri ?


*************************************************
##Q2.10 comment permettre à Nutriment::update de connaître la température de l'assiette de Petri ?

- en appelant dans Application la méthode getTemperature, et en utilisant la température ainsi trouvée en paramètre de la méthode update



*************************************************
##Q2.11 Quelles méthodes de Lab et de PetriDish faut-il modifier et comment pour que la croissance des nutriments deviennent visible lors de l'exécution du test graphique ?

- il faut que Lab::update appelle PetriDish::update de son attribut PetriDish. Et il faut que PetriDish::update appelle à son tour la méthode Nutriment::update pour chacun des nutriments pointés dans son vector de pointeurs. 


*************************************************
##Q2.12 Quelles méthodes devez vous ajouter et dans quelles classes pour que appuyer sur 'PgUp' ou 'PgDn' permette respectivement d'augmenter ou diminuer la température de l'assiette? Quelles méthode(s) devez vous également ajouter et à quelle(s) classe(s) pour que les touches 'R' et 'C' permettent aussi (en plus de ce qu'elles font) de réinitialiser l'attribut température?

?
?



*************************************************
##Q2.6     ?????????????


*************************************************
##Q2.6     ?????????????