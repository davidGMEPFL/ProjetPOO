#include "PetriDish.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"
#include "Utility/Vec2d.hpp"
#include <numeric>

using namespace std;

//Constructeur
PetriDish::PetriDish(Vec2d position,double rayon):
    CircularBody(position,rayon),
    Temp(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()),
    puissance((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+
               getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2)
{}


// Méthodes principales
void PetriDish::update(sf::Time dt)
{
    /* Fait évoluer tout ce que contient l'assiette à chaque pas de temps,
    en appelant de façon polymorphique leur méthode 'update' respective
    La méthode appelle les tests pour vérifier si les objets doivent
    être supprimés, et modifie les vecteurs en conséquence */

    for (auto& objet : Nut) {
        if(objet->testEpuise()) { // verifie si le nombre de nutriments est nul avant d'en rajouter
            delete objet;    // libère la mémoire de l'objet pointé (appelle destructeur)
            objet=nullptr; // nécessaire pour enlever le pointeur du vecteur
        } else objet->update(dt);
    }

    Nut.erase(std::remove(Nut.begin(), Nut.end(), nullptr), Nut.end());
    // permet d'enlever tous les nullptr du vecteur de pointeurs

    for(auto& troupe : mesTroupes) {
        troupe->update(dt);
    } // un swarm ne peut pas mourrir donc pas de gestion nécessaire

    for (auto& objet : Bact) {
        objet->update(dt);
        if(objet->testMort()) { // vérifie si l'energie de la bactérie est trop faible (<=0)
            delete objet;   // dans les cas d'une SwarmBacterium, fait appel au destructeur
            // de la bactérie, qui la retire du Swarm
            objet=nullptr;
        }
    }
    if(!vecteur_clones.empty()) { // si le vecteur de clones n'est pas vide
        append(vecteur_clones,Bact); // ajoute les pointeurs sur les clones au vecteur des bactéries de l'assiette
        vecteur_clones.clear(); // empêche d'ajouter les clones plus d'une fois
    }
    vecteur_clones.erase(std::remove(vecteur_clones.begin(), vecteur_clones.end(), nullptr),
                         vecteur_clones.end());
    Bact.erase(std::remove(Bact.begin(), Bact.end(), nullptr), Bact.end());
    //suppression de tous les pointeurs à valeur nullptr, placés en fin des vecteurs
}


void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    /* Dessine sur une fenêtre graphique le contour de l'assiette
       Fait appel de façon polymorphique aux méthodes de dessin de
       ses attibuts dessinables */

    sf::Color couleur(sf::Color::Black);
    double epaisseur(5);
    auto border = buildAnnulus(position, rayon, couleur, epaisseur);
    targetWindow.draw(border);
    for (auto& nutr : Nut) nutr->drawOn(targetWindow);
    for (auto& bac : Bact) bac->drawOn(targetWindow);
}


//AJOUTS D'OBJETS
bool PetriDish::addNutriment(Nutriment* nut)
{
    /* Place des nutriments à l'intérieur de l'assiette en les ajoutant
    au vecteurs de nutriments. S'il est à l'extérieur, il est détruit.
    Le retour permet de savoir si l'on a réussit à placer le nutriment*/

    bool testContain(contains(*nut));
    if(testContain)     Nut.push_back(nut);
    else    delete nut;
    return testContain;
}

bool PetriDish::addBacterium(Bacterium* bact,bool const& newBorn)
{
    /* Place des bactéries à l'intérieur de l'assiette, en les ajoutant au vecteur
    des bactéries. Si elle est à l'extérieur, elle est détruite.
    Pour les bactéries issues de clonage (newBorn), elles sont placées dans le vecteur temporaire.
    Le retour permet de savoir si l'on a réussit à placer la bactérie*/

    if(contains(*bact)) {
        if(!newBorn) {
            Bact.push_back(bact); //pour bacteries non clones
        } else vecteur_clones.push_back(bact); //clones ajoutés dans le vecteur temporaire vecteur_clones
        return true;
    } else {
        delete bact;
        return false;
    }
}

