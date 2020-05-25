#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"
#include "Swarm.hpp"



class NutrimentA; //prédéclaration afin d'éviter dépendance circulaire
class NutrimentB;


class SwarmBacterium : public Bacterium, public DiffEqFunction
{
    Swarm* SonSwarm; // connait son leader
    j::Value& getConfig() const override;
public:
    SwarmBacterium(const Vec2d&, Swarm* ); // Constructeur




// Méthodes utilitaires
    void drawOn(sf::RenderTarget& target) const override;
    Bacterium* clone() const override;
    void addSwarmBacterium(SwarmBacterium *, Swarm*) const; // Necessaire pour enlever
    // le statut const des ptrs sur SwarmBacterium (erreur constaté sans)

// Déplacement des bactéries
    Vec2d f(Vec2d position, Vec2d speed) const override;
    void move(sf::Time) override;


// Consommation selon nutriment
    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    ~SwarmBacterium();
};
