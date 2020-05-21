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



void PetriDish::update(sf::Time dt)
{   /* Fait évoluer tout ce que contient  l'assiette à chaque pas de temps,
    en appelant de façon polymorphique leur méthode update respective
    La méthode appelle testEpuise et testMort pour vérifier si les objets doivent
    être supprimés et modifie les vecteurs si nécessaire */

    for (auto& objet : Nut) {
        objet->update(dt);
        if(objet->testEpuise()){ // Verifie si le nombre de nutriments de nutriments est nul
            delete objet;   // libère la mémoire de l'objet pointé (appelle destructeur)
            objet=nullptr;} // nécessaire pour enlever le pointeur du vecteur
    }
    Nut.erase(std::remove(Nut.begin(), Nut.end(), nullptr), Nut.end()); // permet d'enlever tous les
                                                                    // nullptr du vecteur de pointeurs

    for(auto& troupe : mesTroupes){ // un swarm ne peut pas mourrir donc pas de gestion nécessaire
        troupe->update(dt);
    }

    for (auto& objet : Bact) {
        objet->update(dt);
        if(objet->testMort()) { // Verifie si l'energie de la bactérie est trop faible (<=0)
            delete objet;
            objet=nullptr;}
    }
    if(!vecteur_clones.empty()) { // si le vecteur de clones n'est pas vide
        append(vecteur_clones,Bact); // Ajoute les pointeurs sur les clones au vecteur de pointeurs
        vecteur_clones.clear(); // Empêched d'ajouter les clones plus d'une fois
    }
    vecteur_clones.erase(std::remove(vecteur_clones.begin(), vecteur_clones.end(), nullptr),
                         vecteur_clones.end());
    Bact.erase(std::remove(Bact.begin(), Bact.end(), nullptr), Bact.end());
}
void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{   /*Dessine sur une fenêtre graphique le contour de l'assiette
    Fait appel aux méthodes de dessin de ses attibuts déssinables
    de façon polymorphique*/
    sf::Color couleur(sf::Color::Black);
    double epaisseur(5);
    auto border = buildAnnulus(position, rayon, couleur, epaisseur);
    targetWindow.draw(border);
    for (auto& nutr : Nut) nutr->drawOn(targetWindow);
    for (auto& bac : Bact) bac->drawOn(targetWindow);
}


//Methodes d'ajout d'objets dans l'assiette
bool PetriDish::addNutriment(Nutriment* nut)
{   /* Place des nutriments à l'intérieur de l'assiette
    en les ajoutant au vecteurs des nutriments
    Si le nutriment est à l'extérieur, il est détruit
    Le retour permet de savoir si l'on a réussit à placer le nutriment*/
    bool testContain(contains(*nut));
    if(testContain)     Nut.push_back(nut);
    else    delete nut;
    return testContain;
}
bool PetriDish::addBacterium(Bacterium* bact,bool const& newBorn)
{   /* Place des bactéries à l'intérieur de l'assiette
    Si la bactérie est à l'extérieur, elle est détruite
    Les bactéries issues de clonage (newBorn) sont placées dans le vecteur temporaire
    les autres dans le vecteur des bactéries
    Le retour permet de savoir si l'on a réussit à placer la bactérie*/
    if(contains(*bact)){
        if(!newBorn) {
            Bact.push_back(bact); //pour bacteries non clones
        } else vecteur_clones.push_back(bact); //clones ajoutés dans le vecteur temporaire vecteur_clones,
        return true;}
    else { delete bact;
        return false;   }
}
void PetriDish::addSwarm(Swarm* LeSwamp){
    mesTroupes.push_back(LeSwamp);
}
Swarm* PetriDish::getSwarmWithId(std::string id) const
{   /*Retourne le pointeur vers le swarm avec identificateur correspondant
    sinon, retourne un nullptr*/
    for(auto troupe : mesTroupes){
        if(troupe->getId()==id) return troupe;
    }
    return nullptr;
}





