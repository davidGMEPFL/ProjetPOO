#pragma once
#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "Swarm.hpp"
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
    std::vector<Swarm*> troupe;
    double Temp;
    double puissance;


public:
    std::vector<Bacterium*> vecteur_clones;//Vecteur temporaire de pointeurs vers bactéries clonées

    // Constructeurs
    PetriDish(Vec2d position,double rayon);
    PetriDish& operator=(const PetriDish&) = delete;
    PetriDish(PetriDish const&) = delete;

    //Methodes
    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const&);

    void addSwarm(Swarm*);


    Nutriment* getNutrimentColliding(CircularBody const& body);


    double getPositionScore(const Vec2d&);
    double getGradientExponent();
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();



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
