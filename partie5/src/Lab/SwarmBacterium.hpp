#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"
#include "Swarm.hpp"



class NutrimentA;
class NutrimentB;


class SwarmBacterium : public Bacterium, public DiffEqFunction
{
    Swarm* SonSwarm;
public:
    SwarmBacterium(const Vec2d&, Swarm* );
    void addSwarmBacterium(SwarmBacterium *, Swarm*) const;

    void move(sf::Time);
    Vec2d f(Vec2d position, Vec2d speed) const override;
    void drawOn(sf::RenderTarget& target) const override;
    Bacterium* clone() const override;
    j::Value& getConfig() const;

    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    void addToGraph(const std::string & ,std::unordered_map<std::string, double>&) override;

    ~SwarmBacterium();
};
