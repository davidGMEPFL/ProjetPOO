#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"
#include "Swarm.hpp"


class SwarmBacterium : public Bacterium, public DiffEqFunction
{
    bool estLeader;
public:
    SwarmBacterium(const Vec2d&, Swarm* );
    void move(sf::Time);
    Vec2d f(Vec2d position, Vec2d speed) const override;
    void drawOn(sf::RenderTarget& target) const override;
    Bacterium* clone() const override;
    j::Value& getConfig() const;

    void addSwarmBacterium(SwarmBacterium* Bact,Swarm*);
};
