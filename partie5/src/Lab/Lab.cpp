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

bool Lab::contains(const CircularBody& autre) const
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
Swarm* Lab::getSwarmWithId(std::string id) const {
    return Petri.getSwarmWithId(id);
}


bool Lab::doesCollideWithDish(CircularBody const& body) const
{   /* Vérifie que l'objet en argument touche les bords de l'assiette: sa distance
    par rapport au centre de l'assiette + son rayon, doit dépasser le rayon de l'asstiete */
    return (distance(body.getPosition(),Petri.getPosition())>=(Petri.getRadius()-body.getRadius()));
}




// GESTION TEMP :
double Lab::getTemperature() const
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
double Lab::getPositionScore(const Vec2d& pos) const
{
    return Petri.getPositionScore(pos);
}
double Lab::getGradientExponent() const
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
Nutriment* Lab::getNutrimentColliding(CircularBody const& body) const
{
    return Petri.getNutrimentColliding(body);
}

std::unordered_map<std::string, double> Lab::fetchData(const std::string & titreGraph){
    return Petri.fetchData(titreGraph);
}

void Lab::reset()
{
    Petri.reset();
    Generator.reset();
}
