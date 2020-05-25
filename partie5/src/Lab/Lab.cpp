#include "Lab.hpp"
#include "Application.hpp"

Lab::Lab():
    Petri(getApp().getCentre(),0.5*.95*getApp().getLabSize().x)
{}


// Méthodes utilitaires (appels aux méthodes de PetriDish + NutrimentGenerator):
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



//AJOUT BACTERIES ET NUTRIMENTS (appels aux méthodes de PetriDish):
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
Swarm* Lab::getSwarmWithId(std::string id) const
{
    return Petri.getSwarmWithId(id);
}

//Tests des collisions
bool Lab::doesCollideWithDish(CircularBody const& body) const
{
    /* Vérifie si l'objet en argument touche les bords de l'assiette: sa distance
    par rapport au centre de l'assiette + son rayon, doit dépasser le rayon de l'asstiete */

    return (distance(body.getPosition(),Petri.getPosition())>=(Petri.getRadius()-body.getRadius()));
}
Nutriment* Lab::getNutrimentColliding(CircularBody const& body) const
{
    return Petri.getNutrimentColliding(body);
}

// GESTION TEMP (appels aux méthodes de PetriDish):
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


// GESTION GRADIENT (appels aux méthodes de PetriDish):
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



std::unordered_map<std::string, double> Lab::fetchData(const std::string & titreGraph) const
{
    return Petri.fetchData(titreGraph);
}

void Lab::reset() //(appels aux méthodes de PetriDish + NutrimentGenerator)
{
    Petri.reset();
    Generator.reset();
}
