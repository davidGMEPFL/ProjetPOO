#pragma once
#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "CircularBody.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"

class Lab: public Updatable, public Drawable
{
public:
    PetriDish Petri;
public:
    Lab();
    void drawOn(sf::RenderTarget&) const;
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
