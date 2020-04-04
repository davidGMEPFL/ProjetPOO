#pragma once
#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility/Vec2d.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include <math.h>

class PetriDish: public CircularBody, public Updatable, public Drawable
{
protected:
    std::vector<Nutriment*> Nut;
    std::vector<Bacterium*> Bact;
    double Temp;
    double puissance;

public:
    // Constructeurs
    PetriDish(Vec2d position,double rayon);
    PetriDish& operator=(const PetriDish&) = delete;
    PetriDish(PetriDish const&) = delete;

    //Methodes
    bool addBacterium(Bacterium*);
    Nutriment* getNutrimentColliding(CircularBody const& body);

    double getPositionScore(const Vec2d&);
    double getGradientExponent();
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();

    bool addNutriment(Nutriment*);

    void update(sf::Time dt);
    double getTemperature();
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();

    void drawOn(sf::RenderTarget& targetWindow) const;

    void reset();

    //Destructeur
    ~PetriDish();
};
