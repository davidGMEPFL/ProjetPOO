#pragma once
#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <SFML/Graphics.hpp>

class Lab
{
public:
    PetriDish Petri;
public:
    Lab();
    void drawOn(sf::RenderTarget&);
    void update(sf::Time);
    void reset();
    bool contains(const CircularBody&);

    bool addNutriment(Nutriment*);

// Gestion de la température de l'assiette de Petri
    double getTemperature();
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();
};
