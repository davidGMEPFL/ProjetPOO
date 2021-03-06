#pragma once
#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include "Swarm.hpp"
#include "CircularBody.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include "NutrimentGenerator.hpp"

class Lab: public Updatable, public Drawable
{
private:
    PetriDish Petri;
    NutrimentGenerator Generator;
public:
    Lab();
    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time);
    void reset();
    bool contains(const CircularBody&);


    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const& newBorn=false);
    void addSwarm(Swarm*);


    bool doesCollideWithDish(CircularBody const& body);
    Nutriment* getNutrimentColliding(CircularBody const& body);
    double getPositionScore(const Vec2d&);

    Swarm* getSwarmWithId(std::string id) const;

// Gestion de la température de l'assiette de Petri
    double getTemperature();
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();


// Gestion de l'exposant du gradient pour l'assiette de Petri
    double getGradientExponent();
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();

};
