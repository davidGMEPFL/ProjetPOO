#include "Bacterium.hpp"
#include "Application.hpp"

using namespace std;

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur)
    : CircularBody(position,rayon), couleur(couleur), direction(direction),abstinence(false),
        energie(energie), TimeLastMeal(sf::Time::Zero)
{}

void Bacterium::drawOn(sf::RenderTarget& target) const{
    auto const circle = buildCircle(position, rayon, couleur.get());
    target.draw(circle);

    if (isDebugOn()){
        auto const text = buildText(std::to_string(int(energie)),position + Vec2d(0,-100),
                                    getAppFont(),18,sf::Color::Red);
        target.draw(text);
    }
}


void Bacterium::update(sf::Time dt){
    move(dt);
    TimeLastMeal+=dt;
    if(getAppEnv().doesCollideWithDish(*this)) direction=-direction;
    Nutriment* NutrProxi(nullptr);
    if ( (NutrProxi=getAppEnv().getNutrimentColliding(*this)) != nullptr &&
            TimeLastMeal > getTempsDelay() && !abstinence){
        TimeLastMeal=sf::Time::Zero;
        energie+=NutrProxi->takeQuantity(mealMax());
    }
}

void Bacterium::consumeEnergy(Quantity qt){
    energie-=qt;
}
bool Bacterium::testMort(){
    return energie<=0;
}

void Bacterium::mutate(){
    couleur.mutate();
    std::map<std::string, MutableNumber>::iterator it = Params.begin();
    while (it != Params.end())
        {
            it->second.mutate();
            it++;
        }
}

//Getters utilitaires
double Bacterium::getMinEnDiv(){    return getConfig()["energy"]["division"].toDouble();
}
sf::Time Bacterium::getTempsDelay(){    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}
double Bacterium::EnergieDepl(){    return getConfig()["energy"]["consumption factor"].toDouble();
}
double Bacterium::mealMax(){    return getConfig()["meal"]["max"].toDouble();
}

void Bacterium::addProperty(const string& key, MutableNumber valeur){
    Params[key]=valeur;
}

MutableNumber& Bacterium::getProperty(const string& key){
    return Params[key];
}
