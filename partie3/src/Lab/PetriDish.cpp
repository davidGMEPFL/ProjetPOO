#include "PetriDish.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"

//Constructeur
PetriDish::PetriDish(Vec2d position,double rayon):
    CircularBody(position,rayon),Temp(getAppConfig()["petri dish"]["temperature"]["default"].toDouble()), puissance((getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2)
{}

//Methodes
bool PetriDish::addBacterium(Bacterium* bact){
    //permettra de peupler l'assiette
    //bool sert à savoir si l'on a réussit à placer la bactérie
    if(contains(*bact)) Bact.push_back(bact);
    return contains(*bact);
}
Nutriment* PetriDish::getNutrimentColliding(CircularBody const& body){
    for(auto const nut : Nut) {
        if (nut->isColliding(body))
            return nut;
    }
    return nullptr;
}

bool PetriDish::addNutriment(Nutriment* nut){
    //place des nutriments dans l'assiette
    //bool sert à savoir si l'on a réussit à placer le nutriment
    if(contains(*nut)) Nut.push_back(nut);
    return contains(*nut);
}

double PetriDish::getTemperature(){
    return Temp;
}
void PetriDish::increaseTemperature(){
    Temp+=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp> getAppConfig()["petri dish"]["temperature"]["max"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["max"].toDouble();
}
void PetriDish::decreaseTemperature(){
    Temp-=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
    if(Temp< getAppConfig()["petri dish"]["temperature"]["min"].toDouble())
        Temp=getAppConfig()["petri dish"]["temperature"]["min"].toDouble();
}
void PetriDish::resetTemp(){
    Temp=getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}



double PetriDish::getGradientExponent(){
    return puissance;
}
void PetriDish::increaseGradientExponent(){
    puissance+=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance> getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble();
}
void PetriDish::decreaseGradientExponent(){
    puissance-=getAppConfig()["petri dish"]["gradient"]["exponent"]["delta"].toDouble();
    if(puissance< getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())
        puissance=getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble();
}
void PetriDish::resetGradientExponent(){
    puissance=(getAppConfig()["petri dish"]["gradient"]["exponent"]["max"].toDouble()+getAppConfig()["petri dish"]["gradient"]["exponent"]["min"].toDouble())/2;
}


void PetriDish::update(sf::Time dt){
    //fait évoluer toutes les bactéries de l'assiette à chaque pas de temps
    for (auto& objet : Nut) {
        objet->update(dt);
        if(objet->testEpuise())objet=nullptr;
    }
    Nut.erase(std::remove(Nut.begin(), Nut.end(), nullptr), Nut.end());

    for (auto& objet : Bact) {
        objet->update(dt);
        if(objet->testMort()) objet=nullptr;
    }
    Bact.erase(std::remove(Bact.begin(), Bact.end(), nullptr), Bact.end());
}
void PetriDish::drawOn(sf::RenderTarget& targetWindow) const {
    //dessine sur une fenêtre graphique le contour de l'assiette
    sf::Color couleur(sf::Color::Black);
    double epaisseur(5);
    auto border = buildAnnulus(position, rayon, couleur, epaisseur);
    targetWindow.draw(border);
    for (auto& nutr : Nut) nutr->drawOn(targetWindow);
    for (auto& bac : Bact) bac->drawOn(targetWindow);
}
void PetriDish::reset(){
    //supprime toutes les nutriments et toutes les bactéries de l'assiette
    for (auto& objet : Nut)
        delete objet;
    Nut.clear();
    resetTemp();
    resetGradientExponent();
}

double PetriDish::getPositionScore(const Vec2d& pos){
    double score(0);
    for (auto&  nut : Nut)  score+=nut->getScoreNutriment(pos);
    return score;
}



//Destructeur
PetriDish::~PetriDish(){
    reset();
}