// Gestion de la température
double PetriDish::getTemperature() const
{
    return Temp;
}
void PetriDish::increaseTemperature()
{   // Augmente la température de "Delta" puis vérifie si la nouvelle n'est pas trop élevée
    Temp+=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp> getAppConfig()["petri dish"]["temperature"]["max"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["max"].toDouble();
}
void PetriDish::decreaseTemperature()
{   // Diminue la température de "Delta" puis vérifie si la nouvelle n'est pas trop faible
    Temp-=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp< getAppConfig()["petri dish"]["temperature"]["min"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["min"].toDouble();
}
void PetriDish::resetTemp()
{   // Reprend la valeur par défaut
    Temp=getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}


// Gestion de l'exposant du gradient utilisé dans le calcul du score
double PetriDish::getPositionScore(const Vec2d& pos) const
{   // Retourne le score de la position, en sommant l'impact de tous les nutriments
    // Le calcul de l'impact de chaque nutriment est expliqué dans nutriment::getScoreNutriment
    double score(0);
    for (auto&  nut : Nut)  score+=nut->getScoreNutriment(pos);
    return score;
}
double PetriDish::getGradientExponent() const
{
    return puissance;
}
void PetriDish::increaseGradientExponent()
{   // Augmente l'exposant de "Delta" puis vérifie si la nouvelle n'est pas trop élevée
    puissance+=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance> getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble();
}
void PetriDish::decreaseGradientExponent()
{   // Diminue l'exposant de "Delta" puis vérifie si la nouvelle n'est pas trop faible
    puissance-=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance< getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble();
}
void PetriDish::resetGradientExponent()
{   // Reprend la valeur par défaut
    puissance=(getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+
               getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2;
}
Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{   /* Cherche un nutriment en cantact avec l'objet en argument, et retourne un pointeur
    vers le nutriment s'il y en a un, et sinon retourne un nullptr */
    for(auto const nut : Nut) {
        if (nut->isColliding(body))
            return nut;
    }
    return nullptr;
}




std::unordered_map<std::string, double> PetriDish::fetchData(const std::string & titreGraph)
{

    std::unordered_map<std::string, double> GraphTemp;

    // General graph update
    if(s::GENERAL == titreGraph){
        GraphTemp[s::SIMPLE_BACTERIA] = 0;
        GraphTemp[s::SWARM_BACTERIA] = 0;
        GraphTemp[s::TWITCHING_BACTERIA] = 0;
        GraphTemp[s::NUTRIMENT_SOURCES] = 0;
        GraphTemp[s::DISH_TEMPERATURE]=Temp;

        for(auto chaq : Bact) chaq->addToGraph(titreGraph, GraphTemp);
        for(auto chaq : Nut)  chaq->addToGraph(titreGraph, GraphTemp);

    }

    if(s::NUTRIMENT_QUANTITY == titreGraph){
        GraphTemp[s::NUTRIMENT_QUANTITY] = 0;
        for(auto chaq : Nut)  chaq->addToGraph(titreGraph, GraphTemp);
    }

    if(s::SIMPLE_BACTERIA == titreGraph){
        vector<double> Better;
        vector<double> Worse;
        for(auto chaq : Bact)  chaq->getDataSimple(Better, Worse);

        GraphTemp[s::BETTER]=(float)std::accumulate(Better.begin(), Better.end(), 0.0)/Better.size();
        GraphTemp[s::WORSE]=(float)std::accumulate(Worse.begin(), Worse.end(), 0.0)/Worse.size();
    }

    // Twitching Bacterium graph update
    if(s::TWITCHING_BACTERIA == titreGraph){
        vector<double> TentaculeLongueur;
        vector<double> TentaculeVitesse;

        for(auto chaq : Bact)  chaq->getDataTwitching(TentaculeLongueur,TentaculeVitesse);
        GraphTemp[s::TENTACLE_LENGTH]=std::accumulate(TentaculeLongueur.begin(),
                                                      TentaculeLongueur.end(), 0.0)/TentaculeLongueur.size();
        GraphTemp[s::TENTACLE_SPEED]=std::accumulate(TentaculeVitesse.begin(),
                                                     TentaculeVitesse.end(), 0.0)/TentaculeVitesse.size();
    }


    if(s::BACTERIA == titreGraph){
        vector<double> Speed;
        for(auto chaq : Bact) chaq->getSpeed(Speed);

        GraphTemp[s::SPEED]=std::accumulate(Speed.begin(), Speed.end(), 0.0)/Speed.size();
        GraphTemp[s::TENTACLE_SPEED]=std::accumulate(Speed.begin(), Speed.end(), 0.0)/Speed.size();
    }

    return GraphTemp;
}

void PetriDish::reset()
{   /*supprime tout ce que contient l'assiette: on détruit les objets pointés,
    puis on vide les vecteurs de pointeurs.
    Remet les paramètres à leurs valeurs par défaut*/
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
{   /* Le destructeur est responsable de supprimer ce que l'assiette contient*/
    reset();
}

