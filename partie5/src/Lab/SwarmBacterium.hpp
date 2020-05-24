#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"
#include "Swarm.hpp"



class NutrimentA; //prédéclaration afin d'éviter dépendance circulaire
class NutrimentB;


class SwarmBacterium : public Bacterium, public DiffEqFunction
{
    Swarm* SonSwarm;

public:
    SwarmBacterium(const Vec2d&, Swarm* );

    j::Value& getConfig() const;

    void addSwarmBacterium(SwarmBacterium *, Swarm*) const;

// Méthodes utilitaires
    void drawOn(sf::RenderTarget& target) const override;
    Bacterium* clone() const override;

// Déplacement des bactéries
    void move(sf::Time);
    Vec2d f(Vec2d position, Vec2d speed) const override;

// Consommation selon nutriment
    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    ~SwarmBacterium();
};
