#include "PetriDish.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"
#include "Bacterium.hpp"
#include <numeric>
#include <iostream>

using namespace std;

//Constructeur
PetriDish::PetriDish(Vec2d position,double rayon):
    CircularBody(position,rayon),
    Temp(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()),
    puissance((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+
               getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2)
{}



void PetriDish::update(sf::Time dt)
{
    //fait évoluer toutes les bactéries de l'assiette à chaque pas de temps
    for (auto& objet : Nut) {
        objet->update(dt);
        if(objet->testEpuise()){
            delete objet;
            objet=nullptr;}
    }
    Nut.erase(std::remove(Nut.begin(), Nut.end(), nullptr), Nut.end());

    for(auto& troupe : mesTroupes){
        troupe->update(dt);
    }

    for (auto& objet : Bact) {
        objet->update(dt);
        if(objet->testMort()) {
            delete objet;
            objet=nullptr;}
    }
    if(!vecteur_clones.empty()) {
        append(vecteur_clones,Bact);
        vecteur_clones.clear();
    }
    vecteur_clones.erase(std::remove(vecteur_clones.begin(), vecteur_clones.end(), nullptr), vecteur_clones.end());
    Bact.erase(std::remove(Bact.begin(), Bact.end(), nullptr), Bact.end());
}
void PetriDish::drawOn(sf::RenderTarget& targetWindow) const
{
    //dessine sur une fenêtre graphique le contour de l'assiette
    sf::Color couleur(sf::Color::Black);
    double epaisseur(5);
    auto border = buildAnnulus(position, rayon, couleur, epaisseur);
    targetWindow.draw(border);
    for (auto& nutr : Nut) nutr->drawOn(targetWindow);
    for (auto& bac : Bact) bac->drawOn(targetWindow);
}


//Methodes
bool PetriDish::addNutriment(Nutriment* nut)
{
    //place des nutriments dans l'assiette
    //bool sert à savoir si l'on a réussit à placer le nutriment
    if(contains(*nut)) Nut.push_back(nut);
    else delete nut;
    return contains(*nut);
}

bool PetriDish::addBacterium(Bacterium* bact,bool const& newBorn)
{
    if(contains(*bact)){  //bool sert à savoir si l'on a réussit à placer la bactérie
        if(!newBorn) {   //pour bacteries non clones
            Bact.push_back(bact);
        } else vecteur_clones.push_back(bact);} //on ajoute les clones contenus dans le vecteur temporaire vecteur_clones,
                                               //dans le vecteur des bactéries appartenant à l'assiette
    else delete bact;
    return contains(*bact);
}

void PetriDish::addSwarm(Swarm* LeSwamp){
    mesTroupes.push_back(LeSwamp);
}

Swarm* PetriDish::getSwarmWithId(std::string id) const {
    for(auto troupe : mesTroupes){
        if(troupe->getId()==id) return troupe;
    }
    return nullptr;
}



Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body) const
{
    for(auto const nut : Nut) {
        if (nut->isColliding(body))
            return nut;
    }
    return nullptr;
}







double PetriDish::getTemperature() const
{
    return Temp;
}
void PetriDish::increaseTemperature()
{
    Temp+=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp> getAppConfig()["petri dish"]["temperature"]["max"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["max"].toDouble();
}
void PetriDish::decreaseTemperature()
{
    Temp-=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp< getAppConfig()["petri dish"]["temperature"]["min"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["min"].toDouble();
}
void PetriDish::resetTemp()
{
    Temp=getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}



double PetriDish::getGradientExponent() const
{
    return puissance;
}
void PetriDish::increaseGradientExponent()
{
    puissance+=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance> getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble();
}
void PetriDish::decreaseGradientExponent()
{
    puissance-=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance< getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble();
}
void PetriDish::resetGradientExponent()
{
    puissance=(getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+
               getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2;
}



void PetriDish::reset()
{
    //supprime toutes les nutriments et toutes les bactéries de l'assiette
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

double PetriDish::getPositionScore(const Vec2d& pos) const
{
    double score(0);
    for (auto&  nut : Nut)  score+=nut->getScoreNutriment(pos);
    return score;
}

std::unordered_map<std::string, double> PetriDish::fetchData(const std::string & titreGraph){
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
        GraphTemp[s::TENTACLE_LENGTH]=std::accumulate(TentaculeLongueur.begin(), TentaculeLongueur.end(), 0.0)/TentaculeLongueur.size();
        GraphTemp[s::TENTACLE_SPEED]=std::accumulate(TentaculeVitesse.begin(), TentaculeVitesse.end(), 0.0)/TentaculeVitesse.size();
    }


    if(s::BACTERIA == titreGraph){
        vector<double> Speed;
        for(auto chaq : Bact) chaq->getSpeed(Speed);

        GraphTemp[s::SPEED]=std::accumulate(Speed.begin(), Speed.end(), 0.0)/Speed.size();
        GraphTemp[s::TENTACLE_SPEED]=std::accumulate(Speed.begin(), Speed.end(), 0.0)/Speed.size();
    }

    return GraphTemp;
}


//Destructeur
PetriDish::~PetriDish()
{
    reset();
}

