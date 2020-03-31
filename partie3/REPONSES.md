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

- Il faut que la classe PetriDish hérite de la classe CircularBody, et qu'on ajoute le constructeur de CircularBody au constructeur de PetriDish. Enfin, on passe les attributs et certaines méthodes en protected.



*************************************************
##Q2.2 Quelles méthodes vous semble t-il judicieux de déclarer comme const?

- La méthode drawOn doit être déclarée constante car elle ne doit pas modifier les attributs de l'instance courante. 
- Les méthodes reset, addBacterium et addNutriments ne sont pas const car elles modifient le vecteur de pointeurs. 
- La méthode update n'a pas à priori besoin d'être déclarée const car elle pourraient elle aussi influencer le vecteur de pointeur, selon comme on décide de la modifier par la suite.

*************************************************
##Q2.3 Quelle(s) solution(s) proposeriez-vous pour satisfaire cette contrainte?

- Pour éviter les copies on doit obligatoirement supprimer le constructeur de copie et l'opérateur =, qui sont tous 2 définis par défaut. On utilisera donc la syntaxe = delete. 

*************************************************
##Q2.4 Quelle incidence cela a t-il sur la destruction d'une assiette de Petri ? La destruction peut-elle se faire en utilisant une méthode existante de la classe PetriDish.

- Le destructeur de l'assiette de petri doit prendre en charge la libération de la mémoire représentant les bactéries et nutrimemts qu'elle contenait. 
- On peut utiliser la méthode déjà présentée `reset` dans le destructeur, puisqu'elle a déjà pour rôle de libérer les pointeurs dans le vecteur de l'assiette de petri. 


*************************************************
##Q2.5 Comment proposez-vous de coder le corps des méthodes Lab::drawOn et Lab::update ?

- Puisqu'il ne s'agit que d'opérations sur l'assiette de Petri, on se suffit d'appeler les méthodes de l'attribut assiette de Petri du lab (par exemple, `Petri.drawOn`).



*************************************************
##Q2.7 Comment proposez-vous d'utiliser la classe fournie CircularBody (dans le répertoire Lab) pour modéliser cet aspect ?

- Puisque les nutriments sont aussi des corps circulaires, les méthodes et attributs de CircularBody seront probablement utiles pour la classe méthode. On fait donc hériter (par un héritage public) la classe CircularBody à la classe Nutriments.

*************************************************
##Q2.8  A quoi cela peut-il bien servir d'utiliser le type Quantity plutôt que tout simplement un double ?

- Pour améliorer la lisibilité du code: la fonction des variables initialisées avec ce type sera évidente à chaque fois. 
- Cela peut aussi permettre de rajouter une sécurité en contraignant l'argument d'une méthode ou d'une fonction à être du type Quantity, et ainsi ne pas mélanger différentes variables.
- Si on décide de changer le type de Quantity et de le rendre int ou uint, par exemple, il suffira de le changer une fois dans Types, et on n'aura pas besoin de chercher toutes les utilisationss.


*************************************************
##Q2.9     quelle méthode doit-elle être ajoutée à la classe Lab pour permettre l'ajout de nutriments à l'assiette de Petri ? Quelle méthode existante doit être modifiée pour permettre le dessin des sources de nutriments nouvellement ajoutées?

- Pour ajouter des nutriments à l'assiette de petri, on fait simplement un appel à la méthode addNutriments de l'assiette de petri du lab. 
- Dans la méthode `petriDish::drawOn` on passe un appel aux méthodes drawOn de chacun des nutriments pointés.

*************************************************
##Q2.10 comment permettre à Nutriment::update de connaître la température de l'assiette de Petri ?

- On fait un appel, par la méthode Application::getAppEnv au laboratoire courant, dans lequel on cherche la méthode petriDish::getTemperature de l'assiette de Petri. 



*************************************************
##Q2.11 Quelles méthodes de Lab et de PetriDish faut-il modifier et comment pour que la croissance des nutriments deviennent visible lors de l'exécution du test graphique ?

