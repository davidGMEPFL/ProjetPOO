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
##Q3.6     Quelles méthodes parmi celles suggérées pour un MutableNumber devront procéder au plafonnage de la valeur entre la borne inférieure et la borne supérieure ? Comment éviter les duplications de code si ce traitement est amené à se répéter à plusieurs endroits ?

- Les méthodes qui devront procéder au plafonnage sont les constructeurs de la classe MutableNumber, ainsi que la méthode reset().
  Pour éviter la duplication de code, on fait appel à "reset()" afin de plafonner les valeurs dans les constructeurs.

*************************************************
##Q3.7     Comment faut-il procéder pour que ces méthodes puissent être invoquées sans passer par la création d'une instance de MutableNumber ?

- Une façon d'avoir accès à des méthodes sans créer d'objet MutableNumber serait l'utilisation de méthodes de classes, signalées par le mot "static" : ces méthodes seront donc statiques.

*************************************************
##Q3.8     Au vu de ce qui précède, comment proposez-vous de modéliser la classe Bacterium (héritage, attributs, méthodes , ...) ? 

- La classe Bacterium héritera des classes CircularBody, Uptadable et Drawable : elle aura pour caractéristiques une couleur, une direction, des paramètres, un état, une énergie. Elle aura pour méthode un constructeur, un bool "testMort", "clone", "drawOn" et "update".

*************************************************
##Q3.9    Quelles méthodes parmi celles suggérées pour une Bacterium devront vraisemblablement être virtuelles/virtuelles pures ?

- Les méthodes nécessitant d'être présentes dans les sous-classes de Bacterium, et donc virtuelles pures, seraient les méthodes "clone()" et "move()" qui doiventt être définies de façon spécifique.

*************************************************
##Q3.10    La méthode getConfig est-elle virtuelle pure selon vous ?    

- Dans la mesure où Bacterium est une classe abstraite, il n'y a pas d'utilisation de cette méthode en dehors d'une sous-classe. Chaque sous-classe devra alors avoir sa propre défintion de "getConfig" : la méthode devra donc être virtuelle pure.
 
*************************************************
##Q3.11    Comment retrouvez-vous la couleur SFML de la bactérie à partir de son attribut de type MutableColor ?

- La méthode "MutableColor::get()" nous donne la couleur SFML de l'attribut <couleur> de la classe Bacterium.
 
*************************************************
##Q3.12   Le fait qu'aucune méthode de déplacement concrète n'existe encore est-elle un frein à l'écriture de la méthode update ? 

- La méthode "move()" étant virtuelle pure, l'écriture de "update()" ne recquiert pas d'être au préalable générale et définie.

*************************************************
##Q3.13   La classe PetriDish ne donne pas d'accès à sa collection de nutriments, comment procéder dans ce cas pour coder Lab::getNutrimentColliding(CircularBody const& body) ? 

- Pour y avoir accès, on code une méthode "Nutriment* PetriDish::getNutrimentColliding" qui procède avec des itérations sur le vecteur contenant les pointeurs sur les nutriments. Elle cherche le nutriment qui sera au contact de la bactérie (par un appel à "isColliding"), et le cas échéant le retourne nullptr.

*************************************************
##Q3.14   Quelle méthode de la classe PetriDish doit être modifiée pour permettre la simulation de l'évolution des bactéries ? Comment doit-elle être modifiée ? 

- Il s'agit de la méthode "update" qui gère l'évolution des bactéries : au sein de celle-ci on fera donc un appel aux méthodes "update".

*************************************************
##Q3.15   Que devez-vous modifier et dans quelle classe pour faire en sorte que les bactéries et sources de nutriments de votre simulation meurent/disparaissent si leur énergie/quantité devient nulle ?

- Dans la classe PetriDish, c'est par la méthode "update()" que l'on peut ajouter cette fonctionnalité : par les tests 'testMort' et 'testEpuise', on vérifie le nombre de nutriments et la quantité d'énergie des bactéries. Dans les cas où ils nuls, la commande de suppression est alors activée.

*************************************************
##Q3.16   Comment vous proposez d'utiliser cette classe pour doter une bactérie simple d'une méthode qui calcule la force f régissant son déplacement ? 

