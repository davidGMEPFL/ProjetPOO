#pragma once
#include "SFML/Graphics.hpp"

class NutrimentGenerator : public
{
    sf::Time TimeLastGen;
public:
    NutrimentGenerator();
    void update(sf::Time);
    void reset();
};
