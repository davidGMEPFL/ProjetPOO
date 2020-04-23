#pragma once
#include "Interface/Updatable.hpp"
#include "Utility/Vec2d.hpp"
#include "SFML/Graphics.hpp"

class SwarmBacterium;

class Swarm: public Updatable
{
    std::string id;
    std::vector<SwarmBacterium*> mesBacts;
    SwarmBacterium* leader;

public:
    Swarm(std::string const&);
    void update(sf::Time dt);
    j::Value& getConfig() const;
    void addSwarmBacterium(SwarmBacterium*);

//    void PopBact(SwarmBacterium*);

    Vec2d getPosLeader();

    sf::Color getColor();


};