- il faut que Lab::update appelle la méthode PetriDish::update de son attribut PetriDish. Et il faut que PetriDish::update appelle à son tour la méthode Nutriment::update pour chacun des nutriments pointés dans son vector de pointeurs. 


*************************************************
##Q2.12 Quelles méthodes devez vous ajouter et dans quelles classes pour que appuyer sur 'PgUp' ou 'PgDn' permette respectivement d'augmenter ou diminuer la température de l'assiette? Quelles méthode(s) devez vous également ajouter et à quelle(s) classe(s) pour que les touches 'R' et 'C' permettent aussi (en plus de ce qu'elles font) de réinitialiser l'attribut température?

- Pour que les touches 'PgUp' ou 'PgDn' fonctionnent, il faut coder des méthodes `increaseTemperature()` et `decreaseTemperature()` dans les classes Lab (ici, elle ne fera qu'un appel à la méthode de petriDish) et petriDish (incrémentera ou décrémentera la température d'une valeur delta). 
- Pour les touches 'R' et 'C', on code une méthode `petriDish::resetTemp()` qui ramène la température à sa valeur par défaut (et `Lab::resetTemp()` qui appel cette méthode). On ajoute dans la méthode `reset` de l'assiette de Petri un appel à `resetTemp()` par logique de réinitialisation, et pour la touche 'C', on fait un appel à la méthode `resetTemp()` du laboratoire courant. 


*************************************************
##Q3.1     Quelles classes de votre conception actuelle serait-il bon de faire hériter des sous-classes <t>Updatable<t> et <t>Drawable<t>? Quel plus cela amène t-il à la conception ?

- Les classes Lab, Nutriments et PetriDish ont intérêt à être définies comme des sous-classes de ces classes-ci. Ceci permet de s'assurer que les classes contiennent une méthode update et drawOn const valide (puisque ce sont des classes abstraites), et cela améliore la compréhension du code (on sait directement que les classes doivent pouvoir être déssinées et actualisées). Cela permet également de rendre toutes les méthodes drawOn et update virtuelles et d'utiliser le polymorphisme.


*************************************************
##Q3.2     Qu'implique cette contrainte au niveau des définitions de drawOn et update?

- Ces 2 méthodes ne sont pas redéfinies dans les sous classes. Le changement tient au choix des paramètres dans `getConfig()`.

*************************************************
##Q3.3     Comment doit-être codée la méthode getConfig dans la hiérarchie de classes pour satisfaire cette contrainte ?

- On fera varier le chemin renvoyé entre les paramètres des NutrimentsA ou NutrimentsB. On utilise donc le polymorphisme en rendant `getConfig()` virtuelle pure, et qui en fonction de la classe de l'objet pointé par `*this` (dans `drawOn` et `update`), renverra soit à la méthode `NutrimentA::getConfig()` ou `NutrimentB::getConfig()`.


*************************************************
##Q3.4     Qu'est-ce qui fait que sans modifier les méthodes drawOn et update dans les sous-classes, l'affichage graphique peut faire usage de textures différentes et la croissance dépend de conditions différentes ?

- Le polymorphisme permet de choisir le "classeur" de paramètres appropriés pour chaque type de Nutriments, en fonction de la classe de l'objet pointé dans le vecteur de l'assiette de Petri.


*************************************************
##Q3.5     Quelle modification doit être faite dans Lab et dans quelle méthode pour permettre au générateur d'effectivement générer des sources de nutriments dans l'assiette de Petri qui lui est associée ?

- Dans la méthode Lab::update, on rajoute un appel à la méthode update de l'attribut de NutrimentGenerator.

*************************************************
##Q3.6     ?????????????


*************************************************
##Q3.7     Comment faut-il procéder pour que ces méthodes puissent être invoquées sans passer par la création d'une instance de MutableNumber ?

- 



*************************************************
##Q2.6     ?????????????