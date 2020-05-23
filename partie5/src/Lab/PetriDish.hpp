#pragma once
#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "Swarm.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"


class PetriDish: public CircularBody, public Updatable, public Drawable
{
protected:
    std::vector<Nutriment*> Nut;    // Vecteur contenant les pointeurs sur nutriments
    std::vector<Bacterium*> Bact;   // Vecteur contenant les pointeurs sur bactéries
    std::vector<Swarm*> mesTroupes; // Vecteur contenant les pointeurs sur les swarm

    double Temp;        // Température
    double puissance;  // Exposant du gradient pour le calcul du score

    std::vector<Bacterium*> vecteur_clones; //Vecteur temporaire de pointeurs vers bactéries clônées

public:

// Constructeurs
    PetriDish(Vec2d position,double rayon);
    PetriDish& operator=(const PetriDish&) = delete; //Désactive l'affectation
    PetriDish(PetriDish const&) = delete; // Désactive la copie


// Méthodes principales
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;


// Méthodes d'ajout d'objets dans l'assiette
    bool addNutriment(Nutriment*);
    bool addBacterium(Bacterium*,bool const&);
    void addSwarm(Swarm*);
    Swarm* getSwarmWithId(std::string id) const; // Retourne le swarm demandé

// Gestion de la température de l'assiette
    double getTemperature() const;
    void increaseTemperature();
    void decreaseTemperature();
    void resetTemp();


// Gestion de l'exposant de gradient
    double getPositionScore(const Vec2d&) const; // Retourne le score de la position
    double getGradientExponent() const;
    void increaseGradientExponent();
    void decreaseGradientExponent();
    void resetGradientExponent();
    Nutriment* getNutrimentColliding(CircularBody const& body) const;


// Méthode pour la mise à jour des graphs
    std::unordered_map<std::string, double> fetchData(const std::string &);


    void reset();

// Destructeur
    ~PetriDish();
};
