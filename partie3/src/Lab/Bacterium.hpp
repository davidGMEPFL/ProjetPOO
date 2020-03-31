#pragma once
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CircularBody.hpp"
#include "Utility/MutableColor.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include <vector>
#include <string>

class Bacterium: public Drawable, public Updatable, public CircularBody
{
    MutableColor couleur;
    Vec2d direction;
    bool etat;
    Quantity energie;
    bool abstinence;
    std::map<std::string, MutableNumber> Params;
    sf::Time TimeLastMeal;

public:
    Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur);
    virtual void move(sf::Time dt)=0;
    virtual Bacterium* clone() const=0;

    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time dt);
    void consumeEnergy(Quantity qt);
    bool testMort();

    virtual j::Value& getConfig() const =0;

    bool doesCollideWithDish(CircularBody const& body);

    double getMinEnDiv();
    sf::Time getTempsDelay();
    double EnergieDepl();
    double mealMax();
};
