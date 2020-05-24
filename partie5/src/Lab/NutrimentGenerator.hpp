#pragma once
#include "Interface/Updatable.hpp"

class NutrimentGenerator : public Updatable
{
    sf::Time TimeLastGen;
public:
    NutrimentGenerator();

    void update(sf::Time); //ajoute de façon aléatoire des nutriments au fil du temps
    void reset(); //remise du chrono à zéro
};
