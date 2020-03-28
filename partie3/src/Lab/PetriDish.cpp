#include "PetriDish.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"

//Constructeur
PetriDish::PetriDish(Vec2d position,double rayon):
    CircularBody(position,rayon),Temp(getAppConfig()["petri dish"]["temperature"]["default"].toDouble())
{}

//Methodes
bool PetriDish::addBacterium(Bacterium*){
    //permettra de peupler l'assiette
    //bool sert à savoir si l'on a réussit à placer la bactérie
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
}
void PetriDish::decreaseTemperature(){
    Temp-=getAppConfig()["petri dish"]["temperature"]["delta"].toDouble();
}
void PetriDish::resetTemp(){
    Temp=getAppConfig()["petri dish"]["temperature"]["default"].toDouble();
}


void PetriDish::update(sf::Time dt){
    //fait évoluer toutes les bactéries de l'assiette à chaque pas de temps
    for (auto& objet : Nut) objet->update(dt);
}
void PetriDish::drawOn(sf::RenderTarget& targetWindow) const {
    //dessine sur une fenêtre graphique le contour de l'assiette
    sf::Color couleur(sf::Color::Black);
    double epaisseur(5);
    auto border = buildAnnulus(position, rayon, couleur, epaisseur);
    targetWindow.draw(border);
    for (auto& nutr : Nut) nutr->drawOn(targetWindow);
}
void PetriDish::reset(){
    //supprime toutes les nutriments et toutes les bactéries de l'assiette
    for (auto& objet : Nut)
        delete objet;
    Nut.clear();
    resetTemp();
}


//Destructeur
PetriDish::~PetriDish(){
    reset();
}
