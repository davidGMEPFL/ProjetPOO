#include "Lab.hpp"
#include "Application.hpp"

Lab::Lab():
    Petri(getApp().getCentre(),0.5*.95*getApp().getLabSize().x)
{}


void Lab::drawOn(sf::RenderTarget& targetWindow) const
{
    Petri.drawOn(targetWindow);
}

void Lab::update(sf::Time dt)
{
    Generator.update(dt);
    Petri.update(dt);
}
void Lab::reset()
{
    Petri.reset();
    Generator.reset();
}

bool Lab::contains(const CircularBody& autre)
{
    return Petri.contains(autre);
}



//AJOUT BACTERIES ET NUTRIMENTS :

bool Lab::addNutriment(Nutriment* nut)
{
    return Petri.addNutriment(nut);
}
bool Lab::addBacterium(Bacterium* bact, bool const& newBorn)
{
    return Petri.addBacterium(bact,newBorn);
}
void Lab::addSwarm(Swarm* LeSwarm)
{
    Petri.addSwarm(LeSwarm);
}



//test des collisions
bool Lab::doesCollideWithDish(CircularBody const& body)
{
    return (distance(body.getPosition(),Petri.getPosition())>=(Petri.getRadius()-body.getRadius()));
}
Nutriment* Lab::getNutrimentColliding(CircularBody const& body)
{
    return Petri.getNutrimentColliding(body);
}

//somme tous les scores de l'environnement autour de la bacétrie dans Petri
double Lab::getPositionScore(const Vec2d& pos)
{
    return Petri.getPositionScore(pos);
}


Swarm* Lab::getSwarmWithId(std::string id) const {
    return Petri.getSwarmWithId(id);
}


// GESTION TEMP :
double Lab::getTemperature()
{
    return Petri.getTemperature();
}
void Lab::increaseTemperature()
{
    Petri.increaseTemperature();
}
void Lab::decreaseTemperature()
{
    Petri.decreaseTemperature();
}
void Lab::resetTemp()
{
    Petri.resetTemp();
}

// GESTION GRADIENT :
double Lab::getGradientExponent()
{
    return Petri.getGradientExponent();
}
void Lab::increaseGradientExponent()
{
    Petri.increaseGradientExponent();
}
void Lab::decreaseGradientExponent()
{
    Petri.decreaseGradientExponent();
}
void Lab::resetGradientExponent()
{
    Petri.resetGradientExponent();
}


std::unordered_map<std::string, double> Lab::fetchData(const std::string & titreGraph){
    return Petri.fetchData(titreGraph);
}