- Pour permettre à une bactérie simple l'utilisation de cette force f, on définit la classe SimpleBacterium comme sous-classe de DiffEqFunction, dont elle hérite la méthode virtuelle f que l'on définit. On peut alors utiliser notre instance de SimpleBacterium en argument de stepDiffEq qui retourne une structure.

*************************************************
##Q3.17  Où déclarer et initialiser le temps t ?

- On déclare t comme un attribut de SimpleBacterium, initialisé aléatoirement dans le constructeur de la classe. Il est updaté dans la méthode "update" comme cité dans l'énoncé.

*************************************************
##Q3.18   Comment mémoriser l'angle de direction et à quel endroit du code l'initialiser et le mettre à jour si l'on considère que toutes les bactéries ont une direction et un angle de direction ?

- On ajoute un attribut correspondant à l'angle de rotation des flagelles des bactéries. Il sera alors initialisé dans le constructeur de la classe, tel qu'il soit dans la même direction que le déplacement de la bactérie.

*************************************************
##Q3.19   Comment mémoriser l'angle de direction et à quel endroit du code l'initialiser et le mettre à jour si l'on considère que toutes les bactéries ont une direction et un angle de direction ?

- Il faut ajouter comme attribut la <puissance>, ainsi que la méthode "getPositionScore" qui va faire me cumul des scores des nutriments en fonction de la position.

*************************************************
##Q3.20   Quel(s) attributs suggérez-vous d'ajouter à la représentation des bactéries (simples ou "tout court") pour permettre la mise en oeuvre cet algorithme ? Comment initialiser ces attributs et à quels endroits devez-vous les mettre à jour ?

- Des attributs <TimerTumble> et <ancien_score> pourraient être ajoutés à la classe : ils sont initialisés dans le constructeur. Ils seront alors modifiés dans la méthode "update()" de chaque bactérie.

*************************************************
##Q3.21   Dans quelle classe proposez-vous d'ajouter la méthode de mutation ?

- La méthode "mutate()" de mutation des bactéries peut être ajoutée à la classe Bacterium qui possède les attributs suceptibles de muter. 

*************************************************

##Q3.22  Dans quelle classe proposez-vous d'ajouter ces méthodes ?

- C'est la classe `Bacterium` qui possède l'attribut "vecteur de paramètres". C'est donc dans cette classe qu'on ajoute ces méthodes d'accès aux vecteurs.

*************************************************

##Q3.23  Où choisissez-vous de placer la méthode de division d'une bactérie ?

- La méthode étant la même pour toute les bactéries, elle est placée simplement dans la classe `Bacterium` et elle appelera la méthode `clone` de façon polymorphique.

*************************************************

##Q4.1 Quel(s) lien(s) d'héritage proposez-vous de mettre en place pour intégrer les TwitchingBacterium à l'architecture existante ?

-TwitchingBacterium serait une sous-classe de Bacterium, de même qu’une SimpleBacterium : elle héritera des classes CircularBody, Updatable et Drawable.

*************************************************

##Q4.2 Comment proposez-vous d'accéder aux paramètres caractérisant ce type de bactéries (comme la longueur maximale de son tentacule ou sa vitesse d'extension) ?

-A la manière de SimpleBacterium, on introduit une méthode   "getConfig()"  qui retournera les valeurs associées aux étiquettes de ["twitchingbacterium "] dans app.jason .

*************************************************

##Q4.3 Quelles méthodes déjà présentes dans la hiérarchie de classes des bactéries devrez-vous impérativement redéfinir dans TwitchingBacterium ?

-Les méthodes virtuelles pures  "getConfig() " et  "clone()"  doivent être adaptées dans la sous-classe TwitchingBacterium, par définition. 
 Par la présence du tentacule, les méthodes "drawOn()", "update()", et "move()" devront être redéfinies pour s’adapter aux nouvelles fonctionnalités de ces bactéries.

*************************************************

##Q4.4  Quel «getters» proposez-vous d'ajouter/redéfinir à/dans votre classe pour retrouver ces valeurs lorsque nécessaires ?

-Le getter donnant accès à l’énergie consumée par le déplacement étant déjà existant dans Bacterium (EnergieDepl()), il suffira de le modifier. 
 Pour avoir accès à l’énergie utilisée par un déploiement de tentacule, on crée un getter dans la classe (EnergieTentac()), qui fera appel à  "getConfig()".

