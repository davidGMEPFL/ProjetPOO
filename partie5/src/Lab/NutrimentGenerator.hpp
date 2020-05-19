#pragma once
#include "SFML/Graphics.hpp"

class NutrimentGenerator
{
    sf::Time TimeLastGen;
public:
    NutrimentGenerator();

    void update(sf::Time); //ajoute de façon aléatoire des nutriments au fil du temps
    void reset();
};
