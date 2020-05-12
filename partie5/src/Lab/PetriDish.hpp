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
    std::vector<Swarm*> mesTroupes;
    double Temp;
    double puissance;


public:
    std::vector<Bacterium*> vecteur_clones;//Vecteur temporaire de pointeurs vers bactéries clonées

    // Constructeurs
    PetriDish(Vec2d position,double rayon);
    PetriDish& operator=(const PetriDish&) = delete;
    PetriDish(PetriDish const&) = delete;

    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;


    //Methodes d'additions
    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const&);
    void addSwarm(Swarm*);
    Swarm* getSwarmWithId(std::string id) const;





    // Méthodes de calcul du score et d'alimentation
    double getPositionScore(const Vec2d&) const;
    double getGradientExponent() const;
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();
    Nutriment* getNutrimentColliding(CircularBody const& body) const;



    // Méthodes de température
    double getTemperature() const;
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();

    std::unordered_map<std::string, double> fetchData(const std::string &);



    void reset();

    //Destructeur
    ~PetriDish();
};
