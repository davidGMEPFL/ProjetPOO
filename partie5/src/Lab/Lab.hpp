#pragma once
#include "PetriDish.hpp"
#include "NutrimentGenerator.hpp"


class Lab: public Updatable, public Drawable
{
private:
    PetriDish Petri;
    NutrimentGenerator Generator;

public:
    Lab();

// Méthodes utilitaires
    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time);
    bool contains(const CircularBody&) const;

// Ajout des bactéries et nutriments
    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const& newBorn=false); //s'occupera d'ajouter les clones dans PetriDish
    void addSwarm(Swarm*);
    Swarm* getSwarmWithId(std::string id) const; // retourne le swarm demandé

// Tests des collisions
    Nutriment* getNutrimentColliding(CircularBody const& body) const;
    bool doesCollideWithDish(CircularBody const& body) const;


// Gestion de la température de l'assiette de Petri
    double getTemperature() const;
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();


// Gestion de l'exposant de gradient
    double getPositionScore(const Vec2d&) const;
    double getGradientExponent() const;
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();

    std::unordered_map<std::string, double> fetchData(const std::string &)const;

    void reset();
};
