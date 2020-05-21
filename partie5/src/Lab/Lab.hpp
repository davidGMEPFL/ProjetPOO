#pragma once
#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "Bacterium.hpp"
#include "Swarm.hpp"
#include "CircularBody.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include "NutrimentGenerator.hpp"

class Lab: public Updatable, public Drawable
{
private:
    PetriDish Petri;
    NutrimentGenerator Generator;
public:
    Lab();

// Appels aux méthodes sur l'assiette Petri
    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time);
    bool contains(const CircularBody&) const;

// Ajout des bactéries et nutriments
    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const& newBorn=false); //s'occupera d'ajouter les clones dans PetriDish
    void addSwarm(Swarm*);

    Swarm* getSwarmWithId(std::string id) const; // Retourne le swarm demandé

    bool doesCollideWithDish(CircularBody const& body) const; // Vérifie si en contact avec bord assiette


// Gestion de la température de l'assiette de Petri
    double getTemperature() const;
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();


// Méthodes de calcul du score et d'alimentation
    double getPositionScore(const Vec2d&) const;
    double getGradientExponent() const;
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();
    Nutriment* getNutrimentColliding(CircularBody const& body) const;



    std::unordered_map<std::string, double> fetchData(const std::string &);

    void reset();

};