*************************************************
##Q4.5 Un type énuméré peut être une bonne solution pour répertorier les différents états cités plus haut. Comment proposeriez-vous d'en utiliser un pour mettre en oeuvre l'algorithme de mouvement ?

- En créant une liste d'énumaration avec les différents états, on peut créer un paramètre qui donnera au switch (de la machine d'état) l'instruction pour aller dans le bon état. Ce paramètre sera modifié à l'intérieur de la machine d'état, càd dans les différents `case` du switch.


*************************************************
##Q4.6 Quelle(s) modification(s) faites-vous et à quelle(s) classe(s) pour intégrer cela ?

- Dans la classe `PetriDish`, on ajoute un attribut vecteur de pointeurs sur des `Swarm`. Par ailleurs, dans la classe `Lab` on ajoute une méthode addSwarm qui fait appel à la méthode `PetriDish::addSwarm` qui permet d'ajouter un Swarm au vecteur des pointeurs. 


*************************************************
##Q4.7 Une SwarmBacterium doit disposer d'une force régissant son déplacement, exactement comme les bactéries simples. Quels liens mettez-vous en place pour modéliser cette force ? 

- la classe `SwarmBacterium` hérite de la classe `DiffEqFunction`. On ajoute donc une méthode `f` à `SwarmBacterium` qui calculera la force sur les bactéries. 

*************************************************
##Q4.8 Au vu de ce qui précède, quelles méthodes déjà présentes dans la hiérarchie de classes des bactéries devrez-vous impérativement redéfinir dans SwarmBacterium ?

- Puisque `SwarmBacterium` hérite de `Bacterium` il est donc nécessaire de rajouter les méthodes virtuelles pures de `Bacterium`: `move`, `clone` et `getConfig`. 

*************************************************
##Q4.9 Que devez-vous ajouter à votre code et où pour mettre en place cette fonctionnalité ?

- On ajoute la méthode `Lab::getSwarmWithId` qui appelle une `PetriDish::getSwarmWithId` qui cherche le Swarm avec le bon id parmi le vecteur de pointeurs sur `Swarm`, et le retourne le bon pointeur


*************************************************
##Q4.10 Le destructeur de Swarm doit-il faire quelque chose selon vous ?

- Etant donné qu'on gère déjà les bactéries (objets pointés) dans `PetriDish`, il ne reste à `Swarm` qu'à s'occuper des pointeurs eux-mêmes (qui sont ses attributs), ce qui est fait par défaut.


*************************************************
##Q4.11  Lorsqu'une SwarmBacterium meurt, elle ne doit plus être recensée dans son Swarm. Que devez-vous ajoutez à votre code et où pour que cette contrainte soit respectée ?

- `PetriDish::update()` s'occupe de tester si la bactérie est morte. Quand c'est le cas, elle appelle le destructeur de `SwarmBacterium`, qui va appeler la méthode `Swarm::PopBack()` qui va supprimer le pointeur du `Swarm`. Enfin, `PetriDish::update()` supprime le pointeur dans `PetriDish`.


*************************************************
##Q5.1 Pourquoi tester le type des objets à l'exécution est-il potentiellement nocif ? 

- Un test de type d'objet viendrait casser la notion de polymorphisme, qui par définition se charge d'appliquer la bonne méthode selon le type, la nature de la donnée manipulée. 


*************************************************
##Q5.2 Pourquoi doit on prévoir une méthode virtual Quantity eatenBy(Bacterium& bact) const = 0; avec comme argument une Bacterium quelconque (alors qu'à priori seule nous intéresse la définition de eatenBy pour des sous-classes de bactéries) ?

- Cette méthode virtual est nécessaire puisque c'est elle qui sera d'abord appelée par `Bacterium::eat()`, et qui se chargera ensuite de renvoyer vers la bonne méthode `eatableQuantity()` (qui elle agira par polymorphisme). Dans le cas où voudrait ajouter une nouvelle sous-classe de `Bacterium`, cela évitera aussi d'engendrer des lignes supplémentaires au code.


*************************************************
##Q5.4 Quelle méthodes prévoyez-vous d'ajouter/modifier et dans quelles classes pour réaliser les décomptes souhaités et construire les ensembles new_data? en d'autres termes, comment pouvez-vous compter le nombre d'instances d'une certaine classe?

