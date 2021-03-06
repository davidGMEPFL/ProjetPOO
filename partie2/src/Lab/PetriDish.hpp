#pragma once
#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility/Vec2d.hpp"

class PetriDish: public CircularBody
{
    std::vector<Nutriment*> Nut;
    std::vector<Bacterium*> Bact;
    double Temp;

public:
    // Constructeurs
    PetriDish(Vec2d position,double rayon);
    PetriDish& operator=(const PetriDish&) = delete;
    PetriDish(PetriDish const&) = delete;

    //Methodes
    bool addBacterium(Bacterium*);
    bool addNutriment(Nutriment*);

    void update(sf::Time dt);
    double getTemperature();
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();

    void drawOn(sf::RenderTarget& targetWindow)const;

    void reset();

    //Destructeur
    ~PetriDish();
};
