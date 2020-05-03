#pragma once
#include "Interface/Updatable.hpp"
#include "Utility/Vec2d.hpp"
#include "SFML/Graphics.hpp"
#include "Utility/MutableColor.hpp"
#include "Bacterium.hpp"

class SwarmBacterium;


class Swarm: public Updatable
{
    std::string id;
    std::vector<SwarmBacterium*> mesBacts;
    SwarmBacterium* leader;

public:
    Swarm(std::string const&);
    void update(sf::Time dt);
    void findLeader();

    j::Value& getConfig() const;
    void addSwarmBacterium(SwarmBacterium *);
    void popBact(SwarmBacterium*);


    Vec2d getPosLeader() const;
    SwarmBacterium *getLeader() const;
    std::string getId() const;
    MutableColor getColor() const;
};