void PetriDish::addSwarm(Swarm* LeSwamp)
{
    mesTroupes.push_back(LeSwamp); //ajout d'essaim de bactéries swarm
}
Swarm* PetriDish::getSwarmWithId(std::string id) const
{
    /* Retourne le pointeur vers le swarm avec l'identificateur correspondant,
    sinon retourne un nullptr */

    for(auto troupe : mesTroupes) {
        if(troupe->getId()==id) return troupe;
    }
    return nullptr;
}


// GESTION TEMPERATURE
double PetriDish::getTemperature() const
{
    return Temp;
}
void PetriDish::increaseTemperature()
{
    // Augmente la température d'un pas "Delta" puis vérifie si la nouvelle n'est pas trop élevée
    Temp+=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp> getAppConfig()["petri dish"]["temperature"]["max"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["max"].toDouble();
}
void PetriDish::decreaseTemperature()
{
    // Diminue la température de "Delta" puis vérifie si la nouvelle n'est pas trop faible
    Temp-=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp< getAppConfig()["petri dish"]["temperature"]["min"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["min"].toDouble();
}
void PetriDish::resetTemp()
{
    // Reprend la valeur par défaut
    Temp=getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}


// GESTION EXPOSANT GRADIENT (utilisé dans le calcul du score)
double PetriDish::getPositionScore(const Vec2d& pos) const
{
    // Retourne le score de la position, en sommant l'impact de tous les nutriments
    // Le calcul de l'impact de chaque nutriment est expliqué dans Nutriment::getScoreNutriment
    double score(0);
    for (auto&  nut : Nut)  score+=nut->getScoreNutriment(pos);
    return score;
}
double PetriDish::getGradientExponent() const
{
    return puissance;
}
void PetriDish::increaseGradientExponent()
{
    // Augmente l'exposant de "Delta" puis vérifie si la nouvelle n'est pas trop élevée
    puissance+=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance> getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble();
}
void PetriDish::decreaseGradientExponent()
{
    // Diminue l'exposant de "Delta" puis vérifie si la nouvelle n'est pas trop faible
    puissance-=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance< getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble();
}
void PetriDish::resetGradientExponent()
{
    // Reprend la valeur par défaut
    puissance=(getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+
               getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2;
}
Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{
    /* Cherche un nutriment en contact avec l'objet en argument, et retourne un pointeur
       vers le nutriment s'il y en a un, sinon le retourne nullptr */

    for(auto const nut : Nut) {
        if (nut->isColliding(body))
            return nut;
    }
    return nullptr;
}




std::unordered_map<std::string, double> PetriDish::fetchData(const std::string & titreGraph) const
{
    /*Méthode pour mettre à jour les graphs dans Stats. Une map temporaire (GraphTemp)
    est créée, remplie avec les valeurs nécessaires en fonction du titre en argument,
    et retournée.
    Pour la plupart des Graphs, on utilise un attribut static de Bacterium pour ne pas recalculer
    les valeurs à chaque itération*/

    std::unordered_map<std::string, double> GraphTemp; // map temporaire contenant les données

    // General graph update: les nombres en question sont directement mis à jour
    // dans les constructeurs, destructeurs, et méthodes de clonage de chaque sous-classe
    if(s::GENERAL == titreGraph) {
        GraphTemp[s::SIMPLE_BACTERIA] = Bacterium::accesMap()[s::SIMPLE_BACTERIA];
        GraphTemp[s::SWARM_BACTERIA] = Bacterium::accesMap()[s::SWARM_BACTERIA];
        GraphTemp[s::TWITCHING_BACTERIA] = Bacterium::accesMap()[s::TWITCHING_BACTERIA];
        GraphTemp[s::NUTRIMENT_SOURCES] = Bacterium::accesMap()[s::NUTRIMENT_SOURCES];
        GraphTemp[s::DISH_TEMPERATURE]=Temp; // PetriDish y a directement accés
    }

    // Nutriment Quantity Graph update: boucle sur tous les nutriments, en sommant l'energie de chacun
    if(s::NUTRIMENT_QUANTITY == titreGraph) {
        GraphTemp[s::NUTRIMENT_QUANTITY] = 0;
        for(auto chaq : Nut)  chaq->addToGraph(GraphTemp);
    }

    // Simple Bacteria Graph update: pour les simpleBacterium, les valeurs des tumble (paramètres mutables) sont ajoutées
    // dans le constructeur et la méthode clone, ou soustraites dans le destructeur
    if(s::SIMPLE_BACTERIA == titreGraph) {
        if(Bacterium::accesMap()[s::SIMPLE_BACTERIA]!=0) {
            GraphTemp[s::BETTER]=Bacterium::accesMap()[s::BETTER]/Bacterium::accesMap()[s::SIMPLE_BACTERIA]; // Moyenne sur les
            GraphTemp[s::WORSE]=Bacterium::accesMap()[s::WORSE]/Bacterium::accesMap()[s::SIMPLE_BACTERIA];  // SimpleBacterium
        } else {
            GraphTemp[s::BETTER]=0; // Pour éviter la division par 0
            GraphTemp[s::WORSE]=0;
        }
    }


    // Twitching Bacteria Graph update: pour les twitchingBacterium, les longueurs et vitesse des tentacules (paramètres mutables)
    // sont ajoutées dans le constructeur et la méthode clone, ou soustraites dans le destructeur
    if(s::TWITCHING_BACTERIA == titreGraph) {
        if(Bacterium::accesMap()[s::TWITCHING_BACTERIA]!=0) {
            GraphTemp[s::TENTACLE_LENGTH]=Bacterium::accesMap()[s::TENTACLE_LENGTH]/Bacterium::accesMap()[s::TWITCHING_BACTERIA]; // Moyenne sur les
            GraphTemp[s::TENTACLE_SPEED]=Bacterium::accesMap()[s::TENTACLE_SPEED]/Bacterium::accesMap()[s::TWITCHING_BACTERIA]; // TwitchingBacterium
        } else {
            GraphTemp[s::TENTACLE_LENGTH]=0; // Pour éviter la division par 0
            GraphTemp[s::TENTACLE_SPEED]=0;
        }
    }


    // Bacteria Graph update: pour toutes les bactéries, les vitesses (paramètres mutables)
    // sont ajoutées dans le constructeur et la méthode clone, ou soustraites dans le destructeur
    // Pour les twitchingBacterium il s'agit de la vitesse du grapin multipliée par le speed factor.
    if(s::BACTERIA == titreGraph) {
        double nbBact(Bacterium::accesMap()[s::SIMPLE_BACTERIA] + Bacterium::accesMap()[s::SWARM_BACTERIA] + Bacterium::accesMap()[s::TWITCHING_BACTERIA]);
        if(nbBact) // Pour éviter la division par 0
            GraphTemp[s::SPEED] = Bacterium::accesMap()[s::SPEED]/nbBact; // Moyenne sur toutes les bactéries
        else GraphTemp[s::SPEED] = 0;
    }

    return GraphTemp;
}

void PetriDish::reset()
{
    /* Supprime tout ce que contient l'assiette: on détruit les objets pointés,
    puis on vide les vecteurs de pointeurs.
    Remet les paramètres à leur valeur par défaut */

    for (auto& objet : Nut)
        delete objet;
    Nut.clear();
    for (auto& objet : Bact)
        delete objet;
    Bact.clear();
    for (auto& objet : mesTroupes)
        delete objet;
    mesTroupes.clear();

    resetTemp();
    resetGradientExponent();
}

//Destructeur
PetriDish::~PetriDish()
{
    /* Responsable de supprimer ce que l'assiette contient*/
    reset();
}

